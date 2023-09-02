/*
  ==============================================================================

    FilterComponent.h
    Created: 2 Sep 2023 10:49:53am
    Author:  Matteo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setupSlider(juce::Slider& slider, const std::string& name, juce::Label& label, float min, float max, float initValue);

    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;

    juce::Label cutoffLabel;
    juce::Label resonanceLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;

    juce::ComboBox filterType;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
