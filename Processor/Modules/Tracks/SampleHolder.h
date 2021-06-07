#pragma once
#include <JuceHeader.h>

class Track;

class SampleHolder {
public:
    SampleHolder(Track* owner, int trackIndex, int index) : owner(owner), trackIndex(trackIndex), index(index) {
        
    }
    
    void processBlockBefore(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void processBlockAfter(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void beatCallback(bool isUpBeat);
    void wantsToRecord(int beatCount);
    void clear();
    void restart();
    
    bool hasSample() {
        return _hasSample;
    };
    
    void play(bool state) {
        _isPlaying = state;
    }
    
    bool isPlaying() {
        return _isPlaying;
    }
    
    void stop(bool state) {
        _isStopped = state;
        if (_isStopped) {
            restart();
            play(false);
        } else {
            play(true);
        };
    }
    
    bool isStopped() {
        return _isStopped;
    }
    
    void mute(bool state) {
        _isMuted = state;
    }
    
    bool isMuted() {
        return _isMuted;
    }


private:
    juce::AudioBuffer<float> sampleBuffer;
    Track* owner;
    int trackIndex = -1;
    int index = -1;
    bool _wantsToRecord = false;
    bool _isPlaying = false;
    bool _isStopped = true;
    bool _isRecording = false;
    bool _isMuted = false;
    bool _hasSample = false;

    int beatLength = 0;
    int sampleSize = 0;
    int recordedBeats = 0;
    int samplesPlayed = 0;
    int beatsPlayed = 0;
    
    void record(juce::AudioBuffer<float>& buffer);
    void setRecordState(bool isUpBeat);
    void startRecording();
    void stopRecording();
    
    void setPlayState(bool isUpBeat);
    
    void addToBuffer(juce::AudioBuffer<float>& buffer, int sourceChannel, int outNumSamples, int numSamples);
};
