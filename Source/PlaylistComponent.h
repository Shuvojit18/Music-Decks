/*
  ==============================================================================

    PlaylistComponent.h
    Created: 4 Mar 2023 9:16:10pm
    Author:  Shuvojit

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeckGUI.h"
#include "DJAudioPlayer.h"
#include <fstream>
//==============================================================================

class PlaylistComponent  : public juce::Component, public TableListBoxModel, public Button::Listener, public FileDragAndDropTarget

{
public:
    PlaylistComponent(AudioFormatManager& _formatManager, DeckGUI* _gui );
    ~PlaylistComponent() override;
    //usual juce function to set size and draw 
    void paint (juce::Graphics&) override;
    void resized() override;
    //getting num of rows
    int getNumRows() override;

    //painting the row background
    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    //painting indivitual cell
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;


    //checks if a cell is clicked
    //void cellClicked(int rowNumber, int columnId, const MouseEvent&);

    // pointer
    Component* refreshComponentForCell( int rowNumber,
                                        int columnId,
                                        bool isRowSelected,
                                        Component* existingComponentToUpdate) override;

    //function for button clicks
    void buttonClicked(Button* button) override;

    //controls the drag n drop feature
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    // saves the library to a file
    void write(std::string filename, std::vector<std::string> dataset);

    //reads from file
    void read();

    //loads up the music library
    void loadPlaylist(File file);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent);
    //ref from main component
    AudioFormatManager& formatManager;
    TableListBox tableComponent;

    //vectors for storing file datas
    std::vector<std::string> trackTitles;
    std::vector<std::string> trackLength;
    std::vector<std::string> trackURLString;
    std::vector<URL> trackURL;

    // a ref of deckgui
    DeckGUI* gui;
    //a do once bool, to control flow
    bool doOnce = true;
  
};
