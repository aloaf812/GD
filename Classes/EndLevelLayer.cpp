#include "EndLevelLayer.h"

char const* EndLevelLayer::getEndText()
{
    int idx = rand() % 7;
    switch(idx) {
    case 2: return "Good Job!"; break;
    case 3: return "Well Done!"; break;
    case 4: return "Impressive!"; break;
    case 5: return "Amazing!"; break;
    case 6: return "Incredible!"; break;
    case 7: return "Skillful!"; break;
    default: return "Awesome!";
    }
}