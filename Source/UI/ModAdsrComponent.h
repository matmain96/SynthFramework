/*
  ==============================================================================

    ModAdsrComponent.h
    Created: 2 Sep 2023 1:51:13pm
    Author:  Matteo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
/*
*/
class ModAdsrComponent  : public AdsrComponent
{
public:
    ModAdsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String& attack, juce::String& decay, juce::String& sustain, juce::String& release);
    ~ModAdsrComponent() override;

    void paint (juce::Graphics&) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModAdsrComponent)
};
