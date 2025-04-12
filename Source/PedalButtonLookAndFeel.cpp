// PedalButtonLookAndFeel.cpp
#include "PedalButtonLookAndFeel.h"
void PedalButtonLookAndFeel::drawToggleButton(juce::Graphics& g,
    juce::ToggleButton& button,
    bool isMouseOverButton,
    bool isButtonDown)
{
    juce::Rectangle<int> bounds = button.getLocalBounds();
    int diameter = juce::jmin(bounds.getWidth(), bounds.getHeight());
    juce::Point<int> center = bounds.getCentre();
    int outerRadius = diameter / 2;
    int innerRadius = outerRadius - 8;

    juce::Colour outerColor = juce::Colours::darkgrey;
    juce::Colour innerColor = button.getToggleState() ? juce::Colours::red : juce::Colours::lightgrey;

    g.setColour(outerColor);
    g.fillEllipse(center.x - outerRadius, center.y - outerRadius, outerRadius * 2, outerRadius * 2);

    g.setColour(innerColor);
    g.fillEllipse(center.x - innerRadius, center.y - innerRadius, innerRadius * 2, innerRadius * 2);

    if (isMouseOverButton)
    {
        g.setColour(juce::Colours::white.withAlpha(0.5f));
        g.drawEllipse(center.x - outerRadius, center.y - outerRadius, outerRadius * 2, outerRadius * 2, 2.0f);
    }
}

//
//hei