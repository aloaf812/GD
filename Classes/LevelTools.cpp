#include "LevelTools.h"
USING_NS_CC;

std::string LevelTools::getAudioTitle(int p0)
{
    switch (p0) {
        case 0: return "Stereo Madness";
        case 1: return "Back On Track";
        case 2: return "Polargeist";
        case 3: return "Dry Out";
        case 4: return "Base After Base";
        case 5: return "Cant Let Go";
        case 6: return "Jumper";
        case 7: return "Time Machine";
        case 8: return "Cycles";
        case 9: return "xStep";
        case 10: return "Clutterfunk";
        case 11: return "Theory of Everything";
        case 12: return "Electroman Adventures";
        case 13: return "Clubstep";
        case 14: return "Electrodynamix";
        case 15: return "Active";
        case -1: return "Practice: Stay Inside Me";
        default: return "Unknown";
    }
}

std::string LevelTools::getAudioFileName(int p0)
{
    switch (p0) {
        case 0: return "StereoMadness.mp3";
        case 1: return "BackOnTrack.mp3";
        case 2: return "Polargeist";
        case 3: return "DryOut.mp3";
        case 4: return "BaseAfterBase.mp3";
        case 5: return "CantLetGo.mp3";
        case 6: return "Jumper.mp3";
        case 7: return "TimeMachine.mp3";
        case 8: return "Cycles.mp3";
        case 9: return "xStep.mp3";
        case 10: return "Clutterfunk.mp3";
        case 11: return "TheoryOfEverything.mp3";
        case 12: return "ElectromanAdventures.mp3";
        case 13: return "Clubstep.mp3";
        case 14: return "Electrodynamix.mp3";
        case 15: return "Active.mp3";
    }
}

GJGameLevel* LevelTools::getLevel(int level)
{
    GJGameLevel* m_level = GJGameLevel::create();
    switch (level) {
        // Stereo Madness
        case 1:
            m_level->setLevelName(getAudioTitle(0));
            m_level->setAudioTrack(0);
            m_level->setDifficulty(1);
            m_level->setStars(1);
        // Back on Track
        case 2:
            m_level->setLevelName(getAudioTitle(1));
            m_level->setAudioTrack(1);
            m_level->setDifficulty(2);
            m_level->setStars(2);
        // Polargeist
        case 3:
            m_level->setLevelName(getAudioTitle(2));
            m_level->setAudioTrack(2);
            m_level->setDifficulty(3);
            m_level->setStars(3);
        // Dry Out
        case 4:
            m_level->setLevelName(getAudioTitle(3));
            m_level->setAudioTrack(3);
            m_level->setDifficulty(4);
            m_level->setStars(4);
        // Base After Base
        case 5:
            m_level->setLevelName(getAudioTitle(4));
            m_level->setAudioTrack(4);
            m_level->setDifficulty(4);
            m_level->setStars(5);
        // Cant Let Go
        case 6:
            m_level->setLevelName(getAudioTitle(5));
            m_level->setAudioTrack(5);
            m_level->setDifficulty(5);
            m_level->setStars(6);
        // Jumper
        case 7:
            m_level->setLevelName(getAudioTitle(6));
            m_level->setAudioTrack(6);
            m_level->setDifficulty(5);
            m_level->setStars(7);
    }
}
