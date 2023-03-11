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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(tableComponent);
    tableComponent.getHeader().addColumn("Track title", 1, 200);
    tableComponent.getHeader().addColumn("Length", 2, 75);
    tableComponent.getHeader().addColumn("Action", 3, 75);

    tableComponent.setModel(this);
    gui = _gui;
    //trackTitles.push_back("Track 1");
    //trackTitles.push_back("Track 2");
    //trackTitles.push_back("Track 3");
    //trackTitles.push_back("Track 4");

    

}

PlaylistComponent::~PlaylistComponent()
{

}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::darkviolet);
   
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 30.f, 3.f);
   
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
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

void PlaylistComponent::cellClicked(int rowNumber, int columnId, const MouseEvent&) {
    //std::cout << "cell clicked" << rowNumber << columnId <<std::endl;
    DBG("cell clicked");
    DBG(rowNumber);
    DBG(columnId);
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
            TextButton *btn = new TextButton("Load");
            btn->addListener(this);
            existingComponentToUpdate = btn;
            auto id{ rowNumber };
            btn->setComponentID(std::to_string(id));
            //DBG(rowNumber);



        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    //DBG("PlaylistComponent::buttonClicked " << trackTitles[id]);
    //DBG(trackURL[id]);
    //player->loadURL(trackURL[id]);
    gui->switchOn(trackURL[id]);
    

}



bool PlaylistComponent::isInterestedInFileDrag(const StringArray& files) {
    return true;
}
void PlaylistComponent::filesDropped(const StringArray& files, int x, int y) {
    String length;
    
    if (files.size() < 10)
    {
        for (int i = 0; i < files.size(); ++i)
        {
            File file = files[i];
            auto filename = file.getFileNameWithoutExtension();
            ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(file);
            //DBG(file);
            auto minutes = ((reader->lengthInSamples / reader->sampleRate) / 60);
            auto seconds = (minutes - floor(minutes)) * 60;

            String mins{ floor(minutes) };
            String secs{ floor(seconds) };
            length += mins;
            length += ":";
            length += secs;
            
            trackLength.push_back(length);
            trackTitles.push_back(filename);
            trackURL.push_back(URL{file});

            tableComponent.updateContent();
            repaint();
            length.clear();

        }
        /*
        for each (auto var in files)
        {

            trackURL.push_back(var);
        }
        */

    }
};


void PlaylistComponent::writeCsv(std::string filename, std::vector<std::pair<String, std::vector<String>>> dataset) {
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Create an output filestream object
    std::ofstream myFile(filename);

    // Send column names to the stream
    for (int i = 0; i < dataset.size(); ++i)
    {
        myFile << dataset.at(i).first;
        if (i != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for (int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }