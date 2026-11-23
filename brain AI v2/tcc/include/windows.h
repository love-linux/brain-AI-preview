/*
 * brain-ai: Brain（Windows CE）で TinyCC から Win32 API を使うための windows.h。
 * 共通の設定（_braince.h）を読んでから、CeGCC の Windows CE 用ヘッダー（tcc\include\ce\windows.h）を読む。
 * 関数は coredll（窓・描画・ファイル・スレッドなど）、commctrl（画面の部品）、commdlg（ファイルを開く画面）、
 * mmtimer（時間）などにある。アプリはこれらを全部リンクする。文字は UNICODE（MessageBox → MessageBoxW、文字列は L"…"）。
 * 窓を出すプログラムは WinMain を書く（起動コードは lib\crtw.o。アプリは WinMain があれば自動で切り替える）
 */
#ifndef BRAIN_WINDOWS_H
#define BRAIN_WINDOWS_H
#include "_braince.h"
#include_next <windows.h>
#endif
