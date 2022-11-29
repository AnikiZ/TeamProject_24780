//
//  gamemenu.cpp
//  final-project
//
//  Created by Xinlu Liu on 11/28/22.
//

#include "gamemenu.hpp"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

void GameMenu::Initialize(void)
{
    aircraft = 1;
    difficulty = 1;
    state = 0; // initial state
    //0: start or quit
    //1: choose aircraft
    //2: choose difficulty
    //3: start or quit
    //4: playing
    //5: quit
}

void GameMenu::Run(void)
{
    if(0==state) // welcome state
    {
        Welcome();
        FsPollDevice();
        auto key = FsInkey();
        if(FSKEY_S==key) // start
        {
            state=1; // choose aircraft
        }
        else if(FSKEY_Q==key) //quit
        {
            state=5;
        }
    } else if (state == 1) { // choose aircraft
        ChooseAircraft();
        FsPollDevice();
        auto key = FsInkey();
        switch(key) {
            case FSKEY_1:
                aircraft = 1;
                state = 2;
                break;
            case FSKEY_2:
                aircraft = 2;
                state = 2;
                break;
            case FSKEY_3:
                aircraft = 2;
                state = 2;
                break;
        }
    }
    else if (state == 2) // choose difficulty
    {
        ChooseDifficulty();
        FsPollDevice();
        auto key = FsInkey();
        switch(key) {
            case FSKEY_1:
                difficulty = 1;
                state = 3;
                break;
            case FSKEY_2:
                difficulty = 2;
                state = 3;
                break;
            case FSKEY_3:
                difficulty = 3;
                state = 3;
                break;
        }
    } else if (state == 3) { // start or quit
        DrawStart();
        FsPollDevice();
        auto key = FsInkey();
        if(FSKEY_S==key)
        {
            state=4; // start game
        }
        else if(FSKEY_Q==key)
        {
            state=5; // quit
        }
    }
    // if state == 4 (playing)
    // main function calls Replay(), state back to 0 to restart the game
}

// Draw welcome
void GameMenu::Welcome() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // draw aircrafts
    glColor3f(0,0,0);
    glRasterPos2i(300,80);
    YsGlDrawFontBitmap10x14("Welcome to");
    glColor3ub(0, 153, 0);
    glRasterPos2i(250,180);
    YsGlDrawFontBitmap32x48("Fighter");
    glRasterPos2i(220,250);
    YsGlDrawFontBitmap32x48("Aircrafts");
    glColor3ub(0, 0, 0);
    glRasterPos2i(250,330);
    YsGlDrawFontBitmap10x14("S...Start the game");
    glRasterPos2i(250,350);
    YsGlDrawFontBitmap10x14("Q...Quit the program");

    FsSwapBuffers();
    FsSleep(20);
}

// user choose aircraft type
void GameMenu::ChooseAircraft(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // TODO: draw aircrafts
    glColor3f(0,0,0);
    glRasterPos2i(250,100);
    YsGlDrawFontBitmap10x14("Please Choose your aircraft");
    glRasterPos2i(250,120);
    YsGlDrawFontBitmap10x14("Press 1 or 2 or 3");

    FsSwapBuffers();
    FsSleep(20);
}

// user choose difficulty
void GameMenu::ChooseDifficulty(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // draw aircrafts
    glColor3f(0,0,0);
    glRasterPos2i(250,100);
    YsGlDrawFontBitmap10x14("Please Choose level of difficulty");
    glRasterPos2i(250,120);
    YsGlDrawFontBitmap10x14("Press 1 or 2 or 3");

    FsSwapBuffers();
    FsSleep(20);
}

// user choose start or quit
void GameMenu::DrawStart(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glColor3f(0,0,0);
    glRasterPos2i(250,100);
    YsGlDrawFontBitmap10x14("S...Start the game");
    glRasterPos2i(250,120);
    YsGlDrawFontBitmap10x14("Q...Quit the program");

    FsSwapBuffers();
    FsSleep(20);
}

int GameMenu::GetMenuState() {
    return state;
}

int GameMenu::GetAircraft() {
    return aircraft;
}

int GameMenu::GetDifficulty() {
    return difficulty;
}

void GameMenu::Replay() {
    state = 0;
}
