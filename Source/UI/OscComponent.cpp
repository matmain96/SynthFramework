/*
  ==============================================================================

    OscComponent.cpp
    Created: 10 Aug 2023 4:07:31pm
    Author:  Matteo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts)
{
    setSize(400,150);
    addAndMakeVisible(oscType);
    oscType.addItemList(juce::StringArray{ "Sine", "Saw", "Square" }, 1);
    oscillatorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSC", oscType);
    setupSlider(fmFreqSlider, "FM Freq", fmFreqLabel, 0.1f, 1000.f, 0.1f);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FMFREQ", fmFreqSlider);
    setupSlider(fmDepthSlider, "FM Depth", fmDepthLabel, 0.1f, 1000.f, 0.1f);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FMDEPTH", fmDepthSlider);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("OscComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void OscComponent::resized()
{
    auto bound = getLocalBounds();
    int comboBoxWidth = bound.getWidth() / 4;
    int comboBoxHeight = bound.getHeight() / 2;
    int comboBoxStartX = bound.getWidth() / 2 - bound.getWidth() / 4;
    int comboBoxStartY = bound.getHeight() / 2 - bound.getHeight() / 4;

    oscType.setBounds(bound.getWidth()/2 - comboBoxWidth/2, bound.getHeight() / 4, bound.getWidth() / 4, bound.getHeight()/2);
    fmFreqSlider.setBounds(bound.getWidth() / 2 - comboBoxWidth / 2 - bound.getWidth() / 4, 30 , bound.getWidth() / 4, bound.getHeight()-30);
    fmDepthSlider.setBounds(oscType.getRight(),30 , bound.getWidth() / 4, bound.getHeight()-30 );
}

void OscComponent::setupSlider(juce::Slider& slider, const std::string& name, juce::Label& label, float min, float max, float initValue)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    slider.setRange(min, max);
    slider.setSkewFactorFromMidPoint(100.);
    slider.setValue(initValue);
    label.setSize(50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
}