#ifndef ITEM_H
#define ITEM_H

#include "global.h"


HBITMAP hGameBackgroundPicture;
HBITMAP hWelcomeBackgroundPicture;
HBITMAP hHelpBackgroundPicture;
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
HBITMAP hTerrainPicture;
HBITMAP hGrenadeExplosionPicture;


Faction    faction[kMaxFactionNumber];
Terrain    terrain[kTerrainNumberX][kTerrainNumberY];
GameButton gameStartButton;
GameButton gameHelpButton;
GameButton gameExitButton;
GameButton helpExitButton;

Missile    gMissile;
Grenade    gGrenade;
StickyBomb gStickyBomb;
TNT        gTNT;

MedicalBox gMedicalBox[kMaxMedicalBoxNum];
WeaponBox  gWeaponBox[kMaxWeaponBoxNum];
SkillBox   gSkillBox[kMaxSkillBoxNum];

GameStatus gameStatus;

int gFactionNumber;            // ��Ϸ��ʼʱ��Ӫ��Ŀ
int gRobotNumberPerFaction;    // ��Ϸ��ʼʱÿ����Ӫ����
int gRobotNumber;              // �����Ϸ�еĻ�������Ŀ

int gRobotControlled = 0;                 // ��ǰ��Ծ�Ļ�����
int gFactionControlled = gFactionNumber;    // ��ǰ��Ծ����Ӫ
int gFactionAlive = -1;                // ���һ�����µ���Ӫ

bool     gCameraOverride = false;
bool     gCameraAutoMoving = false;
VectorXY gCameraVelocity;
VectorXY gCameraTargetPosition;
VectorXY gCameraPosition;

bool gRobotWeaponOn = false;    // ����ָ���������Ƿ������������Ϊ�棬��������޷��ƶ�
int  gWeaponSelected = 0;        // ����ָ����������ѡ�������
bool gMissileActivated = false;    // 1
bool gGrenadeActivated = false;    // 2
bool gStickyBombActivated = false;    // 3
bool gTNTActivated = false;    // 4

bool gRobotSkillOn = false;
int  gSkillSelected = 0;
bool gSkillRangeSelecting = false;
bool gSkillTargetSelecting = false;
int  gSkillTargetFaction = -1;
int  gSkillTargetRobot = -1;

int    gChangingWeaponAngle = 0;        // ����ָ��������ת״̬��ֵΪ1Ϊ��ʱ����ת��-1Ϊ˳ʱ�룬0Ϊ����ת
bool   gIncreasingWeaponPower = false;    // ����ָ���Ƿ��ڼӴ�����������0Ϊ�ڼӴ�1Ϊδ�Ӵ�
double gLaunchingAngle = 0;        // ��������ĽǶ�
int    gPower = 0;        // �������������

int gSeaLevel = 95;    // ȫ�ּ�¼��ƽ��߶�
int gWindPower = 0;

bool    gTerrainNeedUpdate = true;
bool    gRenderOnce = false;
HBITMAP hTerrainBmp;

bool gRobotMoving = false;
bool gRobotEscaping = false;
bool gRoundWaiting = false;
int  gRobotMovingTimeRemain = kActionTime;
int  gRobotEscapingTimeRemain = kWithdrawTime;
int  gRoundWaitingTimeRemain = kWaitTime;

bool gPlayingMissileAnimation = false;
bool gPlayingGrenadeAnimation = false;
bool gPlayingStickyBombAnimation = false;
bool gPlayingTNTAnimation = false;

int gMissileAnimationTimeRemain = 0;
int gGrenadeAnimationTimeRemain = 0;
int gStickyBombAnimationTimeRemain = 0;
int gTNTAnimationTimeRemain = 0;

VectorXY gMissileAnimationPosition;
VectorXY gGrenadeAnimationPosition;
VectorXY gStickyBombAnimationPosition;
VectorXY gTNTAnimationPosition;

#endif
