//
//  Project.cpp
//  2780Project
//
//  Created by MaxHu on 2022/11/28.
//

#include "gameAircraft.h"

void DrawMissiles(int n,Missile missiles[])
{
    for(int i=0; i<n; ++i)
    {
        auto &m=missiles[i];
        if(1==m.state)
        {
            m.Draw();
        }
    }
}

void DrawTargets(int n, Target targets[], double playerX, double playerY)
{
    for(int i=0; i<n; ++i)
    {
        // use reference!!! Otherwise is shallow copy!!!
        auto &t=targets[i];
        if(1==t.state)
        {
            t.Draw();
        }
        else if(2==t.state)
        {
            t.ControlledDraw(playerX, playerY);
        }
        else if(3==t.state)
        {
            t.DrawExplosion();
        }
    }
}

void DrawCircle(double x, double y, double radius)
{
    int r, g, b;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
    glColor3ub(r, g, b);
    glBegin(GL_POLYGON);
    for (double i = 0; i < 256.0; i++) {
        double a = PI * (double)i / 128.0;
        double dx = cos(a) * radius;
        double dy = sin(a) * radius;
        glVertex2d(x+dx,y+dy);
    }
    glEnd();
}


void DrawPlayer(double x,double y,double radius)
{

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,1,0);
    glVertex2d(x,y-8);
    glVertex2d(x+15,y);
    glColor3f(0,0,1);
    glVertex2d(x+15,y+8);
    glVertex2d(x+10,y+4);
    glColor3f(1,0,0);
    glVertex2d(x+5,y+8);
    glVertex2d(x,y+6);
    glColor3f(1,1,0);
    glVertex2d(x-5,y+8);
    glVertex2d(x-10,y+4);
    glColor3f(1,0,1);
    glVertex2d(x-15,y+8);
    glVertex2d(x-15,y);
    glEnd();
    DrawCircle(x, y, radius);
}

void playMusic(char name[]) {
    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav;

    if(YSOK!=wav.LoadWav(name))
    {
        printf("Failed to read \n");
        return;
    }

    player.Start();
    player.PlayOneShot(wav);
    while(YSTRUE==player.IsPlaying(wav))
    {
        player.KeepPlaying();
    }

    player.End();
    return;
}

void displayText(char text1[], char text2[], char text3[]) {
    int l[3] = {0, 0, 0};
    int nl = 0;
    
    for(int i = 0; text1[i] != 0; ++i){
        l[0] = i;
    }
    for(int i = 0; text2[i] != 0; ++i){
        l[1] = i;
    }
    for(int i = 0; text3[i] != 0; ++i){
        l[2] = i;
    }
    for(int i = 0; i < 3; ++i){
        if(l[i] > 0){
            ++nl;
        }
    }
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glRasterPos2i(window_width/2 - l[0]/2*16, window_height/2 - nl*20/2);
    YsGlDrawFontBitmap16x20(text1);
    if(l[1]){
        glRasterPos2i(window_width/2 - l[1]/2*16, window_height/2 - nl*20/2 + 25);
        YsGlDrawFontBitmap16x20(text2);
    }
    if(l[2]){
        glRasterPos2i(window_width/2 - l[2]/2*16, window_height/2 - nl*20/2 + 50);
        YsGlDrawFontBitmap16x20(text3);
    }
}


/***
** Controll Ball Class definition
***/
void ControlBall::Initialize(void)
    {
        state=0;
        radius=5;
    }

void ControlBall::Launch(int x0,int y0)
    {
        state=1;
        x=x0;
        y=y0;
    }

void ControlBall::Disappear(void)
    {
        state=0;
    }

void ControlBall::Move(void)
    {
        y-=10;
        if(y<0) {
            Disappear();
        }
    }

void ControlBall::Draw(void)
    {
        int r, g, b;
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
        glColor3ub(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 64; i++) {
            double a = PI * (double)i / 32;
            double dx = cos(a) * radius;
            double dy = sin(a) * radius;
            glVertex2d(x+dx,y+dy);
        }
        glEnd();
    }




/***
** Player Class definition
***/

void Player::InitPlayer() {
    x= 400;
    y= 550;
    radius = 5;
    live = 1;
    laser = 0;
    laserCount = 0;
    controlled = 0;
}
void Player::DrawPlayer() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,1,0);
    glVertex2d(x,y-8);
    glVertex2d(x+15,y);
    glColor3f(0,0,1);
    glVertex2d(x+15,y+8);
    glVertex2d(x+10,y+4);
    glColor3f(1,0,0);
    glVertex2d(x+5,y+8);
    glVertex2d(x,y+6);
    glColor3f(1,1,0);
    glVertex2d(x-5,y+8);
    glVertex2d(x-10,y+4);
    glColor3f(1,0,1);
    glVertex2d(x-15,y+8);
    glVertex2d(x-15,y);
    glEnd();
    DrawCircle(x, y, radius);
}
void Player::DrawLaser() {
    if (laserCount <= 30) {
        laserCount++;
        DrawCircle(x, y - 22, radius);
    } else if (laserCount <= 200) {
        laserCount++;
        int r, g, b;
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(r,g,b);
        glVertex2d(x - 8, 0);
        glColor3ub(r,g,b);
        glVertex2d(x + 8, 0);
        glColor3ub(r,g,b);
        glVertex2d(x + 8, y - 20);
        glColor3ub(r,g,b);
        glVertex2d(x - 8, y - 20);
        glEnd();
    } else {
        laser = 0;
        laserCount = 0;
    }
}
void Player::Move(int dir) {
    if (dir == Left) {
        x -= 10;
        if (x <= 15) {
            x = 15;
        }
    } else if (dir == Right) {
        x += 10;
        if (x >= 785) {
            x = 785;
        }
    }
}

/**
 * Missile Class definition
 */
void Missile::Initialize(void)
{
    state=0;
    
}

void Missile::Launch(int x0,int y0)
{
    state=1;
    x=x0;
    y=y0;
}

void Missile::Disappear(void)
{
    state=0;

}

void Missile::Move(void)
{
    y-=10;
    if(y<0) {
        Disappear();
    }
}
void Missile::tMove(void)
{
    y+=10;
}

void Missile::Draw(void)
{
    glColor3ub(0,0,255);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i(x,y+10);
    glEnd();
}
void Missile::EnemyDraw(void)
{
    glColor3ub(255,0,0);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i(x,y+10);
    glEnd();
}


/**
 * Target Class definition
 */
void Target::Initialize(void)
{
    state=1;
    m.Initialize();
    tx=rand()%800;
    x=0+rand()%800;
    y=50+rand()%50;
    w=50+rand()%40;
    h=10+rand()%20;
    r=rand()%256;
    g=rand()%256;
    b=rand()%256;
    v=5;
    explosionR=4;
}
void Target::Move(void)
{
    tx=rand()%800;
    x+=v + rand()%10;
    if(800<x)
    {
        x=0;
    }
}
void Target::Disappear(void)
{
    state=0;
}
void Target::Draw(void)
{

    glColor3ub(r,g,b);
    glBegin(GL_QUADS);
    glVertex2d(x,y);
    glVertex2d(x+w,y);
    glVertex2d(x+w,y+h);
    glVertex2d(x,y+h);
    glEnd();
}
void Target::ControlledDraw(double playerX, double playerY)
{
    glColor4ub(r,g,b,100);
    glBegin(GL_QUADS);
    glVertex2d(playerX-w/2,playerY-20);
    glVertex2d(playerX+w/2,playerY-20);
    glVertex2d(playerX+w/2,playerY-20-h);
    glVertex2d(playerX-w/2,playerY-20-h);
    glEnd();
}

bool Target::CheckCollisionTarget(int mx,int my,int tx,int ty,int tw,int th)
{
    int rx=mx-tx;
    int ry=my-ty;
    if(0<=rx && rx<=tw && 0<=ry && ry<=th)
    {
        return true;
    }
    return false;
}
bool Target::CheckCollisonLaser(int playerX, int tx, int tw) {
    if (tx <= playerX && (tx + tw) >= playerX) {
        return true;
    }
    return false;
}
bool Target::CheckCollisionControlled(int mx,int my,double tx,double ty,int tw,int th)
{
    int rx=mx-tx;
    int ry=ty-my;
    if(0<=rx && rx<=tw && 0<=ry && ry<=th)
    {
        return true;
    }
    return false;
}
bool Target::CheckCollisionPlayer(int mx,int my,double playerX,double playerY,double radius)
{
    double rx = mx-playerX;
    double ry = my-playerY;
    double sq = rx*rx+ry*ry;
    if(0<=sq && sq<=(radius*radius))
    {
        return true;
    }
    return false;
}
void Target::DrawExplosion()
{
    int r, g, b;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
    glColor3ub(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 64; i++) {
        double a = PI * (double)i / 32;
        double dx = cos(a) * explosionR;
        double dy = sin(a) * explosionR;
        glVertex2d(explosionX+dx,explosionY+dy);
    }
    explosionR+=2;
    if(explosionR >= 30)
    {
        state=0;
    }
    glEnd();
}


void Project::TargetMissleInit(int t, int m){
    numTarget = t;
    numMissile = m;
    
    targets = new Target[numTarget];
    missles = new Missile[numMissile];
    
    for(int i = 0; i < numTarget; i++){
        targets[i].Initialize();
    }
    
    for(int i = 0; i < numMissile; i++){
        missles[i].Initialize();
    }
}


void Project::missilesInit(){
    missles = new Missile[numMissile];
}

void Project::targetsInit(){
    targets = new Target[numTarget];
}

/*
 * Initialize the project object and corresponding game elements
 */
Project::Project(){
    width = window_width;
    height = window_height;
    numMissile = defaultNumMissile;
    numTarget = defaultNumTarget;
    windowInit();
//    aircraft.InitPlayer();
//    ball.Initialize();
//    TargetMissleInit(numTarget,numMissile);
}
/*
 * Initialize the project object and corresponding game elements
 */
Project::Project(int w, int h,int m, int t){
    width = w;
    height = h;
    windowInit();
    aircraft.InitPlayer();
    ball.Initialize();
    TargetMissleInit(t , m);
    
}

void Project:: windowInit(void){
    // initialize the widow frame and random seed
    srand((unsigned int)time(nullptr));
    FsOpenWindow(0,0,width,height,1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

// getter methods for private class members

Player Project::getAircraft(){
    return this->aircraft;
}

ControlBall Project::getBall(){
    return this->ball;
}

Target* Project::getTargets(){
    return this->targets;
}

Missile* Project::getMissle(){
    return this->missles;
}

int Project::getNumMissle(){
    return numMissile;
}

int Project::getNumTarget(){
    return numTarget;
}


//void Project::musicInit(void){
//    char background[] = "./background.wav";
//    char bullet[] = "./bulletShort.wav";
//    char explosion[] = "./explosion.wav";
//    char controll[] = "./controlBullet.wav";
//    char laser[] = "./laser.wav";
//
//    thread bg(playMusic, background);
//    bg.detach();
//}
