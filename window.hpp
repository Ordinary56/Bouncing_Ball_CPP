#include <windows.h>
#include <iostream>
class Window {
    public:
        Window(HINSTANCE instance);
        void Init(int nCmdShow);
        ~Window();
    private:
        HINSTANCE hinstance;
        WNDCLASSA wndClass;
        HWND wndMain;
};