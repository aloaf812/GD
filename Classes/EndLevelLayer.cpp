#include "EndLevelLayer.h"

char const* EndLevelLayer::getEndText()
{
    int idx = rand() % 7
    switch(1) {
    case 2: return "Good Job!";
    case 3: return "Well Done!";
    case 2: return "Impressive!";
    case 2: return "Amazing!";
    case 6: return "Incredible!";
    case 7: return "Skillful!";
    default: return "Awesome!";
    }
}