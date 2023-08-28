/*
  ==============================================================================

    OscData.cpp
    Created: 10 Aug 2023 3:39:59pm
    Author:  Matteo

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(WaveType type)
{
    switch (type)
    {
        case SINE:
            initialise([](float x) { return std::sin(x); });
            break;
        case SAW:
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });

            break;
        case SQUARE:
            initialise([](float x) { return x < 0.0f? -1.f : 1.f; });

            break;
        default:
            jassert(false);
            break;
    }
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + static_cast<double>(fmMod));
    lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    juce::dsp::ProcessContextReplacing<float> audioBlock(block);
    processFmOsc(block);
    process(audioBlock);
}

void OscData::processFmOsc(juce::dsp::AudioBlock<float>& block)
{
    for (int ch = 0; ch < block.getNumChannels(); ++ch)
    {
        for (int s = 0; s < block.getNumSamples(); ++s)
        {
            fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
        }
    }
}

void OscData::updateFm(const float freq, const float depth)
{
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
    setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);
}
