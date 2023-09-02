/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , adsr(audioProcessor.getParameters(), juce::String{ "ATTACK" }, juce::String{ "DECAY" }, juce::String{ "SUSTAIN" }, juce::String{ "RELEASE" })
    , osc(audioProcessor.getParameters())
    , filter(audioProcessor.getParameters())
    , modAdsr(audioProcessor.getParameters(), juce::String{ "MODATTACK" }, juce::String{ "MODDECAY" }, juce::String{ "MODSUSTAIN" }, juce::String{ "MODRELEASE" })

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 800);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(modAdsr);

}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::grey);
}

void SynthFrameworkAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bound = getLocalBounds();
    adsr.setBounds(bound.removeFromTop(250));
    osc.setBounds(bound.removeFromTop(200));
    filter.setBounds(bound.removeFromTop(150));
    modAdsr.setBounds(bound);
}

