/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SynthFrameworkAudioProcessor::SynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    , apvts(*this, nullptr, "Parameters", createApvtsLayout())
{
    mySynth.clearVoices();

    for (int i=0; i<5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }

    mySynth.clearSounds();

    for (int i = 0; i < 5; i++)
    {
        mySynth.addSound(new SynthSound());
    }

}

SynthFrameworkAudioProcessor::~SynthFrameworkAudioProcessor()
{
}

//==============================================================================
const juce::String SynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthFrameworkAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    //juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    for (int i = 0; i < mySynth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate,samplesPerBlock,getNumOutputChannels());
        }
    }
}

void SynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthFrameworkAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int voiceNum = 0; voiceNum < mySynth.getNumVoices(); ++voiceNum)
    {
        if (auto aVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(voiceNum)))
        {
            float attack = apvts.getRawParameterValue("ATTACK")->load();
            float release = apvts.getRawParameterValue("RELEASE")->load();
            float sustain = apvts.getRawParameterValue("SUSTAIN")->load();
            float decay = apvts.getRawParameterValue("DECAY")->load();

            float fmFreq = apvts.getRawParameterValue("FMFREQ")->load();
            float fmDepth = apvts.getRawParameterValue("FMDEPTH")->load();
            auto filterType = apvts.getRawParameterValue("FILTERTYPE")->load();
            auto filterFrequency = apvts.getRawParameterValue("FILTERCUTOFF")->load();
            auto filterResonance = apvts.getRawParameterValue("FILTERRESONANCE")->load();

            aVoice->getOscillator().updateFm(fmDepth, fmFreq);

            aVoice->setOscType(apvts.getRawParameterValue("OSC")->load());
            aVoice->setADSRParameters(attack, decay, sustain, release);
            aVoice->setFilterParameters(filterType, filterFrequency, filterResonance);
        }
    }

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool SynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthFrameworkAudioProcessor::createEditor()
{
    return new SynthFrameworkAudioProcessorEditor (*this);
}

//==============================================================================
void SynthFrameworkAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


juce::AudioProcessorValueTreeState::ParameterLayout SynthFrameworkAudioProcessor::createApvtsLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> layout;

    //Wave type
    layout.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Osc",juce::StringArray { "Sine", "Saw", "Square"},0));

    //ADSR
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.5f));
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.1f, 3.0f, 0.1f));
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.1f, 3.0f, 0.1f));
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 0.1f, 3.0f, 0.1f));
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.1f, 1.0f, 0.5f));

    //FM FREQ
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("FMDEPTH", "FM Depth", 0.1f, 1000.0f, 500.f));
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ", "FM Frequency", 0.1f, 1000.0f, 5.f));

    //FILTER TYPE
    layout.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter", juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.f, 20000.f, 0.6f }, 200.f));
    layout.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRESONANCE", "Filter Resonance", juce::NormalisableRange<float> { 1.f, 10.f, 0.1f }, 1.f));


    return { layout.begin(), layout.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFrameworkAudioProcessor();
}

