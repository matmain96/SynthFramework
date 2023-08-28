/*
  ==============================================================================

    AdsrData.h
    Created: 9 Aug 2023 5:38:26pm
    Author:  Matteo

  ==============================================================================
*/

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
    public:
        AdsrData() : ADSR() {};
        void setADSRParameters(const float attack, const float decay, const float sustain, const float release);

    private:
        juce::ADSR::Parameters adsrParameters;
};