/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Play Screen Functions Definitions (Init, Update, Draw, Unload)
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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
// static int framesCounter = 0;
// static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Play Screen Functions Definition
//----------------------------------------------------------------------------------

// // Play Screen Initialization logic
// void initPlayScreen(void)
// {
//     // framesCounter = 0;
//     // finishScreen = 0;
// }

// Play Screen Update logic
void StatePlay::update(void)
{

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        // finishScreen = 1;
        transTo = &stateWin;
    }
}

// Play Screen Draw logic
void StatePlay::draw(void) const
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "PLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
}

// // Play Screen Unload logic
// void unloadPlayScreen(void)
// {
// }

// // Play Screen should finish?
// int FinishPlayScreen(void)
// {
//     return finishScreen;
// }