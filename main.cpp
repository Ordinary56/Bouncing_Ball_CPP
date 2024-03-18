#include <iostream>
#include <memory>
#include <windows.h>
#include "window.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR pCmdLine, int nCmdShow) {
    std::unique_ptr<Window> wnd = std::make_unique<Window>(hInstance);
    wnd->Init(nCmdShow);
    return 0;
}