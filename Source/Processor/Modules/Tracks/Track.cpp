#include "Track.h"

#include "Processor/Modules/Tracks/Tracks.h"
#include "Processor/SpoolProcessor.h"
#include "Processor/Modules/ControlGroup/ControlGroup.h"


Track::Track(Tracks* owner, int index, ParameterValue& volume, ParameterValue& balance) : owner(owner), index(index), volume(volume), balance(balance) {
    for (int smpl = 0; smpl < Config::TrackCount; smpl++) {
        samples.add(new Sample(this, index, smpl));
    }

    effects.reset(new Effects(owner->owner, index));
    setupParameters();
}

void Track::setupParameters() {
    volume.set(0.75f, true);
    balance.set(0.5f, true);
}
 
void Track::prepareToPlay(double sampleRate, int samplesPerBlock) {
    effects->prepareToPlay(sampleRate, samplesPerBlock);
    for (Sample* sample : samples) {
        sample->prepareToPlay(sampleRate, sampleRate);
    }
}

void Track::processBlockBefore(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    for (Sample* sample : samples) sample->processBlockBefore(buffer, midiMessages);
    if (hasSamples()) effects->processBlockBefore(buffer, midiMessages);
}


void Track::processBlockAfter(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    int numSamples = buffer.getNumSamples();
    trackBuffer.setSize(Config::CHCount, numSamples);
    trackBuffer.clear();

    if (!hasSamples()) return;

    for (Sample* sample : samples) sample->processBlockAfter(trackBuffer, midiMessages);
    effects->processBlockAfter(trackBuffer, midiMessages);


    basicProcessing.setBuffer(trackBuffer).setBalance(balance).setVolume(volume).addTo(buffer).process();
    
//    for (int sampleIndex = 0; sampleIndex < trackBuffer.getNumSamples(); sampleIndex++) {
//        float drySampleL = buffRead[Config::CHLeft][sampleIndex];
//        float drySampleR = buffRead[Config::CHRight][sampleIndex];
//        float tmpSampleL = drySampleL;
//        float tmpSampleR = drySampleR;
//
//        tmpSampleL *= balanceL;
//        if (balanceR < 1) {
//            tmpSampleL *= balanceR;
//            tmpSampleL += drySampleR * (1 - balanceR);
//        }
//        tmpSampleL *= volume.percent;
//        
//        tmpSampleR *= balanceR;
//        if (balanceL < 1) {
//            tmpSampleR *= balanceL;
//            tmpSampleR += drySampleL * (1 - balanceL);
//        }
//        tmpSampleR *= volume.percent;
//    
//        buffWrite[Config::CHLeft][sampleIndex] = tmpSampleL;
//        buffWrite[Config::CHRight][sampleIndex] = tmpSampleR;
//    }
//

}

void Track::beatCallback(int beat, bool isUpBeat) {
    for (Sample* sample : samples) {
        sample->beatCallback(beat, isUpBeat);
    }
}

void Track::select(Track::Mode mode) {
    if (owner->owner->isEffectMode()) {
        bool value = getValueBasedOnMode(_isEffectSelected, mode);
        _isEffectSelected = value;
        return;
    }
    
    
    bool value = getValueBasedOnMode(_isSelected, mode);
    _isSelected = value;
    if (value == true) owner->setLastSelectedTrackIndex(index);
    
    setLastSelectedTrackIndex();
};

void Track::mute(Track::Mode mode) {
    bool value = getValueBasedOnMode(_isMuted, mode);
    _isMuted = value;

    if (owner->hasSampleLayer()) {
        samples[owner->getSampleLayer()]->mute(_isMuted);
    } else {
        for (Sample* sample : samples) sample->mute(_isMuted);
    }
};

void Track::cue(Track::Mode mode) {
    bool value = getValueBasedOnMode(_isCueued, mode);
    _isCueued = value;
    
    //TODO: implement cue channel
    if (_isCueued) {
        DBG("on cue");
    } else {
        DBG("not on cue");
    }
};

void Track::play(Track::Mode mode) {
    bool value = getValueBasedOnMode(_isPlaying, mode);
    _isPlaying = value;
    
    if (owner->hasSampleLayer()) {
        samples[owner->getSampleLayer()]->play(_isPlaying);
    } else {
        for (Sample* sample : samples) sample->play(_isPlaying);
    }
};

void Track::stop(Track::Mode mode) {
    bool value = getValueBasedOnMode(_isStopped, mode);
    _isStopped = value;
    
    if (owner->hasSampleLayer()) {
        samples[owner->getSampleLayer()]->stop(_isStopped);
    } else {
        for (Sample* sample : samples) sample->stop(_isStopped);
    }
};

void Track::restart() {
    for (Sample* sample : samples) {
        sample->restart();
    }
}

void Track::record() {
    int recordLength = owner->owner->getRecordLength();
    
    for (Sample* sample : samples) {
        if (!sample->isFilled()) {
            sample->wantsToRecord(recordLength);
            return;
        }
    }
    
    
    //TODO: Flash all buttons red to indicate full buffer
    DBG("all samples are filled");
};

void Track::cancelRecord() {
    for (Sample* sample : samples) {
        sample->cancelRecord();
    }
};

void Track::clear() {
    if (owner->hasSampleLayer()) {
        samples[owner->getSampleLayer()]->clear();
    } else {
        for (Sample* sample : samples) sample->clear();
    }
};

bool Track::isGrouped() {
    return (isInGroup(0) || isInGroup(1));
}

bool Track::isInGroup(int group) {
    ControlGroup controlGroup = nullptr;
    if (group == 0) controlGroup = owner->owner->controlGroupA;
    if (group == 1) controlGroup = owner->owner->controlGroupB;
    return controlGroup.containsTrack(index);
}

int Track::getGroup() {
    ControlGroup groupA = owner->owner->controlGroupA;
    ControlGroup groupB = owner->owner->controlGroupB;
    if (groupA.containsTrack(index)) return 0;
    if (groupB.containsTrack(index)) return 1;

    return -1;
}

int Track::isInEffectGroup(int group) {
    ControlGroup controlGroup = nullptr;
    if (group == 0) controlGroup = owner->owner->controlGroupA;
    if (group == 1) controlGroup = owner->owner->controlGroupB;
    return controlGroup.containsEffect(index);
}

void Track::addTrackToGroupA() {
    owner->owner->controlGroupA.addTrack(index);
}

void Track::removeTrackFromGroupA() {
    owner->owner->controlGroupA.removeTrack(index);
}

void Track::addTrackToGroupB() {
    owner->owner->controlGroupB.addTrack(index);
}

void Track::removeTrackFromGroupB() {
    owner->owner->controlGroupB.removeTrack(index);
}

void Track::removeTrackFromAllGroups() {
    owner->owner->controlGroupA.removeTrack(index);
    owner->owner->controlGroupB.removeTrack(index);
}

void Track::addEffectToGroupA() {
    owner->owner->controlGroupA.addEffect(index);
}

void Track::removeEffectFromGroupA() {
    owner->owner->controlGroupA.removeEffect(index);
}

void Track::addEffectToGroupB() {
    owner->owner->controlGroupB.addEffect(index);
}

void Track::removeEffectFromGroupB() {
    owner->owner->controlGroupB.removeEffect(index);
}


// private
void Track::setLastSelectedTrackIndex() {
   bool hasTracksSelected = false;
   juce::OwnedArray<Track>& tracks = owner->getTracks();
   for (int trk = 0; trk < Config::TrackCount; trk++) {
       if (tracks[trk]->isSelected()) {
           hasTracksSelected = true;
       }
   }

   if (!hasTracksSelected) owner->setLastSelectedTrackIndex(-1);
}


bool Track::getValueBasedOnMode(bool value, Track::Mode mode) {
    switch (mode) {
        case Track::Mode::On:
            value = true;
            break;
        case Track::Mode::Off:
            value = false;
            break;
        case Track::Mode::Toggle:
            value = !value;
            break;
        default:
            break;
    }

    return value;
}
