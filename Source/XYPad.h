/*
  ==============================================================================

    XYPad.h
    Created: 7 Mar 2023 6:58:26pm
    Author:  ACER

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//==============================================================================
/*
*/
class XYPad  : public juce::Component
{
public:
    XYPad();
    ~XYPad() override;

    //a  child class for the thumbpad we drag
    class Thumb : public Component {
    public:
        Thumb();

        bool isOn = false;

        void paint(juce::Graphics&) override;
        //mouse events handler
        void mouseDown(const MouseEvent& event) override;
        void mouseDrag(const MouseEvent& event) override;
        //callback function from parent
        std::function<void(Point<double>)> moveCallback;
    private:
        //dragger component so we can drag it
        ComponentDragger dragger;
        ComponentBoundsConstrainer constrainer;
    
    };

    void paint (juce::Graphics&) override;
    void resized() override;
    // setting a enum class for axis 
    enum class Axis {X, Y};

    //registering the sliders to the pads
    void registerSlider(Slider* slider, Axis axis);
   
    //mouse event handler
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    //bool to check if it's on
    bool isOn = false;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad);

        std::vector<Slider*> xSliders, ySliders;

        Thumb thumb;
        const int thumbsize = 25;
        //DJAudioPlayer* djplayer;
        ComponentDragger dragger;
        ComponentBoundsConstrainer constrainer;

        
};
