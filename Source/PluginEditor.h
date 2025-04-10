/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PedalButtonLookAndFeel.h"
//==============================================================================
/**
*/
class RokPedalAudioProcessorEditor  :   public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener     
                                       
{
public:
    RokPedalAudioProcessorEditor (RokPedalAudioProcessor&);
    ~RokPedalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RokPedalAudioProcessor& audioProcessor;
    juce::Slider gainSlider;
    juce::Label gainLabel;

    juce::Slider bassSlider;
    juce::Label bassLabel;

    juce::Slider trebleSlider;
    juce::Label trebleLabel;

    juce::Slider wetDrySlider;
    juce::Label wetDryLabel;

    juce::Slider postGainSlider;
    juce::Label postGainLabel;

    juce::Image image;

    juce::ToggleButton powerButton;

    PedalButtonLookAndFeel pedalButtonLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RokPedalAudioProcessorEditor)
};
