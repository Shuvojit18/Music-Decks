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

    //stopButton.setColour(TextButton::ColourIds::textColourOffId, Colours::grey);
    volPad.registerSlider(&volSlider, XYPad::Axis::Y);
    speedPad.registerSlider(&speedSlider, XYPad::Axis::Y);
    posPad.registerSlider(&posSlider, XYPad::Axis::X);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    //g.fillAll(Colours::darkviolet);
    if (isOn) {
        g.setColour(Colours::blueviolet);
        repaint();
    }
    else g.setColour(Colours::dimgrey);
    

    
   // g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 30.f, 3.f);

    //g.setColour (Colours::azure);
    g.setFont (14.0f);
    //g.drawText ("DeckGUI", getLocalBounds(),
    //            Justification::centred, true);   // draw some placeholder text
    loadButton.setColour(TextButton::ColourIds::buttonColourId, Colours::blueviolet);

    playButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::blueviolet);
    playButton.setColour(TextButton::ColourIds::textColourOffId, Colours::grey);
    
    stopButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::blueviolet);
    stopButton.setColour(TextButton::ColourIds::textColourOffId, Colours::grey);

    loopButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::blueviolet);
    loopButton.setColour(TextButton::ColourIds::textColourOffId, Colours::grey);
}

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
                //auto chooser = chooser.getResult();
            //player->loadURL(URL{chooser.getResult()});
            // and now the waveformDisplay as well
            //waveformDisplay.loadURL(URL{chooser.getResult()}); 
           
            switchOn(URL{ chooser.getResult() });
        });
    }
    // if (button == &loadButton)
    // {
    //     FileChooser chooser{"Select a file..."};
    //     if (chooser.browseForFileToOpen())
    //     {
    //         player->loadURL(URL{chooser.getResult()});
    //         waveformDisplay.loadURL(URL{chooser.getResult()});
            
    //     }


    // }
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

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  //std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    //player->loadURL(URL{File{files[0]}});
    //waveformDisplay.loadURL(URL{ File{files[0]} });
    switchOn(URL{ File{files[0]} });
  }
}

void DeckGUI::timerCallback()
{
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}


void DeckGUI::mouseDown(const MouseEvent& event) {
    dragger.startDraggingComponent(this, event);
}

void DeckGUI::mouseDrag(const MouseEvent& event) {
    dragger.dragComponent(this, event, &constrainer);
}

