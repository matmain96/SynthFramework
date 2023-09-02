/*
  ==============================================================================

    FilterData.cpp
    Created: 1 Sep 2023 8:19:47am
    Author:  Matteo

  ==============================================================================
*/

#include "FilterData.h"
#define LOW_PASS 0
#define BAND_PASS 1
#define HIGH_PASS 2

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    filter.prepare(spec);
    isPrepared = true;
}

void FilterData::process(juce::dsp::AudioBlock<float>& block)
{
    jassert(isPrepared);
    filter.process(juce::dsp::ProcessContextReplacing<float>{block});
}

void FilterData::reset()
{
    filter.reset();
}

void FilterData::updateParameters(const int filterType, const float frequency, const float resonance, const float modulator)
{
    switch(filterType)
    {
        case LOW_PASS:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case BAND_PASS:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case HIGH_PASS:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
        default:
            break;
    }

    float modFreq = frequency * modulator;
    modFreq = std::max(modFreq, 20.f);
    modFreq = std::min(modFreq, 20000.f);


    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);
}
