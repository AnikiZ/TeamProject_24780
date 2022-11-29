

#ifndef GAMEAIRCTAFT_H
#define GAMEAIRCTAFT_H


#define GL_SILENCE_DEPRECATION


#define PI cos(-1)
#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include <cmath>
#include <cstdlib>
const int defaultNumTarget = 10;
const int defaultNumMissile = 5;
const int window_height = 600;
const int window_width = 800;

enum direction {
    Left,
    Right
};


class ControlBall
{
public:
    int state,x,y,radius;
    void Initialize(void);
    void Launch(int x0,int y0);
    void Disappear(void);
    void Move(void);
    void Draw(void);
};

class Missile
{
public:
    int state,x,y;
    void Initialize(void);
    void Launch(int x0,int y0);
    void Disappear(void);
    void Move(void);
    void tMove(void);
    void Draw(void);
    void EnemyDraw(void);
};

class Player
{
public:
    double x, y, radius, live;
    int laser, laserCount;
    int controlled;
    void InitPlayer();
    void DrawPlayer();
    void Move(int dir);
    void DrawLaser();
};

class Target
{
public:
    int state,x,y,w,h,v,r,g,b,tx;
    int count=0;
    int explosionX, explosionY, explosionR;
    Missile m;
    void Initialize(void);
    void Move(void);
    void Disappear(void);
    void Draw(void);
    void ControlledDraw(double x, double y);
    bool CheckCollisionTarget(int mx,int my,int tx,int ty,int tw,int th);
    void DrawExplosion();
    bool CheckCollisionControlled(int mx,int my,double tx,double ty,int tw,int th);
    bool CheckCollisionPlayer(int mx,int my,double playerX,double playerY,double radius);
    bool CheckCollisonLaser(int playerX, int tx, int tw);
};

void DrawCircle(double x, double y, double radius);
void DrawPlayer(double x,double y,double radius);
void playMusic(char name[]);
void displayText(char text1[], char text2[], char text3[]);
void DrawMissiles(int n,Missile missiles[]);
void DrawTargets(int n, Target targets[], double playerX, double playerY);

class Project {
public:
    Player aircraft;
    ControlBall ball;
    Missile* missles;
    Target* targets;
    YsSoundPlayer music;
    int width;
    int height;
    int numTarget;
    int numMissile;
    void windowInit(void);
    // override class constructor
    Project(int w, int h, int m, int t);
    // default class constructor
    Project(void);
    void moveAircraft(int dir);
    void moveBall();
    void missilesInit();
    void targetsInit();
    
    Target* getTargets(void);
    Missile* getMissle(void);
    Player getAircraft(void);
    ControlBall getBall(void);
    
    int getNumTarget(void);
    int getNumMissle(void);
    
    void TargetMissleInit(int t, int m);
    void musicInit(void);
    
    
};
#endif

