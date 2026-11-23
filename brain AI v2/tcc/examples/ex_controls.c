/* 例: 画面の部品（commctrl）。入力欄・ボタン・リスト（ListView）・進み具合の棒（Progress）・つまみ（Trackbar） */
#include <windows.h>
#include <commctrl.h>

static HWND g_edit, g_list, g_prog, g_track;
static int g_n;

static void add_row(const WCHAR *text) {
    LVITEMW it;
    WCHAR num[16];
    wsprintfW(num, L"%d", ++g_n);
    memset(&it, 0, sizeof it);
    it.mask = LVIF_TEXT;
    it.iItem = g_n - 1;
    it.pszText = num;
    SendMessageW(g_list, LVM_INSERTITEMW, 0, (LPARAM)&it);
    it.iSubItem = 1;
    it.pszText = (WCHAR *)text;
    SendMessageW(g_list, LVM_SETITEMTEXTW, g_n - 1, (LPARAM)&it);
    SendMessageW(g_prog, PBM_SETPOS, (g_n * 10) % 101, 0);
}

static LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE: {
        LVCOLUMNW col;
        g_edit = CreateWindowW(L"EDIT", L"ここに書く", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 5, 200, 26, h, (HMENU)10, NULL, NULL);
        CreateWindowW(L"BUTTON", L"追加", WS_CHILD | WS_VISIBLE, 210, 5, 60, 26, h, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"閉じる", WS_CHILD | WS_VISIBLE, 275, 5, 70, 26, h, (HMENU)2, NULL, NULL);
        g_list = CreateWindowW(WC_LISTVIEWW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, 5, 36, 340, 120, h, (HMENU)11, NULL, NULL);
        memset(&col, 0, sizeof col);
        col.mask = LVCF_TEXT | LVCF_WIDTH;
        col.cx = 40; col.pszText = L"番号";
        SendMessageW(g_list, LVM_INSERTCOLUMNW, 0, (LPARAM)&col);
        col.cx = 280; col.pszText = L"内容";
        SendMessageW(g_list, LVM_INSERTCOLUMNW, 1, (LPARAM)&col);
        g_prog = CreateWindowW(PROGRESS_CLASSW, L"", WS_CHILD | WS_VISIBLE, 5, 162, 340, 18, h, (HMENU)12, NULL, NULL);
        g_track = CreateWindowW(TRACKBAR_CLASSW, L"", WS_CHILD | WS_VISIBLE, 5, 186, 340, 30, h, (HMENU)13, NULL, NULL);
        SendMessageW(g_track, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
        return 0;
    }
    case WM_COMMAND:
        if (LOWORD(wp) == 1) {
            WCHAR s[128];
            GetWindowTextW(g_edit, s, 128);
            add_row(s);
        } else if (LOWORD(wp) == 2) DestroyWindow(h);
        return 0;
    case WM_HSCROLL:                                     /* つまみを動かすと進み具合の棒も動く */
        if ((HWND)lp == g_track) SendMessageW(g_prog, PBM_SETPOS, SendMessageW(g_track, TBM_GETPOS, 0, 0), 0);
        return 0;
    case WM_DESTROY: PostQuitMessage(0); return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPWSTR cmd, int show) {
    WNDCLASSW wc;
    MSG m;
    INITCOMMONCONTROLSEX ic;
    ic.dwSize = sizeof ic;
    ic.dwICC = ICC_LISTVIEW_CLASSES | ICC_PROGRESS_CLASS | ICC_BAR_CLASSES;
    InitCommonControlsEx(&ic);
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = inst;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszClassName = L"ExControls";
    RegisterClassW(&wc);
    CreateWindowW(L"ExControls", L"部品", WS_VISIBLE, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, inst, NULL);
    while (GetMessageW(&m, NULL, 0, 0)) { TranslateMessage(&m); DispatchMessageW(&m); }
    return 0;
}
