/*
  ==============================================================================

    SynthVoice.cpp
    Created: 7 Aug 2023 11:15:38pm
    Author:  Matteo

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice() : juce::SynthesiserVoice(), isPrepared(false)
{

}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);
    gain.prepare(spec);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);

    gain.setGainLinear(0.01f);

    isPrepared = true;

}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
    {
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    osc.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    filter.process(audioBlock);
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}

void SynthVoice::setADSRParameters(const float attack, const float decay , const float sustain, const float release)
{
    adsr.setADSRParameters(attack,decay,sustain,release);
}

void SynthVoice::setOscType(const int type)
{
    osc.setWaveType(static_cast<WaveType>(type));
}

void SynthVoice::setFilterParameters(const int filterType, const float frequency, const float resonance)
{
    filter.updateParameters(filterType, frequency, resonance);
}

OscData& SynthVoice::getOscillator()
{
    return osc;
}

AdsrData& SynthVoice::getAdsr()
{
    return adsr;
}

FilterData& SynthVoice::getFilter()
{
    return filter;
}
