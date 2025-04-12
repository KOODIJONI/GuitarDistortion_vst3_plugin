/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

//==============================================================================
/**
*/
class RokPedalAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    RokPedalAudioProcessor();
    ~RokPedalAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void setGain(float gain);
	void setBass(float bass);
	void setTreble(float treble);
	void setWetDry(float wetDry);
	void setPostGain(float postGain);
	void setPowerButtonState(bool state);
    void updateFilters();
	float Distortion(float x, float a);

    std::vector<juce::dsp::StateVariableTPTFilter<float>> bassFilters;
    std::vector<juce::dsp::StateVariableTPTFilter<float>> trebleFilters;
    float lowPassCutoff;              
    float highPassCutoff;             

    float lowPassAlpha;                // Low-pass filter coefficient
    float highPassAlpha;               // High-pass filter coefficient

    float lowPassPreviousInput;        // Previous input sample for low-pass filter
    float lowPassPreviousOutput;       // Previous output sample for low-pass filter

    float highPassPreviousInput;       // Previous input sample for high-pass filter
    float highPassPreviousOutput;
    void setLowPassCutoff(float value);      // Set the low-pass cutoff frequency
    void setHighPassCutoff(float value);


private:
	float gain = 0.0f;
	float bass = 1.0f;
	float treble = 1.0f;
	float wetDry = 0.0f;
	float postGain = 0.0f;
	bool powerButtonState = false;
    std::vector<juce::dsp::IIR::Filter<float>> lowShelfFilters;
    std::vector<juce::dsp::IIR::Filter<float>> highShelfFilters;
    juce::dsp::Compressor<float> postCompressor;


    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RokPedalAudioProcessor)
};
