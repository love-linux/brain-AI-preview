/* 例: 図形と文字を描く（GDI）。線・四角・円・塗りつぶし・色・大きな文字 */
#include <windows.h>
#include <math.h>

static LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        RECT rc;
        HPEN pen = CreatePen(PS_SOLID, 3, RGB(200, 0, 0));
        HBRUSH br = CreateSolidBrush(RGB(0, 120, 255));
        LOGFONTW lf;
        HFONT font;
        int i;
        GetClientRect(h, &rc);
        SelectObject(dc, pen);
        MoveToEx(dc, 10, 10, NULL);
        LineTo(dc, rc.right - 10, rc.bottom - 10);
        SelectObject(dc, br);
        Rectangle(dc, 20, 60, 120, 140);
        Ellipse(dc, 140, 60, 240, 140);
        for (i = 0; i < 36; i++) {                       /* 円の上の点（sin・cos は浮動小数点エミュレーターで計算） */
            int x = 330 + (int)(60 * cos(i * M_PI / 18)), y = 100 + (int)(40 * sin(i * M_PI / 18));
            SetPixel(dc, x, y, RGB(0, 150, 0));
        }
        memset(&lf, 0, sizeof lf);
        lf.lfHeight = 32;
        lf.lfWeight = FW_BOLD;
        font = CreateFontIndirectW(&lf);
        SelectObject(dc, font);
        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, RGB(80, 0, 160));
        ExtTextOutW(dc, 20, 160, 0, NULL, L"Brain で描いた", 10, NULL);
        DeleteObject(font);
        DeleteObject(pen);
        DeleteObject(br);
        EndPaint(h, &ps);
        return 0;
    }
    case WM_LBUTTONDOWN: DestroyWindow(h); return 0;     /* タップで閉じる */
    case WM_DESTROY: PostQuitMessage(0); return 0;
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
    wc.lpszClassName = L"ExDraw";
    RegisterClassW(&wc);
    CreateWindowW(L"ExDraw", L"描く", WS_VISIBLE, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, inst, NULL);
    while (GetMessageW(&m, NULL, 0, 0)) { TranslateMessage(&m); DispatchMessageW(&m); }
    return 0;
}
