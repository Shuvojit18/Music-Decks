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
/*
*/
class PlaylistComponent  : public juce::Component, public TableListBoxModel, public Button::Listener, public FileDragAndDropTarget

{
public:
    PlaylistComponent(AudioFormatManager& _formatManager, DeckGUI* _gui );
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;

    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    void cellClicked(int rowNumber, int columnId, const MouseEvent&);

    Component* refreshComponentForCell( int rowNumber,
                                        int columnId,
                                        bool isRowSelected,
                                        Component* existingComponentToUpdate) override;

    void buttonClicked(Button* button) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    //void writeCsv(std::string filename, std::vector<std::pair<String, std::vector<String>>> dataset);
    void writeCSV(std::string filename, std::vector<std::string> dataset);

    void readCSV();

    void loadPlaylist(File file);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent);

    AudioFormatManager& formatManager;
    TableListBox tableComponent;

    std::vector<std::string> trackTitles;
    std::vector<std::string> trackLength;
    std::vector<std::string> trackURLString;
    std::vector<URL> trackURL;

    //DJAudioPlayer* player;
    DeckGUI* gui;
    //URL url;
    bool doOnce = true;
    //std::ofstream save;
    //std::ifstream load;
    //TextButton* playbtn;
    //AudioFormatReader read;
};
