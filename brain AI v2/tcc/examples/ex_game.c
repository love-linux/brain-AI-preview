/* 例: 小さなゲーム。跳ね回る玉をタップで当てると点が入る。裏の画面に描いてちらつかないようにする（BitBlt） */
#include <windows.h>
#include <stdlib.h>

static double g_x = 50, g_y = 50, g_vx = 3.3, g_vy = 2.1;     /* 浮動小数点で動かす */
static int g_w, g_h, g_score, g_r = 18;
static HDC g_mem;
static HBITMAP g_bmp;

static void draw(void) {
    RECT r = {0, 0, g_w, g_h};
    WCHAR s[32];
    HBRUSH b = CreateSolidBrush(RGB(255, 80, 0));
    FillRect(g_mem, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));
    SelectObject(g_mem, b);
    Ellipse(g_mem, (int)g_x - g_r, (int)g_y - g_r, (int)g_x + g_r, (int)g_y + g_r);
    DeleteObject(b);
    SetTextColor(g_mem, RGB(255, 255, 255));
    SetBkMode(g_mem, TRANSPARENT);
    wsprintfW(s, L"点 %d（左上をタップで終わる）", g_score);
    ExtTextOutW(g_mem, 5, 5, 0, NULL, s, lstrlenW(s), NULL);
}

static LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE: {
        RECT rc;
        HDC dc = GetDC(h);
        GetClientRect(h, &rc);
        g_w = rc.right; g_h = rc.bottom;
        g_mem = CreateCompatibleDC(dc);
        g_bmp = CreateCompatibleBitmap(dc, g_w, g_h);
        SelectObject(g_mem, g_bmp);
        ReleaseDC(h, dc);
        srand(GetTickCount());
        SetTimer(h, 1, 30, NULL);
        return 0;
    }
    case WM_TIMER:
        g_x += g_vx; g_y += g_vy;
        if (g_x < g_r || g_x > g_w - g_r) g_vx = -g_vx;
        if (g_y < g_r || g_y > g_h - g_r) g_vy = -g_vy;
        draw();
        InvalidateRect(h, NULL, FALSE);
        return 0;
    case WM_LBUTTONDOWN: {
        int x = (short)LOWORD(lp), y = (short)HIWORD(lp);
        double dx = x - g_x, dy = y - g_y;
        if (x < 40 && y < 30) { DestroyWindow(h); return 0; }
        if (dx * dx + dy * dy < (g_r + 6) * (g_r + 6)) {        /* 当たり: 点を足して速くする */
            g_score++;
            g_vx *= 1.15; g_vy *= 1.15;
            g_x = g_r + rand() % (g_w - 2 * g_r);
            g_y = g_r + rand() % (g_h - 2 * g_r);
        }
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        BitBlt(dc, 0, 0, g_w, g_h, g_mem, 0, 0, SRCCOPY);
        EndPaint(h, &ps);
        return 0;
    }
    case WM_DESTROY: KillTimer(h, 1); DeleteDC(g_mem); DeleteObject(g_bmp); PostQuitMessage(0); return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPWSTR cmd, int show) {
    WNDCLASSW wc;
    MSG m;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = inst;
    wc.lpszClassName = L"ExGame";
    RegisterClassW(&wc);
    CreateWindowW(L"ExGame", L"玉当て", WS_VISIBLE, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, inst, NULL);
    while (GetMessageW(&m, NULL, 0, 0)) { TranslateMessage(&m); DispatchMessageW(&m); }
    return 0;
}
