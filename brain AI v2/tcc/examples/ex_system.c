/* 例: 窓を出さないプログラム（main）から Win32 API。結果はアプリの「実行結果」に出る。
 * ファイルの一覧・ファイルの読み書き・スレッド・メモリ・時刻（time.h）・数学（math.h）・ファイルを選ぶ画面（commdlg） */
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

static volatile LONG g_count;

static DWORD WINAPI worker(LPVOID p) {
    int i, n = (int)p;
    for (i = 0; i < n; i++) InterlockedIncrement((LONG *)&g_count);
    return 0;
}

int main(void) {
    WIN32_FIND_DATAW fd;
    HANDLE f, th[2];
    MEMORYSTATUS ms;
    char line[200];
    int n = 0;
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    FILE *fp;

    /* 1. 時刻と数学 */
    strftime(line, sizeof line, "%Y-%m-%d %H:%M:%S", lt);
    printf("今: %s（time=%ld）\n", line, (long)t);
    printf("sqrt(2)=%.6f  sin(30度)=%.6f  pow(2,10)=%.0f\n", sqrt(2.0), sin(M_PI / 6), pow(2.0, 10.0));

    /* 2. メモリ */
    ms.dwLength = sizeof ms;
    GlobalMemoryStatus(&ms);
    printf("空きメモリ: %lu KB / %lu KB\n", (unsigned long)(ms.dwAvailPhys / 1024), (unsigned long)(ms.dwTotalPhys / 1024));

    /* 3. ファイルの一覧（ルート） */
    f = FindFirstFileW(L"\\*", &fd);
    if (f != INVALID_HANDLE_VALUE) {
        do {
            char name[MAX_PATH * 3];
            WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, name, sizeof name, NULL, NULL);
            printf("  %s%s\n", name, (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "\\" : "");
        } while (++n < 15 && FindNextFileW(f, &fd));
        FindClose(f);
    }

    /* 4. ファイルの読み書き（C の fopen） */
    fp = fopen("\\Temp\\brain_test.txt", "w");
    if (fp) { fprintf(fp, "hello from tcc %d\n", 42); fclose(fp); }
    fp = fopen("\\Temp\\brain_test.txt", "r");
    if (fp) { if (fgets(line, sizeof line, fp)) printf("読んだ: %s", line); fclose(fp); }
    remove("\\Temp\\brain_test.txt");

    /* 5. スレッド 2 本で数える */
    th[0] = CreateThread(NULL, 0, worker, (LPVOID)50000, 0, NULL);
    th[1] = CreateThread(NULL, 0, worker, (LPVOID)50000, 0, NULL);
    WaitForMultipleObjects(2, th, TRUE, INFINITE);
    CloseHandle(th[0]); CloseHandle(th[1]);
    printf("スレッドで数えた: %ld（100000 なら正しい）\n", (long)g_count);

    printf("経過: %ld ms\n", (long)clock());
    return 0;
}
