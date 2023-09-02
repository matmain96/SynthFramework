/*
  ==============================================================================

    FilterData.h
    Created: 1 Sep 2023 8:19:47am
    Author:  Matteo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData 
{
    public:
        void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
        void process(juce::dsp::AudioBlock<float>& block);
        void reset();
        void updateParameters(const int filterType, const float frequency, const float resonance);

    private:
        juce::dsp::StateVariableTPTFilter<float> filter;
        bool isPrepared{ false };
};