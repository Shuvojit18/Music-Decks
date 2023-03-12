/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 4 Mar 2023 9:16:10pm
    Author:  Shuvojit

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(AudioFormatManager& _formatManager, DeckGUI* _gui)
    : formatManager(_formatManager)
{
    
    addAndMakeVisible(tableComponent);
    tableComponent.getHeader().addColumn("Track title", 1, 200);
    tableComponent.getHeader().addColumn("Length", 2, 75);
    tableComponent.getHeader().addColumn("Action", 3, 75);

    tableComponent.setModel(this);
    gui = _gui;
    

}

PlaylistComponent::~PlaylistComponent()
{
    //trying to save the library 
    try
    {
        write("C:/Users/ACER/Desktop/new juce/JUCE/OtoDecks/Source/save.txt", trackURLString );
    }
    catch (const std::exception&)
    {

    }
    
}

//paints the background 
void PlaylistComponent::paint (juce::Graphics& g)
{
    
    g.setColour (juce::Colours::darkviolet);
   
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 30.f, 3.f);
   
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);


    try
    {
        //controls the flow of reading library, so it can read only once
        if (doOnce) {
            read();
            doOnce = false;
        };
    }
    catch (const std::exception&)
    {

    }

}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(25, 25, getWidth()-50, getHeight()/5);
    
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();

}

void PlaylistComponent::paintRowBackground(Graphics& g,
                                            int rowNumber,
                                            int width,
                                            int height,
                                            bool rowIsSelected)
{// just highlight selected rows
    if (rowIsSelected)
    {
        g.fillAll(Colours::darkviolet);
    }
    else {
        g.fillAll(Colours::blueviolet);
    }
}
void PlaylistComponent::paintCell(Graphics& g,
                                   int rowNumber,
                                    int columnId,
                                    int width,
                                    int height,
                                    bool rowIsSelected)
{
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    //switch to display columns of data
    switch (columnId)
    {
        case 1:
            g.drawText(trackTitles[rowNumber], // we will change this later
                                     2, 2,
                                width - 4, height,
                                Justification::centredLeft,
                                    true);
            break;
        case 2:
            g.drawText(trackLength[rowNumber],
                2, 2,
                width - 4, height,
                Justification::centredLeft,
                true);
            break;
    }
    

    
}


Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                      int columnId,
                                                      bool isRowSelected,
                                                      Component* existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            //a new button called 'load', we use it load the music ti deck
            TextButton *btn = new TextButton("Load");
            btn->addListener(this);
            existingComponentToUpdate = btn;
            auto id{ rowNumber };
            btn->setComponentID(std::to_string(id));
         
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    //switching on the specific deck to play the file
    gui->switchOn(trackURL[id]);

}


// drag n drop loader
bool PlaylistComponent::isInterestedInFileDrag(const StringArray& files) {
    return true;
}

void PlaylistComponent::filesDropped(const StringArray& files, int x, int y) {
   
    if (files.size() < 10)
    {
        for (int i = 0; i < files.size(); ++i)
        {
            File file = files[i];
            trackURLString.push_back(files[i].toStdString());
            //loading up the playlist
            loadPlaylist(file);

        }
        
    }
};

//saving the library
void PlaylistComponent::write(std::string filename, std::vector<std::string> dataset){
    std::ofstream myFile(filename);
    for (auto &content : dataset)
    {
       myFile << content << std::endl;
    }

    myFile.close();
    
};

//reading the library from file
void PlaylistComponent::read() {
    std::ifstream file("C:/Users/ACER/Desktop/new juce/JUCE/OtoDecks/Source/save.txt");

    
    std::string str;
    
    if (file.good()) {

        while (std::getline(file, str)) {
            File file = str;
            //loading up the library
            loadPlaylist(file);

    };
            
    file.close();
    }
};

//loads the library
void PlaylistComponent::loadPlaylist(File file) {

    auto filename = file.getFileNameWithoutExtension();

    ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(file);
    
    //sets the song length and stores in vector
    String length;
    auto minutes = ((reader->lengthInSamples / reader->sampleRate) / 60);
    auto seconds = (minutes - floor(minutes)) * 60;

    String mins{ floor(minutes) };
    String secs{ floor(seconds) };
    length += mins;
    length += ":";
    length += secs;

    trackLength.push_back(length.toStdString());
    trackTitles.push_back(filename.toStdString());
    trackURL.push_back(URL{ file });

    tableComponent.updateContent();
    repaint();
    length.clear();
}