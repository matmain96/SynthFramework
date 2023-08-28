/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 9 Aug 2023 5:42:07pm
    Author:  Matteo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(400, 200);
    setupSlider(attackSlider, "Attack", attackLabel, 0.1f, 3.f, 0.1f);
    setupSlider(decaySlider, "Decay", decayLabel, 0.1f, 3.f, 0.1f);
    setupSlider(sustainSlider, "Sustain", sustainlabel, 0.1f, 1.f, 0.1f);
    setupSlider(releaseSlider, "Release", releaseLabel, 0.1f, 3.f, 0.1f);

    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AdsrComponent::resized()
{
    float padding = 10;
    auto bound = getLocalBounds().reduced(10);

    int32_t widthPerSlider = bound.getWidth() / 4;
    int32_t heightPerSlider = bound.getHeight() - 20;
    int sliderStartX = padding;
    int sliderStartY = padding*3;
    attackSlider.setBounds(sliderStartX, sliderStartY, widthPerSlider, heightPerSlider);
    decaySlider.setBounds(attackSlider.getRight(), sliderStartY, widthPerSlider, heightPerSlider);
    sustainSlider.setBounds(decaySlider.getRight() , sliderStartY, widthPerSlider, heightPerSlider);
    releaseSlider.setBounds(sustainSlider.getRight() , sliderStartY, widthPerSlider, heightPerSlider);

}

void AdsrComponent::setupSlider(juce::Slider& slider, const std::string& name, juce::Label& label, float min, float max, float initValue)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    slider.setRange(min,max);
    slider.setValue(initValue);
    label.setSize(50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
}