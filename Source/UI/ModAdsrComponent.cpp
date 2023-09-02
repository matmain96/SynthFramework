/*
  ==============================================================================

    ModAdsrComponent.cpp
    Created: 2 Sep 2023 1:51:13pm
    Author:  Matteo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModAdsrComponent.h"

//==============================================================================
ModAdsrComponent::ModAdsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String& attack, juce::String& decay, juce::String& sustain, juce::String& release) 
    : AdsrComponent(apvts, attack, release, sustain, decay)
{
}

ModAdsrComponent::~ModAdsrComponent()
{
}

void ModAdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::cadetblue);
}