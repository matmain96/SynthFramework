/*
  ==============================================================================

    OscComponent.h
    Created: 10 Aug 2023 4:07:31pm
    Author:  Matteo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setupSlider(juce::Slider& slider, const std::string& name, juce::Label& label, float min, float max, float initValue);

private:
    juce::Slider fmFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    juce::Label fmFreqLabel;

    juce::Slider fmDepthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;
    juce::Label fmDepthLabel;

    juce::ComboBox oscType;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscillatorAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
