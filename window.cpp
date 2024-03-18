#include "window.hpp"
#include <windows.h>
#include <iostream>

typedef struct Ball
{
    RECT rect;
    int dX, dY;
} Ball_t;
void UpdateBall(HDC& hdc, Ball_t &ball, const RECT &client,HBRUSH& brush)
{
    RECT temp = ball.rect;
    FillRect(hdc,&temp,WHITE_BRUSH);
    if(ball.rect.left  < client.left || ball.rect.right > client.right) {
        ball.dX = -ball.dX;
    }
    if(ball.rect.top < client.top || ball.rect.bottom > client.bottom) {
        ball.dY = -ball.dY;
    }
    OffsetRect(&ball.rect,ball.dX,ball.dY);
    Ellipse(hdc,ball.rect.left,ball.rect.top,ball.rect.right, ball.rect.bottom);
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
    HDC hdc;
    HBRUSH brush;
    RECT client;
    static Ball_t ball = {
        .rect = {
            .left = 30,
            .top = 30,
            .right = 200,
            .bottom = 200
        },
        .dX = 5,
        .dY = 5
    };
    switch (uMsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, 1, 20, NULL);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT paint;
        HDC hdc = BeginPaint(hwnd, &paint);
        FillRect(hdc, &paint.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &paint);
        return 0;
    }
    case WM_TIMER:
    {
        hdc = GetDC(hwnd);
        brush = CreateSolidBrush(RGB(255, 0, 0));
        RECT client, temp;
        GetClientRect(hwnd, &client);
        UpdateBall(hdc,ball,client,brush);
        DeleteObject(brush);
        ReleaseDC(hwnd, hdc);
        break;
    }
    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hwnd, uMsg, wparam, lparam);
    }
    return 0;
}

Window::Window(HINSTANCE instance) : hinstance(instance)
{
}
Window::~Window()
{
    DestroyWindow(wndMain);
}

void Window::Init(int nCmdShow)
{
    wndClass = {
        .lpfnWndProc = WinProc,
        .hInstance = hinstance,
        .hIcon = LoadIconA(NULL, (LPSTR)IDI_APPLICATION),
        .hCursor = LoadCursorA(this->hinstance, (LPSTR)IDC_ARROW),
        .lpszClassName = "Ball"};
    RegisterClassA(&this->wndClass);
    wndMain = CreateWindowExA(
        0,
        "Ball",
        "Bouncing Ball",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hinstance, NULL);
    ShowWindow(wndMain, nCmdShow);
    MSG msg;
    while (GetMessageA(&msg, wndMain, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}