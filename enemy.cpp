//
//  enemy.cpp
//  24780 final-project
//
//  Created by An-Chen Li / Xuyuan Liang on 11/28/22.
//

#include "enemy.hpp"
#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#define PI 3.1415927

void Enemy::show() const {
    printf("status=%d, boss=%d\n", status, isBoss);
    printf("type=%d, cx=%d, cy=%d\n\n", type, cx, cy);
}

Enemy::Enemy(int _type, int _difficulty) {
    Setup(_type, 400, 300, _difficulty);
};

Enemy::Enemy(int _type, int _cx, int _cy, int _difficulty) {
    Setup(_type, _cx, _cy, _difficulty);
}

void Enemy::Setup(int _type, int _cx, int _cy, int _difficulty) {
    status = 1;
    type = _type;
    cx = _cx; cy = _cy;
    difficulty = _difficulty;

    if (type == 1 || type == 2) {
        isBoss = 0;
        hp = 0;
        dx = 3; dy = 3;
    } else {
        isBoss = 1;
        hp = 100;
        dx = 3; dy = 3;
    }
};

void Enemy::Draw() const {
    if (status == 0) return;
    if (type == 0) DrawAlience();
    else if (type == 1) DrawInvader1();
    else if (type == 2) DrawInvader2();
}

void Enemy::DrawAlience() const {
    DrawShip();
    char pattern[] = {
        "................222............." // 0
        "................2.2............." // 1
        "................222......1......" // 2
        ".222...111..............1111...." // 3
        ".2.2....11.............11......." // 4
        ".222.....1........1....1........" // 5
        ".........1...11111.1...1........" // 6
        ".........1.1111111.111.1........" // 7
        "..........11111111..111....222.." // 8
        "..............11111........2.2.." // 9
        "..............1111.........222.." // 10
        "........1..2..11111..2..1......." // 11
        "........1..2..11111..2..1......." // 12
        ".......111....111.1....11......." // 13
        "........111...11.11...111......." // 14
        "........1111..11111..1111......." // 15
        "..222...1111111...1111111......." // 16
        "..2.2...111111.111..11111......." // 17
        "..222....111111111111111...1.1.." // 18
        ".........111111111111111...111.." // 19
        "1.........1111.....1111...1111.." // 20
        "11.........111.....111.....111.." // 21
        "111..........1111111.......111.." // 22
        "1111.................222....11.." // 23
        "11111.........1111...2.2...111.." // 24
        "111111.......11111...222..1111.." // 25
        ".111111.....1111111......1111..." // 26
        "..111111...11111111.....1111...." // 27
        "....1111111111111111..11111....." // 28
        ".......1111111111111.11111......" // 29
        "..........1111111.1111111......." // 30
        ".........111111111.11111........" // 31
    };

    for (int x = 0; x < 32; x++) {
        int _x = cx - (16 - x) * dx;
        for (int y = 0; y < 32; y++) {
            int _y = cy - (16 - y) * dy;
            if (pattern[y * 32 + x] == '1') {
                glColor3ub(0, 255, 0);
//                DrawPix(x + 320 + dx, y + 10 + dy);
            }
            else if (pattern[y * 32 + x] == '.') {
                glColor3ub(0, 0, 0);
//                DrawPix(x + 320 + dx, y + 10 + dy);
            }
            else if (pattern[y * 32 + x] == '2') {
                glColor3ub(255, 255, 255);
//                DrawPix(x + 320 + dx, y + 10 + dy);
            }
            DrawPix(_x, _y);

        }
    }
}

void Enemy::DrawInvader1() const {
    char pattern[] = {
        "............" // 0
        "..1......1.." // 1
        "...1....1..." // 2
        "..11111111.." // 3
        ".1121111211." // 4
        "111111111111" // 5
        "1.11111111.1" // 6
        "1.1......1.1" // 7
        "...11..11..." // 8
        "............" // 9
    };

    for (int x = 0; x < 12; x++) {
        int _x = cx - (6 - x) * dx;
        for (int y = 0; y < 10; y++) {
            int _y = cy - (5 - y) * dy;
            if (pattern[y * 12 + x] == '1') {
                glColor3ub(0, 0, 0);
                DrawPix(_x, _y);
            } else if (pattern[y * 12 + x] == '.') {
                glColor3ub(255, 255, 255);
            } else if (pattern[y * 12 + x] == '2') {
                glColor3ub(255, 0, 0);
                DrawPix(_x, _y);
            }
        }
    }
}

void Enemy::DrawInvader2() const {
    char pattern[] =
    {
        "............" // 0
        "..1......1.." // 1
        "1..1....1..1" // 2
        "1.11111111.1" // 3
        "111211112111" // 4
        "111111111111" // 5
        "..11111111.." // 6
        "...1....1..." // 7
        "..1......1.." // 8
        "............" // 9
    };

    for (int x = 0; x < 12; x++) {
        int _x = cx - (6 - x) * dx;
        for (int y = 0; y < 10; y++) {
            int _y = cy - (5 - y) * dy;
            if (pattern[y * 12 + x] == '1') {
                glColor3ub(0, 0, 0);
                DrawPix(_x, _y);
            }
            else if (pattern[y * 12 + x] == '.') {
//        glColor3ub(255, 255, 255);
            }
            else if (pattern[y * 12 + x] == '2') {
                glColor3ub(255, 0, 0);
                DrawPix(_x, _y);
            }
//      DrawPix(_x, _y);
        }
    }
}

void Enemy::DrawPix(int x, int y) const {
    glBegin(GL_QUADS);

    glVertex2i(x, y);
    glVertex2i(x + dx, y);
    glVertex2i(x + dx, y + dy);
    glVertex2i(x, y + dy);

    glEnd();
}

void Enemy::DrawShip() const {
    glBegin(GL_POLYGON);
    glColor3ub(105, 105, 105);

    for (int i = 0; i < 64; i++) {
        double angle = (double)i * PI / 32.0;
        double x = (double)cx + cos(angle) * 68.0;
        double y = (double)cy + sin(angle) * 68.0;
        glVertex2d(x, y);
    }
    glEnd();
}

void Enemy::Move() {
    if (isBoss) {
        if (cy <= 90) cy += 2;
        return;
    };
    if (difficulty == 1) cy += 3;
    else if (difficulty == 2) cy += 4;
    else if (difficulty == 3) cy += 6;
    
    if (cy >= 600) {
        status = 0;
    }
}
//void Enemy::BeHitted(int x, int y) {
//    if (x <= && x >= &&
//        y <= && y <= ) {
//        if (isBoss) {
//            hp--;
//            if (hp <= 0) statua = 0;
//
//        } else {
//            status = 0;
//        }
//    }
//}

int Enemy::getStatus() const { return status; }
