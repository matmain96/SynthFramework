/*
  ==============================================================================

    SynthSound.h
    Created: 27 Jul 2023 10:50:02pm
    Author:  Matteo

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public juce::SynthesiserSound
{
public:
        SynthSound() : juce::SynthesiserSound() {}
        bool appliesToNote(int midiNoteNumber=0) { return true;}
        bool appliesToChannel(int midichannel=0) { return true;}
        
};