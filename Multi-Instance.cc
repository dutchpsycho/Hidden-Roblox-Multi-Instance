#include <Windows.h>

int main() {
    // roblox checks for a window to make sure this is a 'real' mutex
    // fix: make invisible window
    
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = DefWindowProcW;
    wc.lpszClassName = L"HiddenWindowClass";

    if (RegisterClassW(&wc) == 0) {
        return GetLastError();
    }

    HWND hWnd = CreateWindowExW(0, wc.lpszClassName, L"", 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);

    if (hWnd == NULL) {
        return GetLastError();
    }

    FreeConsole();

    HANDLE hMutex = CreateMutexW(NULL, TRUE, L"ROBLOX_singletonMutex");
    if (hMutex == NULL) {
        return GetLastError();
    }

    MSG msg; // do this so windows doesnt just kill it
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}