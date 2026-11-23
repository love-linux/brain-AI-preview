/* brain-ai: Brain の C で窓を出す試験（WinMain）。ボタンを押すと数えて表示し、浮動小数点も使う */
#include <windows.h>

static int g_count;
static HWND g_label;

static LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"BUTTON", L"押す", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 10, 120, 40, h, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"閉じる", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 10, 120, 40, h, (HMENU)2, NULL, NULL);
        g_label = CreateWindowW(L"STATIC", L"0 回", WS_CHILD | WS_VISIBLE, 10, 60, 300, 30, h, NULL, NULL, NULL);
        return 0;
    case WM_COMMAND:
        if (LOWORD(wp) == 1) {
            WCHAR s[64];
            double avg;
            g_count++;
            avg = 100.0 / g_count;
            wsprintfW(s, L"%d 回（100 / 回数 = %d.%02d）", g_count, (int)avg, (int)((avg - (int)avg) * 100));
            SetWindowTextW(g_label, s);
        } else if (LOWORD(wp) == 2) DestroyWindow(h);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPWSTR cmd, int show) {
    WNDCLASSW wc;
    MSG m;
    HWND h;
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = inst;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = L"BrainCTest";
    RegisterClassW(&wc);
    h = CreateWindowW(L"BrainCTest", L"C で作った窓", WS_VISIBLE, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, inst, NULL);
    ShowWindow(h, show);
    UpdateWindow(h);
    while (GetMessageW(&m, NULL, 0, 0)) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    return (int)m.wParam;
}
