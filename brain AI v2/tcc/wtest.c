/* brain-ai: Brain の C から Win32 API を使う試験（コンソールの main から） */
#include <stdio.h>
#include <windows.h>

int main(void) {
    WCHAR buf[128];
    SYSTEMTIME st;
    DWORD t = GetTickCount();
    MEMORYSTATUS ms;
    GetLocalTime(&st);
    ms.dwLength = sizeof ms;
    GlobalMemoryStatus(&ms);
    printf("tick=%lu time=%d:%02d free=%lu KB\n", (unsigned long)t, st.wHour, st.wMinute,
           (unsigned long)(ms.dwAvailPhys / 1024));
    wsprintfW(buf, L"今は %d:%02d です。空きメモリ %lu KB", st.wHour, st.wMinute, (unsigned long)(ms.dwAvailPhys / 1024));
    MessageBoxW(NULL, buf, L"brain-ai", MB_OK | MB_ICONINFORMATION);
    return 0;
}
