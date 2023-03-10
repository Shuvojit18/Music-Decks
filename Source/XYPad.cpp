/*
  ==============================================================================

    XYPad.cpp
    Created: 7 Mar 2023 6:58:26pm
    Author:  ACER

  ==============================================================================
*/

#include <JuceHeader.h>
#include "XYPad.h"

//==============================================================================
XYPad::XYPad()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(thumb);
    thumb.moveCallback = [&](Point<double> position)
    {
        //const std::lock_guard<std::mutex> lock(mutex);
        const auto bounds = getLocalBounds().toDouble();
        const auto w = static_cast<double>(thumbsize);
        for (auto* slider : xSliders)
        {
            slider->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w, slider->getMinimum(), slider->getMaximum()));
        }
        for (auto* slider : ySliders)
        {
            slider->setValue(jmap(position.getY(), bounds.getHeight() - w, 0.0, slider->getMinimum(), slider->getMaximum()));
        }
        repaint();

        
    };
}

XYPad::~XYPad()
{
}

XYPad::Thumb::Thumb() {
    constrainer.setMinimumOnscreenAmounts(25,25,25,25);
}

void XYPad::Thumb::paint(juce::Graphics& g) {
    if(isOn) g.setColour(Colours::blueviolet);
    else g.setColour(Colours::dimgrey);
   
    g.fillEllipse(getLocalBounds().toFloat());
}

void XYPad::Thumb::mouseDown(const MouseEvent& event) {
    dragger.startDraggingComponent(this, event);
}

void XYPad::Thumb::mouseDrag(const MouseEvent& event) {
    dragger.dragComponent(this, event, &constrainer);
    if (moveCallback)
        moveCallback(getPosition().toDouble());
}


void XYPad::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    if (isOn) {
        g.setColour(juce::Colours::blueviolet);
        thumb.isOn = true;
       
    }
    else g.setColour(juce::Colours::dimgrey);
    //g.fillRoundedRectangle(getLocalBounds().toFloat(), 10.f);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 20.f, 2.f);

    //g.drawRect(getLocalBounds(), 1);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("XYPad", getLocalBounds(),
   //             juce::Justification::centred, true);   // draw some placeholder text
}

void XYPad::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbsize, thumbsize));
   
}



void XYPad::registerSlider(Slider* slider, Axis axis) {
    
    if (axis == Axis::X) xSliders.push_back(slider);
    if (axis == Axis::Y) ySliders.push_back(slider);
};


void XYPad::mouseDown(const MouseEvent& event) {
    dragger.startDraggingComponent(this, event);
}

void XYPad::mouseDrag(const MouseEvent& event) {
    dragger.dragComponent(this, event, &constrainer);    
}


