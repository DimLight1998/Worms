/*
todolist
开始界面布局
结束界面布局

帮助界面布局
地图选择界面布局
制作人物贴图
不同阵营的人物
手榴弹的爆炸效果

回合制对战
多背景图片

帮助界面，地图选择界面
随机地图生成器，能输入种子
显示弹药量和技能点
多种武器支持
对战AI
地形贴图
武器箱，医疗箱，技能箱
背景音乐
放弃操作

*/

//

//kWindowHeight
#include "event.h"
#include "global.h"
#include "item.h"


/*
 ██████  ██       ██████  ██████   █████  ██
██       ██      ██    ██ ██   ██ ██   ██ ██
██   ███ ██      ██    ██ ██████  ███████ ██
██    ██ ██      ██    ██ ██   ██ ██   ██ ██
 ██████  ███████  ██████  ██████  ██   ██ ███████
*/
bool gGamePaused = false;    // 状态变量，记录当前游戏是否暂停

int gRobotControlled   = 0;     // 当前活跃的机器人
int gFactionControlled = 0;     // 当前活跃的阵营
int gFactionAlive      = -1;    // 最后一个活下的阵营

int gFactionNumber;            // 游戏开始时阵营数目
int gRobotNumberPerFaction;    // 游戏开始时每个阵营人数
int gRobotNumber;              // 这个游戏中的机器人数目

int gCameraX;    // 摄像机水平位置
int gCameraY;    // 摄像机数值位置

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


int  gChangingWeaponAngle   = 0;        // 用以指定武器旋转状态，值为1为逆时针旋转，-1为顺时针，0为不旋转
bool gIncreasingWeaponPower = false;    // 用以指定是否在加大武器力量，0为在加大，1为未加大

double gLaunchingAngle = 0;    // 武器发射的角度
int    gPower          = 0;    // 武器发射的力度

long long int DEBUG_ONLY_seaLevelIncHelper = 0;                     // 用作海平面上涨的速度的因子
int           gSeaLevel                    = kOringinalSeaLevel;    // 全局记录海平面高度
int           gWindPower                   = 0;

bool gTerrainNeedUpdate = true;

/*
██ ███    ██ ██ ████████ ██  █████  ██      ██ ███████ ███████
██ ████   ██ ██    ██    ██ ██   ██ ██      ██    ███  ██
██ ██ ██  ██ ██    ██    ██ ███████ ██      ██   ███   █████
██ ██  ██ ██ ██    ██    ██ ██   ██ ██      ██  ███    ██
██ ██   ████ ██    ██    ██ ██   ██ ███████ ██ ███████ ███████
*/

void initialize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    
    // 将资源载入到资源句柄中
    hGameBackgroundPicture    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_GameBackground_01));
    hWelcomeBackgroundPicture = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_WelcomeBackground));
    hPauseBackgroundPicture   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_GameBackground_01));
    hRockPicture              = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Rock_01));
    hRobotPicture[0]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_01_left));
    hRobotPicture[1]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_02_left));
    hRobotPicture[2]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_03_left));
    hRobotPicture[3]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_04_left));
    hRobotPicture[4]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_01_right));
    hRobotPicture[5]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_02_right));
    hRobotPicture[6]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_03_right));
    hRobotPicture[7]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_04_right));
    hGameStartButtonPicture   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_GameButton_01));
    hMissilePictureRight      = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Missile_Right));
    hMissilePictureLeft       = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Missile_Left));
    hMissilePictureUp         = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Missile_Up));
    hMissilePictureDown       = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Missile_Down));
    hGrenadePicture           = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Grenade));
    hStickyBombPicture        = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_StickyBomb));
    hTNTPicture               = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_TNT));
    hAimPicture               = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Aim));
    hMedicalBoxPicture        = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MedicalBox));
    hWeaponBoxPicture         = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_WeaponBox));
    hSkillBoxPicture          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_SkillBox));
    hTerrainPicture           = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_TerrainRes));

    //
    gFactionNumber         = kMaxFactionNumber;
    gRobotNumberPerFaction = kMaxRobotNumberPerFaction;
    gRobotNumber           = gFactionNumber * gRobotNumberPerFaction;
    //

    // 初始化箱子，会自动更新
    for (int i = 0; i < kMaxMedicalBoxNum; i++)
    {
        gMedicalBox[i].picked = true;
    }
    for (int i = 0; i < kMaxWeaponBoxNum; i++)
    {
        gWeaponBox[i].picked = true;
    }
    for (int i = 0; i < kMaxSkillBoxNum; i++)
    {
        gSkillBox[i].picked = true;
    }

    // 初始化阵营
    for (int i = 0; i < gFactionNumber; i++)
    {
        faction[i] = creatFaction(i);
        for (int j = 0; j < gRobotNumberPerFaction; j++)
        {
            if (faction[i].robot[j].direction == kFacingLeft)
            {
                faction[i].robot[j].hPicture = hRobotPicture[i];
            }
            if (faction[i].robot[j].direction == kFacingRight)
            {
                faction[i].robot[j].hPicture = hRobotPicture[i + gFactionNumber];
            }
        }
    }


    // 初始化地形数组
    for (int i = 0; i < kTerrainNumberX; i++)
        for (int j = 0; j < kTerrainNumberY; j++)
        {
            terrain[i][j] = creatTerrain(i, j);
        }

    creatRandomTerrain(clock());
    terrainShapeUpdate(0, 0, kTerrainNumberX - 1, kTerrainNumberY - 1);

    // 将机器人放到地面上
    for (int i = 0; i < gFactionNumber; i++)
    {
        for (int j = 0; j < gRobotNumberPerFaction; j++)
        {
            while (robotInTerrain(i, j))
                faction[i].robot[j].position.y--;
            while (!robotLanded(i, j))
                faction[i].robot[j].position.y++;
        }
    }

    // 创建开始游戏的按钮
    VectorXY temp_1, temp_2;
    temp_1.x        = kGameStartButtonSizeX;    // 开始游戏按钮的横向大小
    temp_1.y        = kGameStartButtonSizeY;    // 开始游戏按钮的纵向大小
    temp_2.x        = 200;                      // 开始游戏按钮的横坐标
    temp_2.y        = 200;                      // 开始游戏按钮的纵坐标
    gameStartButton = creatGameButton(temp_1, temp_2, false, hGameStartButtonPicture);

    // 设置游戏状态
    gameStatus.status   = Game_start;
    gameStatus.hPicture = hWelcomeBackgroundPicture;    // 设置背景图片

    srand(unsigned((time(0))));
}
/*
 ██████ ██████  ███████  █████  ████████ ██████   █████  ███    ██ ██████   ██████  ███    ███ ████████ ███████ ██████  ██████   █████  ██ ███    ██
██      ██   ██ ██      ██   ██    ██    ██   ██ ██   ██ ████   ██ ██   ██ ██    ██ ████  ████    ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██
██      ██████  █████   ███████    ██    ██████  ███████ ██ ██  ██ ██   ██ ██    ██ ██ ████ ██    ██    █████   ██████  ██████  ███████ ██ ██ ██  ██
██      ██   ██ ██      ██   ██    ██    ██   ██ ██   ██ ██  ██ ██ ██   ██ ██    ██ ██  ██  ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██
 ██████ ██   ██ ███████ ██   ██    ██    ██   ██ ██   ██ ██   ████ ██████   ██████  ██      ██    ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████
*/

void creatRandomTerrain(int seed)
{
    srand(seed);
    // 从最左边开始，最左边距离天空的高度为10到20地块
    // 每次向右加载一个地块，0.3概率高度不变，0.25概率高度变化为1，0.2概率高度变化为2，0.1概率高度变化为3，0.05分别概率高度变化为4,5,6

    // 确定最左边的高度
    int heightLeftMost = kTerrainHeightBase + rand() % (kLeftMostTerrainDelta + 1);
    for (int i                    = 0; i < heightLeftMost; i++)
        terrain[0][i].isDestoried = true;
    int prevHeight                = heightLeftMost;
    for (int i = 1; i < kTerrainNumberX; i++)
    {
        int decider = rand() % 1000;
        if (decider < 300)
        {
            for (int j = 0; j < prevHeight; j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 425)
        {
            for (int j = 0; j < min(prevHeight + 1, kTerrainNumberY); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 550)
        {
            for (int j = 0; j < max(prevHeight - 1, 1); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 650)
        {
            for (int j = 0; j < min(prevHeight + 2, kTerrainNumberY); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 750)
        {
            for (int j = 0; j < max(prevHeight - 2, 1); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 800)
        {
            for (int j = 0; j < min(prevHeight + 3, kTerrainNumberY); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 850)
        {
            for (int j = 0; j < max(prevHeight - 3, 1); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 875)
        {
            for (int j = 0; j < min(prevHeight + 4, kTerrainNumberY); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 900)
        {
            for (int j = 0; j < max(prevHeight - 4, 1); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 925)
        {
            for (int j = 0; j < min(prevHeight + 5, kTerrainNumberY); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 950)
        {
            for (int j = 0; j < max(prevHeight - 5, 1); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 975)
        {
            for (int j = 0; j < min(prevHeight + 6, kTerrainNumberY); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        else if (decider < 1000)
        {
            for (int j = 0; j < max(prevHeight - 6, 1); j++)
            {
                terrain[i][j].isDestoried = true;
            }
        }
        prevHeight = 0;
        while (terrain[i][prevHeight].isDestoried)
            prevHeight++;
    }
    // 随机山洞
    int numOfHole = rand() % (kMaxHoleNumber - 1) + 2;
    for (int i = 0; i <= numOfHole; i++)
    {
        int radius      = rand() % (kMaxHoleRadius) + 2;
        int holeCenterX = rand() % kTerrainNumberX;
        int holeCenterY = rand() % kTerrainNumberY;
        for (int j = 0; j < kTerrainNumberX; j++)
            for (int k = 0; k < kTerrainNumberY; k++)
                if ((j - holeCenterX) * (j - holeCenterX) + (k - holeCenterY) * (k - holeCenterY) <= radius * radius)
                    terrain[j][k].isDestoried = true;
    }
}
/*
██████  ███████ ███    ██ ██████  ███████ ██████
██   ██ ██      ████   ██ ██   ██ ██      ██   ██
██████  █████   ██ ██  ██ ██   ██ █████   ██████
██   ██ ██      ██  ██ ██ ██   ██ ██      ██   ██
██   ██ ███████ ██   ████ ██████  ███████ ██   ██
*/

void render(HWND hWnd)
{
    switch (gameStatus.status)
    {
    case Game_start:    // 游戏准备开始，主界面
        renderStart(hWnd);
        break;
    case Game_running:    // 游戏正在进行
        renderGame(hWnd);
        break;
    case Game_end:    // 游戏结束界面
        renderEnd(hWnd);
        break;
    case Game_pause:
        renderPause(hWnd);    // 游戏暂停界面
        break;
    default:
        break;
    }
}
/*
██████  ███████ ███    ██ ██████  ███████ ██████  ███████ ████████  █████  ██████  ████████
██   ██ ██      ████   ██ ██   ██ ██      ██   ██ ██         ██    ██   ██ ██   ██    ██
██████  █████   ██ ██  ██ ██   ██ █████   ██████  ███████    ██    ███████ ██████     ██
██   ██ ██      ██  ██ ██ ██   ██ ██      ██   ██      ██    ██    ██   ██ ██   ██    ██
██   ██ ███████ ██   ████ ██████  ███████ ██   ██ ███████    ██    ██   ██ ██   ██    ██
*/

void renderStart(HWND hWnd)
{
    // 开始界面绘制
    PAINTSTRUCT ps;
    HDC         hdc;

    // 开始绘制
    hdc = BeginPaint(hWnd, &ps);
    HDC     hdcBmp, hdcBuffer;
    HBITMAP cptBmp;
    cptBmp    = CreateCompatibleBitmap(hdc, kWindowWidth, kWindowHeight);
    hdcBmp    = CreateCompatibleDC(hdc);
    hdcBuffer = CreateCompatibleDC(hdc);

    // 绘制背景到缓冲区
    SelectObject(hdcBuffer, cptBmp);
    SelectObject(hdcBmp, gameStatus.hPicture);
    BitBlt(hdcBuffer, 0, 0, kWindowWidth, kWindowHeight, hdcBmp, 0, 0, SRCCOPY);

    // 绘制开始游戏按钮
    SelectObject(hdcBmp, gameStartButton.hPicture);
    TransparentBlt(hdcBuffer, gameStartButton.position.x, gameStartButton.position.y, gameStartButton.size.x, gameStartButton.size.y, hdcBmp, 0, 0, gameStartButton.size.x, gameStartButton.size.y, RGB(0, 0, 0));

    // 绘制到屏幕
    BitBlt(hdc, 0, 0, kWindowWidth, kWindowHeight, hdcBuffer, 0, 0, SRCCOPY);

    // 释放资源
    DeleteObject(cptBmp);
    DeleteDC(hdcBuffer);
    DeleteDC(hdcBmp);

    // 结束绘制
    EndPaint(hWnd, &ps);
}
/*
██████  ███████ ███    ██ ██████  ███████ ██████   ██████   █████  ███    ███ ███████
██   ██ ██      ████   ██ ██   ██ ██      ██   ██ ██       ██   ██ ████  ████ ██
██████  █████   ██ ██  ██ ██   ██ █████   ██████  ██   ███ ███████ ██ ████ ██ █████
██   ██ ██      ██  ██ ██ ██   ██ ██      ██   ██ ██    ██ ██   ██ ██  ██  ██ ██
██   ██ ███████ ██   ████ ██████  ███████ ██   ██  ██████  ██   ██ ██      ██ ███████
*/

void renderGame(HWND hWnd)
{
    // 游戏界面绘制
	HDC hdc_RenderGameOnly;
    PAINTSTRUCT ps;

    // 开始绘制
    hdc_RenderGameOnly = BeginPaint(hWnd, &ps);

    HDC     hdcBmp, hdcBuffer;   
    HBITMAP cptBmp;


    cptBmp    = CreateCompatibleBitmap(hdc_RenderGameOnly, kWorldWidth, kWorldHeight);
    hdcBmp    = CreateCompatibleDC(hdc_RenderGameOnly);
    hdcBuffer = CreateCompatibleDC(hdc_RenderGameOnly);

    // 绘制背景图片至缓冲区

    SelectObject(hdcBuffer, cptBmp);
    SelectObject(hdcBmp, gameStatus.hPicture);
    TransparentBlt(hdcBuffer, 0, 0, kWorldWidth, kWorldHeight, hdcBmp, 0, 0, kWindowWidth, kWindowHeight, RGB(255, 0, 0));


    // 绘制所有的地块，实心矩形
    //if (gTerrainNeedUpdate)
    {
        SelectObject(hdcBmp, hTerrainPicture);
        for (int i = 0; i < kTerrainNumberX; i++)
            for (int j = 0; j < kTerrainNumberY; j++)
            {
                TransparentBlt(hdcBuffer, terrain[i][j].position.left, terrain[i][j].position.top, kTerrainWidth, kTerrainHeight, hdcBmp, 18 * (terrain[i][j].picturePosition.x - 1), 18 * (terrain[i][j].picturePosition.y - 1), 16, 16, RGB(255, 255, 255));
            }
        gTerrainNeedUpdate = false;
        
    }
    
	//BitBlt(hdc_RenderGameOnly, 0, 0, kWindowWidth, kWindowHeight, hdcBuffer, gCameraX, gCameraY, SRCCOPY);


    // 阵营血量显示
    HBRUSH factionHPBarBrush;
    int    factionHPBarWidth;

    factionHPBarBrush = CreateSolidBrush(Color_Faction_1);
    SelectObject(hdcBuffer, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[0].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdcBuffer, 1 * kFactionHPBarDistance + 0 * kFactionHPBarWidth, kFactionHPBarDistance, 1 * kFactionHPBarDistance + 0 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    factionHPBarBrush = CreateSolidBrush(Color_Faction_2);
    SelectObject(hdcBuffer, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[1].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdcBuffer, 3 * kFactionHPBarDistance + 1 * kFactionHPBarWidth, kFactionHPBarDistance, 3 * kFactionHPBarDistance + 1 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    factionHPBarBrush = CreateSolidBrush(Color_Faction_3);
    SelectObject(hdcBuffer, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[2].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdcBuffer, 5 * kFactionHPBarDistance + 2 * kFactionHPBarWidth, kFactionHPBarDistance, 5 * kFactionHPBarDistance + 2 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    factionHPBarBrush = CreateSolidBrush(Color_Faction_4);
    SelectObject(hdcBuffer, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[3].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdcBuffer, 7 * kFactionHPBarDistance + 3 * kFactionHPBarWidth, kFactionHPBarDistance, 7 * kFactionHPBarDistance + 3 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    // 绘制箱子
    for (int i = 0; i < kMaxMedicalBoxNum; i++)
    {
        if (!gMedicalBox[i].picked)
        {
            SelectObject(hdcBmp, gMedicalBox[i].hPicture);
            TransparentBlt(hdcBuffer, gMedicalBox[i].position.x, gMedicalBox[i].position.y, kMedicalBoxSizeX, kMedicalBoxSizeY, hdcBmp, 0, 0, kMedicalBoxPictureX, kMedicalBoxPictureY, RGB(255, 255, 255));
        }
    }
    for (int i = 0; i < kMaxWeaponBoxNum; i++)
    {
        if (!gWeaponBox[i].picked)
        {
            SelectObject(hdcBmp, gWeaponBox[i].hPicture);
            TransparentBlt(hdcBuffer, gWeaponBox[i].position.x, gWeaponBox[i].position.y, kWeaponBoxSizeX, kWeaponBoxSizeY, hdcBmp, 0, 0, kWeaponBoxPictureX, kWeaponBoxPictureY, RGB(255, 255, 255));
        }
    }
    for (int i = 0; i < kMaxSkillBoxNum; i++)
    {
        if (!gSkillBox[i].picked)
        {
            SelectObject(hdcBmp, gSkillBox[i].hPicture);
            TransparentBlt(hdcBuffer, gSkillBox[i].position.x, gSkillBox[i].position.y, kSkillBoxSizeX, kSkillBoxSizeY, hdcBmp, 0, 0, kSkillBoxPictureX, kSkillBoxPictureY, RGB(255, 255, 255));
        }
    }

    // 绘制血条
    for (int i = 0; i < gFactionNumber; i++)
        for (int j = 0; j < gRobotNumberPerFaction; j++)
        {
            if (faction[i].robot[j].alive)
            {
                // 确定血条颜色
                COLORREF HPBarColor;
                if (faction[i].robot[j].hitPoint > 750)
                    HPBarColor = HPBar_1000;
                else if (faction[i].robot[j].hitPoint > 500)
                    HPBarColor = HPBar_0750;
                else if (faction[i].robot[j].hitPoint > 250)
                    HPBarColor = HPBar_0500;
                else if (faction[i].robot[j].hitPoint > 0)
                    HPBarColor = HPBar_0250;
                else
                    HPBarColor = HPBar_0000;

                for (int k = faction[i].robot[j].position.x; k < faction[i].robot[j].position.x + kHitPointBarWidth; k++)
                {
                    SetPixel(hdcBuffer, k, faction[i].robot[j].position.y - kHitPointBarDistance - kHitPointBarHeigth, HPBarColor);
                    SetPixel(hdcBuffer, k, faction[i].robot[j].position.y - kHitPointBarDistance, HPBarColor);
                }
                for (int k = faction[i].robot[j].position.y - kHitPointBarDistance; k >= faction[i].robot[j].position.y - kHitPointBarDistance - kHitPointBarHeigth; k--)
                {
                    SetPixel(hdcBuffer, faction[i].robot[j].position.x, k, HPBarColor);
                    SetPixel(hdcBuffer, faction[i].robot[j].position.x + kHitPointBarWidth, k, HPBarColor);
                }
                int    width      = (kHitPointBarWidth)*faction[i].robot[j].hitPoint / kRobotFullHitPoint;
                HBRUSH HPBarBrush = CreateSolidBrush(HPBarColor);
                SelectObject(hdcBuffer, HPBarBrush);
                Rectangle(hdcBuffer, faction[i].robot[j].position.x, faction[i].robot[j].position.y - kHitPointBarDistance - kHitPointBarHeigth + 1, faction[i].robot[j].position.x + width + 2, faction[i].robot[j].position.y - kHitPointBarDistance + 1);
                DeleteObject(HPBarBrush);
            }
        }

    // 绘制指示器
    COLORREF activeColor;
    switch (gFactionControlled)
    {
    case 0:
        activeColor = Color_Faction_1;
        break;
    case 1:
        activeColor = Color_Faction_2;
        break;
    case 2:
        activeColor = Color_Faction_3;
        break;
    case 3:
        activeColor = Color_Faction_4;
        break;
    default:
        break;
    }
    HPEN activePen = CreatePen(PS_DOT, 5, activeColor);
    SelectObject(hdcBuffer, activePen);
    MoveToEx(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x + kRobotSizeX / 2, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2 - 2 * kRobotControlSignHeight, NULL);
    LineTo(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x + kRobotSizeX / 2, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2 - kRobotControlSignHeight);
    DeleteObject(activePen);

    // 绘制所有机器人
    for (int i = 0; i < gFactionNumber; i++)
        for (int j = 0; j < gRobotNumberPerFaction; j++)
        {
            if (faction[i].robot[j].alive)
            {
                SelectObject(hdcBmp, faction[i].robot[j].hPicture);
                TransparentBlt(hdcBuffer, faction[i].robot[j].position.x, faction[i].robot[j].position.y, kRobotSizeX, kRobotSizeY, hdcBmp, 0, faction[i].robot[j].currentFrameNum * kRobotPictureY, kRobotPictureX, kRobotPictureY, RGB(255, 255, 255));
            }
        }

    // 绘制武器角度和力度的改变
    if (gRobotWeaponOn && gWeaponSelected)
    {
        SelectObject(hdcBmp, hAimPicture);
        TransparentBlt(hdcBuffer, int((faction[gFactionControlled].robot[gRobotControlled].position.x + kRobotSizeX / 2) + kAimDistance * cos(gLaunchingAngle) - kAimUIWidth / 2), int((faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2) - kAimDistance * sin(gLaunchingAngle) - kAimUIHeight / 2), kAimUIWidth, kAimUIHeight, hdcBmp, 0, 0, kAimPictureX, kAimPictureY, RGB(255, 255, 255));
    }
    if (gIncreasingWeaponPower && gWeaponSelected)
    {
        HPEN weaponPowerPen;
        weaponPowerPen = CreatePen(PS_DOT, 15, RGB(50, 200, 50));
        SelectObject(hdcBuffer, weaponPowerPen);
        MoveToEx(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x + kRobotSizeX / 2, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2, NULL);
        LineTo(hdcBuffer, int(faction[gFactionControlled].robot[gRobotControlled].position.x + kRobotSizeX / 2 + (kAimDistance * cos(gLaunchingAngle) * gPower / 100)), int(faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2 - (kAimDistance * sin(gLaunchingAngle) * gPower / 100)));
        DeleteObject(weaponPowerPen);
    }

    // 绘制武器
    if (gMissileActivated)
    {
        SelectObject(hdcBmp, gMissile.hPicture);
        if ((gMissile.hPicture == hMissilePictureLeft) || (gMissile.hPicture == hMissilePictureRight))
            TransparentBlt(hdcBuffer, gMissile.position.x, gMissile.position.y, kMissileSizeX, kMissileSizeY, hdcBmp, 0, 0, kMissilePictureX, kMissilePictureY, RGB(255, 255, 255));
        else
            TransparentBlt(hdcBuffer, gMissile.position.x, gMissile.position.y, kMissileSizeY, kMissileSizeX, hdcBmp, 0, 0, kMissilePictureY, kMissilePictureX, RGB(255, 255, 255));
    }
    if (gGrenadeActivated)
    {
        SelectObject(hdcBmp, gGrenade.hPicture);
        TransparentBlt(hdcBuffer, gGrenade.position.x, gGrenade.position.y, kGrenadeSizeX, kGrenadeSizeY, hdcBmp, 0, 0, kGrenadePictureX, kGrenadePictureY, RGB(255, 255, 255));
    }
    if (gStickyBombActivated)
    {
        SelectObject(hdcBmp, gStickyBomb.hPicture);
        TransparentBlt(hdcBuffer, gStickyBomb.position.x, gStickyBomb.position.y, kStickyBombSizeX, kStickyBombSizeY, hdcBmp, 0, 0, kStickyBombPictureX, kStickyBombPictureY, RGB(255, 255, 255));
    }
    if (gTNTActivated)
    {
        SelectObject(hdcBmp, gTNT.hPicture);
        TransparentBlt(hdcBuffer, gTNT.position.x, gTNT.position.y, kTNTSizeX, kTNTSizeY, hdcBmp, 0, 0, kTNTPictureX, kTNTPictureY, RGB(255, 255, 255));
    }

    // 绘制技能的选择对象界面
    //if (gRobotSkillOn && (gSkillTargetRobot))

    // 绘制海洋
    SelectObject(hdcBuffer, GetStockObject(NULL_PEN));    // 选择笔刷。但是这句话没懂
    HBRUSH seaBrush;                                      // 建立了一个笔刷的句柄
    seaBrush = CreateSolidBrush(Color_Sea);               // 指定笔刷的属性和颜色
    SelectObject(hdcBuffer, seaBrush);                    // 选择笔刷
    drawClosedRectangle(hdcBuffer, 0, gSeaLevel, kWorldWidth, kWorldHeight);
    DeleteObject(seaBrush);    // 释放资源


    // 绘制比分
    TCHAR szDist[1000] = L"";                                                                                                                                                                               // 目测是比分字符串
    SetTextColor(hdcBuffer, RGB(255, 255, 255));                                                                                                                                                            // 设置颜色
    SetBkMode(hdcBuffer, TRANSPARENT);                                                                                                                                                                      // 目测是字符串背景属性，设成透明
    wsprintf(szDist, L"%d %d %d %d", faction[gFactionControlled].ammoMissile, faction[gFactionControlled].ammoGrenade, faction[gFactionControlled].ammoStickyBomb, faction[gFactionControlled].ammoTNT);    // 猜测是把一个字符串赋给前面
    TextOut(hdcBuffer, kWindowWidth - 500, 15, szDist, _tcslen(szDist));
    wsprintf(szDist, L"weapon %d   skill %d", faction[gFactionControlled].robot[gRobotControlled].weapon, faction[gFactionControlled].robot[gRobotControlled].skill);
    TextOut(hdcBuffer, kWindowWidth - 500, 25, szDist, _tcslen(szDist));


    // 绘制到屏幕
    //BitBlt(hdc_RenderGameOnly, gCameraX, gCameraY, kWindowWidth, kWindowHeight, hdcBuffer, gCameraX, gCameraY, SRCCOPY);
    //BitBlt(hdc_RenderGameOnly, 0, 0, kWindowWidth, kWindowHeight, hdcBackground, 0, 0, SRCCOPY);
    BitBlt(hdc_RenderGameOnly, 0, 0, kWindowWidth, kWindowHeight, hdcBuffer, gCameraX, gCameraY, SRCCOPY);


    // 释放资源
    DeleteObject(cptBmp);
    DeleteDC(hdcBuffer);
    DeleteDC(hdcBmp);
    //DeleteDC(hdcBackground);

    // 结束绘制
    EndPaint(hWnd, &ps);
}
/*
██████  ███████ ███    ██ ██████  ███████ ██████  ███████ ███    ██ ██████
██   ██ ██      ████   ██ ██   ██ ██      ██   ██ ██      ████   ██ ██   ██
██████  █████   ██ ██  ██ ██   ██ █████   ██████  █████   ██ ██  ██ ██   ██
██   ██ ██      ██  ██ ██ ██   ██ ██      ██   ██ ██      ██  ██ ██ ██   ██
██   ██ ███████ ██   ████ ██████  ███████ ██   ██ ███████ ██   ████ ██████
*/

void renderEnd(HWND hWnd)
{
    // 结束界面绘制
    PAINTSTRUCT ps;
    HDC         hdc;

    // 开始绘制
    hdc = BeginPaint(hWnd, &ps);
    HDC     hdcBmp, hdcBuffer;
    HBITMAP cptBmp;
    cptBmp    = CreateCompatibleBitmap(hdc, kWindowWidth, kWindowHeight);
    hdcBmp    = CreateCompatibleDC(hdc);
    hdcBuffer = CreateCompatibleDC(hdc);

    // 绘制背景到缓冲区
    SelectObject(hdcBuffer, cptBmp);
    SelectObject(hdcBmp, gameStatus.hPicture);
    BitBlt(hdcBuffer, 0, 0, kWindowWidth, kWindowHeight, hdcBmp, 0, 0, SRCCOPY);

    // 绘制结束信息
    TCHAR szDist[1000] = L"";
    SetTextColor(hdcBuffer, RGB(255, 255, 255));
    SetBkMode(hdcBuffer, TRANSPARENT);
    wsprintf(szDist, L"Game over !");
    TextOut(hdcBuffer, kWindowWidth / 2, kWindowHeight / 3, szDist, _tcslen(szDist));
    wsprintf(szDist, L"The winner is Team %d .", gFactionAlive);
    TextOut(hdcBuffer, kWindowWidth / 2, 2 * kWindowWidth / 3, szDist, _tcslen(szDist));

    // 绘制到屏幕
    BitBlt(hdc, 0, 0, kWindowWidth, kWindowHeight, hdcBuffer, 0, 0, SRCCOPY);

    // 释放资源
    DeleteObject(cptBmp);
    DeleteDC(hdcBuffer);
    DeleteDC(hdcBmp);

    // 结束绘制
    EndPaint(hWnd, &ps);
}
/*
██████  ███████ ███    ██ ██████  ███████ ██████  ██████   █████  ██    ██ ███████ ███████
██   ██ ██      ████   ██ ██   ██ ██      ██   ██ ██   ██ ██   ██ ██    ██ ██      ██
██████  █████   ██ ██  ██ ██   ██ █████   ██████  ██████  ███████ ██    ██ ███████ █████
██   ██ ██      ██  ██ ██ ██   ██ ██      ██   ██ ██      ██   ██ ██    ██      ██ ██
██   ██ ███████ ██   ████ ██████  ███████ ██   ██ ██      ██   ██  ██████  ███████ ███████
*/

void renderPause(HWND hWnd)
{
    // 暂停界面绘制
    PAINTSTRUCT ps;
    HDC         hdc;

    // 开始绘制
    hdc = BeginPaint(hWnd, &ps);
    HDC     hdcBmp, hdcBuffer;
    HBITMAP cptBmp;
    cptBmp    = CreateCompatibleBitmap(hdc, kWindowWidth, kWindowHeight);
    hdcBmp    = CreateCompatibleDC(hdc);
    hdcBuffer = CreateCompatibleDC(hdc);

    // 绘制背景到缓冲区
    SelectObject(hdcBuffer, cptBmp);
    SelectObject(hdcBmp, gameStatus.hPicture);
    BitBlt(hdcBuffer, 0, 0, kWindowWidth, kWindowHeight, hdcBmp, 0, 0, SRCCOPY);

    RECT       rect;
    TEXTMETRIC tm;
    GetTextMetrics(ps.hdc, &tm);
    rect.top    = kWindowHeight / 2 - 1.5 * tm.tmHeight;
    rect.left   = 0;
    rect.right  = kWindowWidth;
    rect.bottom = rect.top + 3 * tm.tmHeight;
    SetTextColor(hdcBuffer, RGB(255, 255, 255));
    SetBkMode(hdcBuffer, TRANSPARENT);
    DrawTextW(hdcBuffer, L"游戏已暂停\n\n请按P键继续游戏", -1, &rect, DT_CENTER);

    // 绘制到屏幕
    BitBlt(hdc, 0, 0, kWindowWidth, kWindowHeight, hdcBuffer, 0, 0, SRCCOPY);

    // 释放资源
    DeleteObject(cptBmp);
    DeleteDC(hdcBuffer);
    DeleteDC(hdcBmp);

    // 结束绘制
    EndPaint(hWnd, &ps);
}

/*
████████ ██ ███    ███ ███████ ██████  ██    ██ ██████  ██████   █████  ████████ ███████
   ██    ██ ████  ████ ██      ██   ██ ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
   ██    ██ ██ ████ ██ █████   ██████  ██    ██ ██████  ██   ██ ███████    ██    █████
   ██    ██ ██  ██  ██ ██      ██   ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
   ██    ██ ██      ██ ███████ ██   ██  ██████  ██      ██████  ██   ██    ██    ███████
*/

void timerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 计时器更新函数
    if (gameStatus.status == Game_running)
    {
        robotUpdate();    // 更新所有机器人状态
        factionUpdate();
        windUpdate();
        weaponUpdate();
        terrainUpdate();    // 更新所有地块状态
        seaLevelUpdate();
        medicalBoxUpdate();
        weaponBoxUpdate();
        skillBoxUpdate();
    }
    gameStatusUpdate();    // 更新游戏状态，应该是判断游戏是否结束或移交控制权之类
    if (gameStatus.status == Game_end)
        KillTimer(hWnd, kTimerID);
    InvalidateRect(hWnd, NULL, FALSE);    // 该函数向指定的窗体更新区域添加一个矩形，然后窗口客户区域的这一部分将被重新绘制。
}
/*
██████   ██████  ██████   ██████  ████████ ██    ██ ██████  ██████   █████  ████████ ███████
██   ██ ██    ██ ██   ██ ██    ██    ██    ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
██████  ██    ██ ██████  ██    ██    ██    ██    ██ ██████  ██   ██ ███████    ██    █████
██   ██ ██    ██ ██   ██ ██    ██    ██    ██    ██ ██      ██   ██ ██   ██    ██    ██
██   ██  ██████  ██████   ██████     ██     ██████  ██      ██████  ██   ██    ██    ███████
*/

void robotUpdate(void)
{
    for (int i = 0; i < gFactionNumber; i++)
    {
        for (int j = 0; j < gRobotNumberPerFaction; j++)

        {
            // 更新血量使其正常显示
            if ((faction[i].robot[j].hitPoint <= 0) && (faction[i].robot[j].alive))    // hp小于等于零判定死亡
            {
                faction[i].robot[j].alive    = false;    // 注 加医疗包的时候只能给hp大于零的单位加
                faction[i].robot[j].hitPoint = 0;
                faction[i].aliveRobot--;
            }

            if ((faction[i].robot[j].position.y > gSeaLevel) && (faction[i].robot[j].alive))    // 低于海平面判定死亡
            {
                faction[i].robot[j].alive    = false;
                faction[i].robot[j].hitPoint = 0;
                faction[i].aliveRobot--;
            }


            if (faction[i].robot[j].alive)
            {
                if (faction[gFactionControlled].robot[gRobotControlled].protectiveShellTime > 0)
                {
                    // TODO
                    // 机器人护甲时间递减
                }


                if ((faction[i].robot[j].direction == kFacingLeft) && (faction[i].robot[j].velocity.x > 0))
                {
                    faction[i].robot[j].hPicture  = hRobotPicture[i + gFactionNumber];
                    faction[i].robot[j].direction = kFacingRight;
                }
                else if ((faction[i].robot[j].direction == kFacingRight) && (faction[i].robot[j].velocity.x < 0))
                {
                    faction[i].robot[j].hPicture  = hRobotPicture[i];
                    faction[i].robot[j].direction = kFacingLeft;
                }

                // 计算被加速度更新后的速度
                faction[i].robot[j].velocity.x += faction[i].robot[j].acceleration.x;
                faction[i].robot[j].velocity.y += faction[i].robot[j].acceleration.y;

                // 计算预计的位置值
                int estimatedPositionX = faction[i].robot[j].position.x + faction[i].robot[j].velocity.x;
                int estimatedPositionY = faction[i].robot[j].position.y + faction[i].robot[j].velocity.y;

                // 当机器人没有碰到地块时就一直运动
                BOOL estimatedPositionXReached = (estimatedPositionX == faction[i].robot[j].position.x);
                BOOL estimatedPositionYReached = (estimatedPositionY == faction[i].robot[j].position.y);

                // 注 写的时候把冒号前后的东西写反了导致出现Bug
                while (!robotInTerrain(i, j) && (!estimatedPositionXReached || !estimatedPositionYReached))
                {
                    if (!estimatedPositionXReached)
                    {
                        faction[i].robot[j].position.x += (faction[i].robot[j].velocity.x) ? ((faction[i].robot[j].velocity.x) / (abs(faction[i].robot[j].velocity.x))) : 0;
                        faction[i].robot[j].frameCounter = (faction[i].robot[j].frameCounter + 1) % (kFrameSwitchFrequency + 1);
                        if (faction[i].robot[j].frameCounter == kFrameSwitchFrequency)
                        {
                            faction[i].robot[j].currentFrameNum = (faction[i].robot[j].velocity.x) ? ((faction[i].robot[j].currentFrameNum + 1) % kMaxRobotFrameNum) : (faction[i].robot[j].currentFrameNum);
                        }
                        estimatedPositionXReached = (estimatedPositionX == faction[i].robot[j].position.x);
                        if (robotInTerrain(i, j))
                        {
                            faction[i].robot[j].position.x -= (faction[i].robot[j].velocity.x) ? ((faction[i].robot[j].velocity.x) / (abs(faction[i].robot[j].velocity.x))) : 0;
                            estimatedPositionXReached           = true;
                            estimatedPositionYReached           = true;
                            faction[i].robot[j].velocity.x      = 0;
                            faction[i].robot[j].acceleration.x  = 0;
                            faction[i].robot[j].velocity.y      = 0;
                            faction[i].robot[j].acceleration.y  = 0;
                            faction[i].robot[j].currentFrameNum = kRobotStopPictureIndex;
                            if (robotLanded(i, j))
                                faction[i].robot[j].isJumping = false;
                        }
                    }
                    if (!estimatedPositionYReached)
                    {
                        faction[i].robot[j].position.y += (faction[i].robot[j].velocity.y) ? ((faction[i].robot[j].velocity.y) / (abs(faction[i].robot[j].velocity.y))) : 0;
                        //faction[i].robot[j].currentFrameNum = (faction[i].robot[j].velocity.y) ? ((faction[i].robot[j].currentFrameNum + 1) % kMaxRobotFrameNum) : (faction[i].robot[j].currentFrameNum);
                        estimatedPositionYReached = (estimatedPositionY == faction[i].robot[j].position.y);
                        if (robotInTerrain(i, j))
                        {
                            faction[i].robot[j].position.y -= (faction[i].robot[j].velocity.y) ? ((faction[i].robot[j].velocity.y) / (abs(faction[i].robot[j].velocity.y))) : 0;
                            estimatedPositionXReached           = true;
                            estimatedPositionYReached           = true;
                            faction[i].robot[j].velocity.x      = 0;
                            faction[i].robot[j].acceleration.x  = 0;
                            faction[i].robot[j].velocity.y      = 0;
                            faction[i].robot[j].acceleration.y  = 0;
                            faction[i].robot[j].currentFrameNum = kRobotStopPictureIndex;
                            if (robotLanded(i, j))
                                faction[i].robot[j].isJumping = false;
                        }
                    }
                }

                if (!robotInTerrain(i, j) && !robotLanded(i, j))
                {
                    faction[i].robot[j].acceleration.y = kGravityAcceleration;
                }
            }
            gWeaponSelected = faction[gFactionControlled].robot[gRobotControlled].weapon;
        }
        if ((faction[i].alive) && (faction[i].aliveRobot <= 0))
            faction[i].alive = false;
    }
    // 自动切换到下一人物，如果不可行，就切换到下一阵营
    if (!faction[gFactionControlled].alive)
    {
        do
        {
            gFactionControlled++;
            if (gFactionControlled >= gFactionNumber)
                gFactionControlled = 0;
        } while (!faction[gFactionControlled].alive);
        gRobotControlled = 0;
        gRobotWeaponOn   = false;
    }
    else
    {
        if (!faction[gFactionControlled].robot[gRobotControlled].alive)
        {
            do
            {
                gRobotControlled++;
                if (gRobotControlled >= gRobotNumberPerFaction)
                    gRobotControlled = 0;
            } while (!faction[gFactionControlled].robot[gRobotControlled].alive);
            gRobotWeaponOn = false;
        }
    }
}
/*
███████  █████   ██████ ████████ ██  ██████  ███    ██ ██    ██ ██████  ██████   █████  ████████ ███████
██      ██   ██ ██         ██    ██ ██    ██ ████   ██ ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
█████   ███████ ██         ██    ██ ██    ██ ██ ██  ██ ██    ██ ██████  ██   ██ ███████    ██    █████
██      ██   ██ ██         ██    ██ ██    ██ ██  ██ ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
██      ██   ██  ██████    ██    ██  ██████  ██   ████  ██████  ██      ██████  ██   ██    ██    ███████
*/

void factionUpdate(void)
{
    for (int i = 0; i < gFactionNumber; i++)
    {
        if (faction[i].alive)
        {
            faction[i].alive = false;
            for (int j = 0; j < gRobotNumberPerFaction; j++)
            {
                if (faction[i].robot[j].alive)
                    faction[i].alive = true;
            }
        }
        if (faction[i].alive)
        {
            faction[i].hitPoint = 0;
            for (int j = 0; j < gRobotNumberPerFaction; j++)
                faction[i].hitPoint += faction[i].robot[j].hitPoint;
            gFactionAlive = i;
        }
        else
        {
            faction[i].hitPoint = 0;
        }
    }
}
/*
██     ██ ██ ███    ██ ██████  ██    ██ ██████  ██████   █████  ████████ ███████
██     ██ ██ ████   ██ ██   ██ ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
██  █  ██ ██ ██ ██  ██ ██   ██ ██    ██ ██████  ██   ██ ███████    ██    █████
██ ███ ██ ██ ██  ██ ██ ██   ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
 ███ ███  ██ ██   ████ ██████   ██████  ██      ██████  ██   ██    ██    ███████
*/

void windUpdate(void)
{
    gWindPower = rand() % (2 * kWindPowerRange + 1) - kWindPowerRange;
}

/*
██████   ██████  ██████   ██████  ████████ ██ ███    ██ ████████ ███████ ██████  ██████   █████  ██ ███    ██
██   ██ ██    ██ ██   ██ ██    ██    ██    ██ ████   ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██
██████  ██    ██ ██████  ██    ██    ██    ██ ██ ██  ██    ██    █████   ██████  ██████  ███████ ██ ██ ██  ██
██   ██ ██    ██ ██   ██ ██    ██    ██    ██ ██  ██ ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██
██   ██  ██████  ██████   ██████     ██    ██ ██   ████    ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████
*/

BOOL robotInTerrain(int factionNum, int robotNum)
{
    // 计算覆盖的terrain所占区域
    int left = ((faction[factionNum].robot[robotNum].position.x + kRobotEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;
    int top  = ((faction[factionNum].robot[robotNum].position.y + kRobotEdgeIngnorance) / kTerrainHeight) * kTerrainHeight + 1;

    int right, bottom;

    if ((faction[factionNum].robot[robotNum].position.x + kRobotSizeX - kRobotEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = faction[factionNum].robot[robotNum].position.x + kRobotSizeX - kRobotEdgeIngnorance;
    }
    else
    {
        right = ((faction[factionNum].robot[robotNum].position.x + kRobotSizeX - kRobotEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((faction[factionNum].robot[robotNum].position.y + kRobotSizeY - kRobotEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = faction[factionNum].robot[robotNum].position.y + kRobotSizeY - kRobotEdgeIngnorance;
    }
    else
    {
        bottom = ((faction[factionNum].robot[robotNum].position.y + kRobotSizeY - kRobotEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    // 计算terrain坐标
    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int topTerrainCoordinate    = (top - 1) / kTerrainHeight;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;

    // 检查这些terrain中是否有未被摧毁的
    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        for (int j = topTerrainCoordinate; j <= bottomTerrainCoordinate; j++)
            if (!terrain[i][j].isDestoried)
                return true;
    return false;
}
/*
██████   ██████  ██████   ██████  ████████ ██       █████  ███    ██ ██████  ███████ ██████
██   ██ ██    ██ ██   ██ ██    ██    ██    ██      ██   ██ ████   ██ ██   ██ ██      ██   ██
██████  ██    ██ ██████  ██    ██    ██    ██      ███████ ██ ██  ██ ██   ██ █████   ██   ██
██   ██ ██    ██ ██   ██ ██    ██    ██    ██      ██   ██ ██  ██ ██ ██   ██ ██      ██   ██
██   ██  ██████  ██████   ██████     ██    ███████ ██   ██ ██   ████ ██████  ███████ ██████
*/

BOOL robotLanded(int factionNum, int robotNum)
{
    // return true;
    // 假定robot是不在地形里面的
    // 脚不在地上
    if ((faction[factionNum].robot[robotNum].position.y + kRobotSizeY - kRobotEdgeIngnorance) % kTerrainHeight != 0)
        return false;

    // 仿照上面的函数，这次判定人物下面有没有未被摧毁的地块
    int left = ((faction[factionNum].robot[robotNum].position.x + kRobotEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;

    int right, bottom;

    if ((faction[factionNum].robot[robotNum].position.x + kRobotSizeX - kRobotEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = faction[factionNum].robot[robotNum].position.x + kRobotSizeX - kRobotEdgeIngnorance;
    }
    else
    {
        right = ((faction[factionNum].robot[robotNum].position.x + kRobotSizeX - kRobotEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((faction[factionNum].robot[robotNum].position.y + kRobotSizeY - kRobotEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = faction[factionNum].robot[robotNum].position.y + kRobotSizeY - kRobotEdgeIngnorance;
    }
    else
    {
        bottom = ((faction[factionNum].robot[robotNum].position.y + kRobotSizeY - kRobotEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;


    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        if (!terrain[i][bottomTerrainCoordinate + 1].isDestoried)
            return true;
    return false;
}
/*
██     ██ ███████  █████  ██████   ██████  ███    ██ ██    ██ ██████  ██████   █████  ████████ ███████
██     ██ ██      ██   ██ ██   ██ ██    ██ ████   ██ ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
██  █  ██ █████   ███████ ██████  ██    ██ ██ ██  ██ ██    ██ ██████  ██   ██ ███████    ██    █████
██ ███ ██ ██      ██   ██ ██      ██    ██ ██  ██ ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
 ███ ███  ███████ ██   ██ ██       ██████  ██   ████  ██████  ██      ██████  ██   ██    ██    ███████
*/

void weaponUpdate(void)    // 发射武器前更新角度和力度，发射武器后更新武器的速度，位置和附加数值
{
    // 更新角度力度
    if (gRobotWeaponOn)
    {
        if (gChangingWeaponAngle == 1)
        {
            gLaunchingAngle += kAngelChangingVelocity / Pi;
        }
        else if (gChangingWeaponAngle == -1)
            gLaunchingAngle -= kAngelChangingVelocity / Pi;

        if (gIncreasingWeaponPower && (gPower <= 100))
            gPower++;
    }

    // 更新全局武器状态
    switch (gWeaponSelected)
    {
    case iNoWeapon:
        break;
    case iMissile:
        if (gMissileActivated)
        {
            gMissile.acceleration.x = gWindPower * kWindPowerFactor;

            gMissile.velocity.x += gMissile.acceleration.x;
            gMissile.velocity.y += gMissile.acceleration.y;

            gMissile.position.x += gMissile.velocity.x;
            gMissile.position.y += gMissile.velocity.y;
            // TODO
            if (abs(gMissile.velocity.x) >= abs(gMissile.velocity.y))
            {
                if (gMissile.velocity.x >= 0)
                {
                    gMissile.hPicture = hMissilePictureRight;
                }
                else
                {
                    gMissile.hPicture = hMissilePictureLeft;
                }
            }
            else
            {
                if (gMissile.velocity.y >= 0)
                {
                    gMissile.hPicture = hMissilePictureDown;
                }
                else
                {
                    gMissile.hPicture = hMissilePictureUp;
                }
            }
        }
        break;
    case iGrenade:    // 因为手雷需要有和机器人类似的碰撞特性，所以把代码搬过来
        if (gGrenadeActivated)
        {
            if (!gGrenade.locked)
                gGrenade.acceleration.x = gWindPower * kWindPowerFactor;

            // 更新速度
            gGrenade.velocity.x += gGrenade.acceleration.x;
            gGrenade.velocity.y += gGrenade.acceleration.y;

            // 计算预计位置值
            int estimatedPositionX = gGrenade.position.x + gGrenade.velocity.x;
            int estimatedPositionY = gGrenade.position.y + gGrenade.velocity.y;

            BOOL estimatedPositionXReached = (estimatedPositionX == gGrenade.position.x);
            BOOL estimatedPositionYReached = (estimatedPositionY == gGrenade.position.y);

            while (!grenadeInTerrain() && (!estimatedPositionXReached || !estimatedPositionYReached))
            {
                if (!estimatedPositionXReached)
                {
                    gGrenade.position.x += (gGrenade.velocity.x) ? ((gGrenade.velocity.x) / (abs(gGrenade.velocity.x))) : 0;
                    estimatedPositionXReached = (estimatedPositionX == gGrenade.position.x);
                    if (grenadeInTerrain())
                    {
                        gGrenade.position.x -= (gGrenade.velocity.x) ? ((gGrenade.velocity.x) / (abs(gGrenade.velocity.x))) : 0;
                        estimatedPositionXReached = true;
                        estimatedPositionYReached = true;
                        gGrenade.velocity.x       = 0;
                        gGrenade.acceleration.x   = 0;
                        gGrenade.velocity.y       = 0;
                        gGrenade.acceleration.y   = 0;
                        gGrenade.locked           = true;
                    }
                }
                if (!estimatedPositionYReached)
                {
                    gGrenade.position.y += (gGrenade.velocity.y) ? ((gGrenade.velocity.y) / (abs(gGrenade.velocity.y))) : 0;
                    estimatedPositionYReached = (estimatedPositionY == gGrenade.position.y);
                    if (grenadeInTerrain())
                    {
                        gGrenade.position.y -= (gGrenade.velocity.y) ? ((gGrenade.velocity.y) / (abs(gGrenade.velocity.y))) : 0;
                        estimatedPositionXReached = true;
                        estimatedPositionYReached = true;
                        gGrenade.velocity.x       = 0;
                        gGrenade.acceleration.x   = 0;
                        gGrenade.velocity.y       = 0;
                        gGrenade.acceleration.y   = 0;
                        gGrenade.locked           = true;
                    }
                }
            }
            if (!grenadeLanded() && !grenadeInTerrain())
                gGrenade.acceleration.y = kGravityAcceleration;

            // 减少手雷爆炸时间
            gGrenade.timeToExplode--;
        }
        break;
    case iStickyBomb:
        if (gStickyBombActivated)
        {
            if (!gStickyBomb.locked)
                gStickyBomb.acceleration.x = gWindPower * kWindPowerFactor;

            // 更新速度
            gStickyBomb.velocity.x += gStickyBomb.acceleration.x;
            gStickyBomb.velocity.y += gStickyBomb.acceleration.y;

            // 计算预计位置值
            int estimatedPositionX = gStickyBomb.position.x + gStickyBomb.velocity.x;
            int estimatedPositionY = gStickyBomb.position.y + gStickyBomb.velocity.y;

            BOOL estimatedPositionXReached = (estimatedPositionX == gStickyBomb.position.x);
            BOOL estimatedPositionYReached = (estimatedPositionY == gStickyBomb.position.y);

            while (!stickyBombInTerrain() && (!estimatedPositionXReached || !estimatedPositionYReached))
            {
                if (!estimatedPositionXReached)
                {
                    gStickyBomb.position.x += (gStickyBomb.velocity.x) ? ((gStickyBomb.velocity.x) / (abs(gStickyBomb.velocity.x))) : 0;
                    estimatedPositionXReached = (estimatedPositionX == gStickyBomb.position.x);
                    if (stickyBombInTerrain())
                    {
                        gStickyBomb.position.x -= (gStickyBomb.velocity.x) ? ((gStickyBomb.velocity.x) / (abs(gStickyBomb.velocity.x))) : 0;
                        estimatedPositionXReached  = true;
                        estimatedPositionYReached  = true;
                        gStickyBomb.velocity.x     = 0;
                        gStickyBomb.acceleration.x = 0;
                        gStickyBomb.velocity.y     = 0;
                        gStickyBomb.acceleration.y = 0;
                        gStickyBomb.locked         = true;
                    }
                }
                if (!estimatedPositionYReached)
                {
                    gStickyBomb.position.y += (gStickyBomb.velocity.y) ? ((gStickyBomb.velocity.y) / (abs(gStickyBomb.velocity.y))) : 0;
                    estimatedPositionYReached = (estimatedPositionY == gStickyBomb.position.y);
                    if (stickyBombInTerrain())
                    {
                        gStickyBomb.position.y -= (gStickyBomb.velocity.y) ? ((gStickyBomb.velocity.y) / (abs(gStickyBomb.velocity.y))) : 0;
                        estimatedPositionXReached  = true;
                        estimatedPositionYReached  = true;
                        gStickyBomb.velocity.x     = 0;
                        gStickyBomb.acceleration.x = 0;
                        gStickyBomb.velocity.y     = 0;
                        gStickyBomb.acceleration.y = 0;
                        gStickyBomb.locked         = true;
                    }
                }
            }
            gStickyBomb.timeToExplode--;
        }
        break;
    case iTNT:
        if (gTNTActivated)
        {
            if (!gTNT.locked)
                gTNT.acceleration.x = gWindPower * kWindPowerFactor;

            // 更新速度
            gTNT.velocity.x += gTNT.acceleration.x;
            gTNT.velocity.y += gTNT.acceleration.y;

            // 计算预计位置值
            int estimatedPositionX = gTNT.position.x + gTNT.velocity.x;
            int estimatedPositionY = gTNT.position.y + gTNT.velocity.y;

            BOOL estimatedPositionXReached = (estimatedPositionX == gTNT.position.x);
            BOOL estimatedPositionYReached = (estimatedPositionY == gTNT.position.y);

            while (!TNTInTerrain() && (!estimatedPositionXReached || !estimatedPositionYReached))
            {
                if (!estimatedPositionXReached)
                {
                    gTNT.position.x += (gTNT.velocity.x) ? ((gTNT.velocity.x) / (abs(gTNT.velocity.x))) : 0;
                    estimatedPositionXReached = (estimatedPositionX == gTNT.position.x);
                    if (TNTInTerrain())
                    {
                        gTNT.position.x -= (gTNT.velocity.x) ? ((gTNT.velocity.x) / (abs(gTNT.velocity.x))) : 0;
                        estimatedPositionXReached = true;
                        estimatedPositionYReached = true;
                        gTNT.velocity.x           = 0;
                        gTNT.acceleration.x       = 0;
                        gTNT.velocity.y           = 0;
                        gTNT.acceleration.y       = 0;
                        gTNT.locked               = true;
                    }
                }
                if (!estimatedPositionYReached)
                {
                    gTNT.position.y += (gTNT.velocity.y) ? ((gTNT.velocity.y) / (abs(gTNT.velocity.y))) : 0;
                    estimatedPositionYReached = (estimatedPositionY == gTNT.position.y);
                    if (TNTInTerrain())
                    {
                        gTNT.position.y -= (gTNT.velocity.y) ? ((gTNT.velocity.y) / (abs(gTNT.velocity.y))) : 0;
                        estimatedPositionXReached = true;
                        estimatedPositionYReached = true;
                        gTNT.velocity.x           = 0;
                        gTNT.acceleration.x       = 0;
                        gTNT.velocity.y           = 0;
                        gTNT.acceleration.y       = 0;
                        gTNT.locked               = true;
                    }
                }
            }
            if (!TNTLanded() && !TNTInTerrain())
                gTNT.acceleration.y = kGravityAcceleration;

            gTNT.timeToExplode--;
        }
        break;
    }

    // 武器击中处理
    if (weaponHit(gWeaponSelected))
    {
        weaponDestroied();
    }
}
/*
██     ██ ███████  █████  ██████   ██████  ███    ██ ██       █████  ██    ██ ███    ██  ██████ ██   ██
██     ██ ██      ██   ██ ██   ██ ██    ██ ████   ██ ██      ██   ██ ██    ██ ████   ██ ██      ██   ██
██  █  ██ █████   ███████ ██████  ██    ██ ██ ██  ██ ██      ███████ ██    ██ ██ ██  ██ ██      ███████
██ ███ ██ ██      ██   ██ ██      ██    ██ ██  ██ ██ ██      ██   ██ ██    ██ ██  ██ ██ ██      ██   ██
 ███ ███  ███████ ██   ██ ██       ██████  ██   ████ ███████ ██   ██  ██████  ██   ████  ██████ ██   ██
*/

void weaponLaunch(void)    // 武器发射函数，用来初始化全局武器的数值
{
    VectorXY position, velocity, acceleration;

    switch (gWeaponSelected)
    {
    case iNoWeapon:
        break;
    case iMissile:
        if (faction[gFactionControlled].ammoMissile == kAmmoInfinity || faction[gFactionControlled].ammoMissile > 0)
        {
            gMissileActivated = true;
            if (faction[gFactionControlled].ammoMissile > 0)
            {
                faction[gFactionControlled].ammoMissile--;
            }
            position.x     = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y     = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x     = int(kMissileVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y     = int(-kMissileVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x = 0;
            acceleration.y = kGravityAcceleration;
            gMissile       = creatMissile(position, velocity, acceleration, hMissilePictureRight);
        }
        gPower = 0;
        break;
    case iGrenade:
        if (faction[gFactionControlled].ammoGrenade == kAmmoInfinity || faction[gFactionControlled].ammoGrenade > 0)
        {
            gGrenadeActivated = true;
            if (faction[gFactionControlled].ammoGrenade > 0)
            {
                faction[gFactionControlled].ammoGrenade--;
            }
            position.x     = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y     = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x     = int(kGrenadeVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y     = int(-kGrenadeVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x = 0;
            acceleration.y = kGravityAcceleration;
            gGrenade       = creatGrenade(position, velocity, acceleration, hGrenadePicture);
        }
        gPower = 0;
        break;
    case iStickyBomb:
        if (faction[gFactionControlled].ammoStickyBomb == kAmmoInfinity || faction[gFactionControlled].ammoStickyBomb > 0)
        {
            gStickyBombActivated = true;
            if (faction[gFactionControlled].ammoStickyBomb > 0)
            {
                faction[gFactionControlled].ammoStickyBomb--;
            }
            position.x     = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y     = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x     = int(kStickyBombVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y     = int(-kStickyBombVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x = 0;
            acceleration.y = kGravityAcceleration;
            gStickyBomb    = creatStickyBomb(position, velocity, acceleration, hStickyBombPicture);
        }
        gPower = 0;
        break;
    case iTNT:
        if (faction[gFactionControlled].ammoTNT == kAmmoInfinity || faction[gFactionControlled].ammoTNT > 0)
        {
            gTNTActivated = true;
            if (faction[gFactionControlled].ammoTNT > 0)
            {
                faction[gFactionControlled].ammoTNT--;
            }
            position.x     = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y     = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x     = int(kTNTVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y     = int(-kTNTVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x = 0;
            acceleration.y = kGravityAcceleration;
            gTNT           = creatTNT(position, velocity, acceleration, hTNTPicture);
        }
        gPower = 0;
        break;
    }
}
/*
██     ██ ███████  █████  ██████   ██████  ███    ██ ██████  ███████ ███████ ████████ ██████   ██████  ██ ███████ ██████
██     ██ ██      ██   ██ ██   ██ ██    ██ ████   ██ ██   ██ ██      ██         ██    ██   ██ ██    ██ ██ ██      ██   ██
██  █  ██ █████   ███████ ██████  ██    ██ ██ ██  ██ ██   ██ █████   ███████    ██    ██████  ██    ██ ██ █████   ██   ██
██ ███ ██ ██      ██   ██ ██      ██    ██ ██  ██ ██ ██   ██ ██           ██    ██    ██   ██ ██    ██ ██ ██      ██   ██
 ███ ███  ███████ ██   ██ ██       ██████  ██   ████ ██████  ███████ ███████    ██    ██   ██  ██████  ██ ███████ ██████
*/

void weaponDestroied(void)    // 函数用来搞定武器爆炸之后的处理
{
    switch (gWeaponSelected)
    {
    case 0:
        break;
    case 1:
    {
        if (gMissileActivated)
        {
            gMissileActivated = false;

            // 计算爆点，即导弹中心
            int missilePositionCenterX = gMissile.position.x + kMissileSizeX / 2;
            int missilePositionCenterY = gMissile.position.y + kMissileSizeY / 2;

            // 伤害机器人并炸开
            for (int i = 0; i < gFactionNumber; i++)
                for (int j = 0; j < gRobotNumberPerFaction; j++)
                {
                    if (faction[i].robot[j].alive)
                    {
                        int robotPositionCenterX = faction[i].robot[j].position.x + kRobotSizeX / 2;
                        int robotPositionCenterY = faction[i].robot[j].position.y + kRobotSizeY / 2;
                        if (pointPointDistanceSquare(missilePositionCenterX, missilePositionCenterY, robotPositionCenterX, robotPositionCenterY) <= kMissileHarmRange * kMissileHarmRange)
                        {
                            faction[i].robot[j].hitPoint -= kMissileHarm;
                            if (missilePositionCenterX == robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -2 * kMissileExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (missilePositionCenterX < robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kMissileExplosionPower;
                                faction[i].robot[j].velocity.x = kMissileExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (missilePositionCenterX > robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kMissileExplosionPower;
                                faction[i].robot[j].velocity.x = -kMissileExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                        }
                    }
                }

            // 破坏地形
            for (int i = 0; i < kTerrainNumberX; i++)
                for (int j = 0; j < kTerrainNumberY; j++)
                {
                    int terrainPositionCenterX = (terrain[i][j].position.left + terrain[i][j].position.right) / 2;
                    int terrainPositionCenterY = (terrain[i][j].position.bottom + terrain[i][j].position.top) / 2;
                    if (pointPointDistanceSquare(terrainPositionCenterX, terrainPositionCenterY, missilePositionCenterX, missilePositionCenterY) <= kMissileHarmRange * kMissileHarmRange)
                    {
                        terrain[i][j].isDestoried = true;
                        terrainShapeUpdate(i - 1, j - 1, i + 1, j + 1);
                    }
                }
        }
        break;
    }
    case 2:
    {
        if (gGrenadeActivated)
        {
            // 计算手雷爆点
            gGrenadeActivated          = false;
            int grenadePositionCenterX = gGrenade.position.x + kGrenadeSizeX / 2;
            int grenadePositionCenterY = gGrenade.position.y + kGrenadeSizeY / 2;

            // 伤害机器人
            for (int i = 0; i < gFactionNumber; i++)
                for (int j = 0; j < gRobotNumberPerFaction; j++)
                {
                    if (faction[i].robot[j].alive)
                    {
                        int robotPositionCenterX = faction[i].robot[j].position.x + kRobotSizeX / 2;
                        int robotPositionCenterY = faction[i].robot[j].position.y + kRobotSizeY / 2;
                        if (pointPointDistanceSquare(grenadePositionCenterX, grenadePositionCenterY, robotPositionCenterX, robotPositionCenterY) <= kGrenadeHarmRange * kGrenadeHarmRange)
                        {
                            faction[i].robot[j].hitPoint -= kGrenadeHarm;
                            if (grenadePositionCenterX == robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -2 * kGrenadeExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (grenadePositionCenterX < robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kGrenadeExplosionPower;
                                faction[i].robot[j].velocity.x = kGrenadeExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (grenadePositionCenterX > robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kGrenadeExplosionPower;
                                faction[i].robot[j].velocity.x = -kGrenadeExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                        }
                    }
                }

            // 破坏地形
            for (int i = 0; i < kTerrainNumberX; i++)
                for (int j = 0; j < kTerrainNumberY; j++)
                {
                    int terrainPositionCenterX = (terrain[i][j].position.left + terrain[i][j].position.right) / 2;
                    int terrainPositionCenterY = (terrain[i][j].position.bottom + terrain[i][j].position.top) / 2;
                    if (pointPointDistanceSquare(terrainPositionCenterX, terrainPositionCenterY, grenadePositionCenterX, grenadePositionCenterY) <= kGrenadeHarmRange * kGrenadeHarmRange)
                    {
                        terrain[i][j].isDestoried = true;
                        terrainShapeUpdate(i - 1, j - 1, i + 1, j + 1);
                    }
                }
        }
        break;
    }
    case 3:
    {
        if (gStickyBombActivated)
        {
            // 计算粘性炸弹爆点
            gStickyBombActivated          = false;
            int StickyBombPositionCenterX = gStickyBomb.position.x + kStickyBombSizeX / 2;
            int StickyBombPositionCenterY = gStickyBomb.position.y + kStickyBombSizeY / 2;

            // 伤害机器人
            for (int i = 0; i < gFactionNumber; i++)
                for (int j = 0; j < gRobotNumberPerFaction; j++)
                {
                    if (faction[i].robot[j].alive)
                    {
                        int robotPositionCenterX = faction[i].robot[j].position.x + kRobotSizeX / 2;
                        int robotPositionCenterY = faction[i].robot[j].position.y + kRobotSizeY / 2;
                        if (pointPointDistanceSquare(StickyBombPositionCenterX, StickyBombPositionCenterY, robotPositionCenterX, robotPositionCenterY) <= kStickyBombHarmRange * kStickyBombHarmRange)
                        {
                            faction[i].robot[j].hitPoint -= kStickyBombHarm;
                            if (StickyBombPositionCenterX == robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -2 * kStickyBombExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (StickyBombPositionCenterX < robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kStickyBombExplosionPower;
                                faction[i].robot[j].velocity.x = kStickyBombExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (StickyBombPositionCenterX > robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kStickyBombExplosionPower;
                                faction[i].robot[j].velocity.x = -kStickyBombExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                        }
                    }
                }

            // 破坏地形
            for (int i = 0; i < kTerrainNumberX; i++)
                for (int j = 0; j < kTerrainNumberY; j++)
                {
                    int terrainPositionCenterX = (terrain[i][j].position.left + terrain[i][j].position.right) / 2;
                    int terrainPositionCenterY = (terrain[i][j].position.bottom + terrain[i][j].position.top) / 2;
                    if (pointPointDistanceSquare(terrainPositionCenterX, terrainPositionCenterY, StickyBombPositionCenterX, StickyBombPositionCenterY) <= kStickyBombHarmRange * kStickyBombHarmRange)
                    {
                        terrain[i][j].isDestoried = true;
                        terrainShapeUpdate(i - 1, j - 1, i + 1, j + 1);
                    }
                }
        }
    }
    break;
    case 4:
    {
        if (gTNTActivated)
        {
            // 计算粘性炸弹爆点
            gTNTActivated          = false;
            int TNTPositionCenterX = gTNT.position.x + kTNTSizeX / 2;
            int TNTPositionCenterY = gTNT.position.y + kTNTSizeY / 2;

            // 伤害机器人
            for (int i = 0; i < gFactionNumber; i++)
                for (int j = 0; j < gRobotNumberPerFaction; j++)
                {
                    if (faction[i].robot[j].alive)
                    {
                        int robotPositionCenterX = faction[i].robot[j].position.x + kRobotSizeX / 2;
                        int robotPositionCenterY = faction[i].robot[j].position.y + kRobotSizeY / 2;
                        if (pointPointDistanceSquare(TNTPositionCenterX, TNTPositionCenterY, robotPositionCenterX, robotPositionCenterY) <= kTNTHarmRange * kTNTHarmRange)
                        {
                            faction[i].robot[j].hitPoint -= kTNTHarm;
                            if (TNTPositionCenterX == robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -2 * kTNTExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (TNTPositionCenterX < robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kTNTExplosionPower;
                                faction[i].robot[j].velocity.x = kTNTExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                            else if (TNTPositionCenterX > robotPositionCenterX)
                            {
                                faction[i].robot[j].velocity.y = -kTNTExplosionPower;
                                faction[i].robot[j].velocity.x = -kTNTExplosionPower;
                                faction[i].robot[j].isJumping  = true;
                            }
                        }
                    }
                }

            // 破坏地形
            for (int i = 0; i < kTerrainNumberX; i++)
                for (int j = 0; j < kTerrainNumberY; j++)
                {
                    int terrainPositionCenterX = (terrain[i][j].position.left + terrain[i][j].position.right) / 2;
                    int terrainPositionCenterY = (terrain[i][j].position.bottom + terrain[i][j].position.top) / 2;
                    if (pointPointDistanceSquare(terrainPositionCenterX, terrainPositionCenterY, TNTPositionCenterX, TNTPositionCenterY) <= kTNTHarmRange * kTNTHarmRange)
                    {
                        terrain[i][j].isDestoried = true;
                        terrainShapeUpdate(i - 1, j - 1, i + 1, j + 1);
                    }
                }
        }
        break;
    }
    }
}
/*
██     ██ ███████  █████  ██████   ██████  ███    ██ ██   ██ ██ ████████
██     ██ ██      ██   ██ ██   ██ ██    ██ ████   ██ ██   ██ ██    ██
██  █  ██ █████   ███████ ██████  ██    ██ ██ ██  ██ ███████ ██    ██
██ ███ ██ ██      ██   ██ ██      ██    ██ ██  ██ ██ ██   ██ ██    ██
 ███ ███  ███████ ██   ██ ██       ██████  ██   ████ ██   ██ ██    ██
*/

bool weaponHit(int weapon)    // 检查武器是否满足爆炸条件
{
    // weapon参数用来分流，这样可以把几个功能集成到一个函数里面
    switch (weapon)
    {
    case 0:
        break;
    case 1:    // 导弹击中逻辑：接触到地面或机器人即刻引爆
    {
        // 先检查导弹有没有打到地面
        int left = ((gMissile.position.x + kMissileEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;
        int top  = ((gMissile.position.y + kMissileEdgeIngnorance) / kTerrainHeight) * kTerrainHeight + 1;

        int right, bottom;

        if ((gMissile.position.x + kMissileSizeX - kMissileEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
        {
            right = gMissile.position.x + kMissileSizeX - kMissileEdgeIngnorance;
        }
        else
        {
            right = ((gMissile.position.x + kMissileSizeX - kMissileEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
        }

        if ((gMissile.position.y + kMissileSizeY - kMissileEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
        {
            bottom = gMissile.position.y + kMissileSizeY - kMissileEdgeIngnorance;
        }
        else
        {
            bottom = ((gMissile.position.y + kMissileSizeY - kMissileEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
        }

        int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
        int rightTerrainCoordinate  = right / kTerrainWidth - 1;
        int topTerrainCoordinate    = (top - 1) / kTerrainHeight;
        int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;

        // 检查这些terrain中是否有未被摧毁的
        for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
            for (int j = topTerrainCoordinate; j <= bottomTerrainCoordinate; j++)
                if (!terrain[i][j].isDestoried)
                    return true;

        // 再检查导弹有没有打到机器人，这里以后要判断机器人是否死亡
        int missilePositionCenterX = gMissile.position.x + kMissileSizeX / 2;
        int missilePositionCenterY = gMissile.position.y + kMissileSizeY / 2;
        for (int i = 0; i < gFactionNumber; i++)
            for (int j = 0; j < gRobotNumberPerFaction; j++)
            {
                int robotPositionCenterX = faction[i].robot[j].position.x + kRobotSizeX / 2;
                int robotPositionCenterY = faction[i].robot[j].position.y + kRobotSizeY / 2;
                if (pointPointDistanceSquare(missilePositionCenterX, missilePositionCenterY, robotPositionCenterX, robotPositionCenterY) <= kMissileSenseDistance * kMissileSenseDistance)
                    return true;
            }


        return false;
        break;
    }
    case 2:    // 手雷引爆逻辑：计时器停止即可引爆
    {
        // 检查手雷的计时器
        if (gGrenade.timeToExplode < 0)
        {
            gGrenade.timeToExplode = 0;
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case 3:
    {
        // 检查计时器
        if (gStickyBomb.timeToExplode < 0)
        {
            gStickyBomb.timeToExplode = 0;
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case 4:
    {
        // 检查计时器
        if (gTNT.timeToExplode < 0)
        {
            gTNT.timeToExplode = 0;
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    }
}
/*
 ██████  ██████  ███████ ███    ██  █████  ██████  ███████ ██ ███    ██ ████████ ███████ ██████  ██████   █████  ██ ███    ██
██       ██   ██ ██      ████   ██ ██   ██ ██   ██ ██      ██ ████   ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██
██   ███ ██████  █████   ██ ██  ██ ███████ ██   ██ █████   ██ ██ ██  ██    ██    █████   ██████  ██████  ███████ ██ ██ ██  ██
██    ██ ██   ██ ██      ██  ██ ██ ██   ██ ██   ██ ██      ██ ██  ██ ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██
 ██████  ██   ██ ███████ ██   ████ ██   ██ ██████  ███████ ██ ██   ████    ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████
*/

bool grenadeInTerrain(void)
{
    // 检查碰撞
    int left = ((gGrenade.position.x + kGrenadeEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;
    int top  = ((gGrenade.position.y + kGrenadeEdgeIngnorance) / kTerrainHeight) * kTerrainHeight + 1;

    int right, bottom;

    if ((gGrenade.position.x + kGrenadeSizeX - kGrenadeEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = gGrenade.position.x + kGrenadeSizeX - kGrenadeEdgeIngnorance;
    }
    else
    {
        right = ((gGrenade.position.x + kGrenadeSizeX - kGrenadeEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((gGrenade.position.y + kGrenadeSizeY - kGrenadeEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = gGrenade.position.y + kGrenadeSizeY - kGrenadeEdgeIngnorance;
    }
    else
    {
        bottom = ((gGrenade.position.y + kGrenadeSizeY - kGrenadeEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int topTerrainCoordinate    = (top - 1) / kTerrainHeight;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;

    // 检查这些terrain中是否有未被摧毁的
    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        for (int j = topTerrainCoordinate; j <= bottomTerrainCoordinate; j++)
            if (!terrain[i][j].isDestoried)
                return true;
    return false;
}
/*
 ██████  ██████  ███████ ███    ██  █████  ██████  ███████ ██       █████  ███    ██ ██████  ███████ ██████
██       ██   ██ ██      ████   ██ ██   ██ ██   ██ ██      ██      ██   ██ ████   ██ ██   ██ ██      ██   ██
██   ███ ██████  █████   ██ ██  ██ ███████ ██   ██ █████   ██      ███████ ██ ██  ██ ██   ██ █████   ██   ██
██    ██ ██   ██ ██      ██  ██ ██ ██   ██ ██   ██ ██      ██      ██   ██ ██  ██ ██ ██   ██ ██      ██   ██
 ██████  ██   ██ ███████ ██   ████ ██   ██ ██████  ███████ ███████ ██   ██ ██   ████ ██████  ███████ ██████
*/

bool grenadeLanded(void)
{
    if ((gGrenade.position.y + kGrenadeSizeX - kGrenadeEdgeIngnorance) % kTerrainHeight != 0)
        return false;


    // 仿照上面的函数，这次判定人物下面有没有未被摧毁的地块
    int left = ((gGrenade.position.x + kGrenadeEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;

    int right, bottom;

    if ((gGrenade.position.x + kGrenadeSizeX - kGrenadeEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = gGrenade.position.x + kGrenadeSizeX - kGrenadeEdgeIngnorance;
    }
    else
    {
        right = ((gGrenade.position.x + kGrenadeSizeX - kGrenadeEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((gGrenade.position.y + kGrenadeSizeY - kGrenadeEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = gGrenade.position.y + kGrenadeSizeY - kGrenadeEdgeIngnorance;
    }
    else
    {
        bottom = ((gGrenade.position.y + kGrenadeSizeY - kGrenadeEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;


    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        if (!terrain[i][bottomTerrainCoordinate + 1].isDestoried)
            return true;
    return false;
}
/*
███████ ████████ ██  ██████ ██   ██ ██████   ██████  ███    ███ ██████  ██ ███    ██ ████████ ███████ ██████  ██████   █████  ██ ███    ██
██         ██    ██ ██      ██  ██  ██   ██ ██    ██ ████  ████ ██   ██ ██ ████   ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██
███████    ██    ██ ██      █████   ██████  ██    ██ ██ ████ ██ ██████  ██ ██ ██  ██    ██    █████   ██████  ██████  ███████ ██ ██ ██  ██
     ██    ██    ██ ██      ██  ██  ██   ██ ██    ██ ██  ██  ██ ██   ██ ██ ██  ██ ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██
███████    ██    ██  ██████ ██   ██ ██████   ██████  ██      ██ ██████  ██ ██   ████    ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████
*/

bool stickyBombInTerrain(void)
{
    // 检查碰撞
    int left = ((gStickyBomb.position.x + kStickyBombEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;
    int top  = ((gStickyBomb.position.y + kStickyBombEdgeIngnorance) / kTerrainHeight) * kTerrainHeight + 1;

    int right, bottom;

    if ((gStickyBomb.position.x + kStickyBombSizeX - kStickyBombEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = gStickyBomb.position.x + kStickyBombSizeX - kStickyBombEdgeIngnorance;
    }
    else
    {
        right = ((gStickyBomb.position.x + kStickyBombSizeX - kStickyBombEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((gStickyBomb.position.y + kStickyBombSizeY - kStickyBombEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = gStickyBomb.position.y + kStickyBombSizeY - kStickyBombEdgeIngnorance;
    }
    else
    {
        bottom = ((gStickyBomb.position.y + kStickyBombSizeY - kStickyBombEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int topTerrainCoordinate    = (top - 1) / kTerrainHeight;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;

    // 检查这些terrain中是否有未被摧毁的
    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        for (int j = topTerrainCoordinate; j <= bottomTerrainCoordinate; j++)
            if (!terrain[i][j].isDestoried)
                return true;
    return false;
}
/*
████████ ███    ██ ████████ ██ ███    ██ ████████ ███████ ██████  ██████   █████  ██ ███    ██
   ██    ████   ██    ██    ██ ████   ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██
   ██    ██ ██  ██    ██    ██ ██ ██  ██    ██    █████   ██████  ██████  ███████ ██ ██ ██  ██
   ██    ██  ██ ██    ██    ██ ██  ██ ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██
   ██    ██   ████    ██    ██ ██   ████    ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████
*/

bool TNTInTerrain(void)
{
    // 检查碰撞
    int left = ((gTNT.position.x + kTNTEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;
    int top  = ((gTNT.position.y + kTNTEdgeIngnorance) / kTerrainHeight) * kTerrainHeight + 1;

    int right, bottom;

    if ((gTNT.position.x + kTNTSizeX - kTNTEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = gTNT.position.x + kTNTSizeX - kTNTEdgeIngnorance;
    }
    else
    {
        right = ((gTNT.position.x + kTNTSizeX - kTNTEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((gTNT.position.y + kTNTSizeY - kTNTEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = gTNT.position.y + kTNTSizeY - kTNTEdgeIngnorance;
    }
    else
    {
        bottom = ((gTNT.position.y + kTNTSizeY - kTNTEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int topTerrainCoordinate    = (top - 1) / kTerrainHeight;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;

    // 检查这些terrain中是否有未被摧毁的
    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        for (int j = topTerrainCoordinate; j <= bottomTerrainCoordinate; j++)
            if (!terrain[i][j].isDestoried)
                return true;
    return false;
}
/*
████████ ███    ██ ████████ ██       █████  ███    ██ ██████  ███████ ██████
   ██    ████   ██    ██    ██      ██   ██ ████   ██ ██   ██ ██      ██   ██
   ██    ██ ██  ██    ██    ██      ███████ ██ ██  ██ ██   ██ █████   ██   ██
   ██    ██  ██ ██    ██    ██      ██   ██ ██  ██ ██ ██   ██ ██      ██   ██
   ██    ██   ████    ██    ███████ ██   ██ ██   ████ ██████  ███████ ██████
*/

bool TNTLanded(void)
{
    if ((gTNT.position.y + kTNTSizeX - kTNTEdgeIngnorance) % kTerrainHeight != 0)
        return false;


    // 仿照上面的函数，这次判定下面有没有未被摧毁的地块
    int left = ((gTNT.position.x + kTNTEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;

    int right, bottom;

    if ((gTNT.position.x + kTNTSizeX - kTNTEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = gTNT.position.x + kTNTSizeX - kTNTEdgeIngnorance;
    }
    else
    {
        right = ((gTNT.position.x + kTNTSizeX - kTNTEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((gTNT.position.y + kTNTSizeY - kTNTEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = gTNT.position.y + kTNTSizeY - kTNTEdgeIngnorance;
    }
    else
    {
        bottom = ((gTNT.position.y + kTNTSizeY - kTNTEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;


    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        if (!terrain[i][bottomTerrainCoordinate + 1].isDestoried)
            return true;
    return false;
}

/*
███████ ██   ██ ██ ██      ██       █████   ██████ ████████ ██ ██    ██  █████  ████████ ███████
██      ██  ██  ██ ██      ██      ██   ██ ██         ██    ██ ██    ██ ██   ██    ██    ██
███████ █████   ██ ██      ██      ███████ ██         ██    ██ ██    ██ ███████    ██    █████
     ██ ██  ██  ██ ██      ██      ██   ██ ██         ██    ██  ██  ██  ██   ██    ██    ██
███████ ██   ██ ██ ███████ ███████ ██   ██  ██████    ██    ██   ████   ██   ██    ██    ███████
*/

void skillActivate(void)    // TODO 记得把数量给减掉
{
    switch (gSkillSelected)
    {
    case iNoSkill:
        break;
    case iCure:
        if (faction[gFactionControlled].ammoCure == kAmmoInfinity || faction[gFactionControlled].ammoCure > 0)
        {
            if (faction[gFactionControlled].ammoCure > 0)
            {
                faction[gFactionControlled].ammoCure--;
            }
            faction[gSkillTargetFaction].robot[gSkillTargetRobot].hitPoint += kCureEffect;
            faction[gFactionControlled].ammoCure--;
        }
        break;
    case iTransfer:
        if (faction[gFactionControlled].ammoTransfer == kAmmoInfinity || faction[gFactionControlled].ammoTransfer > 0)
        {
            if (faction[gFactionControlled].ammoTransfer > 0)
            {
                faction[gFactionControlled].ammoTransfer--;
            }
            faction[gFactionControlled].robot[gRobotControlled].direction  = (rand() % 2) ? kFacingLeft : kFacingRight;
            faction[gFactionControlled].robot[gRobotControlled].position.x = rand() % (kWorldWidth + 1);
            faction[gFactionControlled].robot[gRobotControlled].position.y = kWorldHeight / 2;
            while (robotInTerrain(gFactionControlled, gRobotControlled))
            {
                faction[gFactionControlled].robot[gRobotControlled].position.y--;
            }
            while (robotLanded(gFactionControlled, gRobotControlled))
            {
                faction[gFactionControlled].robot[gRobotControlled].position.y++;
            }
            faction[gFactionControlled].ammoTransfer--;
        }
        break;
    case iSafeTransfer:    // TODO
        if (faction[gFactionControlled].ammoSafeTransfer == kAmmoInfinity || faction[gFactionControlled].ammoSafeTransfer > 0)
        {
            if (faction[gFactionControlled].ammoSafeTransfer > 0)
            {
                faction[gFactionControlled].ammoSafeTransfer--;
            }
            if (faction[gFactionControlled].aliveRobot > 1)
            {
                int transferTo = gRobotControlled;
                while ((transferTo == gRobotControlled) || (!faction[gFactionControlled].robot[transferTo].alive))
                {
                    transferTo = rand() % gRobotNumberPerFaction;
                }

                faction[gFactionControlled].robot[gRobotControlled].direction  = (rand() % 2) ? kFacingLeft : kFacingRight;
                faction[gFactionControlled].robot[gRobotControlled].position.x = faction[gFactionControlled].robot[transferTo].position.x;
                faction[gFactionControlled].robot[gRobotControlled].position.y = faction[gFactionControlled].robot[transferTo].position.y;
            }
            faction[gFactionControlled].ammoSafeTransfer--;
        }
        break;
    case iProtect:
        if (faction[gFactionControlled].ammoProtect == kAmmoInfinity || faction[gFactionControlled].ammoProtect > 0)
        {
            if (faction[gFactionControlled].ammoProtect > 0)
            {
                faction[gFactionControlled].ammoProtect--;
            }
            if (faction[gFactionControlled].robot[gRobotControlled].protectiveShellTime <= 0)
            {
                faction[gFactionControlled].robot[gRobotControlled].protectiveShellTime = kProtectiveShellTime;
            }
            faction[gFactionControlled].ammoProtect--;
        }
        break;
    default:
        break;
    }
}

/*
████████ ███████ ██████  ██████   █████  ██ ███    ██ ██    ██ ██████  ██████   █████  ████████ ███████
   ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██ ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
   ██    █████   ██████  ██████  ███████ ██ ██ ██  ██ ██    ██ ██████  ██   ██ ███████    ██    █████
   ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
   ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████  ██████  ██      ██████  ██   ██    ██    ███████
*/

void terrainUpdate(void)
{
}
/*
████████ ███████ ██████  ██████   █████  ██ ███    ██ ███████ ██   ██  █████  ██████  ███████ ██    ██ ██████  ██████   █████  ████████ ███████
   ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██ ██      ██   ██ ██   ██ ██   ██ ██      ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
   ██    █████   ██████  ██████  ███████ ██ ██ ██  ██ ███████ ███████ ███████ ██████  █████   ██    ██ ██████  ██   ██ ███████    ██    █████
   ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██      ██ ██   ██ ██   ██ ██      ██      ██    ██ ██      ██   ██ ██   ██    ██    ██
   ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████ ███████ ██   ██ ██   ██ ██      ███████  ██████  ██      ██████  ██   ██    ██    ███████
*/

void terrainShapeUpdate(int left, int top, int right, int bottom)
{
    gTerrainNeedUpdate = true;
    int terrainExist   = 0;
    for (int i = left; i <= right; i++)
        for (int j = top; j <= bottom; j++)
        {
            terrainExist = 0;
            if (terrain[i][j].isDestoried)
                terrain[i][j].connectionStatus = iTerrainEmpty;
            else
            {
                if ((i != 0) && (i != kTerrainNumberX - 1) && (j != 0) && (j != kTerrainNumberY - 1))
                {
                    terrainExist = (int(!terrain[i][j - 1].isDestoried) << 3) + (int(!terrain[i - 1][j].isDestoried) << 2) + (int(!terrain[i + 1][j].isDestoried) << 1) + (int(!terrain[i][j + 1].isDestoried) << 0);
                }
                if ((i == 0) && (j == 0))
                {
                    terrainExist = (1 << 3) + (1 << 2) + (int(!terrain[i + 1][j].isDestoried) << 1) + (int(!terrain[i][j + 1].isDestoried) << 0);    //11xx
                }
                if ((i == kTerrainNumberX - 1) && (j == 0))
                {
                    terrainExist = (1 << 3) + (int(!terrain[i - 1][j].isDestoried) << 2) + (1 << 1) + (int(!terrain[i][j + 1].isDestoried) << 0);    //1x1x
                }
                if ((i == 0) && (j == kTerrainNumberY - 1))
                {
                    terrainExist = int((!terrain[i][j - 1].isDestoried) << 3) + (1 << 2) + (int(!terrain[i + 1][j].isDestoried) << 1) + (1 << 0);    //x1x1
                }
                if ((i == kTerrainNumberX - 1) && (j == kTerrainNumberY - 1))
                {
                    terrainExist = int((!terrain[i][j - 1].isDestoried) << 3) + (int(!terrain[i - 1][j].isDestoried) << 2) + (1 << 1) + (1 << 0);    //xx11
                }
                if ((i == 0) && (j != 0) && (j != kTerrainNumberY - 1))
                {
                    terrainExist = int((!terrain[i][j - 1].isDestoried) << 3) + (1 << 2) + (int(!terrain[i + 1][j].isDestoried) << 1) + (int(!terrain[i][j + 1].isDestoried) << 0);    //x1xx
                }
                if ((i == kTerrainNumberX - 1) && (j != 0) && (j != kTerrainNumberY - 1))
                {
                    terrainExist = int((!terrain[i][j - 1].isDestoried) << 3) + (int(!terrain[i - 1][j].isDestoried) << 2) + (1 << 1) + (int(!terrain[i][j + 1].isDestoried) << 0);    //xx1x
                }
                if ((j == 0) && (i != 0) && (i != kTerrainNumberX - 1))
                {
                    terrainExist = (1 << 3) + (int(!terrain[i - 1][j].isDestoried) << 2) + (int(!terrain[i + 1][j].isDestoried) << 1) + (int(!terrain[i][j + 1].isDestoried) << 0);    //1xxx
                }
                if ((j == kTerrainNumberY - 1) && (i != 0) && (i != kTerrainNumberX - 1))
                {
                    terrainExist = int((!terrain[i][j - 1].isDestoried) << 3) + (int(!terrain[i - 1][j].isDestoried) << 2) + (int(!terrain[i + 1][j].isDestoried) << 1) + (1 << 0);    //xxx1
                }

                switch (terrainExist)
                {
                case ((0 << 3) + (0 << 2) + (0 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTerrainIndependantMiddle;
                    break;
                case ((0 << 3) + (0 << 2) + (0 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainIndependantUp;
                    break;
                case ((0 << 3) + (0 << 2) + (1 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTerrainIndependantLeft;
                    break;
                case ((0 << 3) + (0 << 2) + (1 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainAngleLeftUp;
                    break;
                case ((0 << 3) + (1 << 2) + (0 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTerrainIndependantRight;
                    break;
                case ((0 << 3) + (1 << 2) + (0 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainAngleRightUp;
                    break;
                case ((0 << 3) + (1 << 2) + (1 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTerrainMiddleLeftRight;
                    break;
                case ((0 << 3) + (1 << 2) + (1 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainHalfUp;
                    break;
                case ((1 << 3) + (0 << 2) + (0 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTerrainIndependantDown;
                    break;
                case ((1 << 3) + (0 << 2) + (0 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainMiddleUpDown;
                    break;
                case ((1 << 3) + (0 << 2) + (1 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTerrainAngleLeftDown;
                    break;
                case ((1 << 3) + (0 << 2) + (1 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainHalfLeft;
                    break;
                case ((1 << 3) + (1 << 2) + (0 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTarrainAngleRightDown;
                    break;
                case ((1 << 3) + (1 << 2) + (0 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainHalfRight;
                    break;
                case ((1 << 3) + (1 << 2) + (1 << 1) + (0 << 0)):
                    terrain[i][j].connectionStatus = iTerrainHalfDown;
                    break;
                case ((1 << 3) + (1 << 2) + (1 << 1) + (1 << 0)):
                    terrain[i][j].connectionStatus = iTerrainFull;
                    break;
                }
            }

            VectorXY pos                    = getTerrainBlockPicture(terrain[i][j].connectionStatus);
            terrain[i][j].picturePosition.x = pos.x;
            terrain[i][j].picturePosition.y = pos.y;
        }
}

void terrainShapeUpdate(int x, int y)
{
    terrainShapeUpdate(x, y, x, y);
}

/*
███████ ███████  █████  ██      ███████ ██    ██ ███████ ██      ██    ██ ██████  ██████   █████  ████████ ███████
██      ██      ██   ██ ██      ██      ██    ██ ██      ██      ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
███████ █████   ███████ ██      █████   ██    ██ █████   ██      ██    ██ ██████  ██   ██ ███████    ██    █████
     ██ ██      ██   ██ ██      ██       ██  ██  ██      ██      ██    ██ ██      ██   ██ ██   ██    ██    ██
███████ ███████ ██   ██ ███████ ███████   ████   ███████ ███████  ██████  ██      ██████  ██   ██    ██    ███████
*/

void seaLevelUpdate(void)
{
    DEBUG_ONLY_seaLevelIncHelper++;
    if (DEBUG_ONLY_seaLevelIncHelper == 10)
    {
        gSeaLevel -= kSeaLevelIncreasingVelocity;
        DEBUG_ONLY_seaLevelIncHelper = 0;
    }
}
/*
██████   ██████  ██   ██ ██    ██ ██████  ██████   █████  ████████ ███████
██   ██ ██    ██  ██ ██  ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
██████  ██    ██   ███   ██    ██ ██████  ██   ██ ███████    ██    █████
██   ██ ██    ██  ██ ██  ██    ██ ██      ██   ██ ██   ██    ██    ██
██████   ██████  ██   ██  ██████  ██      ██████  ██   ██    ██    ███████
*/

void medicalBoxUpdate(void)
{
    for (int i = 0; i < kMaxMedicalBoxNum; i++)
    {
        // 如果有医疗箱被捡起，就再刷出来一个
        if (gMedicalBox[i].picked)
        {
            VectorXY position;
            VectorXY velocity;
            VectorXY acceleration;
            // 随机决定医疗包位置
            position.x     = rand() % kWorldWidth + 1;
            position.y     = kWorldHeight / 2;
            velocity.x     = 0;
            velocity.y     = 0;
            acceleration.x = 0;
            acceleration.y = 0;
            gMedicalBox[i] = creatMedicalBox(position, velocity, acceleration, hMedicalBoxPicture);
            // 合法化医疗包位置
            while (boxInTerrain(kMedicalBoxNumber, i))
            {
                gMedicalBox[i].position.y--;
            }
            while (!boxLanded(kMedicalBoxNumber, i))
            {
                gMedicalBox[i].position.y++;
            }
        }

        // 如果机器人靠近医疗包，就让医疗包被捡起，同时给人物加血
        for (int j = 0; j < gFactionNumber; j++)
            for (int k = 0; k < gRobotNumberPerFaction; k++)
            {
                int robotPositionCenterX = faction[j].robot[k].position.x + kRobotSizeX / 2;
                int robotPositionCenterY = faction[j].robot[k].position.y + kRobotSizeY / 2;
                int boxCenterX           = gMedicalBox[i].position.x + kMedicalBoxSizeX / 2;
                int boxCenterY           = gMedicalBox[i].position.y + kMedicalBoxSizeY / 2;
                if (pointPointDistanceSquare(robotPositionCenterX, robotPositionCenterY, boxCenterX, boxCenterY) <= kPickingBoxRange * kPickingBoxRange)
                {
                    gMedicalBox[i].picked        = true;
                    faction[j].robot[k].hitPoint = min(faction[j].robot[k].hitPoint + kMedicalBoxEffect, kRobotFullHitPoint);    // 如果血量加满，保证血量不溢出
                }
            }
    }

    // 医疗包的自由落体
    for (int i = 0; i < kMaxMedicalBoxNum; i++)
    {
        gMedicalBox[i].velocity.x += gMedicalBox[i].acceleration.x;
        gMedicalBox[i].velocity.y += gMedicalBox[i].acceleration.y;

        int estimatedPositionX = gMedicalBox[i].position.x + gMedicalBox[i].velocity.x;
        int estimatedPositionY = gMedicalBox[i].position.y + gMedicalBox[i].velocity.y;

        bool estimatedPositionXReached = (gMedicalBox[i].position.x == estimatedPositionX);
        bool estimatedPositionYReached = (gMedicalBox[i].position.y == estimatedPositionY);

        while (!boxInTerrain(kMedicalBoxNumber, i) && (!estimatedPositionXReached) || (!estimatedPositionYReached))
        {
            if (!estimatedPositionXReached)
            {
                gMedicalBox[i].position.x += (gMedicalBox[i].velocity.x) ? ((gMedicalBox[i].velocity.x) / (abs(gMedicalBox[i].velocity.x))) : 0;
                estimatedPositionXReached = (estimatedPositionX == gMedicalBox[i].position.x);
                if (boxInTerrain(kMedicalBoxNumber, i))
                {
                    gMedicalBox[i].position.x -= (gMedicalBox[i].velocity.x) ? ((gMedicalBox[i].velocity.x) / (abs(gMedicalBox[i].velocity.x))) : 0;
                    estimatedPositionXReached     = true;
                    estimatedPositionYReached     = true;
                    gMedicalBox[i].velocity.x     = 0;
                    gMedicalBox[i].acceleration.x = 0;
                    gMedicalBox[i].velocity.y     = 0;
                    gMedicalBox[i].acceleration.y = 0;
                }
            }
            if (!estimatedPositionYReached)
            {
                gMedicalBox[i].position.y += (gMedicalBox[i].velocity.y) ? ((gMedicalBox[i].velocity.y) / (abs(gMedicalBox[i].velocity.y))) : 0;
                estimatedPositionYReached = (estimatedPositionY == gMedicalBox[i].position.y);
                if (boxInTerrain(kMedicalBoxNumber, i))
                {
                    gMedicalBox[i].position.y -= (gMedicalBox[i].velocity.y) ? ((gMedicalBox[i].velocity.y) / (abs(gMedicalBox[i].velocity.y))) : 0;
                    estimatedPositionXReached     = true;
                    estimatedPositionYReached     = true;
                    gMedicalBox[i].velocity.x     = 0;
                    gMedicalBox[i].acceleration.x = 0;
                    gMedicalBox[i].velocity.y     = 0;
                    gMedicalBox[i].acceleration.y = 0;
                }
            }
        }
        if (!boxLanded(kMedicalBoxNumber, i) && !boxInTerrain(kMedicalBoxNumber, i))
        {
            gMedicalBox[i].acceleration.y = kGravityAcceleration;
        }
    }
    // 医疗包自由落体处理结束
}

void weaponBoxUpdate(void)
{
    for (int i = 0; i < kMaxWeaponBoxNum; i++)
    {
        if (gWeaponBox[i].picked)
        {
            VectorXY position;
            VectorXY velocity;
            VectorXY acceleration;
            position.x     = rand() % kWorldWidth + 1;
            position.y     = kWorldHeight / 2;
            velocity.x     = 0;
            velocity.y     = 0;
            acceleration.x = 0;
            acceleration.y = 0;
            gWeaponBox[i]  = creatWeaponBox(position, velocity, acceleration, hWeaponBoxPicture);
            while (boxInTerrain(kWeaponBoxNumber, i))
            {
                gWeaponBox[i].position.y--;
            }
            while (!boxLanded(kWeaponBoxNumber, i))
            {
                gWeaponBox[i].position.y++;
            }
        }

        for (int j = 0; j < gFactionNumber; j++)
            for (int k = 0; k < gRobotNumberPerFaction; k++)
            {
                int robotPositionCenterX = faction[j].robot[k].position.x + kRobotSizeX / 2;
                int robotPositionCenterY = faction[j].robot[k].position.y + kRobotSizeY / 2;
                int boxCenterX           = gWeaponBox[i].position.x + kWeaponBoxSizeX / 2;
                int boxCenterY           = gWeaponBox[i].position.y + kWeaponBoxSizeY / 2;
                if (pointPointDistanceSquare(robotPositionCenterX, robotPositionCenterY, boxCenterX, boxCenterY) <= kPickingBoxRange * kPickingBoxRange)
                {
                    gWeaponBox[i].picked = true;

                    switch (gWeaponBox[i].content)
                    {
                    case iMissile:
                        if (faction[j].ammoMissile >= 0)
                            faction[j].ammoMissile++;
                        break;
                    case iGrenade:
                        if (faction[j].ammoGrenade >= 0)
                            faction[j].ammoGrenade++;
                        break;
                    case iStickyBomb:
                        if (faction[j].ammoStickyBomb >= 0)
                            faction[j].ammoStickyBomb++;
                        break;
                    case iTNT:
                        if (faction[j].ammoTNT >= 0)
                            faction[j].ammoTNT++;
                        break;
                    }
                }
            }
    }

    // 武器箱自由落体处理
    for (int i = 0; i < kMaxWeaponBoxNum; i++)
    {
        gWeaponBox[i].velocity.x += gWeaponBox[i].acceleration.x;
        gWeaponBox[i].velocity.y += gWeaponBox[i].acceleration.y;

        int estimatedPositionX = gWeaponBox[i].position.x + gWeaponBox[i].velocity.x;
        int estimatedPositionY = gWeaponBox[i].position.y + gWeaponBox[i].velocity.y;

        bool estimatedPositionXReached = (gWeaponBox[i].position.x == estimatedPositionX);
        bool estimatedPositionYReached = (gWeaponBox[i].position.y == estimatedPositionY);

        while (!boxInTerrain(kWeaponBoxNumber, i) && (!estimatedPositionXReached) || (!estimatedPositionYReached))
        {
            if (!estimatedPositionXReached)
            {
                gWeaponBox[i].position.x += (gWeaponBox[i].velocity.x) ? ((gWeaponBox[i].velocity.x) / (abs(gWeaponBox[i].velocity.x))) : 0;
                estimatedPositionXReached = (estimatedPositionX == gWeaponBox[i].position.x);
                if (boxInTerrain(kWeaponBoxNumber, i))
                {
                    gWeaponBox[i].position.x -= (gWeaponBox[i].velocity.x) ? ((gWeaponBox[i].velocity.x) / (abs(gWeaponBox[i].velocity.x))) : 0;
                    estimatedPositionXReached    = true;
                    estimatedPositionYReached    = true;
                    gWeaponBox[i].velocity.x     = 0;
                    gWeaponBox[i].acceleration.x = 0;
                    gWeaponBox[i].velocity.y     = 0;
                    gWeaponBox[i].acceleration.y = 0;
                }
            }
            if (!estimatedPositionYReached)
            {
                gWeaponBox[i].position.y += (gWeaponBox[i].velocity.y) ? ((gWeaponBox[i].velocity.y) / (abs(gWeaponBox[i].velocity.y))) : 0;
                estimatedPositionYReached = (estimatedPositionY == gWeaponBox[i].position.y);
                if (boxInTerrain(kWeaponBoxNumber, i))
                {
                    gWeaponBox[i].position.y -= (gWeaponBox[i].velocity.y) ? ((gWeaponBox[i].velocity.y) / (abs(gWeaponBox[i].velocity.y))) : 0;
                    estimatedPositionXReached    = true;
                    estimatedPositionYReached    = true;
                    gWeaponBox[i].velocity.x     = 0;
                    gWeaponBox[i].acceleration.x = 0;
                    gWeaponBox[i].velocity.y     = 0;
                    gWeaponBox[i].acceleration.y = 0;
                }
            }
        }
        if (!boxLanded(kWeaponBoxNumber, i) && !boxInTerrain(kWeaponBoxNumber, i))
        {
            gWeaponBox[i].acceleration.y = kGravityAcceleration;
        }
    }
}

void skillBoxUpdate(void)
{
    for (int i = 0; i < kMaxSkillBoxNum; i++)
    {
        // 如果技能箱被捡起，就刷一个新的
        if (gSkillBox[i].picked)
        {
            VectorXY position;
            VectorXY velocity;
            VectorXY acceleration;
            position.x     = rand() % kWorldWidth + 1;
            position.y     = kWorldHeight / 2;
            velocity.x     = 0;
            velocity.y     = 0;
            acceleration.x = 0;
            acceleration.y = 0;
            gSkillBox[i]   = creatSkillBox(position, velocity, acceleration, hSkillBoxPicture);
            // 合法化技能箱位置
            while (boxInTerrain(kSkillBoxNumber, i))
            {
                gSkillBox[i].position.y--;
            }
            while (!boxLanded(kSkillBoxNumber, i))
            {
                gSkillBox[i].position.y++;
            }
        }

        for (int j = 0; j < gFactionNumber; j++)
            for (int k = 0; k < gRobotNumberPerFaction; k++)
            {
                int robotPositionCenterX = faction[j].robot[k].position.x + kRobotSizeX / 2;
                int robotPositionCenterY = faction[j].robot[k].position.y + kRobotSizeY / 2;
                int boxCenterX           = gSkillBox[i].position.x + kSkillBoxSizeX / 2;
                int boxCenterY           = gSkillBox[i].position.y + kSkillBoxSizeY / 2;
                if (pointPointDistanceSquare(robotPositionCenterX, robotPositionCenterY, boxCenterX, boxCenterY) <= kPickingBoxRange * kPickingBoxRange)
                {
                    gSkillBox[i].picked = true;

                    switch (gSkillBox[i].content)
                    {
                    case iCure:
                        if (faction[j].ammoCure >= 0)
                            faction[j].ammoCure++;
                        break;
                    case iGrenade:
                        if (faction[j].ammoTransfer >= 0)
                            faction[j].ammoTransfer++;
                        break;
                    case iStickyBomb:
                        if (faction[j].ammoSafeTransfer >= 0)
                            faction[j].ammoSafeTransfer++;
                        break;
                    case iTNT:
                        if (faction[j].ammoProtect >= 0)
                            faction[j].ammoProtect++;
                        break;
                    }
                }
            }
    }

    // 技能箱自由落体处理
    for (int i = 0; i < kMaxSkillBoxNum; i++)
    {
        gSkillBox[i].velocity.x += gSkillBox[i].acceleration.x;
        gSkillBox[i].velocity.y += gSkillBox[i].acceleration.y;

        int estimatedPositionX = gSkillBox[i].position.x + gSkillBox[i].velocity.x;
        int estimatedPositionY = gSkillBox[i].position.y + gSkillBox[i].velocity.y;

        bool estimatedPositionXReached = (gSkillBox[i].position.x == estimatedPositionX);
        bool estimatedPositionYReached = (gSkillBox[i].position.y == estimatedPositionY);

        while (!boxInTerrain(kSkillBoxNumber, i) && (!estimatedPositionXReached) || (!estimatedPositionYReached))
        {
            if (!estimatedPositionXReached)
            {
                gSkillBox[i].position.x += (gSkillBox[i].velocity.x) ? ((gSkillBox[i].velocity.x) / (abs(gSkillBox[i].velocity.x))) : 0;
                estimatedPositionXReached = (estimatedPositionX == gSkillBox[i].position.x);
                if (boxInTerrain(kSkillBoxNumber, i))
                {
                    gSkillBox[i].position.x -= (gSkillBox[i].velocity.x) ? ((gSkillBox[i].velocity.x) / (abs(gSkillBox[i].velocity.x))) : 0;
                    estimatedPositionXReached   = true;
                    estimatedPositionYReached   = true;
                    gSkillBox[i].velocity.x     = 0;
                    gSkillBox[i].acceleration.x = 0;
                    gSkillBox[i].velocity.y     = 0;
                    gSkillBox[i].acceleration.y = 0;
                }
            }
            if (!estimatedPositionYReached)
            {
                gSkillBox[i].position.y += (gSkillBox[i].velocity.y) ? ((gSkillBox[i].velocity.y) / (abs(gSkillBox[i].velocity.y))) : 0;
                estimatedPositionYReached = (estimatedPositionY == gSkillBox[i].position.y);
                if (boxInTerrain(kSkillBoxNumber, i))
                {
                    gSkillBox[i].position.y -= (gSkillBox[i].velocity.y) ? ((gSkillBox[i].velocity.y) / (abs(gSkillBox[i].velocity.y))) : 0;
                    estimatedPositionXReached   = true;
                    estimatedPositionYReached   = true;
                    gSkillBox[i].velocity.x     = 0;
                    gSkillBox[i].acceleration.x = 0;
                    gSkillBox[i].velocity.y     = 0;
                    gSkillBox[i].acceleration.y = 0;
                }
            }
        }
        if (!boxLanded(kSkillBoxNumber, i) && !boxInTerrain(kSkillBoxNumber, i))
        {
            gSkillBox[i].acceleration.y = kGravityAcceleration;
        }
    }
}
/*
██████   ██████  ██   ██ ██ ███    ██ ████████ ███████ ██████  ██████   █████  ██ ███    ██
██   ██ ██    ██  ██ ██  ██ ████   ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ████   ██
██████  ██    ██   ███   ██ ██ ██  ██    ██    █████   ██████  ██████  ███████ ██ ██ ██  ██
██   ██ ██    ██  ██ ██  ██ ██  ██ ██    ██    ██      ██   ██ ██   ██ ██   ██ ██ ██  ██ ██
██████   ██████  ██   ██ ██ ██   ████    ██    ███████ ██   ██ ██   ██ ██   ██ ██ ██   ████
*/

bool boxInTerrain(int boxType, int boxNum)
{
    int      boxWidth;     // 对应箱子的宽度
    int      boxHeight;    // 对应箱子的高度
    VectorXY boxPosition;
    int      boxEdgeIngnorance;
    // 获取数据
    switch (boxType)
    {
    case kMedicalBoxNumber:
        boxWidth          = kMedicalBoxSizeX;
        boxHeight         = kMedicalBoxSizeY;
        boxPosition       = gMedicalBox[boxNum].position;
        boxEdgeIngnorance = kMedicalBoxEdgeIngnorance;
        break;
    case kWeaponBoxNumber:
        boxWidth          = kWeaponBoxSizeX;
        boxHeight         = kWeaponBoxSizeY;
        boxPosition       = gWeaponBox[boxNum].position;
        boxEdgeIngnorance = kWeaponBoxEdgeIngnorance;
        break;
    case kSkillBoxNumber:
        boxWidth          = kSkillBoxSizeX;
        boxHeight         = kSkillBoxSizeY;
        boxPosition       = gSkillBox[boxNum].position;
        boxEdgeIngnorance = kSkillBoxEdgeIngnorance;
        break;
    }
    int left = ((boxPosition.x + boxEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;
    int top  = ((boxPosition.y + boxEdgeIngnorance) / kTerrainHeight) * kTerrainHeight + 1;
    int right, bottom;

    if ((boxPosition.x + boxWidth - boxEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = boxPosition.x + boxWidth - boxEdgeIngnorance;
    }
    else
    {
        right = ((boxPosition.x + boxWidth - boxEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((boxPosition.y + boxHeight - boxEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = boxPosition.y + boxHeight - boxEdgeIngnorance;
    }
    else
    {
        bottom = ((boxPosition.y + boxHeight - boxEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }
    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int topTerrainCoordinate    = (top - 1) / kTerrainHeight;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;
    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        for (int j = topTerrainCoordinate; j <= bottomTerrainCoordinate; j++)
            if (!terrain[i][j].isDestoried)
                return true;
    return false;
}

/*
██████   ██████  ██   ██ ██       █████  ███    ██ ██████  ███████ ██████
██   ██ ██    ██  ██ ██  ██      ██   ██ ████   ██ ██   ██ ██      ██   ██
██████  ██    ██   ███   ██      ███████ ██ ██  ██ ██   ██ █████   ██   ██
██   ██ ██    ██  ██ ██  ██      ██   ██ ██  ██ ██ ██   ██ ██      ██   ██
██████   ██████  ██   ██ ███████ ██   ██ ██   ████ ██████  ███████ ██████
*/

bool boxLanded(int boxType, int boxNum)
{
    int      boxWidth;     // 对应箱子的宽度
    int      boxHeight;    // 对应箱子的高度
    VectorXY boxPosition;
    int      boxEdgeIngnorance;
    // 获取数据
    switch (boxType)
    {
    case kMedicalBoxNumber:
        boxWidth          = kMedicalBoxSizeX;
        boxHeight         = kMedicalBoxSizeY;
        boxPosition       = gMedicalBox[boxNum].position;
        boxEdgeIngnorance = kMedicalBoxEdgeIngnorance;
        break;
    case kWeaponBoxNumber:
        boxWidth          = kWeaponBoxSizeX;
        boxHeight         = kWeaponBoxSizeY;
        boxPosition       = gWeaponBox[boxNum].position;
        boxEdgeIngnorance = kWeaponBoxEdgeIngnorance;
        break;
    case kSkillBoxNumber:
        boxWidth          = kSkillBoxSizeX;
        boxHeight         = kSkillBoxSizeY;
        boxPosition       = gSkillBox[boxNum].position;
        boxEdgeIngnorance = kSkillBoxEdgeIngnorance;
        break;
    }

    if ((boxPosition.y + boxHeight - boxEdgeIngnorance) % kTerrainHeight != 0)
        return false;

    // 仿照上面的函数，这次判定人物下面有没有未被摧毁的地块
    int left = ((boxPosition.x + boxEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;

    int right, bottom;

    if ((boxPosition.x + boxWidth - boxEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = boxPosition.x + boxWidth - boxEdgeIngnorance;
    }
    else
    {
        right = ((boxPosition.x + boxWidth - boxEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((boxPosition.y + boxHeight - boxEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = boxPosition.y + boxHeight - boxEdgeIngnorance;
    }
    else
    {
        bottom = ((boxPosition.y + boxHeight - boxEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;


    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        if (!terrain[i][bottomTerrainCoordinate + 1].isDestoried)
            return true;
    return false;
}
/*
███████ ██   ██ ██ ██      ██      ██    ██ ██████  ██████   █████  ████████ ███████
██      ██  ██  ██ ██      ██      ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
███████ █████   ██ ██      ██      ██    ██ ██████  ██   ██ ███████    ██    █████
     ██ ██  ██  ██ ██      ██      ██    ██ ██      ██   ██ ██   ██    ██    ██
███████ ██   ██ ██ ███████ ███████  ██████  ██      ██████  ██   ██    ██    ███████
*/

void skillUpdate(void)
{
    if (gRobotSkillOn)
    {
        switch (gSkillSelected)
        {
        case iNoSkill:
            gSkillRangeSelecting  = false;
            gSkillTargetSelecting = false;
            break;
        case iCure:
            gSkillRangeSelecting  = true;
            gSkillTargetSelecting = false;
            break;
        case iTransfer:
            gSkillRangeSelecting  = false;
            gSkillTargetSelecting = false;
            break;
        case iSafeTransfer:
            gSkillRangeSelecting  = false;
            gSkillTargetSelecting = false;
            break;
        case iProtect:
            gSkillRangeSelecting  = false;
            gSkillTargetSelecting = true;
            break;
        }
    }
}

/*
 ██████   █████  ███    ███ ███████ ███████ ████████  █████  ████████ ██    ██ ███████ ██    ██ ██████  ██████   █████  ████████ ███████
██       ██   ██ ████  ████ ██      ██         ██    ██   ██    ██    ██    ██ ██      ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
██   ███ ███████ ██ ████ ██ █████   ███████    ██    ███████    ██    ██    ██ ███████ ██    ██ ██████  ██   ██ ███████    ██    █████
██    ██ ██   ██ ██  ██  ██ ██           ██    ██    ██   ██    ██    ██    ██      ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
 ██████  ██   ██ ██      ██ ███████ ███████    ██    ██   ██    ██     ██████  ███████  ██████  ██      ██████  ██   ██    ██    ███████
*/

void gameStatusUpdate(void)
{
    // 根据地图上机器人更新
    int factionAlive  = 0;
    int winnerPointer = -1;
    for (int i = 0; i < gFactionNumber; i++)
    {
        if (faction[i].alive)
        {
            factionAlive++;
            winnerPointer = i;
        }
    }
    if (factionAlive <= 1)
    {
        Sleep(3000);
        gameStatus.status = Game_end;
    }

    switch (gameStatus.status)
    {
    case Game_start:
        gameStatus.hPicture = hWelcomeBackgroundPicture;
        break;
    case Game_setting:
    case Game_running:
        gameStatus.hPicture = hGameBackgroundPicture;
        break;
    case Game_pause:
        gameStatus.hPicture = hPauseBackgroundPicture;
        break;
    case Game_help:
    case Game_end:
    default:
        break;
    }
}
/*
 ██████   █████  ███    ███ ███████ ██████  ██    ██ ████████ ████████  ██████  ███    ██  ██████ ██      ██  ██████ ██   ██ ███████ ██████
██       ██   ██ ████  ████ ██      ██   ██ ██    ██    ██       ██    ██    ██ ████   ██ ██      ██      ██ ██      ██  ██  ██      ██   ██
██   ███ ███████ ██ ████ ██ █████   ██████  ██    ██    ██       ██    ██    ██ ██ ██  ██ ██      ██      ██ ██      █████   █████   ██   ██
██    ██ ██   ██ ██  ██  ██ ██      ██   ██ ██    ██    ██       ██    ██    ██ ██  ██ ██ ██      ██      ██ ██      ██  ██  ██      ██   ██
 ██████  ██   ██ ██      ██ ███████ ██████   ██████     ██       ██     ██████  ██   ████  ██████ ███████ ██  ██████ ██   ██ ███████ ██████
*/

BOOL gameButtonClicked(POINT ptMouse, RECT rectButton)
{
    // 鼠标点击时触发该函数
    // 用来判断鼠标是不是点在某个矩形里面
    RECT temp = rectButton;
    return PtInRect(&rectButton, ptMouse);
}
/*
██   ██ ███████ ██    ██ ██████   ██████  ██     ██ ███    ██
██  ██  ██       ██  ██  ██   ██ ██    ██ ██     ██ ████   ██
█████   █████     ████   ██   ██ ██    ██ ██  █  ██ ██ ██  ██
██  ██  ██         ██    ██   ██ ██    ██ ██ ███ ██ ██  ██ ██
██   ██ ███████    ██    ██████   ██████   ███ ███  ██   ████
*/

void keyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case 'W':    // W键上跳，设定速度与加速度。跳起后，无法控制。
        if ((!gRobotSkillOn) && (!gRobotWeaponOn) && (!faction[gFactionControlled].robot[gRobotControlled].isJumping))
        {
            faction[gFactionControlled].robot[gRobotControlled].velocity.y     = -kRobotVelocityY_startJump;
            faction[gFactionControlled].robot[gRobotControlled].acceleration.y = kGravityAcceleration;
            faction[gFactionControlled].robot[gRobotControlled].isJumping      = true;
            if (faction[gFactionControlled].robot[gRobotControlled].velocity.x > 0)
            {
                faction[gFactionControlled].robot[gRobotControlled].velocity.x = kRobotVelocityJumping;
            }
            else if (faction[gFactionControlled].robot[gRobotControlled].velocity.x < 0)
            {
                faction[gFactionControlled].robot[gRobotControlled].velocity.x = -kRobotVelocityJumping;
            }
        }
        break;
    case 'A':
        if ((!gRobotSkillOn) && (!gRobotWeaponOn) /*&& (!faction[gFactionControlled].robot[gRobotControlled].isJumping)*/)
        {
            if (!faction[gFactionControlled].robot[gRobotControlled].isJumping)
                faction[gFactionControlled].robot[gRobotControlled].velocity.x = -kRobotVelocityX;
            else
                faction[gFactionControlled].robot[gRobotControlled].velocity.x = -kRobotVelocityJumping;
        }
        break;
    case 'D':
        if ((!gRobotSkillOn) && (!gRobotWeaponOn) /*&& (!faction[gFactionControlled].robot[gRobotControlled].isJumping)*/)
        {
            if (!faction[gFactionControlled].robot[gRobotControlled].isJumping)
                faction[gFactionControlled].robot[gRobotControlled].velocity.x = kRobotVelocityX;
            else
                faction[gFactionControlled].robot[gRobotControlled].velocity.x = kRobotVelocityJumping;
        }
        break;
    case 'R':    // 根据目前打开的界面来决定自己的功能
        if (gRobotWeaponOn)
        {
            faction[gFactionControlled].robot[gRobotControlled].weapon++;
            if (faction[gFactionControlled].robot[gRobotControlled].weapon == kMaxWeaponNum + 1)
                faction[gFactionControlled].robot[gRobotControlled].weapon = 0;
        }
        if (gRobotSkillOn)
        {
            faction[gFactionControlled].robot[gRobotControlled].skill++;
            if (faction[gFactionControlled].robot[gRobotControlled].skill == kMaxSkillNum + 1)
                faction[gFactionControlled].robot[gRobotControlled].skill = 0;
        }
        break;
    case '\t':    // Tab键切换机器人，只在调试时使用
        do
        {
            gRobotControlled++;
            if (gRobotControlled >= gRobotNumberPerFaction)
                gRobotControlled = 0;
        } while (!faction[gFactionControlled].robot[gRobotControlled].alive);
        gRobotWeaponOn = false;
        break;
    case 13:
        do
        {
            gFactionControlled++;
            if (gFactionControlled >= gFactionNumber)
                gFactionControlled = 0;
        } while (!faction[gFactionControlled].alive);
        gRobotControlled = 0;
        gRobotWeaponOn   = false;
        break;
    case 'F':
        if (gRobotSkillOn)
        {
            gRobotSkillOn = false;
        }
        if (!gRobotWeaponOn)
        {
            gRobotWeaponOn  = true;
            gWeaponSelected = faction[gFactionControlled].robot[gRobotControlled].weapon;
        }
        else
        {
            gRobotWeaponOn  = false;
            gWeaponSelected = iNoWeapon;
        }
        break;
    case 'S':
        if (gRobotWeaponOn)    // 关闭武器选择系统
        {
            gRobotWeaponOn = false;
        }
        if (!gRobotSkillOn)    // 打开技能界面
        {
            gRobotSkillOn  = true;
            gSkillSelected = faction[gFactionControlled].robot[gRobotControlled].skill;
        }
        else    // 关闭技能界面
        {
            gRobotSkillOn  = false;
            gSkillSelected = iNoSkill;
        }
        break;
    case 'Q':
        if (gRobotWeaponOn && !gIncreasingWeaponPower && gWeaponSelected)
            gChangingWeaponAngle = 1;
        break;
    case 'E':
        if (gRobotWeaponOn && !gIncreasingWeaponPower && gWeaponSelected)
            gChangingWeaponAngle = -1;
        break;
    case ' ':
        if (gRobotWeaponOn && !gChangingWeaponAngle && gWeaponSelected)
            gIncreasingWeaponPower = true;
        break;
    case 'P':
        if (gameStatus.status == Game_running)
        {
            gameStatus.status = Game_pause;
            gGamePaused       = true;
            break;
        }
        if (gameStatus.status == Game_pause)
        {
            gameStatus.status = Game_running;
            gGamePaused       = false;
            break;
        }
        break;
    case VK_UP:
        if (gCameraY > kCameraLimitTop)
        {
            gCameraY -= kCameraVelocity;
            if (gCameraY < kCameraLimitTop)
                gCameraY = kCameraLimitTop;
        }
        break;
    case VK_DOWN:
        if (gCameraY < kCameraLimitButtom)
        {
            gCameraY += kCameraVelocity;
            if (gCameraY > kCameraLimitButtom)
                gCameraY = kCameraLimitButtom;
        }
        break;
    case VK_LEFT:
        if (gCameraX > kCameraLimitLeft)
        {
            gCameraX -= kCameraVelocity;
            if (gCameraX < kCameraLimitLeft)
                gCameraX = kCameraLimitLeft;
        }
        break;
    case VK_RIGHT:
        if (gCameraX < kCameraLimitRight)
        {
            gCameraX += kCameraVelocity;
            if (gCameraX > kCameraLimitRight)
                gCameraX = kCameraLimitRight;
        }
        break;
    default:
        break;
    }
}
/*
██   ██ ███████ ██    ██ ██    ██ ██████
██  ██  ██       ██  ██  ██    ██ ██   ██
█████   █████     ████   ██    ██ ██████
██  ██  ██         ██    ██    ██ ██
██   ██ ███████    ██     ██████  ██
*/

void keyUp(HWND hWnd, WPARAM wParam, LPARAM lPara)
{
    switch (wParam)
    {
    case 'W':    // 速度置零，但是当跳跃时控制失效
        if ((!gRobotWeaponOn) && (!faction[gFactionControlled].robot[gRobotControlled].isJumping))
            faction[gFactionControlled].robot[gRobotControlled].velocity.y = 0;
        break;
    case 'A':
        if ((!gRobotWeaponOn) && (!faction[gFactionControlled].robot[gRobotControlled].isJumping))
            faction[gFactionControlled].robot[gRobotControlled].velocity.x = 0;
        break;
    case 'D':
        if ((!gRobotWeaponOn) && (!faction[gFactionControlled].robot[gRobotControlled].isJumping))
            faction[gFactionControlled].robot[gRobotControlled].velocity.x = 0;
        break;
    case 'Q':
    case 'E':
        if (gRobotWeaponOn && !gIncreasingWeaponPower && gWeaponSelected)
            gChangingWeaponAngle = 0;
        break;
    case ' ':
        if (gRobotWeaponOn && !gChangingWeaponAngle && gWeaponSelected)
        {
            gIncreasingWeaponPower = false;
            weaponLaunch();
        }
    default:
        break;
    }
}
/*
██      ███████ ███████ ████████ ██████  ██    ██ ████████ ████████  ██████  ███    ██ ██████   ██████  ██     ██ ███    ██
██      ██      ██         ██    ██   ██ ██    ██    ██       ██    ██    ██ ████   ██ ██   ██ ██    ██ ██     ██ ████   ██
██      █████   █████      ██    ██████  ██    ██    ██       ██    ██    ██ ██ ██  ██ ██   ██ ██    ██ ██  █  ██ ██ ██  ██
██      ██      ██         ██    ██   ██ ██    ██    ██       ██    ██    ██ ██  ██ ██ ██   ██ ██    ██ ██ ███ ██ ██  ██ ██
███████ ███████ ██         ██    ██████   ██████     ██       ██     ██████  ██   ████ ██████   ██████   ███ ███  ██   ████
*/
void leftButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 左键按下函数
    // 获取鼠标点击的位置
    POINT ptMouse;
    ptMouse.x = LOWORD(lParam);
    ptMouse.y = HIWORD(lParam);

    // 以下代码只是针对开始游戏按钮
    RECT temp;
    temp.left   = gameStartButton.position.x;
    temp.right  = gameStartButton.position.x + gameStartButton.size.x;
    temp.top    = gameStartButton.position.y;
    temp.bottom = gameStartButton.position.y + gameStartButton.size.y;
    if (gameStatus.status == 0 && gameButtonClicked(ptMouse, temp))
    {
        SetTimer(hWnd, kTimerID, kTimerElapse, NULL);
        gameStatus.status = Game_running;
        InvalidateRect(hWnd, NULL, TRUE);    // 重绘
    }
}
