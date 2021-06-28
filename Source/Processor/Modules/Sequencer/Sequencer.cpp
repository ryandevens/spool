#include "Sequencer.h"

void Sequencer::update() {
    interval = (60.f / bpm * sampleRate);
}

void Sequencer::prepareToPlay(double rate, int samplesPerBlockExpected) {
    sampleRate = rate;
}

void Sequencer::getNextAudioBlock(juce::AudioBuffer<float>& buffer) {
    if (interval == 0) return;
    isRunning = true;
    
    const auto bufferSize = buffer.getNumSamples();

    for (auto sample = 0; sample < bufferSize; sample++) {
        const int sampleRemainder = (totalSamples + sample) % interval;
        if (sampleRemainder == 0) {
            tick = (totalSamples + sample) / interval;
            beat = tick % 4;
            owner->beatCallback(beat, beat == 0);
        }
    }
    
    totalSamples += bufferSize;
}

void Sequencer::stop() {
    totalSamples = 0;
    isRunning = false;
}


void Sequencer::pause() {
    isRunning = false;
}

void Sequencer::setBpm(double bpm) {
    this->bpm = bpm;
}
