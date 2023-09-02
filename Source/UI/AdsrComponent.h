/*
  ==============================================================================

    AdsrComponent.h
    Created: 9 Aug 2023 5:42:07pm
    Author:  Matteo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String& attack, juce::String& decay, juce::String& sustain, juce::String& release);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setupSlider(juce::Slider& slider, const std::string& name, juce::Label& label, float min, float max, float initValue);
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainlabel;
    juce::Label releaseLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
