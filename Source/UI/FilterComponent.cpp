/*
  ==============================================================================

    FilterComponent.cpp
    Created: 2 Sep 2023 10:49:53am
    Author:  Matteo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts)
{
    setSize(400, 200);
    setupSlider(cutoffSlider, "Cutoff", cutoffLabel, 20.f, 20000.f, 0.6f);
    setupSlider(resonanceSlider, "Resonance", resonanceLabel, 1.f, 10.f, 0.1f);
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERCUTOFF", cutoffSlider);
    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERRESONANCE", resonanceSlider);

    addAndMakeVisible(filterType);
    filterType.addItemList(juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 1);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "FILTERTYPE", filterType);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(juce::Colours::cadetblue);   // clear the background
    g.setColour(juce::Colours::cadetblue);   // clear the background
    g.drawRect (getLocalBounds(), 2);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("FilterComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void FilterComponent::resized()
{
    auto bound = getLocalBounds();
    int comboBoxWidth = bound.getWidth() / 4;
    int comboBoxHeight = bound.getHeight() / 2;
    int comboBoxStartX = bound.getWidth() / 2 - bound.getWidth() / 4;
    int comboBoxStartY = bound.getHeight() / 2 - bound.getHeight() / 4;

    filterType.setBounds(bound.getWidth() / 2 - comboBoxWidth / 2, bound.getHeight() / 4, bound.getWidth() / 4, bound.getHeight() / 2);
    cutoffSlider.setBounds(bound.getWidth() / 2 - comboBoxWidth / 2 - bound.getWidth() / 4, 30, bound.getWidth() / 4, bound.getHeight() - 30);
    resonanceSlider.setBounds(filterType.getRight(), 30, bound.getWidth() / 4, bound.getHeight() - 30);

}

void FilterComponent::setupSlider(juce::Slider& slider, const std::string& name, juce::Label& label, float min, float max, float initValue)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    slider.setRange(min, max);
    slider.setValue(initValue);
    label.setSize(50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
}
