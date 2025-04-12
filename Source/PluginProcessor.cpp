/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================

*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cstdint>


//==============================================================================

RokPedalAudioProcessor::RokPedalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
}

RokPedalAudioProcessor::~RokPedalAudioProcessor()
{
}

//==============================================================================

const juce::String RokPedalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RokPedalAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool RokPedalAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool RokPedalAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double RokPedalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RokPedalAudioProcessor::getNumPrograms()
{
    return 1;
}

int RokPedalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RokPedalAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String RokPedalAudioProcessor::getProgramName(int index)
{
    return {};
}

void RokPedalAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================

void RokPedalAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
   
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<uint32_t>(samplesPerBlock);
    spec.numChannels = static_cast<uint32_t>(getTotalNumInputChannels());

    lowShelfFilters.resize(getTotalNumInputChannels());
    highShelfFilters.resize(getTotalNumInputChannels());

    for (auto& filter : lowShelfFilters)
    {
        filter.reset();
        filter.prepare(spec);
        filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 250.0f, 0.707f, 1.0f); // Neutral gain
    }

    for (auto& filter : highShelfFilters)
    {
        filter.reset();
        filter.prepare(spec);
        filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 4000.0f, 0.707f, 1.0f); // Neutral gain
    }
   
    postCompressor.prepare(spec);
    postCompressor.setThreshold(-20.0f);  
    postCompressor.setRatio(2.5f);        
    postCompressor.setAttack(15.0f);      
    postCompressor.setRelease(600.0f);
}

void RokPedalAudioProcessor::releaseResources()
{
  
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RokPedalAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
  
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif
void RokPedalAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    if (powerButtonState)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            juce::dsp::AudioBlock<float> singleChannelBlock(&channelData, 1, buffer.getNumSamples());
            juce::dsp::ProcessContextReplacing<float> context(singleChannelBlock);

            lowShelfFilters[channel].process(context);
            highShelfFilters[channel].process(context);


        }
        
    }
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        if (powerButtonState)
        {
            int numSamples = buffer.getNumSamples();
            for (int sample = 0; sample < numSamples; ++sample)
            {
                float input = channelData[sample] * gain;

                float upsampled1 = input;
                float nextSample = (sample + 1 < numSamples) ? channelData[sample + 1] * gain : input;
                float upsampled2 = 0.5f * (input + nextSample);  

                float processed1 = Distortion(upsampled1, 1);
                float processed2 = Distortion(upsampled2, 1);
                float output = 0.5f * (processed1 + processed2);

                output = (1 - wetDry) * channelData[sample] + wetDry * output;

                channelData[sample] = output * postGain;
            }
        }
    }

    juce::dsp::AudioBlock<float> fullBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> compressorContext(fullBlock);
    postCompressor.process(compressorContext);
    if (buffer.getNumChannels() >= 2)
    {
        float* leftChannel = buffer.getWritePointer(0);
        float* rightChannel = buffer.getWritePointer(1);
        int numSamples = buffer.getNumSamples();
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float monoSignal = (leftChannel[sample] + rightChannel[sample]) * 0.5f;
            leftChannel[sample] = monoSignal;
            rightChannel[sample] = monoSignal;
        }
    }
}

//==============================================================================

bool RokPedalAudioProcessor::hasEditor() const
{
    return true; 
}

juce::AudioProcessorEditor* RokPedalAudioProcessor::createEditor()
{
    return new RokPedalAudioProcessorEditor(*this);
}

//==============================================================================

void RokPedalAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RokPedalAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void RokPedalAudioProcessor::setGain(float value)
{
    gain = value;
}

void RokPedalAudioProcessor::setWetDry(float value)
{
    DBG("wetDry");
    DBG(value);
    wetDry = value;
}
void RokPedalAudioProcessor::setBass(float value)
{
    bass = value;
    updateFilters();
}

void RokPedalAudioProcessor::setTreble(float value)
{
    treble = value;
    updateFilters();
}
void RokPedalAudioProcessor::updateFilters()
{
    auto sampleRate = getSampleRate();

    for (auto& filter : lowShelfFilters)
    {
        auto bassCoeffs = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 250.0f, 0.707f, bass);

        filter.coefficients = bassCoeffs;
    }

    for (auto& filter : highShelfFilters)
    {
        auto trebleCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 4000.0f, 0.707f, treble);
        filter.coefficients = trebleCoeffs;
    }
}

void RokPedalAudioProcessor::setPostGain(float value)
{
    DBG("GAIN");
    DBG(value);
    postGain = value;
}

void RokPedalAudioProcessor::setPowerButtonState(bool state)
{
    if (state)
        powerButtonState = true;
    else
        powerButtonState = false;
    powerButtonState = state;
}

float RokPedalAudioProcessor::Distortion(float x, float a)
{
    if (x == 0.0f) return 0.0f;

    float absX = std::abs(x);
    float sign = x / absX;
    float nonlinear = sign * (1.0f - std::exp(-x * x / absX));
    return (1.0f - a) * x + a * nonlinear;
}

//==============================================================================

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RokPedalAudioProcessor();
}
