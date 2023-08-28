/*
  ==============================================================================

    OscData.h
    Created: 10 Aug 2023 3:39:59pm
    Author:  Matteo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

enum WaveType
{
    SINE = 0,
    SAW = 1,
    SQUARE = 2,
};

class OscData : public juce::dsp::Oscillator<float>
{   
    public:

        void setWaveType(WaveType type);
        void prepareToPlay(juce::dsp::ProcessSpec& spec);
        void setWaveFrequency(const int midiNoteNumber);
        void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
        void updateFm(const float depth, const float freq);
        void processFmOsc(juce::dsp::AudioBlock<float>& block);

    private:
        juce::dsp::Oscillator<float> fmOsc{ [](float x) { return std::sin(x); } };
        float fmMod{ 0.f };
        float fmDepth{ 0.f };
        int lastMidiNote{ 0 };
};