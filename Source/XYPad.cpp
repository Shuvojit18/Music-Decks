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
    // a lambda function sliders 
    thumb.moveCallback = [&](Point<double> position)
    {
        // mapping 
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
    //checks if its on then lights it up
    if (isOn) {
        g.setColour(juce::Colours::blueviolet);
        thumb.isOn = true;
       
    }
    else g.setColour(juce::Colours::dimgrey);
  
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 20.f, 2.f);

}

void XYPad::resized()
{
    thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbsize, thumbsize));
   
}


//regestring sliders with pads
void XYPad::registerSlider(Slider* slider, Axis axis) {
    
    if (axis == Axis::X) xSliders.push_back(slider);
    if (axis == Axis::Y) ySliders.push_back(slider);
};

//mouse events handlers 
void XYPad::mouseDown(const MouseEvent& event) {
    dragger.startDraggingComponent(this, event);
}

void XYPad::mouseDrag(const MouseEvent& event) {
    dragger.dragComponent(this, event, &constrainer);    
}


