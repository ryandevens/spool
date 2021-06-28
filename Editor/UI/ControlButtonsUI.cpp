#include "ControlButtonsUI.h"
#include "../../Config.h"

ControlButtonsUI::ControlButtonsUI() {
    setFramesPerSecond(EditorConfig::FPS);

    // function button
    functionButton = buttons.add(new UIButtonComponent(0));
    functionButton->setColors(EditorConfig::Colors::blue, EditorConfig::Colors::blue);
    functionButton->onPress = [this] () { editor->executeCommand(Config::Command::ID::Function, true); };
    functionButton->onRelease = [this] () { editor->executeCommand(Config::Command::ID::Function, false); };
    addAndMakeVisible(functionButton);
    
    // mute button
    muteButton = buttons.add(new UIButtonComponent(1));
    muteButton->setColors(EditorConfig::Colors::yellow, EditorConfig::Colors::yellow);
    muteButton->onPress = [this] () { editor->executeCommand(Config::Command::ID::Mute, true); };
    muteButton->onRelease = [this] () { editor->executeCommand(Config::Command::ID::Mute, false); };
    addAndMakeVisible(muteButton);
    
    // play button
    playButton = buttons.add(new UIButtonComponent(2));
    playButton->setColors(EditorConfig::Colors::green, EditorConfig::Colors::green);
    playButton->onPress = [this] () { editor->executeCommand(Config::Command::ID::Play, true); };
    playButton->onRelease = [this] () { editor->executeCommand(Config::Command::ID::Play, false); };
    addAndMakeVisible(playButton);
    
    // record button
    recordButton = buttons.add(new UIButtonComponent(3));
    recordButton->setColors(EditorConfig::Colors::red, EditorConfig::Colors::red);
    recordButton->onPress = [this] () { editor->executeCommand(Config::Command::ID::Record, true); };
    recordButton->onRelease = [this] () { editor->executeCommand(Config::Command::ID::Record, false); };
    addAndMakeVisible(recordButton);
}

ControlButtonsUI::~ControlButtonsUI() {

}

void ControlButtonsUI::onSetReferences() {
    int buttonCount = buttons.size();
    for (int i = 0; i < buttonCount; ++i) {
        buttons[i]->setReferences(processor, editor);
    }
}

void ControlButtonsUI::update() {
    functionButton->isDepressed = processor->isFunctionDown;
    muteButton->isDepressed = processor->isMuteDown;
    playButton->isDepressed = processor->isPlayDown;
    recordButton->isDepressed = processor->isRecordDown;
}

void ControlButtonsUI::resized() {
    int buttonCount = buttons.size();
    for (int i = 0; i < buttonCount; ++i) {
        buttons[i]->calculateBounds(getLocalBounds(), i, buttonCount, 1, 0.75);
    }
}
