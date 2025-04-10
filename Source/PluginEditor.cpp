


//==============================================================================
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PedalButtonLookAndFeel.h"
//==============================================================================

RokPedalAudioProcessorEditor::RokPedalAudioProcessorEditor(RokPedalAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 600);

    // Gain Slider and Label
    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0, 1.00f, 0.01f);
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.addListener(this);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    // Set the gray color scheme for the Gain slider
    gainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::darkred);  // Knob fill color
    gainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey); // Knob outline color
    gainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::red); // Thumb color

    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);

    // Bass Slider and Label
    addAndMakeVisible(bassSlider);
    bassSlider.setRange(0, 1.00f, 0.01f);
    bassSlider.setSliderStyle(juce::Slider::Rotary);
    bassSlider.addListener(this);
    bassSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    // Set the gray color scheme for the Bass slider
    bassSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::darkred);
    bassSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    bassSlider.setColour(juce::Slider::thumbColourId, juce::Colours::red);

    addAndMakeVisible(bassLabel);
    bassLabel.setText("Bass", juce::dontSendNotification);
    bassLabel.setJustificationType(juce::Justification::centred);

    // Treble Slider and Label
    addAndMakeVisible(trebleSlider);
    trebleSlider.setRange(0, 1.00f, 0.01f);
    trebleSlider.setSliderStyle(juce::Slider::Rotary);
    trebleSlider.addListener(this);
    trebleSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    // Set the gray color scheme for the Treble slider
    trebleSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::darkred);
    trebleSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    trebleSlider.setColour(juce::Slider::thumbColourId, juce::Colours::red);

    addAndMakeVisible(trebleLabel);
    trebleLabel.setText("Treble", juce::dontSendNotification);
    trebleLabel.setJustificationType(juce::Justification::centred);

    // Wet/Dry Slider and Label
    addAndMakeVisible(wetDrySlider);
    wetDrySlider.setRange(0, 1.00f, 0.01f);
    wetDrySlider.setSliderStyle(juce::Slider::Rotary);
    wetDrySlider.addListener(this);
    wetDrySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    // Set the gray color scheme for the Wet/Dry slider
    wetDrySlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::darkred);
    wetDrySlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    wetDrySlider.setColour(juce::Slider::thumbColourId, juce::Colours::red);

    addAndMakeVisible(wetDryLabel);
    wetDryLabel.setText("Wet/Dry", juce::dontSendNotification);
    wetDryLabel.setJustificationType(juce::Justification::centred);

    // Post Gain Slider and Label
    addAndMakeVisible(postGainSlider);
    postGainSlider.setRange(0, 1.00f, 0.01f);
    postGainSlider.setSliderStyle(juce::Slider::Rotary);
    postGainSlider.addListener(this);
    postGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    // Set the gray color scheme for the Post Gain slider
    postGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::darkred);
    postGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    postGainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::red);

    addAndMakeVisible(postGainLabel);
    postGainLabel.setText("Volume", juce::dontSendNotification);
    postGainLabel.setJustificationType(juce::Justification::centred);

    // Logo Image
    image = juce::ImageCache::getFromFile(juce::File("C:/Juce/RokPedal/RokPedal/Resource/image.png"));

    //Power Button
    powerButton.setButtonText("");  // No text on the button
    addAndMakeVisible(powerButton);

    // Colors & Look
    powerButton.setLookAndFeel(&pedalButtonLookAndFeel);
}


RokPedalAudioProcessorEditor::~RokPedalAudioProcessorEditor()
{
}

//==============================================================================

void RokPedalAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    if (image.isValid())
    {
        juce::Image scaledImage = image.rescaled(image.getWidth()/4,image.getHeight()/4);
        int xPosition = (getWidth() - scaledImage.getWidth()) / 2;

        g.drawImageAt(scaledImage, xPosition, 0);
    }
}

void RokPedalAudioProcessorEditor::resized()
{
    int topBadding = 100;
    gainSlider.setBounds(20, 120+ topBadding, 100, 100);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getBottom() - 5, gainSlider.getWidth(), 20);

    bassSlider.setBounds((this->getWidth() / 2) - 50, 120+ topBadding, 100, 100);
    bassLabel.setBounds(bassSlider.getX(), bassSlider.getBottom() - 5, bassSlider.getWidth(), 20);

    trebleSlider.setBounds(this->getWidth()-120, 120+ topBadding, 100, 100);
    trebleLabel.setBounds(trebleSlider.getX(), trebleSlider.getBottom() - 5, trebleSlider.getWidth(), 20);

    wetDrySlider.setBounds((this->getWidth() / 3)-50, 240+ topBadding, 100, 100);
    wetDryLabel.setBounds(wetDrySlider.getX(), wetDrySlider.getBottom() - 5, wetDrySlider.getWidth(), 20);

    postGainSlider.setBounds((this->getWidth() / 3)*2-50, 240+ topBadding, 100, 100);
    postGainLabel.setBounds(postGainSlider.getX(), postGainSlider.getBottom() - 5, postGainSlider.getWidth(), 20);

    powerButton.setBounds((this->getWidth() / 2) - 40, 360 + topBadding, 80, 80);



}

void RokPedalAudioProcessorEditor::sliderValueChanged(juce::Slider * slider)
{
}
