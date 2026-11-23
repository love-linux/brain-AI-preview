/* 例: お絵かき。ペン（タッチ）でなぞると線が描ける。右下の「消」で全部消す、「×」で終わる */
#include <windows.h>

static HBITMAP g_bmp;      /* 絵を覚えておく裏の画面 */
static HDC g_mem;
static int g_down, g_px, g_py, g_w, g_h;

static void clear_canvas(void) {
    RECT r = {0, 0, g_w, g_h};
    FillRect(g_mem, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
}

static LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    int x = (short)LOWORD(lp), y = (short)HIWORD(lp);
    switch (msg) {
    case WM_CREATE: {
        RECT rc;
        HDC dc = GetDC(h);
        GetClientRect(h, &rc);
        g_w = rc.right; g_h = rc.bottom;
        g_mem = CreateCompatibleDC(dc);
        g_bmp = CreateCompatibleBitmap(dc, g_w, g_h);
        SelectObject(g_mem, g_bmp);
        SelectObject(g_mem, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));
        clear_canvas();
        ReleaseDC(h, dc);
        CreateWindowW(L"BUTTON", L"消", WS_CHILD | WS_VISIBLE, g_w - 90, g_h - 40, 40, 36, h, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"×", WS_CHILD | WS_VISIBLE, g_w - 45, g_h - 40, 40, 36, h, (HMENU)2, NULL, NULL);
        return 0;
    }
    case WM_LBUTTONDOWN: g_down = 1; g_px = x; g_py = y; SetCapture(h); return 0;
    case WM_MOUSEMOVE:
        if (g_down) {
            MoveToEx(g_mem, g_px, g_py, NULL);
            LineTo(g_mem, x, y);
            g_px = x; g_py = y;
            InvalidateRect(h, NULL, FALSE);
        }
        return 0;
    case WM_LBUTTONUP: g_down = 0; ReleaseCapture(); return 0;
    case WM_COMMAND:
        if (LOWORD(wp) == 1) { clear_canvas(); InvalidateRect(h, NULL, FALSE); }
        if (LOWORD(wp) == 2) DestroyWindow(h);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        BitBlt(dc, 0, 0, g_w, g_h, g_mem, 0, 0, SRCCOPY);
        EndPaint(h, &ps);
        return 0;
    }
    case WM_DESTROY: DeleteDC(g_mem); DeleteObject(g_bmp); PostQuitMessage(0); return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPWSTR cmd, int show) {
    WNDCLASSW wc;
    MSG m;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = inst;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = L"ExPaint";
    RegisterClassW(&wc);
    CreateWindowW(L"ExPaint", L"お絵かき", WS_VISIBLE, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, inst, NULL);
    while (GetMessageW(&m, NULL, 0, 0)) { TranslateMessage(&m); DispatchMessageW(&m); }
    return 0;
}
