#include "LevelTools.h"
USING_NS_CC;

std::string LevelTools::getAudioTitle(int audio)
{
    switch (audio) {
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

std::string LevelTools::getAudioFileName(int audio)
{
    switch (audio) {
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
            break;
        // Back on Track
        case 2:
            m_level->setLevelName(getAudioTitle(1));
            m_level->setAudioTrack(1);
            m_level->setDifficulty(2);
            m_level->setStars(2);
            break;
        // Polargeist
        case 3:
            m_level->setLevelName(getAudioTitle(2));
            m_level->setAudioTrack(2);
            m_level->setDifficulty(3);
            m_level->setStars(3);
            break;
        // Dry Out
        case 4:
            m_level->setLevelName(getAudioTitle(3));
            m_level->setAudioTrack(3);
            m_level->setDifficulty(4);
            m_level->setStars(4);
            break;
        // Base After Base
        case 5:
            m_level->setLevelName(getAudioTitle(4));
            m_level->setAudioTrack(4);
            m_level->setDifficulty(4);
            m_level->setStars(5);
            break;
        // Cant Let Go
        case 6:
            m_level->setLevelName(getAudioTitle(5));
            m_level->setAudioTrack(5);
            m_level->setDifficulty(5);
            m_level->setStars(6);
            break;
        // Jumper
        case 7:
            m_level->setLevelName(getAudioTitle(6));
            m_level->setAudioTrack(6);
            m_level->setDifficulty(5);
            m_level->setStars(7);
            break;
        // Time Machine
        case 8:
            m_level->setLevelName(getAudioTitle(7));
            m_level->setAudioTrack(7);
            m_level->setDifficulty(5);
            m_level->setStars(8);
            break;
        // Cycles
        case 9:
            m_level->setLevelName(getAudioTitle(8));
            m_level->setAudioTrack(8);
            m_level->setDifficulty(5);
            m_level->setStars(9);
            break;
        // xStep
        case 10:
            m_level->setLevelName(getAudioTitle(9));
            m_level->setAudioTrack(9);
            m_level->setDifficulty(5);
            m_level->setStars(9);
            break;
        // Clutterfunk
        case 11:
            m_level->setLevelName(getAudioTitle(10));
            m_level->setAudioTrack(10);
            m_level->setDifficulty(5);
            m_level->setStars(11);
            break;
        // Theory of Everything
        case 12:
            m_level->setLevelName(getAudioTitle(11));
            m_level->setAudioTrack(11);
            // uhhh what???: goto LAB_001971ce;
        // Electroman Adventures
        case 13:
            m_level->setLevelName(getAudioTitle(12));
            m_level->setAudioTrack(12);
            m_level->setDifficulty(5);
            m_level->setStars(10);
            break;
        // Clubstep
        case 14:
            m_level->setLevelName(getAudioTitle(13));
            m_level->setAudioTrack(13);
            m_level->setDifficulty(5);
            m_level->setStars(7);
            // m_level->setRequiredCoins(20);
            m_level->setDemon(true);
            break;
        // Electrodynamix
        case 15:
            m_level->setLevelName(getAudioTitle(14));
            m_level->setAudioTrack(14);
            m_level->setDifficulty(5);
            m_level->setStars(12);
            break;
        default: return getLevel(1);
    }
    m_level->setLevelID(level);
    m_level->setLevelType(1);
    m_level->setCoins(3);
}

std::string LevelTools::getAudioString(int audio)
{
    // too much work i'll do it later
    return NULL;
}

const char* LevelTools::nameForArtist(int artist)
{
   switch(artist) {
   case 0: return "DJVI";
   case 1: return "Waterflame";
   case 2: return "OcularNebula";
   case 3: return "ForeverBound";
   case 4: return "Step";
   case 5: return "DJ-Nate";
   default: return " ";
   }
}

const char* LevelTools::ytURLForArtist(int artist)
{
    switch (artist) {
    case 0: return "http://www.youtube.com/user/DJVITechno";
    case 1: return "http://www.youtube.com/user/waterflame89";
    default: return NULL;
    case 3: return "http://www.youtube.com/user/ForeverBoundOfficial";
    case 4: return "http://www.youtube.com/user/NGStep";
    case 5: return "http://www.robtopgames.com/djnate";
    }
}

const char* LevelTools::ngURLForArtist(int artist)
{
    switch(artist) {
    case 0: return "http://djvi.newgrounds.com/";
    case 1: return "http://waterflame.newgrounds.com/";
    case 2: return "http://ocularnebula.newgrounds.com/";
    case 3: return "http://foreverbound.newgrounds.com/";
    case 4: return "http://step.newgrounds.com/";
    case 5: return "http://dj-nate.newgrounds.com/";
    default: return NULL;
    }
}

const char* LevelTools::urlForAudio(int audio)
{
    switch (audio) {
    case 0: return "http://www.youtube.com/watch?v=JhKyKEDxo8Q";
    case 1: return "http://www.youtube.com/watch?v=N9vDTYZpqXM";
    case 2: return "http://www.youtube.com/watch?v=4W28wWWxKuQ";
    case 3: return "http://www.youtube.com/watch?v=FnXabH2q2A0";
    case 4: return "http://www.youtube.com/watch?v=TZULkgQPHt0";
    case 5: return "http://www.youtube.com/watch?v=fLnF-QnR1Zw";
    case 6: return "http://www.youtube.com/watch?v=ZXHO4AN_49Q";
    case 7: return "http://www.youtube.com/watch?v=zZ1L9JD6l0g";
    case 8: return "http://www.youtube.com/watch?v=KDdvGZn6Gfs";
    case 9: return "http://www.youtube.com/watch?v=PSvYfVGyQfw";
    case 10: return "http://www.youtube.com/watch?v=D5uJOpItgNg";
    case 11: return "http://www.newgrounds.com/audio/listen/354826";
    case 12: return "https://www.youtube.com/watch?v=Pb6KyewC_Vg";
    case 13: return "http://www.newgrounds.com/audio/listen/396093";
    case 14: return "http://www.newgrounds.com/audio/listen/368392";
    case 15: return "http://www.youtube.com/watch?v=scaU56CWyJ4";
    case -1: return "http://www.youtube.com/watch?v=5Epc1Beme90";
    default: return NULL;
    }
}
