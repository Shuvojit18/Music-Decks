/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener
                           
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay();
    //juce function to setup compponents
    void paint (Graphics&) override;
    void resized() override;
    //a lister for changes
    void changeListenerCallback (ChangeBroadcaster *source) override;

    //loads up url
    void loadURL(URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

    //mouse event listers
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent & event) override;
     
    //a bool to check if its on 
    bool isOn = false;


private:
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;


    ComponentDragger dragger;
    ComponentBoundsConstrainer constrainer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
