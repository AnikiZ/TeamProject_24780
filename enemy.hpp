//
//  enemy.hpp
//  24780 final-project
//
//  Created by An-Chen Li/Xuyuan Liang on 11/28/22.
//

#ifndef enemy_hpp
#define enemy_hpp

#include <stdio.h>
class Enemy {
public:
    Enemy(int _type, int _difficulty);
    Enemy(int _type, int _cx, int _cy, int _difficulty);
    void Setup(int _type, int _cx, int _cy, int _difficulty);
    void Draw() const;
    void DrawAlience() const;
    void DrawInvader1() const;
    void DrawInvader2() const;
    void DrawPix(int x, int y) const;
    void DrawShip() const;
    void Move();
    void BeHitted(int x, int y);
    void show() const;
    int getStatus() const;
//    animation();
private:
    int status;
    int isBoss;
    int type;   // 0: alience (boss), 1: invade1, 2: invade2
    int cx, cy;
    int dx, dy; // pixel size
    int hp;
    int difficulty;
};

#endif /* enemy_hpp */
