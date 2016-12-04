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


#endif
