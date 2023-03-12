/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position(0)
                          
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

  audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    if (isOn) g.setColour (Colours::blueviolet);
    else g.setColour(Colours::dimgrey);

    // draw an outline around the component
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 20.f, 2.f);
    if (isOn) g.setColour(Colours::blueviolet);
    else g.setColour(Colours::dimgrey);
    if(fileLoaded)
    {
      audioThumb.drawChannel(g, 
        getLocalBounds(), 
        0, 
        audioThumb.getTotalLength(), 
        0, 
        1.0f
      );
      g.setColour(Colours::darkviolet);
      g.drawRect(position * getWidth(), 2.5, getWidth() / 30 - 5, getHeight() - 5);
    }
    else 
    {
      g.setFont (20.0f);
      g.drawText ("...", getLocalBounds(),
                  Justification::centred, true);   // draw some placeholder text

    }
}

void WaveformDisplay::resized()
{

}

//load the file
void WaveformDisplay::loadURL(URL audioURL)
{
  audioThumb.clear();
  fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
  if (fileLoaded)
  {
      repaint();
  }
}

//repaint when change received 
void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    
    repaint();

}

//pos
void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position)
  {
    position = pos;
    repaint();
  }

  
}

//checks when mouse down and dragged
void WaveformDisplay::mouseDown(const MouseEvent& event) {
    dragger.startDraggingComponent(this, event);
}

void WaveformDisplay::mouseDrag(const MouseEvent& event) {
    dragger.dragComponent(this, event, &constrainer);
}




