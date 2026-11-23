/* 例: 大きなデジタル時計（タイマー・フォント）。タップで終わる */
#include <windows.h>

static LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE: SetTimer(h, 1, 500, NULL); return 0;
    case WM_TIMER: InvalidateRect(h, NULL, TRUE); return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        SYSTEMTIME st;
        WCHAR s[32], d[48];
        static const WCHAR *wd = L"日月火水木金土";
        LOGFONTW lf;
        HFONT big, small, old;
        RECT rc;
        GetLocalTime(&st);
        GetClientRect(h, &rc);
        wsprintfW(s, L"%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
        wsprintfW(d, L"%d年%d月%d日（%c）", st.wYear, st.wMonth, st.wDay, wd[st.wDayOfWeek]);
        memset(&lf, 0, sizeof lf);
        lf.lfHeight = rc.bottom / 3;
        lf.lfWeight = FW_BOLD;
        big = CreateFontIndirectW(&lf);
        lf.lfHeight = rc.bottom / 10;
        lf.lfWeight = FW_NORMAL;
        small = CreateFontIndirectW(&lf);
        old = (HFONT)SelectObject(dc, big);
        rc.bottom = rc.bottom * 2 / 3;
        DrawTextW(dc, s, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        SelectObject(dc, small);
        rc.top = rc.bottom;
        rc.bottom = rc.top * 3 / 2;
        DrawTextW(dc, d, -1, &rc, DT_CENTER | DT_TOP | DT_SINGLELINE);
        SelectObject(dc, old);
        DeleteObject(big);
        DeleteObject(small);
        EndPaint(h, &ps);
        return 0;
    }
    case WM_LBUTTONDOWN: DestroyWindow(h); return 0;
    case WM_DESTROY: KillTimer(h, 1); PostQuitMessage(0); return 0;
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
    wc.lpszClassName = L"ExClock";
    RegisterClassW(&wc);
    CreateWindowW(L"ExClock", L"時計", WS_VISIBLE, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, inst, NULL);
    while (GetMessageW(&m, NULL, 0, 0)) { TranslateMessage(&m); DispatchMessageW(&m); }
    return 0;
}
