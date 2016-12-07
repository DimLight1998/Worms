#ifndef EVENT_H
#define EVENT_H

#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void initialize(HWND hWnd, WPARAM wParam, LPARAM lParam);
void creatRandomTerrain(int seed);

void render(HWND hWnd);
void renderStart(HWND hWnd);
void renderGame(HWND hWnd);

void renderHelp(HWND hWnd);
void renderEnd(HWND hWnd);
void renderPause(HWND hWnd);

void timerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
void robotUpdate(void);
void seaLevelUpdate(void);
void seaUpdate(void);
void gameStatusUpdate(void);
void factionUpdate(void);
void windUpdate(void);
void roundUpdate(void);
void setCameraOnRobot(int ,int);

int  getNextRobotControlled(void);
void switchToNextFaction(void);

void terrainUpdate(void);
void terrainShapeUpdate(int, int, int, int);
void terrainShapeUpdate(int, int);

BOOL robotInTerrain(int factionNum, int robotNum);
BOOL robotLanded(int factionNum, int robotNum);

void cameraUpdate(void);

void weaponUpdate(void);
void weaponLaunch(void);
void weaponDestroied(void);
bool weaponHit(int weapon);
void weaponAnimationUpdate(void);
bool grenadeInTerrain(void);
bool grenadeLanded(void);
bool stickyBombInTerrain(void);
bool TNTInTerrain(void);
bool TNTLanded(void);

void skillActivate(void);
void skillUpdate(void);

void medicalBoxUpdate(void);
void weaponBoxUpdate(void);
void skillBoxUpdate(void);
void boxRefresh(void);
bool boxInTerrain(int boxType, int boxNum);
bool boxLanded(int boxType, int boxNum);

BOOL gameButtonClicked(POINT ptMouse, RECT rectButton);
void keyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
void keyUp(HWND hWnd, WPARAM wParam, LPARAM lPara);
void leftButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

void AI_sense(void);
bool AI_NextMovingAvailable(VectorXY currPos, bool movingLeft);

void AI_decide(void);
void AI_act(void);

#endif
