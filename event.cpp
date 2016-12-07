/*
todolist
开始界面布局

帮助界面布局
地图选择界面布局

帮助界面，地图选择界面
随机地图生成器，能输入种子
显示弹药量和技能点
对战AI
地形贴图
武器箱，医疗箱，技能箱
背景音乐
放弃操作
==important==
- 游戏标题和开始按钮
- 显示胜利方
- 游戏结束后可以返回开始界面
- 游戏结束后可以重新开始游戏
- 至少两张背景图片
- 帮助界面和地图选择界面
- 多个可选地图
- 输入种子来进行随机地形
- 显示弹药量和技能点
- 子母手雷和弓箭
- 攻击技能
- 与AI进行对战
- 使用背景音乐
- 使用背景音效
= 坠落伤害
*/

#include "event.h"
#include "global.h"
#include "item.h"


/*
██ ███    ██ ██ ████████ ██  █████  ██      ██ ███████ ███████
██ ████   ██ ██    ██    ██ ██   ██ ██      ██    ███  ██
██ ██ ██  ██ ██    ██    ██ ███████ ██      ██   ███   █████
██ ██  ██ ██ ██    ██    ██ ██   ██ ██      ██  ███    ██
██ ██   ████ ██    ██    ██ ██   ██ ███████ ██ ███████ ███████
*/

void initialize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    srand(unsigned((time(0))));

    // 将资源载入到资源句柄中
    hGameBackgroundPicture    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_GameBackground_01));
    hWelcomeBackgroundPicture = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_WelcomeBackground));
    hHelpBackgroundPicture    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_HelpBackground));
    hPauseBackgroundPicture   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_GameBackground_01));
    hRockPicture              = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Rock_01));
    hRobotPicture[0]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_01_left));
    hRobotPicture[2]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_02_left));
    hRobotPicture[4]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_03_left));
    hRobotPicture[6]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_04_left));
    hRobotPicture[1]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_01_right));
    hRobotPicture[3]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_02_right));
    hRobotPicture[5]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_03_right));
    hRobotPicture[7]          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(Robot_04_right));
    hGameStartButtonPicture   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_StartGame));
    hGameExitButtonPicture    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ExitGame));
    hGameHelpButtonPicture    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_Help));
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
    hGrenadeExplosionPicture  = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_GrenadeExplosion));
    hHelpExitButtonPicture    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ExitHelp));


    //
    gFactionNumber         = 2;    //kMaxFactionNumber;
    gRobotNumberPerFaction = 2;    // kMaxRobotNumberPerFaction;
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
        faction[i] = creatFaction(i, false);
        for (int j = 0; j < gRobotNumberPerFaction; j++)
        {
            if (faction[i].robot[j].direction == kFacingLeft)
            {
                faction[i].robot[j].hPicture = hRobotPicture[getRobotPicture(i, kFacingLeft)];
            }
            if (faction[i].robot[j].direction == kFacingRight)
            {
                faction[i].robot[j].hPicture = hRobotPicture[getRobotPicture(i, kFacingRight)];
            }
        }
    }

    {
        VectorXY temp;
        temp.x        = 0;
        temp.y        = 0;
        gVirtualRobot = creatRobot(-1, temp);
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
    {
        VectorXY temp_1, temp_2;
        temp_1.x        = kButtonWidth;     // 开始游戏按钮的横向大小
        temp_1.y        = kButtonHeight;    // 开始游戏按钮的纵向大小
        temp_2.x        = 275;              // 开始游戏按钮的横坐标
        temp_2.y        = 550;              // 开始游戏按钮的纵坐标
        gameStartButton = creatGameButton(temp_1, temp_2, false, hGameStartButtonPicture);
    }

    {    // TODO
        VectorXY temp_1, temp_2;
        temp_1.x       = kButtonWidth;
        temp_1.y       = kButtonHeight;
        temp_2.x       = 735;
        temp_2.y       = 550;
        gameHelpButton = creatGameButton(temp_1, temp_2, false, hGameHelpButtonPicture);
    }

    {    // TODO
        VectorXY temp_1, temp_2;
        temp_1.x       = kButtonWidth;
        temp_1.y       = kButtonHeight;
        temp_2.x       = 1210;
        temp_2.y       = 550;
        gameExitButton = creatGameButton(temp_1, temp_2, false, hGameExitButtonPicture);
    }

    {    // TODO
        VectorXY temp_1, temp_2;
        temp_1.x       = kButtonWidth;
        temp_1.y       = kButtonHeight;
        temp_2.x       = 1450;
        temp_2.y       = 750;
        helpExitButton = creatGameButton(temp_1, temp_2, false, hHelpExitButtonPicture);
    }


    // 设置游戏状态
    gameStatus.status   = Game_start;
    gameStatus.hPicture = hWelcomeBackgroundPicture;    // 设置背景图片


    switchToNextFaction();
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
            for (int j = 0; j < min(prevHeight + 1, kMinTerrainHeight); j++)
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
            for (int j = 0; j < min(prevHeight + 2, kMinTerrainHeight); j++)
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
            for (int j = 0; j < min(prevHeight + 3, kMinTerrainHeight); j++)
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
            for (int j = 0; j < min(prevHeight + 4, kMinTerrainHeight); j++)
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
            for (int j = 0; j < min(prevHeight + 5, kMinTerrainHeight); j++)
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
            for (int j = 0; j < min(prevHeight + 6, kMinTerrainHeight); j++)
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
    int numOfHole = rand() % (kMaxHoleNumber - kMinHoleNumber + 1) + kMinHoleNumber;
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
    case Game_help:
        renderHelp(hWnd);
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
    TransparentBlt(hdcBuffer, gameStartButton.position.x, gameStartButton.position.y, gameStartButton.size.x, gameStartButton.size.y, hdcBmp, 0, 0, kGameStartButtonPictureX, kGameStartButtonPictureY, RGB(0, 0, 0));

    // 绘制退出按钮
    SelectObject(hdcBmp, gameExitButton.hPicture);
    TransparentBlt(hdcBuffer, gameExitButton.position.x, gameExitButton.position.y, gameExitButton.size.x, gameExitButton.size.y, hdcBmp, 0, 0, kGameExitButtonPictureX, kGameExitButtonPictureY, RGB(0, 0, 0));

    // 绘制帮助按钮
    SelectObject(hdcBmp, gameHelpButton.hPicture);
    TransparentBlt(hdcBuffer, gameHelpButton.position.x, gameHelpButton.position.y, gameHelpButton.size.x, gameHelpButton.size.y, hdcBmp, 0, 0, kGameHelpButtonPictureX, kGameHelpButtonPictureY, RGB(0, 0, 0));

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
    HDC         hdc;
    PAINTSTRUCT ps;

    // 开始绘制
    hdc = BeginPaint(hWnd, &ps);

    HDC     hdcBmp, hdcBuffer;
    HBITMAP cptBmp;


    cptBmp    = CreateCompatibleBitmap(hdc, kWorldWidth, kWorldHeight);
    hdcBmp    = CreateCompatibleDC(hdc);
    hdcBuffer = CreateCompatibleDC(hdc);

    // 绘制背景图片
    SelectObject(hdcBuffer, cptBmp);

    // 如果需要重绘则重绘并保存为Bmp，否则直接读取Bmp
    if (gTerrainNeedUpdate)
    {
        gameStatus.hPicture = hGameBackgroundPicture;
    RENDER_INIT:
        // 绘制背景图片至hdc
        SelectObject(hdcBmp, gameStatus.hPicture);
        //TransparentBlt(hdcBuffer, 0, 0, kWorldWidth, kWorldHeight, hdcBmp, 0, 0, kWindowWidth, kWindowHeight, RGB(255, 0, 0));
        BitBlt(hdcBuffer, 0, 0, kWorldWidth, kWorldHeight, hdcBmp, 0, 0, SRCCOPY);
        // 绘制地块
        SelectObject(hdcBmp, hTerrainPicture);
        for (int i = 0; i < kTerrainNumberX; i++)
            for (int j = 0; j < kTerrainNumberY; j++)
            {
                TransparentBlt(hdcBuffer, terrain[i][j].position.left, terrain[i][j].position.top, kTerrainWidth, kTerrainHeight, hdcBmp, 18 * (terrain[i][j].picturePosition.x - 1), 18 * (terrain[i][j].picturePosition.y - 1), 16, 16, RGB(255, 255, 255));
            }
        gTerrainNeedUpdate = false;    // 直到下次地块破坏前，无需更新

        BYTE *pData  = NULL;
        HDC   hdcMem = CreateCompatibleDC(hdcBuffer);
        // 设置位图信息结构体
        BITMAPINFO bmpInfo           = {};
        bmpInfo.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
        bmpInfo.bmiHeader.biWidth    = kWorldWidth;
        bmpInfo.bmiHeader.biHeight   = kWorldHeight;
        bmpInfo.bmiHeader.biPlanes   = 1;
        bmpInfo.bmiHeader.biBitCount = 24;
        // 创建新的位图
        if (gRenderOnce)
        {
            DeleteObject(hTerrainBmp);
        }
        hTerrainBmp = CreateDIBSection(hdcMem, &bmpInfo, DIB_RGB_COLORS, reinterpret_cast<VOID **>(&pData), NULL, 0);
        SelectObject(hdcMem, hTerrainBmp);
        BitBlt(hdcMem, 0, 0, kWorldWidth, kWorldHeight, hdcBuffer, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);
        gRenderOnce = true;
    }

    // 将位图转到缓冲区上
    SelectObject(hdcBmp, hTerrainBmp);
    BitBlt(hdcBuffer, 0, 0, kWorldWidth, kWorldHeight, hdcBmp, 0, 0, SRCCOPY);


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
                int width = (kHitPointBarWidth)*faction[i].robot[j].hitPoint / kRobotFullHitPoint;
                SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
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
    MoveToEx(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x + kRobotSizeX / 2, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2 - (kRobotControlSignHeight + kRobotControlSignLength), NULL);
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

    // 绘制机器人的武器
    if (gRobotWeaponOn)
    {
        switch (gWeaponSelected)
        {
        case iNoWeapon:
            break;
        case iMissile:
            if (faction[gFactionControlled].robot[gRobotControlled].direction == kFacingLeft)
            {
                SelectObject(hdcBmp, hMissilePictureLeft);
                TransparentBlt(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 3, kMissileSizeX, kMissileSizeY, hdcBmp, 0, 0, kMissilePictureX, kMissilePictureY, RGB(255, 255, 255));
            }
            else
            {
                SelectObject(hdcBmp, hMissilePictureRight);
                TransparentBlt(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 3, kMissileSizeX, kMissileSizeY, hdcBmp, 0, 0, kMissilePictureX, kMissilePictureY, RGB(255, 255, 255));
            }
            break;
        case iGrenade:


            SelectObject(hdcBmp, hGrenadePicture);
            TransparentBlt(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2, kGrenadeSizeX, kGrenadeSizeY, hdcBmp, 0, 0, kGrenadePictureX, kGrenadePictureY, RGB(255, 255, 255));
            break;

        case iStickyBomb:

            SelectObject(hdcBmp, hStickyBombPicture);
            TransparentBlt(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2, kStickyBombSizeX, kStickyBombSizeY, hdcBmp, 0, 0, kStickyBombPictureX, kStickyBombPictureY, RGB(255, 255, 255));


            break;

        case iTNT:

            SelectObject(hdcBmp, hTNTPicture);
            TransparentBlt(hdcBuffer, faction[gFactionControlled].robot[gRobotControlled].position.x, faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2, kTNTSizeX, kTNTSizeY, hdcBmp, 0, 0, kTNTPictureX, kTNTPictureY, RGB(255, 255, 255));


            break;
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


    // 绘制武器爆炸效果
    // TODO
    if (gPlayingGrenadeAnimation)
    {
        SelectObject(hdcBmp, hGrenadeExplosionPicture);
        TransparentBlt(hdcBuffer, gGrenadeAnimationPosition.x, gGrenadeAnimationPosition.y, kGrenadeExplosionAnimationSizeX, kGrenadeExplosionAnimationSizeY, hdcBmp, 0, (4 - gGrenadeAnimationTimeRemain / 10) * (kGrenadeExplosionPictureSizeY / kGrenadeExplosionAnimationFrame), kGrenadeExplosionPictureSizeX, kGrenadeExplosionPictureSizeY / kGrenadeExplosionAnimationFrame, RGB(0, 0, 255));
    }


    // 绘制到屏幕
    BitBlt(hdc, 0, 0, kWindowWidth, kWindowHeight, hdcBuffer, gCameraPosition.x, gCameraPosition.y, SRCCOPY);
    // TransparentBlt(hdc, 0, 0, kWindowWidth, kWindowHeight, hdcBuffer, gCameraPosition.x, gCameraPosition.y, 1.5*kWindowWidth, 1.5*kWindowHeight, RGB(254, 254, 254));

    // 阵营血量显示

    HBRUSH factionHPBarBrush;
    int    factionHPBarWidth;

    SelectObject(hdc, GetStockObject(NULL_PEN));
    factionHPBarBrush = CreateSolidBrush(Color_Faction_1);
    SelectObject(hdc, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[0].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdc, 1 * kFactionHPBarDistance + 0 * kFactionHPBarWidth, kFactionHPBarDistance, 1 * kFactionHPBarDistance + 0 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    SelectObject(hdc, GetStockObject(NULL_PEN));
    factionHPBarBrush = CreateSolidBrush(Color_Faction_2);
    SelectObject(hdc, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[1].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdc, 3 * kFactionHPBarDistance + 1 * kFactionHPBarWidth, kFactionHPBarDistance, 3 * kFactionHPBarDistance + 1 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    SelectObject(hdc, GetStockObject(NULL_PEN));
    factionHPBarBrush = CreateSolidBrush(Color_Faction_3);
    SelectObject(hdc, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[2].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdc, 5 * kFactionHPBarDistance + 2 * kFactionHPBarWidth, kFactionHPBarDistance, 5 * kFactionHPBarDistance + 2 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    SelectObject(hdc, GetStockObject(NULL_PEN));
    factionHPBarBrush = CreateSolidBrush(Color_Faction_4);
    SelectObject(hdc, factionHPBarBrush);
    factionHPBarWidth = kFactionHPBarWidth * faction[3].hitPoint / (gRobotNumberPerFaction * kRobotFullHitPoint);
    drawClosedRectangle(hdc, 7 * kFactionHPBarDistance + 3 * kFactionHPBarWidth, kFactionHPBarDistance, 7 * kFactionHPBarDistance + 3 * kFactionHPBarWidth + factionHPBarWidth, kFactionHPBarHeight + kFactionHPBarDistance);
    DeleteObject(factionHPBarBrush);

    // 绘制log
    TCHAR szDist[1000] = L"";
    SetTextColor(hdc, RGB(255, 0, 0));    // 设置颜色
    SetBkMode(hdc, TRANSPARENT);
    wsprintf(szDist, L"ammo %d %d %d %d", faction[gFactionControlled].ammoMissile, faction[gFactionControlled].ammoGrenade, faction[gFactionControlled].ammoStickyBomb, faction[gFactionControlled].ammoTNT);
    TextOut(hdc, kWindowWidth - 500, 15, szDist, _tcslen(szDist));
    wsprintf(szDist, L"weaponOn %d   skillOn %d", faction[gFactionControlled].robot[gRobotControlled].weapon, faction[gFactionControlled].robot[gRobotControlled].skill);
    TextOut(hdc, kWindowWidth - 500, 35, szDist, _tcslen(szDist));
    wsprintf(szDist, L"mov %d-%d   esc %d-%d  wait %d-%d", gRobotMoving, gRobotMovingTimeRemain, gRobotEscaping, gRobotEscapingTimeRemain, gRoundWaiting, gRoundWaitingTimeRemain);
    TextOut(hdc, kWindowWidth - 500, 55, szDist, _tcslen(szDist));
    wsprintf(szDist, L"currFac %d   currRob %d   wind %d", gFactionControlled, gRobotControlled, gWindPower);
    TextOut(hdc, kWindowWidth - 500, 75, szDist, _tcslen(szDist));

    // 绘制info

    // 释放资源
    DeleteObject(cptBmp);
    DeleteDC(hdcBuffer);
    DeleteDC(hdcBmp);

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
    BitBlt(hdcBuffer, 0, 0, kWindowWidth, kWindowHeight, hdcBmp, gCameraPosition.x, gCameraPosition.y, SRCCOPY);

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
██████  ███████ ███    ██ ██████  ███████ ██████  ██   ██ ███████ ██      ██████
██   ██ ██      ████   ██ ██   ██ ██      ██   ██ ██   ██ ██      ██      ██   ██
██████  █████   ██ ██  ██ ██   ██ █████   ██████  ███████ █████   ██      ██████
██   ██ ██      ██  ██ ██ ██   ██ ██      ██   ██ ██   ██ ██      ██      ██
██   ██ ███████ ██   ████ ██████  ███████ ██   ██ ██   ██ ███████ ███████ ██
*/

void renderHelp(HWND hWnd)
{
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


    // 绘制退出按钮
    SelectObject(hdcBmp, helpExitButton.hPicture);
    TransparentBlt(hdcBuffer, helpExitButton.position.x, helpExitButton.position.y, helpExitButton.size.x, helpExitButton.size.y, hdcBmp, 0, 0, hHelpExitButtonPictureX, hHelpExitButtonPictureY, RGB(0, 0, 0));


    /*
    RECT       rect;
    TEXTMETRIC tm;
    GetTextMetrics(ps.hdc, &tm);
    rect.top    = kWindowHeight / 2 - 1.5 * tm.tmHeight;
    rect.left   = 0;
    rect.right  = kWindowWidth;
    rect.bottom = rect.top + 3 * tm.tmHeight;
    SetTextColor(hdcBuffer, RGB(255, 255, 255));
    SetBkMode(hdcBuffer, TRANSPARENT);
    DrawTextW(hdcBuffer, L"这是帮助界面", -1, &rect, DT_CENTER);
    */

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
        cameraUpdate();
        weaponUpdate();
        terrainUpdate();    // 更新所有地块状态
        medicalBoxUpdate();
        weaponBoxUpdate();
        skillBoxUpdate();
        weaponAnimationUpdate();
        if (gRoundWaiting)
        {
            gRoundWaitingTimeRemain--;
            if (gRoundWaitingTimeRemain <= 0)
            {
                gRoundWaiting   = false;
                gRobotMoving    = true;
                gCameraOverride = false;
                setCameraOnRobot(gFactionControlled, gRobotControlled);
                cameraUpdate();
            }
        }
        else if (gRobotMoving)
        {
            gRobotMovingTimeRemain--;
            if (gRobotMovingTimeRemain <= 0)
                switchToNextFaction();
        }
        else if (gRobotEscaping)
        {
            gRobotEscapingTimeRemain--;
            if (gRobotEscapingTimeRemain <= 0)
                switchToNextFaction();
        }
    }
    gameStatusUpdate();    // 更新游戏状态，应该是判断游戏是否结束或移交控制权之类
    if (gameStatus.status == Game_end)
        KillTimer(hWnd, kTimerID);
    InvalidateRect(hWnd, NULL, FALSE);    // 该函数向指定的窗体更新区域添加一个矩形，然后窗口客户区域的这一部分将被重新绘制。
}
/*
██████   ██████  ██    ██ ███    ██ ██████  ██    ██ ██████  ██████   █████  ████████ ███████
██   ██ ██    ██ ██    ██ ████   ██ ██   ██ ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
██████  ██    ██ ██    ██ ██ ██  ██ ██   ██ ██    ██ ██████  ██   ██ ███████    ██    █████
██   ██ ██    ██ ██    ██ ██  ██ ██ ██   ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
██   ██  ██████   ██████  ██   ████ ██████   ██████  ██      ██████  ██   ██    ██    ███████
*/

void roundUpdate(void)
{
    windUpdate();
    boxRefresh();
    seaLevelUpdate();
    terrainShapeUpdate(0, 0, kTerrainNumberX - 1, kTerrainNumberY - 1);
    gRobotWeaponOn           = false;
    gRobotSkillOn            = false;
    gRobotMoving             = false;
    gRobotEscaping           = false;
    gRoundWaiting            = true;
    gRobotMovingTimeRemain   = kActionTime;
    gRobotEscapingTimeRemain = kWithdrawTime;
    gRoundWaitingTimeRemain  = kWaitTime;
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

            if ((faction[i].robot[j].position.y > (gSeaLevel - 1) * kTerrainHeight) && (faction[i].robot[j].alive))    // 低于海平面判定死亡
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
                    faction[i].robot[j].hPicture  = hRobotPicture[getRobotPicture(i, kFacingRight)];
                    faction[i].robot[j].direction = kFacingRight;
                }
                else if ((faction[i].robot[j].direction == kFacingRight) && (faction[i].robot[j].velocity.x < 0))
                {
                    faction[i].robot[j].hPicture  = hRobotPicture[getRobotPicture(i, kFacingLeft)];
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
            gSkillSelected  = faction[gFactionControlled].robot[gRobotControlled].skill;
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
                gameStatusUpdate();
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

bool robotInTerrainVirtual(VectorXY position)    // TODO merge code
{
    // 计算覆盖的terrain所占区域
    int left = ((position.x + kRobotEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;
    int top  = ((position.y + kRobotEdgeIngnorance) / kTerrainHeight) * kTerrainHeight + 1;

    int right, bottom;

    if ((position.x + kRobotSizeX - kRobotEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = position.x + kRobotSizeX - kRobotEdgeIngnorance;
    }
    else
    {
        right = ((position.x + kRobotSizeX - kRobotEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((position.y + kRobotSizeY - kRobotEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = position.y + kRobotSizeY - kRobotEdgeIngnorance;
    }
    else
    {
        bottom = ((position.y + kRobotSizeY - kRobotEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
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

BOOL robotLandedVirtual(VectorXY position)    // TODO merge code
{
    // return true;
    // 假定robot是不在地形里面的
    // 脚不在地上
    if ((position.y + kRobotSizeY - kRobotEdgeIngnorance) % kTerrainHeight != 0)
        return false;

    // 仿照上面的函数，这次判定人物下面有没有未被摧毁的地块
    int left = ((position.x + kRobotEdgeIngnorance) / kTerrainWidth) * kTerrainWidth + 1;

    int right, bottom;

    if ((position.x + kRobotSizeX - kRobotEdgeIngnorance) % kTerrainWidth == 0)    // 恰好在边上
    {
        right = position.x + kRobotSizeX - kRobotEdgeIngnorance;
    }
    else
    {
        right = ((position.x + kRobotSizeX - kRobotEdgeIngnorance) / kTerrainWidth + 1) * kTerrainWidth;
    }

    if ((position.y + kRobotSizeY - kRobotEdgeIngnorance) % kTerrainHeight == 0)    // 恰好在边上
    {
        bottom = position.y + kRobotSizeY - kRobotEdgeIngnorance;
    }
    else
    {
        bottom = ((position.y + kRobotSizeY - kRobotEdgeIngnorance) / kTerrainHeight + 1) * kTerrainHeight;
    }

    int leftTerrainCoordinate   = (left - 1) / kTerrainWidth;
    int rightTerrainCoordinate  = right / kTerrainWidth - 1;
    int bottomTerrainCoordinate = bottom / kTerrainHeight - 1;


    for (int i = leftTerrainCoordinate; i <= rightTerrainCoordinate; i++)
        if (!terrain[i][bottomTerrainCoordinate + 1].isDestoried)
            return true;
    return false;
}


void setCameraOnRobot(int factionNum, int robotNum)
{
    gCameraTargetPosition.x = faction[gFactionControlled].robot[gRobotControlled].position.x - kWindowWidth / 2;
    gCameraTargetPosition.y = faction[gFactionControlled].robot[gRobotControlled].position.y - kWindowHeight / 2;

    if (gCameraTargetPosition.x > kCameraLimitRight)
    {
        gCameraTargetPosition.x = kCameraLimitRight;
    }
    if (gCameraTargetPosition.x < kCameraLimitLeft)
    {
        gCameraTargetPosition.x = kCameraLimitLeft;
    }
    if (gCameraTargetPosition.y > kCameraLimitButtom)
    {
        gCameraTargetPosition.y = kCameraLimitButtom;
    }
    if (gCameraTargetPosition.y < kCameraLimitTop)
    {
        gCameraTargetPosition.y = kCameraLimitTop;
    }
    gCameraVelocity.x = (gCameraTargetPosition.x - gCameraPosition.x) / kCameraSwitchTime;
    gCameraVelocity.y = (gCameraTargetPosition.y - gCameraPosition.y) / kCameraSwitchTime;
    gCameraAutoMoving = true;
}
/*
 ██████  █████  ███    ███ ███████ ██████   █████  ██    ██ ██████  ██████   █████  ████████ ███████
██      ██   ██ ████  ████ ██      ██   ██ ██   ██ ██    ██ ██   ██ ██   ██ ██   ██    ██    ██
██      ███████ ██ ████ ██ █████   ██████  ███████ ██    ██ ██████  ██   ██ ███████    ██    █████
██      ██   ██ ██  ██  ██ ██      ██   ██ ██   ██ ██    ██ ██      ██   ██ ██   ██    ██    ██
 ██████ ██   ██ ██      ██ ███████ ██   ██ ██   ██  ██████  ██      ██████  ██   ██    ██    ███████
*/

void cameraUpdate(void)
{
    if (gCameraAutoMoving)
    {
        if (gCameraPosition.x != gCameraTargetPosition.x)
        {
            bool less = (gCameraPosition.x < gCameraTargetPosition.x);
            gCameraPosition.x += gCameraVelocity.x;
            if (((gCameraPosition.x < gCameraTargetPosition.x) != less) || (gCameraPosition.x == gCameraTargetPosition.x))
            {
                gCameraPosition.x = gCameraTargetPosition.x;
            }
        }
        if (gCameraPosition.y != gCameraTargetPosition.y)
        {
            bool less = (gCameraPosition.y < gCameraTargetPosition.y);
            gCameraPosition.y += gCameraVelocity.y;
            if (((gCameraPosition.y < gCameraTargetPosition.y) != less) || (gCameraPosition.y == gCameraTargetPosition.y))
            {
                gCameraPosition.y = gCameraTargetPosition.y;
            }
        }

        if ((gCameraPosition.x == gCameraTargetPosition.x) && (gCameraPosition.y == gCameraTargetPosition.y))
            gCameraAutoMoving = false;
    }
    else if (!gCameraOverride)
    {
        // setCameraOnRobot(gFactionControlled, gRobotControlled);
        gCameraPosition.x = faction[gFactionControlled].robot[gRobotControlled].position.x - kWindowWidth / 2;
        gCameraPosition.y = faction[gFactionControlled].robot[gRobotControlled].position.y - kWindowHeight / 2;

        if (gCameraPosition.x > kCameraLimitRight)
        {
            gCameraPosition.x = kCameraLimitRight;
        }
        if (gCameraPosition.x < kCameraLimitLeft)
        {
            gCameraPosition.x = kCameraLimitLeft;
        }
        if (gCameraPosition.y > kCameraLimitButtom)
        {
            gCameraPosition.y = kCameraLimitButtom;
        }
        if (gCameraPosition.y < kCameraLimitTop)
        {
            gCameraPosition.y = kCameraLimitTop;
        }
    }
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

        if (gChangingWeaponAngle != 0)
        {
            if (cos(gLaunchingAngle) >= 0)
            {
                faction[gFactionControlled].robot[gRobotControlled].direction = kFacingRight;
                faction[gFactionControlled].robot[gRobotControlled].hPicture  = hRobotPicture[getRobotPicture(gFactionControlled, kFacingRight)];
            }
            else
            {
                faction[gFactionControlled].robot[gRobotControlled].direction = kFacingLeft;
                faction[gFactionControlled].robot[gRobotControlled].hPicture  = hRobotPicture[getRobotPicture(gFactionControlled, kFacingLeft)];
            }
        }

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
                // gTNT.acceleration.x = gWindPower * kWindPowerFactor; //TODO

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
            position.x      = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y      = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x      = int(kMissileVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y      = int(-kMissileVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x  = 0;
            acceleration.y  = kGravityAcceleration;
            gMissile        = creatMissile(position, velocity, acceleration, hMissilePictureRight);
            gRobotMoving    = false;
            gRobotEscaping  = true;
            gRobotWeaponOn  = false;
            gWeaponSelected = iNoWeapon;
            gCameraOverride = false;
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
            position.x      = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y      = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x      = int(kGrenadeVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y      = int(-kGrenadeVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x  = 0;
            acceleration.y  = kGravityAcceleration;
            gGrenade        = creatGrenade(position, velocity, acceleration, hGrenadePicture);
            gRobotMoving    = false;
            gRobotEscaping  = true;
            gRobotWeaponOn  = false;
            gWeaponSelected = iNoWeapon;
            gCameraOverride = false;
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
            position.x      = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y      = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x      = int(kStickyBombVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y      = int(-kStickyBombVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x  = 0;
            acceleration.y  = kGravityAcceleration;
            gStickyBomb     = creatStickyBomb(position, velocity, acceleration, hStickyBombPicture);
            gRobotMoving    = false;
            gRobotEscaping  = true;
            gRobotWeaponOn  = false;
            gWeaponSelected = iNoWeapon;
            gCameraOverride = false;
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
            position.x      = faction[gFactionControlled].robot[gRobotControlled].position.x;
            position.y      = faction[gFactionControlled].robot[gRobotControlled].position.y;
            velocity.x      = int(kTNTVelocity * gPower * cos(gLaunchingAngle) / 100);
            velocity.y      = int(-kTNTVelocity * gPower * sin(gLaunchingAngle) / 100);
            acceleration.x  = 0;
            acceleration.y  = kGravityAcceleration;
            gTNT            = creatTNT(position, velocity, acceleration, hTNTPicture);
            gRobotMoving    = false;
            gRobotEscaping  = true;
            gRobotWeaponOn  = false;
            gWeaponSelected = iNoWeapon;
            gCameraOverride = false;
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

            gPlayingGrenadeAnimation    = true;
            gGrenadeAnimationTimeRemain = kGrenadeExplosionAnimationTime;
            gGrenadeAnimationPosition   = gGrenade.position;
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
void weaponAnimationUpdate(void)
{
    // TODO
    if (gPlayingGrenadeAnimation)
    {
        gGrenadeAnimationTimeRemain--;
        if (gGrenadeAnimationTimeRemain <= 0)
        {
            gGrenadeAnimationTimeRemain = 0;
            gPlayingGrenadeAnimation    = false;
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
    left               = max(0, left);
    right              = min(kTerrainNumberX - 1, right);
    top                = max(0, top);
    bottom             = min(kTerrainNumberY - 1, bottom);
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
        }

    seaUpdate();
    for (int i = left; i <= right; i++)
        for (int j = top; j <= bottom; j++)
        {
            VectorXY pos                    = getTerrainBlockPicture(terrain[i][j].connectionStatus);
            terrain[i][j].picturePosition.x = pos.x;
            terrain[i][j].picturePosition.y = pos.y;
        }
}

void terrainShapeUpdate(int x, int y)
{
    terrainShapeUpdate(x, y, x, y);
}

void terrainShapeUpdate(void)
{
    terrainShapeUpdate(0, 0, kTerrainNumberX, kTerrainNumberY);
}

void buildTerrain(VectorXY position)
{
    if (terrain[position.x][position.y].isDestoried && faction[gFactionControlled].ammoBuildingBlock > 0)    // 检查是否有剩余的建筑材料
    {
        VectorXY terrainPositionCenter;    // 计算目标地块的中心位置
        terrainPositionCenter.x = (terrain[position.x][position.y].position.left + terrain[position.x][position.y].position.right) / 2;
        terrainPositionCenter.y = (terrain[position.x][position.y].position.top + terrain[position.x][position.y].position.bottom) / 2;
        VectorXY robotPositionCenter;    // 计算人物的中心位置
        robotPositionCenter.x = faction[gFactionControlled].robot[gRobotControlled].position.x + kRobotSizeX / 2;
        robotPositionCenter.y = faction[gFactionControlled].robot[gRobotControlled].position.y + kRobotSizeY / 2;

        if (pointPointDistanceSquare(terrainPositionCenter.x, terrainPositionCenter.y, robotPositionCenter.x, robotPositionCenter.y) <= kBuildingRange * kBuildingRange)    // 比较摆放距离
        {
            terrain[position.x][position.y].isDestoried = false;    // 假定可摆放
            bool ableToBuild                            = true;
            for (int i = 0; i < gFactionNumber; i++)
                for (int j = 0; j < gRobotNumberPerFaction; j++)
                    if (robotInTerrain(i, j))
                    {
                        ableToBuild = false;    // 如果摆放后发生碰撞则无法摆放
                    }
            if (position.x == 0 || position.x == kTerrainNumberX - 1 || position.y == 0 || position.y == kTerrainNumberY - 1)
                ableToBuild = ableToBuild;
            else
            {
                if ((terrain[position.x - 1][position.y - 1].isDestoried) && (terrain[position.x + 1][position.y - 1].isDestoried) && (terrain[position.x - 1][position.y + 1].isDestoried) && (terrain[position.x + 1][position.y + 1].isDestoried))
                {
                    ableToBuild = false;    // 如果四周无连接则无法摆放
                }
            }
            if (ableToBuild)
            {
                faction[gFactionControlled].ammoBuildingBlock--;
                terrainShapeUpdate(position.x - 1, position.y - 1, position.x + 1, position.y + 1);
            }
            else
            {
                terrain[position.x][position.y].isDestoried = true;
            }
        }
    }
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
    gSeaLevel -= kSeaLevelIncreasingVelocity;
}

void seaUpdate(void)
{
    for (int i = 0; i < kTerrainNumberX; i++)
    {
        terrain[i][gSeaLevel].connectionStatus = iWaterSurface;
        for (int j = gSeaLevel + 1; j < kTerrainNumberY; j++)
        {
            terrain[i][j].connectionStatus = iWaterDeep;
        }
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
        // 如果箱子在水下，就标记为被拾起
        if (gMedicalBox[i].position.y > (gSeaLevel - 1) * kTerrainHeight)
            gMedicalBox[i].picked = true;

        if (!gMedicalBox[i].picked)
        {
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
        // 如果箱子在水下，就标记为被拾起
        if (gWeaponBox[i].position.y > (gSeaLevel - 1) * kTerrainHeight)
            gWeaponBox[i].picked = true;


        if (!gWeaponBox[i].picked)
        {
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
        // 如果箱子在水下，就标记为被拾起
        if (gSkillBox[i].position.y > (gSeaLevel - 1) * kTerrainHeight)
            gSkillBox[i].picked = true;


        if (!gSkillBox[i].picked)
        {
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
██████   ██████  ██   ██ ██████  ███████ ███████ ██████  ███████ ███████ ██   ██
██   ██ ██    ██  ██ ██  ██   ██ ██      ██      ██   ██ ██      ██      ██   ██
██████  ██    ██   ███   ██████  █████   █████   ██████  █████   ███████ ███████
██   ██ ██    ██  ██ ██  ██   ██ ██      ██      ██   ██ ██           ██ ██   ██
██████   ██████  ██   ██ ██   ██ ███████ ██      ██   ██ ███████ ███████ ██   ██
*/

void boxRefresh(void)
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
    }

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
    }

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
 ██████  ███████ ████████ ███    ██ ███████ ██   ██ ████████ ██████   ██████  ██████   ██████  ████████  ██████  ██████  ███    ██ ████████ ██████   ██████  ██      ██      ███████ ██████
██       ██         ██    ████   ██ ██       ██ ██     ██    ██   ██ ██    ██ ██   ██ ██    ██    ██    ██      ██    ██ ████   ██    ██    ██   ██ ██    ██ ██      ██      ██      ██   ██
██   ███ █████      ██    ██ ██  ██ █████     ███      ██    ██████  ██    ██ ██████  ██    ██    ██    ██      ██    ██ ██ ██  ██    ██    ██████  ██    ██ ██      ██      █████   ██   ██
██    ██ ██         ██    ██  ██ ██ ██       ██ ██     ██    ██   ██ ██    ██ ██   ██ ██    ██    ██    ██      ██    ██ ██  ██ ██    ██    ██   ██ ██    ██ ██      ██      ██      ██   ██
 ██████  ███████    ██    ██   ████ ███████ ██   ██    ██    ██   ██  ██████  ██████   ██████     ██     ██████  ██████  ██   ████    ██    ██   ██  ██████  ███████ ███████ ███████ ██████
*/

int getNextRobotControlled(void)
{
    int res = faction[gFactionControlled].robotControlled;
    do
    {
        res++;
        if (res >= gRobotNumberPerFaction)
            res = 0;
    } while (!faction[gFactionControlled].robot[res].alive);
    faction[gFactionControlled].robotControlled = res;
    return res;
}
/*
███████ ██     ██ ██ ████████  ██████ ██   ██ ████████  ██████  ███    ██ ███████ ██   ██ ████████ ███████  █████   ██████ ████████ ██  ██████  ███    ██
██      ██     ██ ██    ██    ██      ██   ██    ██    ██    ██ ████   ██ ██       ██ ██     ██    ██      ██   ██ ██         ██    ██ ██    ██ ████   ██
███████ ██  █  ██ ██    ██    ██      ███████    ██    ██    ██ ██ ██  ██ █████     ███      ██    █████   ███████ ██         ██    ██ ██    ██ ██ ██  ██
     ██ ██ ███ ██ ██    ██    ██      ██   ██    ██    ██    ██ ██  ██ ██ ██       ██ ██     ██    ██      ██   ██ ██         ██    ██ ██    ██ ██  ██ ██
███████  ███ ███  ██    ██     ██████ ██   ██    ██     ██████  ██   ████ ███████ ██   ██    ██    ██      ██   ██  ██████    ██    ██  ██████  ██   ████
*/

void switchToNextFaction(void)
{
    gCameraOverride = false;
    do
    {
        gFactionControlled++;
        if (gFactionControlled >= gFactionNumber)
            gFactionControlled = 0;
    } while (!faction[gFactionControlled].alive);
    gRobotControlled = getNextRobotControlled();
    roundUpdate();

    setCameraOnRobot(gFactionControlled, gRobotControlled);
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
        gameStatus.hPicture = hHelpBackgroundPicture;
        break;
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
        if (!gRoundWaiting)
        {
            if ((!gRobotSkillOn) && (!gRobotWeaponOn) && (!faction[gFactionControlled].robot[gRobotControlled].isJumping))
            {
                gCameraOverride                                                    = false;
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
        }
        break;
    case 'A':
        if (!gRoundWaiting)
        {
            if ((!gRobotSkillOn) && (!gRobotWeaponOn))
            {
                gCameraOverride = false;
                if (!faction[gFactionControlled].robot[gRobotControlled].isJumping)
                    faction[gFactionControlled].robot[gRobotControlled].velocity.x = -kRobotVelocityX;
                else
                    faction[gFactionControlled].robot[gRobotControlled].velocity.x = -kRobotVelocityJumping;
            }
        }
        break;
    case 'D':
        if (!gRoundWaiting)
        {
            if ((!gRobotSkillOn) && (!gRobotWeaponOn))
            {
                gCameraOverride = false;
                if (!faction[gFactionControlled].robot[gRobotControlled].isJumping)
                    faction[gFactionControlled].robot[gRobotControlled].velocity.x = kRobotVelocityX;
                else
                    faction[gFactionControlled].robot[gRobotControlled].velocity.x = kRobotVelocityJumping;
            }
        }
        break;
    case 'R':    // 根据目前打开的界面来决定自己的功能
        if (!gRoundWaiting)
        {
            if (gRobotWeaponOn)
            {
                faction[gFactionControlled].robot[gRobotControlled].weapon++;
                if (faction[gFactionControlled].robot[gRobotControlled].weapon == kMaxWeaponNum + 1)
                    faction[gFactionControlled].robot[gRobotControlled].weapon = 0;
                gCameraOverride                                                = false;
            }
            if (gRobotSkillOn)
            {
                faction[gFactionControlled].robot[gRobotControlled].skill++;
                if (faction[gFactionControlled].robot[gRobotControlled].skill == kMaxSkillNum + 1)
                    faction[gFactionControlled].robot[gRobotControlled].skill = 0;
                gCameraOverride                                               = false;
            }
        }
        break;
    case '\t':    // Tab键切换机器人，只在调试时使用
        if (!gRoundWaiting)
        {
            gCameraOverride = false;
            do
            {
                gRobotControlled++;
                if (gRobotControlled >= gRobotNumberPerFaction)
                    gRobotControlled = 0;
            } while (!faction[gFactionControlled].robot[gRobotControlled].alive);
            gRobotWeaponOn = false;
        }
        break;
    case 13:
        // if (!gRoundWaiting)
        {
            switchToNextFaction();
        }
        break;
    case 'F':
        if (!gRoundWaiting)
        {
            if (gRobotMoving)
            {
                if (gRobotSkillOn)
                {
                    gRobotSkillOn   = false;
                    gCameraOverride = false;
                }
                if (!gRobotWeaponOn)
                {
                    gRobotWeaponOn  = true;
                    gWeaponSelected = faction[gFactionControlled].robot[gRobotControlled].weapon;
                    gCameraOverride = false;
                }
                else
                {
                    gRobotWeaponOn  = false;
                    gWeaponSelected = iNoWeapon;
                    gCameraOverride = false;
                }
            }
        }
        break;
    case 'S':
        if (!gRoundWaiting)
        {
            if (gRobotMoving)
            {
                if (gRobotWeaponOn)    // 关闭武器选择系统
                {
                    gRobotWeaponOn  = false;
                    gCameraOverride = false;
                }
                if (!gRobotSkillOn)    // 打开技能界面
                {
                    gRobotSkillOn   = true;
                    gSkillSelected  = faction[gFactionControlled].robot[gRobotControlled].skill;
                    gCameraOverride = false;
                }
                else    // 关闭技能界面
                {
                    gRobotSkillOn   = false;
                    gSkillSelected  = iNoSkill;
                    gCameraOverride = false;
                }
            }
        }
        break;
    case 'Q':
        if (!gRoundWaiting)
        {
            if (gRobotWeaponOn && !gIncreasingWeaponPower && gWeaponSelected)
            {
                gChangingWeaponAngle = 1;
                gCameraOverride      = false;
            }
        }
        break;
    case 'E':
        if (!gRoundWaiting)
        {
            if (gRobotWeaponOn && !gIncreasingWeaponPower && gWeaponSelected)
            {
                gChangingWeaponAngle = -1;
                gCameraOverride      = false;
            }
        }
        break;
    case ' ':
        if (!gRoundWaiting)
        {
            if (gRobotWeaponOn && !gChangingWeaponAngle && gWeaponSelected)
            {
                gIncreasingWeaponPower = true;
                gCameraOverride        = false;
            }
        }
        break;
    case 'P':
        if (!gRoundWaiting)
        {
            if (gameStatus.status == Game_running)
            {
                gameStatus.status = Game_pause;
                break;
            }
            if (gameStatus.status == Game_pause)
            {
                gameStatus.status = Game_running;
                break;
            }
        }
        break;
    case VK_UP:
        if (!gCameraAutoMoving)
        {
            gCameraOverride = true;
            if (gCameraPosition.y > kCameraLimitTop)
            {
                gCameraPosition.y -= kCameraVelocity;
                if (gCameraPosition.y < kCameraLimitTop)
                    gCameraPosition.y = kCameraLimitTop;
            }
        }
        break;
    case VK_DOWN:
        if (!gCameraAutoMoving)
        {
            gCameraOverride = true;
            if (gCameraPosition.y < kCameraLimitButtom)
            {
                gCameraPosition.y += kCameraVelocity;
                if (gCameraPosition.y > kCameraLimitButtom)
                    gCameraPosition.y = kCameraLimitButtom;
            }
        }
        break;
    case VK_LEFT:
        if (!gCameraAutoMoving)
        {
            gCameraOverride = true;
            if (gCameraPosition.x > kCameraLimitLeft)
            {
                gCameraPosition.x -= kCameraVelocity;
                if (gCameraPosition.x < kCameraLimitLeft)
                    gCameraPosition.x = kCameraLimitLeft;
            }
        }
        break;
    case VK_RIGHT:
        if (!gCameraAutoMoving)
        {
            gCameraOverride = true;
            if (gCameraPosition.x < kCameraLimitRight)
            {
                gCameraPosition.x += kCameraVelocity;
                if (gCameraPosition.x > kCameraLimitRight)
                    gCameraPosition.x = kCameraLimitRight;
            }
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
        else if (gRobotSkillOn)
        {
            gSkillTargetSelecting = false;
            gSkillRangeSelecting  = false;
            skillActivate();
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
    switch (gameStatus.status)
    {
    case Game_start:
    {
        // 针对开始游戏按钮
        RECT startButtonRECT;
        startButtonRECT.left   = gameStartButton.position.x;
        startButtonRECT.right  = gameStartButton.position.x + gameStartButton.size.x;
        startButtonRECT.top    = gameStartButton.position.y;
        startButtonRECT.bottom = gameStartButton.position.y + gameStartButton.size.y;
        if (gameStatus.status == 0 && gameButtonClicked(ptMouse, startButtonRECT))
        {
            SetTimer(hWnd, kTimerID, kTimerElapse, NULL);
            gameStatus.status = Game_running;
            InvalidateRect(hWnd, NULL, TRUE);    // 重绘
        }

        // 针对退出游戏按钮
        RECT exitButtonRECT;
        exitButtonRECT.left   = gameExitButton.position.x;
        exitButtonRECT.right  = gameExitButton.position.x + gameExitButton.size.x;
        exitButtonRECT.top    = gameExitButton.position.y;
        exitButtonRECT.bottom = gameExitButton.position.y + gameExitButton.size.y;
        if (gameStatus.status == Game_start && gameButtonClicked(ptMouse, exitButtonRECT))
        {
            PostQuitMessage(0);
        }

        // 针对帮助按钮
        RECT helpButtonRECT;
        helpButtonRECT.left   = gameHelpButton.position.x;
        helpButtonRECT.right  = gameHelpButton.position.x + gameHelpButton.size.x;
        helpButtonRECT.top    = gameHelpButton.position.y;
        helpButtonRECT.bottom = gameHelpButton.position.y + gameHelpButton.size.y;
        if (gameStatus.status == Game_start && gameButtonClicked(ptMouse, helpButtonRECT))
        {
            gameStatus.status = Game_help;
            gameStatusUpdate();
            InvalidateRect(hWnd, NULL, TRUE);    // 重绘
        }
    }
    break;
    case Game_help:
    {
        RECT exitButtonRECT;
        exitButtonRECT.left   = helpExitButton.position.x;
        exitButtonRECT.right  = helpExitButton.position.x + helpExitButton.size.x;
        exitButtonRECT.top    = helpExitButton.position.y;
        exitButtonRECT.bottom = helpExitButton.position.y + helpExitButton.size.y;
        if (gameStatus.status == Game_help && gameButtonClicked(ptMouse, exitButtonRECT))
        {
            gameStatus.status = Game_start;
            gameStatusUpdate();
            InvalidateRect(hWnd, NULL, TRUE);    // 重绘
        }
    }
    break;
    case Game_running:
    {
        if (gRobotMoving)
        {
            VectorXY mousePosition;
            mousePosition.x = ptMouse.x + gCameraPosition.x;
            mousePosition.y = ptMouse.y + gCameraPosition.y;
            VectorXY terrainClicked;
            terrainClicked.x = mousePosition.x / kTerrainBlockSizeX;
            terrainClicked.y = mousePosition.y / kTerrainBlockSizeY;
            buildTerrain(terrainClicked);
        }
    }
    break;
    default:
        break;
    }
}
/*
 ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██       █████  ██      ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██
████████ ████████ ████████ ████████ ████████ ████████ ████████ ████████     ██   ██ ██     ████████ ████████ ████████ ████████ ████████ ████████ ████████ ████████
 ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██      ███████ ██      ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██
████████ ████████ ████████ ████████ ████████ ████████ ████████ ████████     ██   ██ ██     ████████ ████████ ████████ ████████ ████████ ████████ ████████ ████████
 ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██      ██   ██ ██      ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██   ██  ██
*/

void AI_sense()
{
	for (int i = 0; i < kWindowWidth / kTerrainWidth; i++)
	{
		gAIAviliablePosition[i].x = 0;
		gAIAviliablePosition[i].y = 0;
	}
    // 感知系统
    gAIMovingRangeLeft  = (faction[gFactionControlled].robot[gRobotControlled].position.x / kTerrainWidth) * kTerrainWidth;
    gAIMovingRangeRight = gAIMovingRangeLeft;
	VectorXY currentPosition = faction[gFactionControlled].robot[gRobotControlled].position;
	int aviliablePositionPointer = 0;
    // 可用行动范围向左扩展
	while (AI_NextMovingAvailable(currentPosition, true))
	{
		gAIMovingRangeLeft--;
		gAIAviliablePosition[aviliablePositionPointer++]=AI_positionUpdate(currentPosition,true);
	}
	// 当前位置复位
	currentPosition = faction[gFactionControlled].robot[gRobotControlled].position;
	// 可用行动范围向右扩展
	while (AI_NextMovingAvailable(currentPosition, false))
	{
		gAIMovingRangeRight++;
		gAIAviliablePosition[aviliablePositionPointer++]=AI_positionUpdate(currentPosition, false);
	}
    // 现在我们得到了机器人的可用行动范围
    // TODO UPGRADE 在行动范围内，查找所有的敌对人物
    // 剩下的事情转交决策系统
}

void AI_decide()
{
    // 决策系统
    // 现在我们知道可用行动范围
	int numOfTryingLocation = min(kMinTryTime, (gAIMovingRangeRight - gAIMovingRangeLeft) / kTryTimeFactor);// 最坏情况为25
	for (int i = 0; i < numOfTryingLocation; i++)
	{
		// 选择位置（随机的）

		// 遍历所有的武器
		// TODO UPGRADE 对于每一种武器，每一个敌对势力都进行虚拟打击实验，用一个函数来评估效果，然后选取最优解
		// 对于每种武器的射程，计算敌对人物的血量密度，减去自己的血量密度，得到最优打击部位
		// 利用最优打击部位、目前风向以及自己的位置和可用位置计算发射部位、发射角度、发射力度
		// 其中角度和力度直接模拟算了
	}
    // 现在我们知道了要移动到哪里，然后如何发射武器
    // TODO UPGRADE　计算撤离位置

    // 剩下的事情转交执行系统
}

void AI_act()
{
    // 模拟按键，移动到指定的位置，然后发射，然后撤离
}


bool AI_NextMovingAvailable(VectorXY currentPosition, bool movingLeft)    // NOTE 人物的宽度恰好是两倍的地块宽！
{
    // 将机器人拉到正确的地方
    int      left         = (currentPosition.x / kTerrainWidth) * kTerrainWidth;
    VectorXY nextPosition = currentPosition;
    nextPosition.x        = left;
    switch (movingLeft)
    {
    case true:
    {
        nextPosition.x -= kTerrainWidth;
        if (robotInTerrainVirtual(nextPosition))
        {
            // 前方有阻碍，检查能否跳上去
            // 检查方法为看高度差
            // TODO 当头上有阻碍时，AI依然正确工作
        }
        else if (!robotLandedVirtual(nextPosition))
        {
            // 前方会掉下去，检查会不会掉到水里
            // 检查方法为看下一格的情况
            // TODO 估计下去的损失
            // TODO 如果有沟的话就跳过去
        }
        else
        {
            // 此时机器人没有被卡住，而且还在地上，是可行的
            return true;
        }
    }
    break;
    case false:
    {
        nextPosition.x += kTerrainWidth;
        if (robotInTerrainVirtual(nextPosition))
        {
            // 前方有阻碍，检查能否跳上去
            // 检查方法为看高度差
            // TODO 当头上有阻碍时，AI依然正确工作
        }
        else if (!robotLandedVirtual(nextPosition))
        {
            // 前方会掉下去，检查会不会掉到水里
            // 检查方法为看下一格的情况
            // TODO 估计下去的损失
            // TODO 如果有沟的话就跳过去
        }
        else
        {
            // 此时机器人没有被卡住，而且还在地上，是可行的
            return true;
        }
    }
    break;
    }
}

VectorXY AI_positionUpdate(VectorXY position, bool movingLeft)
{

}
