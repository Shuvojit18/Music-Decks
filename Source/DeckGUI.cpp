/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(loopButton);
       
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(volPad);
    addAndMakeVisible(speedPad);
    addAndMakeVisible(posPad);

    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    loopButton.addListener(this);

    playButton.setClickingTogglesState(false);
    stopButton.setClickingTogglesState(false);
    loopButton.setClickingTogglesState(false);
    
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);


    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 2.0);
    posSlider.setRange(0.0, 1.0);

    startTimer(500);

    volPad.registerSlider(&volSlider, XYPad::Axis::Y);
    speedPad.registerSlider(&speedSlider, XYPad::Axis::Y);
    posPad.registerSlider(&posSlider, XYPad::Axis::X);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

//this function is called when a deck is switched on
void DeckGUI::switchOn(URL url) {
    isOn = true;

    volPad.isOn = true;
    volPad.repaint();

    speedPad.isOn = true;
    speedPad.repaint();

    posPad.isOn = true;
    posPad.repaint();

    playButton.setClickingTogglesState(true);
    stopButton.setClickingTogglesState(true);
    loopButton.setClickingTogglesState(true);

    waveformDisplay.isOn = true;
    waveformDisplay.repaint();

    player->loadURL(url);
    waveformDisplay.loadURL(url);
}

void DeckGUI::paint (Graphics& g)
{
    
    //drawing decks depending on status 
    if (isOn) {
        g.setColour(Colours::blueviolet);
        repaint();
    }
    else g.setColour(Colours::dimgrey);
    

    
  
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 30.f, 3.f);

   
    g.setFont (14.0f);
    
    loadButton.setColour(TextButton::ColourIds::buttonColourId, Colours::blueviolet);

    playButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::blueviolet);
    playButton.setColour(TextButton::ColourIds::textColourOffId, Colours::grey);
    
    stopButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::blueviolet);
    stopButton.setColour(TextButton::ColourIds::textColourOffId, Colours::grey);

    loopButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::blueviolet);
    loopButton.setColour(TextButton::ColourIds::textColourOffId, Colours::grey);
}

//seting up their sizes 
void DeckGUI::resized()
{
    double rowH = getHeight()/8; 
    double rowW = getWidth();
    auto margin = 25;
    auto buttonW = playButton.getBestWidthForHeight(rowH);
    auto playButtonX = rowW / 2 - buttonW / 2;
    auto playButtonY = rowH + margin * 2;
    
    loadButton.setBounds(rowW / 2 - buttonW / 2, margin, buttonW, rowH);
    
    playButton.setBounds(playButtonX, playButtonY, buttonW , rowH);
    
    stopButton.setBounds(playButtonX + buttonW + margin, rowH + margin*2, buttonW, rowH);

    loopButton.setBounds(playButtonX - buttonW - margin, rowH + margin * 2, buttonW, rowH);

    volPad.setBounds(margin, getHeight() / 2 - 100, 50, 200);

    speedPad.setBounds(rowW - margin - 50, getHeight() / 2 - 100, 50, 200);

    waveformDisplay.setBounds(margin*4, getHeight() / 2 - 50, rowW - margin * 8, rowH *2);

    posPad.setBounds(rowW / 2 - 100, getHeight() / 2 + 100 + margin, 200, 50);

}

//a function that checks which button is clicked 
void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
       if (button == &loadButton)
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;

        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                // passes the chooses file url to switchon function 
            switchOn(URL{ chooser.getResult() });
        });
    }
       // checks if loop button is pressed then sends audio player signal to loop over
       if (button == &loopButton) {
           //player->loopy = true;
           player->loop();
       }
}



void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        //use this when repeating a track
        player->setPositionRelative(slider->getValue());
    }
    
}


//checks if its interested in taking in files
bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  return true; 
}

//extracts file data and passes them to switchon function
void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    switchOn(URL{ File{files[0]} });
  }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}

//mouse event function
void DeckGUI::mouseDown(const MouseEvent& event) {
    dragger.startDraggingComponent(this, event);
}

void DeckGUI::mouseDrag(const MouseEvent& event) {
    dragger.dragComponent(this, event, &constrainer);
}

