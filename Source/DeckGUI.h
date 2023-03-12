/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once
//includig all other header files
#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "XYPad.h"

//==============================================================================
//declaring class and inheriting it from others
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    //these two function together controls the drag and drop feature 
    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    //a timer func
    void timerCallback() override; 

    // these 2 function take mouse events 
    void mouseDrag(const MouseEvent& event) override;
    void mouseDown(const MouseEvent& event) override;

    // switches on the deck
    void switchOn(URL url);

private:
    //declaring buttons
    TextButton playButton{ "Play" };
    TextButton stopButton{"Stop"};
    TextButton loadButton{"Load"};
    TextButton loopButton{ "Loop" };
    //declaring sliders
    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;
    // a file chooser to choose audio file
    FileChooser fChooser{"Select a file..."};

    //declaring the waveformdisplay class which displays the waves 
    WaveformDisplay waveformDisplay;

    // audio player pointer
    DJAudioPlayer* player; 

    //setting up slider pads
    XYPad volPad;
    XYPad speedPad;
    XYPad posPad;

    //setting up drag feature
    ComponentDragger dragger;
    ComponentBoundsConstrainer constrainer;
    //checks if the deck is on or off
    bool isOn = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
