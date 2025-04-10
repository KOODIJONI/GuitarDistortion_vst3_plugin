#pragma once

#include <JuceHeader.h>

class PedalButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawToggleButton(juce::Graphics&, juce::ToggleButton&, bool, bool) override;  
   
};
