#ifndef ITEM_H
#define ITEM_H

#include "global.h"


HBITMAP hGameBackgroundPicture_01;
HBITMAP hGameBackgroundPicture_02;
HBITMAP hGameBackgroundPicture_03;
HBITMAP hGameBackgroundPic;
HBITMAP hWelcomeBackgroundPicture;
HBITMAP hHelpBackgroundPicture;
HBITMAP hSettingPicture;
HBITMAP hRockPicture;
HBITMAP hPauseBackgroundPicture;
HBITMAP hRobotPicture[kMaxFactionNumber * 2];
HBITMAP hGameStartButtonPicture;
HBITMAP hGameExitButtonPicture;
HBITMAP hGameHelpButtonPicture;
HBITMAP hHelpExitButtonPicture;
HBITMAP hMissilePictureRight;
HBITMAP hMissilePictureLeft;
HBITMAP hMissilePictureUp;
HBITMAP hMissilePictureDown;
HBITMAP hAimPicture;
HBITMAP hGrenadePicture;
HBITMAP hStickyBombPicture;
HBITMAP hTNTPicture;
HBITMAP hMedicalBoxPicture;
HBITMAP hWeaponBoxPicture;
HBITMAP hSkillBoxPicture;
HBITMAP hTerrainPicture_01;
HBITMAP hTerrainPicture_02;
HBITMAP hTerrainPicture_03;
HBITMAP hTerrainPic;
HBITMAP hGrenadeExplosionPicture;
HBITMAP hWindLeft4;
HBITMAP hWindLeft3;
HBITMAP hWindLeft2;
HBITMAP hWindLeft1;
HBITMAP hWindRight4;
HBITMAP hWindRight3;
HBITMAP hWindRight2;
HBITMAP hWindRight1;
HBITMAP hWindNone;
HBITMAP hWindPowerUI;
HBITMAP hWeaponUI;
HBITMAP hWeaponMissile;
HBITMAP hWeaponGrenade;
HBITMAP hWeaponStickyBomb;
HBITMAP hWeaponTNT;
HBITMAP hWeaponNone;
HBITMAP hAmmoUI;


Faction       faction[kMaxFactionNumber];
Terrain       terrain[kTerrainNumberX][kTerrainNumberY];
BuildingBlock buildingBlock[kTerrainNumberX * kTerrainNumberY];
GameButton    gameStartButton;
GameButton    gameHelpButton;
GameButton    gameExitButton;
GameButton    helpExitButton;
GameButton    gameRestartButton;
GameButton    backToMenuButton;


// AI
Robot      gVirtualRobot;
int        gAIMovingRangeLeft                                 = 0;
int        gAIMovingRangeRight                                = 0;
VectorXY   gAIAviliablePosition[kWindowWidth / kTerrainWidth] = {};
int        gAIAviliablePositionLength                         = 0;
Missile    gVirtualMissile;
Grenade    gVirtualGrenade;
StickyBomb gVirtualStickyBomb;
TNT        gVirtualTNT;
Faction    gVirtualFaction[kMaxFactionNumber];
double     gBestLauchingAngle;
int        gBestLauchingPower;
VectorXY   gBestLauchingLocation;
int        gBestWeapon;

Missile    gMissile;
Grenade    gGrenade;
StickyBomb gStickyBomb;
TNT        gTNT;

MedicalBox gMedicalBox[kMaxMedicalBoxNum];
WeaponBox  gWeaponBox[kMaxWeaponBoxNum];
SkillBox   gSkillBox[kMaxSkillBoxNum];

GameStatus gameStatus;

int gFactionNumber;            // 游戏开始时阵营数目
int gRobotNumberPerFaction;    // 游戏开始时每个阵营人数
int gRobotNumber;              // 这个游戏中的机器人数目

int gRobotControlled   = 0;                 // 当前活跃的机器人
int gFactionControlled = gFactionNumber;    // 当前活跃的阵营
int gFactionAlive      = -1;                // 最后一个活下的阵营

bool     gCameraOverride   = false;
bool     gCameraAutoMoving = false;
VectorXY gCameraVelocity;
VectorXY gCameraTargetPosition;
VectorXY gCameraPosition;

int gMapKind;

bool gRobotWeaponOn       = false;    // 用以指定机器人是否持有武器，若为真，则机器人无法移动
int  gWeaponSelected      = 0;        // 用来指定机器人所选择的武器
bool gMissileActivated    = false;    // 1
bool gGrenadeActivated    = false;    // 2
bool gStickyBombActivated = false;    // 3
bool gTNTActivated        = false;    // 4

bool gRobotSkillOn         = false;
int  gSkillSelected        = 0;
bool gSkillRangeSelecting  = false;
bool gSkillTargetSelecting = false;
int  gSkillTargetFaction   = -1;
int  gSkillTargetRobot     = -1;

int    gChangingWeaponAngle   = 0;        // 用以指定武器旋转状态，值为1为逆时针旋转，-1为顺时针，0为不旋转
bool   gIncreasingWeaponPower = false;    // 用以指定是否在加大武器力量，0为在加大，1为未加大
double gLaunchingAngle        = 0;        // 武器发射的角度
int    gPower                 = 0;        // 武器发射的力度

int gSeaLevel  = kOringinalSeaLevel;    // 全局记录海平面高度
int gWindPower = 0;

bool    gTerrainNeedUpdate = true;
bool    gRenderOnce        = false;
HBITMAP hTerrainBmp;

bool gRobotMoving             = false;
bool gRobotEscaping           = false;
bool gRoundWaiting            = false;
int  gRobotMovingTimeRemain   = kActionTime;
int  gRobotEscapingTimeRemain = kWithdrawTime;
int  gRoundWaitingTimeRemain  = kWaitTime;

bool gPlayingMissileAnimation    = false;
bool gPlayingGrenadeAnimation    = false;
bool gPlayingStickyBombAnimation = false;
bool gPlayingTNTAnimation        = false;

int gMissileAnimationTimeRemain    = 0;
int gGrenadeAnimationTimeRemain    = 0;
int gStickyBombAnimationTimeRemain = 0;
int gTNTAnimationTimeRemain        = 0;

VectorXY gMissileAnimationPosition;
VectorXY gGrenadeAnimationPosition;
VectorXY gStickyBombAnimationPosition;
VectorXY gTNTAnimationPosition;

#endif
