/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//#include "WaveformDisplay.h"

class DJAudioPlayer : public AudioSource {
  public:
//constructor 
    DJAudioPlayer(AudioFormatManager& _formatManager);
    //destructor
    ~DJAudioPlayer();

    //setting up audio player 
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    //gets next audio block required to play 
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    //releases resources after playing 
    void releaseResources() override;

    //loads url thats sent to it
    void loadURL(URL audioURL);
    //sets the vol
    void setGain(double gain);
    //sets the speed of music
    void setSpeed(double ratio);
    //sets pan
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    
    //starts the audio
    void start();
    //stops the audio
    void stop();
    //loops over
    void loop();

    /** get the relative position of the playhead */
    double getPositionRelative();

    //bool loopy = false;


private:
    //getting the passed ref of format manager from main component 
    AudioFormatManager& formatManager;
    //setting a pointer
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource; 
    ResamplingAudioSource resampleSource{&transportSource, false, 2};

};




