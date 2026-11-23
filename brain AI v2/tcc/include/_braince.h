/*
 * brain-ai: Brain（Windows CE 6.0 / ARM）で TinyCC を使うときの共通の設定。アプリは -include でどのプログラムにも先に読ませる。
 * CeGCC の Windows CE 用ヘッダー（tcc\include\ce）が期待する印と、tcc が知らない MS・GCC の書き方をここで埋める。
 */
#ifndef BRAIN_CE_H
#define BRAIN_CE_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef _WIN32_WCE
#define _WIN32_WCE 0x600
#endif
#ifndef UNDER_CE
#define UNDER_CE 0x600
#endif
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400        /* 画面の部品（commctrl）の InitCommonControlsEx などを使えるように */
#endif
#ifndef __COREDLL__
#define __COREDLL__ 1           /* C の関数も coredll にある */
#endif
#ifndef ARM
#define ARM 1
#endif
#ifndef _ARM_
#define _ARM_ 1
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN     /* RPC・OLE などは読まない（使うときは先に #define BRAIN_FULL_WINDOWS） */
#endif
#ifdef BRAIN_FULL_WINDOWS
#undef WIN32_LEAN_AND_MEAN
#endif
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8 char
#define NTAPI
#define __stdcall
#define __cdecl
#define __fastcall
#ifndef __declspec
#define __declspec(x)
#endif
#define __forceinline inline
#define _pascal
#define __pascal
#define DECLARE_STDCALL_P(type) type
#define DECLSPEC_NORETURN
#define DECLSPEC_ALIGN(x)
#define DECLSPEC_NOVTABLE
#define DECLSPEC_SELECTANY
/* tcc の stddef.h と型をそろえる（Windows CE 側は long、tcc は int。どちらも 32 ビット） */
#define _SSIZE_T_
typedef __PTRDIFF_TYPE__ _ssize_t;
#endif
