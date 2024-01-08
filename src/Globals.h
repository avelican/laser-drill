#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

extern Font font;
extern Music music;
// extern Sound fxCoin;

#include "states/State.h"
#include "states/States.h"

extern StateLogo  stateLogo;
extern StateMenu  stateMenu;
extern StatePause statePause;
extern StatePlay  statePlay;
extern StateWin   stateWin;

#endif // header guard