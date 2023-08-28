/*
  ==============================================================================

    AdsrData.cpp
    Created: 9 Aug 2023 5:38:26pm
    Author:  Matteo

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::setADSRParameters(const float attack, const float decay, const float sustain, const float release)
{

    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;

    setParameters(adsrParameters);
}