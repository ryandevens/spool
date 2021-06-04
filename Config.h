#pragma once

#include <JuceHeader.h>


// color scheme
// https://coolors.co/82ddf5-ffe95e-78ffa3-ff5452-1d1c22-414148-e9e9ed-ad67ef-eda152

namespace Config
{

// debugs
const bool DebugKeys = false;


const int windowAspectRatio = 1;
const int defaultWindowSize = 900;
const int minimumWindowSize = 700;

const float updateCycle = 1000 / 60; // ms - latter divider represents fps

const int borderRadius = 10;
const int borderWidth = 4;
const int padding = 16;
const int mouseLeftClickKeyCode = 1337; // ms

const double defaultPBM = 128;
const int defaultRecordLength = 4; // bars
const int MaxRecordLength = 32;

// timing relevant stuff
const int doublePressTimeWindow = 200;
const int holdTimeout = 500; // ms
const int debounceTimeout = 200; // ms
const int recordLengthDebounceTime = 1000; // ms


namespace Colors {

const juce::Colour light = juce::Colour { 0xffe9e9ed };
const juce::Colour mid = juce::Colour { 0xff414148 };
const juce::Colour dark = juce::Colour { 0xff1D1C22 };
const juce::Colour blue = juce::Colour { 0xff82DDF5 };
const juce::Colour yellow = juce::Colour { 0xffFFE95E };
const juce::Colour green = juce::Colour { 0xff78FFA3 };
const juce::Colour red = juce::Colour { 0xffFF5452 };

const juce::Colour groupColorOne = juce::Colour { 0xffad67ef };
const juce::Colour groupColorTwo = juce::Colour { 0xffeda152 };

// peakmeter
const juce::Colour peakOne = juce::Colour { 0xffB3FA5C };
const juce::Colour peakTwo = juce::Colour { 0xffFAF75C };
const juce::Colour peakThree = juce::Colour { 0xffFAB35C };
const juce::Colour peakFour = juce::Colour { 0xffFA6C5C };

// automatic variants
const juce::Colour lightBlue = blue.interpolatedWith(light, 0.5);
const juce::Colour midBlue = blue.interpolatedWith(mid, 0.5);
const juce::Colour darkBlue = blue.interpolatedWith(dark, 0.5);
const juce::Colour lightYellow = yellow.interpolatedWith(light, 0.5);
const juce::Colour midYellow = yellow.interpolatedWith(mid, 0.5);
const juce::Colour darkYellow = yellow.interpolatedWith(dark, 0.5);
const juce::Colour lightGreen = green.interpolatedWith(light, 0.5);
const juce::Colour midGreen = green.interpolatedWith(mid, 0.5);
const juce::Colour darkGreen = green.interpolatedWith(dark, 0.5);
const juce::Colour lightRed = red.interpolatedWith(light, 0.5);
const juce::Colour midRed = red.interpolatedWith(mid, 0.5);
const juce::Colour darkRed = red.interpolatedWith(dark, 0.5);




}

namespace Tracks {

const int columns = 4;
const int rows = 4;
const int count = columns * rows;

}

namespace Command {

enum ID
{
    Settings = 1,
    Function,
    Mute,
    Play,
    Record,
    Track1,
    Track2,
    Track3,
    Track4,
    Track5,
    Track6,
    Track7,
    Track8,
    Track9,
    Track10,
    Track11,
    Track12,
    Track13,
    Track14,
    Track15,
    Track16
};


namespace DefaultKeyBind {
    const int Settings = 44;
    const int Function = 72;
    const int Mute = 74;
    const int Play = 75;
    const int Record = 76;
    const int Track1 = 49;
    const int Track2 = 50;
    const int Track3 = 51;
    const int Track4 = 52;
    const int Track5 = 81;
    const int Track6 = 87;
    const int Track7 = 69;
    const int Track8 = 82;
    const int Track9 = 65;
    const int Track10 = 83;
    const int Track11 = 68;
    const int Track12 = 70;
    const int Track13 = 89;
    const int Track13Alt = 90;
    const int Track14 = 88;
    const int Track15 = 67;
    const int Track16 = 86;
}

}

namespace SettingsWindow {

const int SettingsWindowWidth = 600;
const int SettingsWindowMinWidth = 400;
const int SettingsWindowHeight = 800;
const int SettingsWindowMinHeight = 400;

}

}


