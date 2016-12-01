#ifndef GLOBAL_H
#define GLOBAL_H
/*
██ ███    ██  ██████ ██      ██    ██ ██████  ███████
██ ████   ██ ██      ██      ██    ██ ██   ██ ██
██ ██ ██  ██ ██      ██      ██    ██ ██   ██ █████
██ ██  ██ ██ ██      ██      ██    ██ ██   ██ ██
██ ██   ████  ██████ ███████  ██████  ██████  ███████
*/
#include "resource.h"
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
/*
 ██████  ██████  ███    ██ ███████ ████████
██      ██    ██ ████   ██ ██         ██
██      ██    ██ ██ ██  ██ ███████    ██
██      ██    ██ ██  ██ ██      ██    ██
 ██████  ██████  ██   ████ ███████    ██
*/
// 窗口大小
const int kWindowWidth          = 1600;    // 窗口宽度
const int kWindowHeight         = 900;     // 窗口高度
const int kWindowTitleBarHeight = 32;      // 标题栏高度

// 时钟规则
const int kTimerID     = 1;
const int kTimerElapse = 20;

// 资源尺寸
const int kRobotPictureX         = 32;     // 机器人贴图宽度
const int kRobotPictureY         = 56;     // 机器人贴图高度
const int kAimPictureX           = 512;    // 武器准星贴图宽度
const int kAimPictureY           = 512;    // 武器准星贴图高度
const int kMissilePictureX       = 32;     // 导弹贴图宽度
const int kMissilePictureY       = 16;     // 导弹贴图高度
const int kGrenadePictureX       = 14;     // 手雷贴图宽度
const int kGrenadePictureY       = 20;     // 手雷贴图高度
const int kStickyBombPictureX    = 22;     // 粘性炸弹贴图宽度
const int kStickyBombPictureY    = 30;     // 粘性炸弹贴图高度
const int kTNTPictureX           = 10;
const int kTNTPictureY           = 32;
const int kMedicalBoxPictureX    = 32;
const int kMedicalBoxPictureY    = 28;
const int kWeaponBoxPictureX     = 32;
const int kWeaponBoxPictureY     = 28;
const int kSkillBoxPictureX      = 32;
const int kSkillBoxPictureY      = 28;
const int kGameStartButtonPictureX  = 512;    // 开始游戏按钮宽度
const int kGameStartButtonPictureY  = 512;    // 开始游戏按钮高度
const int kGameExitButtonPictureX  = 128;    // 开始游戏按钮宽度
const int kGameExitButtonPictureY  = 122;    // 开始游戏按钮高度
const int kGameHelpButtonPictureX  = 200;    // 开始游戏按钮宽度
const int kGameHelpButtonPictureY  = 200;    // 开始游戏按钮高度
const int kMaxRobotFrameNum      = 16;     // 机器人贴图最大帧数
const int kRobotStopPictureIndex = 0;      // 机器人静止所在贴图
const int kTerrainPictureSizeX   = 288;    // 地块贴图大小
const int kTerrainPictureSizeY   = 270;
const int kTerrainBlockSizeX     = 16;    // 每个地块的贴图大小
const int kTerrainBlockSizeY     = 16;

// 机器人规则
const int kRobotSizeX               = 32;                                               // 机器人宽度
const int kRobotSizeY               = 56;                                               // 机器人高度
const int kMaxFactionNumber         = 4;                                                // 最大阵营数
const int kMaxRobotNumberPerFaction = 4;                                                // 每个阵营最大机器人数
const int kRobotNumber              = kMaxFactionNumber * kMaxRobotNumberPerFaction;    // 地图上最大的机器人数，最大支持四个阵营，每个阵营四个机器人
const int kRobotFullHitPoint        = 1000;                                             // 机器人的最大血量
const int kRobotVelocityX           = 3;                                                // 机器人横向位移速度
const int kRobotVelocityJumping     = 2;                                                // 机器人跳起后水平速度
const int kRobotVelocityY_startJump = 15;                                               // 机器人跳起速度
const int kRobotEdgeIngnorance      = 3;                                                // 处理碰撞时的机器人边缘忽略
const int kMaxWeaponNum             = 4;                                                // 机器人携带武器种类数，每次追加武器时更改该值
const int kMaxSkillNum              = 4;                                                // 最大技能数
const int kFacingLeft               = 1;
const int kFacingRight              = 2;
const int kPickingBoxRange          = 20;
const int kFrameSwitchFrequency     = 3;

// 武器规则 / 索引
const int kAmmoInfinity = -1;
const int iNoWeapon     = 0;
const int iMissile      = 1;
const int iGrenade      = 2;
const int iStickyBomb   = 3;
const int iTNT          = 4;
// 武器规则 / 导弹
const int kMissileSizeX          = 34;     // 导弹实体宽度
const int kMissileSizeY          = 15;     // 导弹实体高度
const int kMissileVelocity       = 40;     // 导弹初始速度
const int kMissileEdgeIngnorance = 3;      // 导弹碰撞边缘忽略
const int kMissileHarm           = 300;    // 导弹伤害值
const int kMissileHarmRange      = 40;     // 导弹伤害范围
const int kMissileSenseDistance  = 20;     // 导弹被机器人触发范围
const int kMissileExplosionPower = 6;      // 导弹震波
const int kMissileDefaultAmmo    = -1;     // 无限，用-1表示
// 武器规则 / 手雷
const int kGrenadeExplodeTime    = 150;    // 手雷爆炸前的时间
const int kGrenadeSizeX          = 14;     // 手雷实体宽度
const int kGrenadeSizeY          = 20;     // 手雷实体高度
const int kGrenadeVelocity       = 25;     // 手雷初始速度
const int kGrenadeEdgeIngnorance = 2;      // 手雷碰撞边缘检测
const int kGrenadeHarm           = 400;    // 手雷伤害
const int kGrenadeHarmRange      = 50;     // 手雷伤害范围
const int kGrenadeExplosionPower = 12;     // 手雷震波
const int kGrenadeDefaultAmmo    = -1;     // 无限，用-1表示
// 武器规则 / 粘性炸弹
const int kStickyBombExplodeTime    = 150;
const int kStickyBombSizeX          = 22;     // 粘性炸弹实体宽度
const int kStickyBombSizeY          = 30;     // 粘性炸弹实体高度
const int kStickyBombVelocity       = 16;     // 粘性炸弹初始速度
const int kStickyBombEdgeIngnorance = 3;      // 粘性炸弹碰撞边缘检测
const int kStickyBombHarm           = 600;    // 粘性炸弹伤害
const int kStickyBombHarmRange      = 100;    // 粘性炸弹伤害范围
const int kStickyBombExplosionPower = 15;     // 粘性炸弹震波
const int kStickyBombDefaultAmmo    = 3;
// 武器规则 / 炸药
const int kTNTExplodeTime    = 200;
const int kTNTSizeX          = 10;     // 炸药实体宽度
const int kTNTSizeY          = 32;     // 炸药实体高度
const int kTNTVelocity       = 0;      // 炸药初始速度
const int kTNTEdgeIngnorance = 3;      // 炸药碰撞边缘检测
const int kTNTHarm           = 800;    // 炸药伤害
const int kTNTHarmRange      = 200;    // 炸药伤害范围
const int kTNTExplosionPower = 20;     // 炸药震波
const int kTNTDefaultAmmo    = 1;


// 技能规则 / 索引
const int iNoSkill      = 0;    // 无技能
const int iCure         = 1;    // 治疗技能，治疗指定阵营的指定对象
const int iTransfer     = 2;    // 随机传送技能，无输入，传送到随机地区
const int iSafeTransfer = 3;    // 安全传送技能，传送到自己阵营的指定对象旁边
const int iProtect      = 4;    // 护盾技能，打开自己的护盾
// 技能规则 / 参数
const int kCureEffect             = 500;
const int kCureDefaultAmmo        = 2;
const int kTransferDefaultAmmo    = 2;
const int kSafeTransferDefaulAmmo = 2;
const int kProtectDefaultAmmo     = 2;
const int kProtectiveShellTime    = 10;


// 补给箱规则 / 索引
const int kMedicalBoxNumber = 1;
const int kWeaponBoxNumber  = 2;
const int kSkillBoxNumber   = 3;
// 补给箱规则 / 医疗箱
const int kMedicalBoxSizeX          = 32;
const int kMedicalBoxSizeY          = 28;
const int kMaxMedicalBoxNum         = 2;
const int kMedicalBoxEdgeIngnorance = 3;
const int kMedicalBoxEffect         = 200;
// 补给箱规则 / 武器箱
const int kWeaponBoxSizeX          = 32;
const int kWeaponBoxSizeY          = 28;
const int kMaxWeaponBoxNum         = 2;
const int kWeaponBoxEdgeIngnorance = 3;
// 补给箱规则 / 技能箱
const int kSkillBoxSizeX          = 32;
const int kSkillBoxSizeY          = 28;
const int kMaxSkillBoxNum         = 2;
const int kSkillBoxEdgeIngnorance = 3;

// 物理规则
const int    kGravityAcceleration = 1;                     // 重力加速度
const double Pi                   = 3.1415926535897932;    // 圆周率

// 地块规则
const int kWorldWidth           = 4000;                             // 世界的宽度
const int kWorldHeight          = 1600;                             // 世界的高度
const int kTerrainWidth         = 16;                               // 每个地块宽度
const int kTerrainHeight        = 16;                               // 每个地块高度
const int kTerrainNumberX       = kWorldWidth / kTerrainWidth;      // 横向地块数目
const int kTerrainNumberY       = kWorldHeight / kTerrainHeight;    // 纵向地块数目
const int kTerrainHeightBase    = 30;                               // 用于随机化地形的高度大基准
const int kLeftMostTerrainDelta = 10;                               // 用于随机化地形的高度小基准
const int kMinTerrainHeight = 50;
const int kMinHoleNumber = 20;
const int kMaxHoleNumber        = 30;                               // 最大山洞数
const int kMaxHoleRadius        = 16;                                // 最大山洞半径
// 地块显示规则

const int iTerrainEmpty             = -2;
const int iTerrainDefault           = -1;    // 初始化值
const int iTerrainFull              = 0;     // 满地块
const int iTerrainHalfRight         = 1;     // 右边缺了一半
const int iTerrainHalfLeft          = 2;     // 左边缺了一半
const int iTerrainHalfUp            = 3;     // 上面缺了一半
const int iTerrainHalfDown          = 4;     // 下面缺了一半
const int iTerrainMiddleUpDown      = 5;     // 左右都缺
const int iTerrainMiddleLeftRight   = 6;     // 上下都缺
const int iTerrainAngleLeftUp       = 7;     // 向左上角的直角
const int iTerrainAngleRightUp      = 8;     // 向右上角的直角
const int iTerrainAngleLeftDown     = 9;     // 向左下角的直角
const int iTarrainAngleRightDown    = 10;    // 向右下角的直角
const int iTerrainIndependantMiddle = 11;    // 上下左右都缺的完全独立地块
const int iTerrainIndependantLeft   = 12;    // 向左凸出一小块
const int iTerrainIndependantRight  = 13;    // 向右凸出一小块
const int iTerrainIndependantUp     = 14;    // 向上凸出一小块
const int iTerrainIndependantDown   = 15;    // 向下凸出一小块


// 海洋规则
const int kOringinalSeaLevel          = kWorldHeight - 25;    // 初始海洋高度
const int kSeaLevelIncreasingVelocity = 0;                    // 海洋上涨速度

// 风规则
const int    kWindPowerRange  = 3;
const double kWindPowerFactor = 1;


// 用户界面规则
const int kButtonWidth=100;
const int kButtonHeight=100;
const int kHitPointBarWidth       = 30;    // 血条的宽度
const int kHitPointBarHeigth      = 5;     // 血条的高度
const int kHitPointBarDistance    = 10;    // 血条距离人物的高度
const int kAimUIWidth             = 50;    // 准星显示宽度
const int kAimUIHeight            = 50;    // 准星显示高度
const int kAimDistance            = 75;    // 准星距离机器人距离
const int kFactionHPBarWidth      = 360;
const int kFactionHPBarHeight     = 25;
const int kFactionHPBarDistance   = 5;
const int kRobotControlSignHeight = 50;

// 用户操作规则
const int    kCameraLimitTop        = 0;
const int    kCameraLimitLeft       = 0;
const int    kCameraLimitButtom     = kWorldHeight - kWindowHeight;
const int    kCameraLimitRight      = kWorldWidth - kWindowWidth;
const int    kCameraVelocity        = 8;      // 摄像机切换速度
const double kAngelChangingVelocity = 0.2;    // 改变武器发射角度的速率
const int    kActionTime            = 0;      // 每回合操作时间
const int    kWithdrawTime          = 0;      // 撤退时间

// 颜色规则
const COLORREF HPBar_1000        = RGB(0, 250, 0);
const COLORREF HPBar_0750        = RGB(100, 150, 0);
const COLORREF HPBar_0500        = RGB(150, 100, 0);
const COLORREF HPBar_0250        = RGB(250, 0, 0);
const COLORREF HPBar_0000        = RGB(0, 0, 0);
const COLORREF Color_Aim         = RGB(26, 188, 156);
const COLORREF Color_Sea         = RGB(0, 0, 250);
const COLORREF Color_Faction_1   = RGB(39, 174, 96);
const COLORREF Color_Faction_2   = RGB(231, 76, 60);
const COLORREF Color_Faction_3   = RGB(41, 128, 185);
const COLORREF Color_Faction_4   = RGB(241, 196, 15);
const COLORREF Color_SkillTarget = RGB(0, 0, 0);

// 游戏状态定义
const int Game_start   = 0;
const int Game_running = 1;
const int Game_end     = 2;
const int Game_pause   = 3;
const int Game_setting = 4;
const int Game_help    = 5;


/*
███████ ████████ ██████  ██    ██  ██████ ████████
██         ██    ██   ██ ██    ██ ██         ██
███████    ██    ██████  ██    ██ ██         ██
     ██    ██    ██   ██ ██    ██ ██         ██
███████    ██    ██   ██  ██████   ██████    ██
*/
// todo
struct VectorXY
{
    int x;
    int y;
};


struct Robot
{
    int      faction;
    int      hitPoint;
    int      direction;
    bool     alive;
    int      weapon;
    int      skill;
    BOOL     isJumping;
    int      protectiveShellTime;
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    HBITMAP  hPicture;
    int      maxFrameNum;
    int      currentFrameNum;
    int      frameCounter;    // 记录当前距离下一帧有多远
};

struct Faction
{
    int   hitPoint;
    bool  alive;
    Robot robot[kMaxRobotNumberPerFaction];
    int   aliveRobot;
    int   ammoMissile;
    int   ammoGrenade;
    int   ammoStickyBomb;
    int   ammoTNT;
    int   ammoCure;
    int   ammoTransfer;
    int   ammoSafeTransfer;
    int   ammoProtect;
};

struct Terrain
{
    int      connectionStatus;
    BOOL     isDestoried;
    RECT     position;
    HBITMAP  hPicture;
    VectorXY picturePosition;
};

struct GameButton
{
    VectorXY size;
    VectorXY position;
    BOOL     status_isClicked;
    HBITMAP  hPicture;
};

struct GameStatus
{
    int     status;
    HBITMAP hPicture;
};

struct Missile
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    HBITMAP  hPicture;
};

struct Grenade
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    int      timeToExplode;
    bool     locked;
    HBITMAP  hPicture;
};

struct StickyBomb
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    int      timeToExplode;
    bool     locked;

    HBITMAP hPicture;
};

struct TNT
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    int      timeToExplode;
    bool     locked;

    HBITMAP hPicture;
};

struct MedicalBox
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    bool     picked;
    HBITMAP  hPicture;
};

struct WeaponBox
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    int      content;
    bool     picked;
    HBITMAP  hPicture;
};

struct SkillBox
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    int      content;
    bool     picked;
    HBITMAP  hPicture;
};
/*
███████ ██    ██ ███    ██  ██████
██      ██    ██ ████   ██ ██
█████   ██    ██ ██ ██  ██ ██
██      ██    ██ ██  ██ ██ ██
██       ██████  ██   ████  ██████
*/


Robot creatRobot(int faction, VectorXY position);
Faction creatFaction(int factionNumber);
GameButton creatGameButton(VectorXY size, VectorXY position, BOOL status, HBITMAP hPicture);
Terrain creatTerrain(int numberX, int numberY);
Missile creatMissile(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture);
Grenade creatGrenade(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture);
StickyBomb creatStickyBomb(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture);
TNT creatTNT(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture);

MedicalBox creatMedicalBox(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture);
WeaponBox creatWeaponBox(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture);
SkillBox creatSkillBox(VectorXY position, VectorXY velocity, VectorXY acceleration, HBITMAP hPicture);

void drawClosedRectangle(HDC hdc, int left, int top, int right, int bottom);
void drawClosedCircle(HDC hdc, int Ox, int Oy, int r);
int pointPointDistanceSquare(int point_1_x, int point_1_y, int point_2_x, int point_2_y);

VectorXY randomSelectTerrainBlockPicture(int num, ...);
VectorXY getTerrainBlockPicture(int type);


#endif
