#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "fssimplewindow.h"
#include "gamemenu.hpp"
#include "enemy.hpp"
#include "gameAircraft.h"

#define MAX_ENEMY_SIZE 12
#define GL_SILENCE_DEPRECATION

void SummonEnemies(std::vector<Enemy*> &enemies, int difficulty) {
    int num = 0;
    if (difficulty == 1) {
        num = 2;
    } else if (difficulty == 2) {
        num = 4;
    } else if (difficulty == 3) {
        num = 6;
    }
    for (int i = 0; i < num; i++) {
        int width = 20 + rand() % 721;
        int height = rand() % 71;
        int type = 1 + i % 2;
        Enemy *enemy = new Enemy(type, width, height, difficulty);   // delete
        enemies.push_back(enemy);
    }
}

void DeleteEnemies(std::vector<Enemy*> &enemies) {
    int i = 0;
    while (i < enemies.size()) {
        if (enemies[i]->getStatus() == 1) {
            i++;
        } else {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
    }
}

void CleanAllEnemies(std::vector<Enemy*> &enemies) {
    while (enemies.size() > 0) {
        delete enemies[0];
        enemies.erase(enemies.begin());
    }
}

void aircraftMissileInit(Player player, Missile* missile){
    player.InitPlayer();
    for(int i = 0; i < defaultNumMissile; i++){
        missile[i].Initialize();
    }
}

void drawMissileAircraft(Player& player, Missile* missiles, int& missileCount, int& missileFree){
    for (int i = 0; i < missileCount; i ++) {
        if(missiles[i].state != 0){
            missiles[i].Move();
            missiles[i].Draw();
        }else{
            missileFree ++;
        }
    }
    // check if all bullets are disappeared
    // reset the aircraft bullet if laser is fired
    if(missileFree == defaultNumMissile || player.laser == 1){
        std::cout <<"reset misssile counters" << std::endl;
        // reset the missle number
        missileCount = 0;
        missileFree = 0;
    }
    
    
    if(player.laser ==  1){
        player.DrawLaser();
    }
    player.DrawPlayer();
}


int main() {
    srand((unsigned int)time(NULL));
    int terminate = 0;
    FsOpenWindow(16, 16, 800, 600, 1);
    // menu
    GameMenu menu;
    menu.Initialize();
    
    // initialize airctaft and missles
    Player aircraft;
    Missile missile[defaultNumMissile];
    
    int missileCount = 0;
    int missileFree = 0;
    
    // enemy
    time_t start = time(0);
    time_t lastSummonTime  = NULL;
    int boss = 0;
    Enemy *alience = NULL;
    std::vector<Enemy*> enemies;

    while (0 == terminate) {
        menu.Run();
        if (menu.GetMenuState() == 4) {
            // start game
            lastSummonTime = time(0);
            aircraftMissileInit(aircraft,missile);
            
            aircraft.InitPlayer();
            for (auto &m : missile) {
                m.Initialize();
            }
            
            SummonEnemies(enemies, menu.GetDifficulty());
            while (menu.GetMenuState() == 4) {
                FsPollDevice();
                int key = FsInkey();
                int diff = difftime(time(0), start);
               // printf("diff = %d\n", diff);

                switch (key) {
                    case FSKEY_ESC:
                        terminate = 1;
                        menu.Replay();
                        break;
                    case FSKEY_LEFT:
                        aircraft.Move(Left);
                        break;
                    case FSKEY_RIGHT:
                        aircraft.Move(Right);
                        break;
                    case FSKEY_SPACE:
                        if(aircraft.laser == 0 && missileCount < defaultNumMissile){
                            std::cout << "fire " << missileCount << " numMissle avaliable " << defaultNumMissile<< std::endl;
                                missile[missileCount].Launch(aircraft.x, aircraft.y);
                                missileCount ++;
                        }
                        break;
                    case FSKEY_V:
                        std::cout << " laser " << std::endl;
                        if(aircraft.laser == 0){
                            aircraft.laser = 1;
                        }
                        break;
                }
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // Draw enemies
                for (auto enemy : enemies) {
                    enemy->Draw();
                }

                if (diff >= 0 && boss == 0) {
                    alience = new Enemy(0, 400, -50, menu.difficulty);
                    boss = 1;
                }
                if (alience != NULL) alience->Draw();

                // draw missile and aircraft
                drawMissileAircraft(aircraft,missile,missileCount,missileFree);
                
                FsSwapBuffers();
                FsSleep(25);

                // Move enemies
                for (auto enemy : enemies) {
                    enemy->Move();
                }
                if (alience != NULL) alience->Move();

                if (difftime(time(0), lastSummonTime) > 1) {
                    SummonEnemies(enemies, menu.difficulty);
                    lastSummonTime = time(0);
                }
                
                // free enemies with statue = 0
                DeleteEnemies(enemies);
            }
        }
        
        
        
        
        FsSleep(20);
    }
    
    CleanAllEnemies(enemies);
    return 0;
}
