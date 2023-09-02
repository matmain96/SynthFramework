/*
  ==============================================================================

    SynthVoice.h
    Created: 27 Jul 2023 10:50:09pm
    Author:  Matteo

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"

class SynthVoice : public juce::SynthesiserVoice 
{
    public:
        SynthVoice();
        bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) override;

        void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

        void stopNote(float velocity, bool allowTailOff) override;
        
        void pitchWheelMoved(int newPitchWheelValue) override;
        
        void controllerMoved(int controllerNumber, int newControllerValue) override;

        void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) ;

        void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

        void setADSRParameters(const float attack, const float decay, const float sustain, const float release);

        void updateFilter(const int filterType, const float frequency, const float resonance);
        void updateModADSR(const float attack, const float decay, const float sustain, const float release);

        void setOscType(const int type);

        OscData& getOscillator();
        AdsrData& getAdsr();
        FilterData& getFilter();

    private:
        AdsrData adsr;
        AdsrData modAdsr;
        juce::AudioBuffer<float> synthBuffer;
        FilterData filter;
        OscData osc; 
        juce::dsp::Gain<float> gain;
        bool isPrepared;

};