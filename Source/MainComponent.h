/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    // setting up initial process
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    //gets next audio blocks to play
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    //release resourcew after done playing 
    void releaseResources() override;

    //==============================================================================
    //draws
    void paint (Graphics& g) override;
    //fixes size
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    // registering basic audio format manager which we will pass down as ref to others 
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 

    //here we declare 2 objects of audio player and deck gui, each for one.
    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1{&player1, formatManager, thumbCache}; 

    DJAudioPlayer player2{formatManager};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache}; 

    MixerAudioSource mixerSource; 
    
    // music library
    PlaylistComponent playlistComponent1{ formatManager,&deckGUI1 };
    //PlaylistComponent playlistComponent2{ formatManager,&deckGUI2 };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
