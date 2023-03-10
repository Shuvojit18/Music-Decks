/*
  ==============================================================================

    XYPad.h
    Created: 7 Mar 2023 6:58:26pm
    Author:  ACER

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "DJAudioPlayer.h"
//==============================================================================
/*
*/
class XYPad  : public juce::Component
{
public:
    XYPad();
    ~XYPad() override;

    class Thumb : public Component {
    public:
        Thumb();

        bool isOn = false;

        void paint(juce::Graphics&) override;

        void mouseDown(const MouseEvent& event) override;
        void mouseDrag(const MouseEvent& event) override;

        std::function<void(Point<double>)> moveCallback;
    private:
        ComponentDragger dragger;
        ComponentBoundsConstrainer constrainer;
    
    };

    void paint (juce::Graphics&) override;
    void resized() override;

    enum class Axis {X, Y};

    void registerSlider(Slider* slider, Axis axis);
    //void deregisterSlider(Slider* slider);
   
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;

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
