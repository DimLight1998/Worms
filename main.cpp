#include "event.h"
#include "global.h"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib,"winmm.lib")

TCHAR szWindowClass[] = _T("win32app");
TCHAR szTitle[]       = _T("Goblin's Warfare");


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND       hWnd;
    MSG        msg;

    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = hInstance;
    wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AppIcon));
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName  = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Mega Plane"), MB_OK);
        return 1;
    }

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, kWindowWidth, kWindowHeight + kWindowTitleBarHeight, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Mega Plane"), MB_OK);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        initialize(hWnd, wParam, lParam);
        break;
    case WM_PAINT:
        render(hWnd);
        break;
    case WM_KEYDOWN:
        keyDown(hWnd, wParam, lParam);
        break;
    case WM_KEYUP:
        keyUp(hWnd, wParam, lParam);
        break;
    case WM_LBUTTONDOWN:
        leftButtonDown(hWnd, wParam, lParam);
        break;
    case WM_TIMER:
        timerUpdate(hWnd, wParam, lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
}
