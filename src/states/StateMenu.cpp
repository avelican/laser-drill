/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Menu Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "Globals.h"
#include "StateMenu.h"
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
// static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Menu Screen Functions Definition
//----------------------------------------------------------------------------------

// Menu Screen Initialization logic
void StateMenu::init(void)
{
    framesCounter = 0;
    // finishScreen = 0;
}

// Menu Screen Update logic
void StateMenu::update(void)
{

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        // //finishScreen = 1;   // PAUSE
        // finishScreen = 2;   // PLAY
        transTo = &statePlay;
    }
}

// Menu Screen Draw logic
void StateMenu::draw(void) const
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "BEGIN SCREEN", pos, font.baseSize*3.0f, 4, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
}

// // Menu Screen Unload logic
// void StateMenu::unload(void)
// {
// }





// // Menu Screen should finish?
// int StateMenu::Finish(void)
// {
//     return finishScreen;
// }