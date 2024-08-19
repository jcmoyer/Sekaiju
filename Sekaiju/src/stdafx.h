//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// 共通インクルードヘッダーファイル
// (C)2002-2021 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN             // Windowsヘッダーから使用されていない部分を除外します。
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 一部の CString コンストラクターは明示的です。

// 一般的で無視しても安全なMFCの警告メッセージの一部の非表示を解除します。
#define _AFX_ALL_WARNINGS

#include <afxwin.h>               // MFCのコアおよび標準コンポーネント
#include <afxext.h>               // MFCの拡張部分
#include <afxcmn.h>               // MFCのWindowsコモンコントロール サポート
#include <afxcontrolbars.h>       // MFCにおけるリボンとコントロールバーのサポート

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


// MIN,MAX,CLIPマクロ
#ifndef MIN
#define MIN(A,B) ((A)<(B)?(A):(B))
#endif
#ifndef MAX
#define MAX(A,B) ((A)>(B)?(A):(B))
#endif
#ifndef CLIP
#define CLIP(A,B,C) ((B)<(A)?(A):((B)>(C)?(C):(B)))
#endif

// TSIZEOFマクロ //20120211追加
#ifndef TSIZEOF
#define TSIZEOF(STR) (sizeof(STR)/sizeof(TCHAR))
#endif

// 共通定数
#define MAXMIDIINDEVICENUM 16           // 最大MIDI入力デバイス数
#define MAXMIDIOUTDEVICENUM 16          // 最大MIDI出力デバイス数
#define MAXMIDITRACKNUM 65536           // 最大MIDIトラック数(1つのMIDIデータに付き)
#define MAXMIDIINSTRUMENTNUM 256        // 最大MIDIインストゥルメント(*.ins)数
#define MAXTIMERESOLUTION 1920          // TPQNベースにおける4分音符の最大の分解能

// 
