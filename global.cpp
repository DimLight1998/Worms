#include "global.h"

Robot creatRobot(int faction, VectorXY position)
{
    Robot robot;
    robot.faction         = faction;
    robot.hitPoint        = kRobotFullHitPoint;
    robot.direction       = (rand() % 2) ? kFacingLeft : kFacingRight;
    robot.alive           = true;
    robot.weapon          = 0;
    robot.isJumping       = false;
    robot.position        = position;
    robot.velocity.x      = 0;
    robot.velocity.y      = 0;
    robot.acceleration.x  = 0;
    robot.acceleration.y  = 0;
    robot.hPicture        = 0;
    robot.maxFrameNum     = kMaxRobotFrameNum;
    robot.currentFrameNum = 0;
    robot.frameCounter    = 0;
    return robot;
}

Faction creatFaction(int factionNumber)
{
    Faction faction;
    faction.alive    = true;
    faction.hitPoint = kMaxRobotNumberPerFaction * kRobotFullHitPoint;
    for (int i = 0; i < kMaxRobotNumberPerFaction; i++)
    {
        VectorXY temp;
        temp.x           = rand() % (kWorldWidth + 1);
        temp.y           = kWorldHeight / 2;
        faction.robot[i] = creatRobot(factionNumber, temp);
    }
    faction.aliveRobot     = kMaxRobotNumberPerFaction;
    faction.ammoMissile    = kMissileDefaultAmmo;
    faction.ammoGrenade    = kGrenadeDefaultAmmo;
    faction.ammoStickyBomb = kStickyBombDefaultAmmo;
    faction.ammoTNT        = kTNTDefaultAmmo;
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

    terrain.isDestoried     = false;
    terrain.position.left   = numberX * kTerrainWidth + 1;
    terrain.position.right  = (numberX + 1) * kTerrainWidth;
    terrain.position.top    = numberY * kTerrainHeight + 1;
    terrain.position.bottom = (numberY + 1) * kTerrainHeight;

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
    weaponBox.content      = rand() % kMaxWeaponNum + 1;
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
    skillBox.content      = 0;    // TODO
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
