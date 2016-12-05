#include "global.h"

Robot creatRobot(int faction, VectorXY position)
{
    Robot robot;
    robot.faction             = faction;
    robot.hitPoint            = kRobotFullHitPoint;
    robot.direction           = (rand() % 2) ? kFacingLeft : kFacingRight;
    robot.alive               = true;
    robot.weapon              = iNoWeapon;
    robot.skill               = iNoSkill;
    robot.protectiveShellTime = 0;
    robot.isJumping           = false;
    robot.position            = position;
    robot.velocity.x          = 0;
    robot.velocity.y          = 0;
    robot.acceleration.x      = 0;
    robot.acceleration.y      = 0;
    robot.hPicture            = 0;
    robot.maxFrameNum         = kMaxRobotFrameNum;
    robot.currentFrameNum     = 0;
    robot.frameCounter        = 0;
    return robot;
}

Faction creatFaction(int factionNumber,bool controlledByAI)
{
    Faction faction;
    faction.controlledByAI=controlledByAI;
    faction.alive    = true;
    faction.hitPoint = kMaxRobotNumberPerFaction * kRobotFullHitPoint;
    for (int i = 0; i < kMaxRobotNumberPerFaction; i++)
    {
        VectorXY temp;
        temp.x           = rand() % (kWorldWidth + 1);
        temp.y           = kWorldHeight / 2;
        faction.robot[i] = creatRobot(factionNumber, temp);
    }
    faction.robotControlled  = 0;
    faction.aliveRobot       = kMaxRobotNumberPerFaction;
	faction.ammoBuildingBlock = kBuildingBlockDefautAmmo;
    faction.ammoMissile      = kMissileDefaultAmmo;
    faction.ammoGrenade      = kGrenadeDefaultAmmo;
    faction.ammoStickyBomb   = kStickyBombDefaultAmmo;
    faction.ammoTNT          = kTNTDefaultAmmo;
    faction.ammoCure         = kCureDefaultAmmo;
    faction.ammoTransfer     = kTransferDefaultAmmo;
    faction.ammoSafeTransfer = kSafeTransferDefaulAmmo;
    faction.ammoProtect      = kProtectDefaultAmmo;
    return faction;
}
GameButton creatGameButton(VectorXY size, VectorXY position, BOOL status, HBITMAP hPicture)
{
    GameButton gameButton;
    gameButton.size             = size;
    gameButton.position         = position;
    gameButton.status_isClicked = status;
    gameButton.hPicture         = hPicture;
    return gameButton;
}

Terrain creatTerrain(int numberX, int numberY)
{
    Terrain terrain;

    terrain.isDestoried       = false;
    terrain.connectionStatus  = -1;
    terrain.position.left     = numberX * kTerrainWidth + 1;
    terrain.position.right    = (numberX + 1) * kTerrainWidth;
    terrain.position.top      = numberY * kTerrainHeight + 1;
    terrain.position.bottom   = (numberY + 1) * kTerrainHeight;
    terrain.picturePosition.x = 0;
    terrain.picturePosition.y = 0;

    return terrain;
}

Missile creatMissile(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture)
{
    Missile missile;
    missile.position     = position;
    missile.velocity     = velocity;
    missile.acceleration = acceleration;
    missile.hPicture     = hPicture;
    return missile;
}

Grenade creatGrenade(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture)
{
    Grenade grenade;
    grenade.position      = position;
    grenade.velocity      = velocity;
    grenade.acceleration  = acceleration;
    grenade.timeToExplode = kGrenadeExplodeTime;
    grenade.locked        = false;
    grenade.hPicture      = hPicture;
    return grenade;
}

StickyBomb creatStickyBomb(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture)
{
    StickyBomb stickyBomb;
    stickyBomb.position      = position;
    stickyBomb.velocity      = velocity;
    stickyBomb.acceleration  = acceleration;
    stickyBomb.timeToExplode = kStickyBombExplodeTime;
    stickyBomb.locked        = false;
    stickyBomb.hPicture      = hPicture;
    return stickyBomb;
}

TNT creatTNT(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture)
{
    TNT tnt;
    tnt.position      = position;
    tnt.velocity      = velocity;
    tnt.acceleration  = acceleration;
    tnt.timeToExplode = kTNTExplodeTime;
    tnt.locked        = false;
    tnt.hPicture      = hPicture;
    return tnt;
}


MedicalBox creatMedicalBox(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture)
{
    MedicalBox medicalBox;
    medicalBox.position     = position;
    medicalBox.velocity     = velocity;
    medicalBox.acceleration = acceleration;
    medicalBox.picked       = false;
    medicalBox.hPicture     = hPicture;
    return medicalBox;
}
WeaponBox creatWeaponBox(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture)
{
    WeaponBox weaponBox;
    weaponBox.position     = position;
    weaponBox.velocity     = velocity;
    weaponBox.acceleration = acceleration;
    weaponBox.content      = rand() % kMaxWeaponNum + 1;    // TODO issue
    weaponBox.picked       = false;
    weaponBox.hPicture     = hPicture;
    return weaponBox;
}
SkillBox creatSkillBox(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture)
{
    SkillBox skillBox;
    skillBox.position     = position;
    skillBox.velocity     = velocity;
    skillBox.acceleration = acceleration;
    skillBox.content      = rand() % kMaxSkillNum + 1;    // TODO issue
    skillBox.picked       = false;
    skillBox.hPicture     = hPicture;
    return skillBox;
}


void drawClosedRectangle(HDC hdc, int left, int top, int right, int bottom)
{
    Rectangle(hdc, left - 1, top - 1, right + 1, bottom + 1);
}

void drawClosedCircle(HDC hdc, int Ox, int Oy, int r)
{
    Ellipse(hdc, Ox - r, Oy - r, Ox + r, Oy + r);
}

int pointPointDistanceSquare(int point_1_x, int point_1_y, int point_2_x, int point_2_y)
{
    return (point_1_x - point_2_x) * (point_1_x - point_2_x) + (point_1_y - point_2_y) * (point_1_y - point_2_y);
}

VectorXY randomSelectTerrainBlockPicture(int num, ...)
{
    VectorXY pool[50] = {};
    va_list  args;
    int      i = 0;
    va_start(args, num);
    int p = rand() % num;
    while (num > 0)
    {
        pool[i] = va_arg(args, VectorXY);
        num--;
        i++;
    }
    va_end(args);
    return pool[p];
}

VectorXY getTerrainBlockPicture(int type)
{
    switch (type)
    {
    case iTerrainEmpty:
    {
        VectorXY vec[1] = { { 10, 5 } };
        return randomSelectTerrainBlockPicture(1, vec[0]);
        break;
    }
    case iTerrainDefault:
    {
        break;
    }
    case iTerrainFull:
    {
        VectorXY vec[8] = { { 2, 2 }, { 3, 2 }, { 4, 2 }, { 3, 6 }, { 3, 7 }, { 3, 8 }, { 3, 9 }, { 3, 10 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iTerrainHalfRight:
    {
        VectorXY vec[8] = { { 5, 1 }, { 5, 2 }, { 5, 3 }, { 6, 6 }, { 6, 7 }, { 6, 8 }, { 6, 9 }, { 6, 10 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iTerrainHalfLeft:
    {
        VectorXY vec[8] = { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 5, 6 }, { 5, 7 }, { 5, 8 }, { 5, 9 }, { 5, 10 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iTerrainHalfUp:
    {
        VectorXY vec[8] = { { 2, 1 }, { 4, 12 }, { 4, 1 }, { 3, 12 }, { 15, 1 }, { 16, 1 }, { 1, 12 }, { 2, 12 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iTerrainHalfDown:
    {
        VectorXY vec[8] = { { 2, 3 }, { 3, 3 }, { 4, 3 }, { 1, 13 }, { 2, 13 }, { 3, 13 }, { 4, 13 }, { 16, 2 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iTerrainMiddleUpDown:
    {
        VectorXY vec[8] = { { 6, 1 }, { 6, 2 }, { 6, 3 }, { 8, 6 }, { 8, 7 }, { 8, 8 }, { 8, 9 }, { 8, 10 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iTerrainMiddleLeftRight:
    {
        VectorXY vec[8] = { { 7, 5 }, { 8, 5 }, { 9, 5 }, { 1, 15 }, { 2, 15 }, { 3, 15 }, { 4, 15 }, { 5, 15 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iTerrainAngleLeftUp:
    {
        VectorXY vec[3] = { { 1, 4 }, { 3, 4 }, { 5, 4 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTerrainAngleRightUp:
    {
        VectorXY vec[3] = { { 2, 4 }, { 4, 4 }, { 6, 4 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTerrainAngleLeftDown:
    {
        VectorXY vec[3] = { { 1, 5 }, { 3, 5 }, { 5, 5 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTarrainAngleRightDown:
    {
        VectorXY vec[3] = { { 2, 5 }, { 4, 5 }, { 6, 5 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTerrainIndependantMiddle:
    {
        VectorXY vec[3] = { { 10, 4 }, { 11, 4 }, { 12, 4 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTerrainIndependantLeft:
    {
        VectorXY vec[3] = { { 10, 1 }, { 10, 2 }, { 10, 3 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTerrainIndependantRight:
    {
        VectorXY vec[3] = { { 13, 1 }, { 13, 2 }, { 13, 3 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTerrainIndependantUp:
    {
        VectorXY vec[3] = { { 7, 1 }, { 8, 1 }, { 9, 1 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iTerrainIndependantDown:
    {
        VectorXY vec[3] = { { 7, 4 }, { 8, 4 }, { 9, 4 } };
        return randomSelectTerrainBlockPicture(3, vec[0], vec[1], vec[2]);
        break;
    }
    case iWaterSurface:
    {
        VectorXY vec[8] = { { 8, 14 }, { 9, 14 }, { 10, 14 }, { 11, 14 }, { 12, 14 }, { 13, 14 }, { 14, 14 }, { 15, 14 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    case iWaterDeep:
    {
        VectorXY vec[8] = { { 8, 15 }, { 9, 15 }, { 10, 15 }, { 11, 15 }, { 12, 15 }, { 13, 15 }, { 14, 15 }, { 15, 15 } };
        return randomSelectTerrainBlockPicture(8, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7]);
        break;
    }
    }
}
