//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// 共用ルーチン
// (C)2002-2021 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
#include "winver.h"
#include "common.h"
#ifndef _UNICODE
#include <mbstring.h>
#endif


// TSIZEOFマクロ //20120211追加
#ifndef TSIZEOF
#define TSIZEOF(STR) (sizeof(STR)/sizeof(TCHAR))
#endif

/* size_tをlongに変換 */
long size_ttolong (size_t n) {
	if (n > LONG_MAX) {
		return LONG_MAX;
	}
	else if (n < 0) {
		return 0;
	}
	return (long)n;
}

/* INT_PTRをlongに変換 */
long INT_PTRtolong (INT_PTR n) {
	if (n > LONG_MAX) {
		return LONG_MAX;
	}
	else if (n < LONG_MIN) {
		return LONG_MIN;
	}
	return (long)n;
}

/* DWORD_PTRをDWORDに変換 */
DWORD DWORD_PTRtoDWORD (DWORD_PTR dw) {
	if (dw > ULONG_MAX) {
		return ULONG_MAX;
	}
	else if (dw < 0) {
		return 0;
	}
	return (DWORD)dw;

}

// 数字として認識できる文字列か調べる(戻り値:認識できた数字の文字数)
long IsNumeric (const TCHAR* pszText) {
	long i;
	TCHAR c = 0;
	long iStart = 0;
	long lLen = size_ttolong (_tcslen (pszText));
	if (lLen == 0) {
		return 0;
	}
	c = *(pszText + 0);
	if (c == _T('-')) {
		iStart = 1;
	}
	for (i = iStart; i < lLen; i++) {
		c = *(pszText + i);
		if (!_istdigit (c)) {
			return i - iStart;
		}
	}
	return i - iStart;
}


/* 16進法で使用可能な文字なら0以外を、そうでなければ0を返す */
long IsHexDigit (TCHAR c) {
	return _istxdigit ((TCHAR)c);
}

/* バイナリ配列を16進テキスト文字列(半角スペース区切り)に変換する */
long bin2txt (BYTE* pBin, long lBinLen, TCHAR* pszText, long lTextLen) {
	long i, iMax;
	TCHAR szText[16];
	memset (pszText, 0, lTextLen * sizeof (TCHAR));
	iMax = __min ((lTextLen - 1) / 3, lBinLen);
	for (i = 0; i < iMax; i++) {
		_sntprintf_s (szText, TSIZEOF (szText), TSIZEOF (szText) - 1, _T("%02X "), *(pBin + i));
		_tcscpy_s (pszText + 3 * i, lTextLen - 3 * i, szText);
	}
	if (i > 0) {
		*(pszText + 3 * i - 1) = _T('\0');
	}
	return i;
}

/* 16進テキスト文字列(半角スペース区切り)をバイナリ配列に変換する */
long txt2bin (TCHAR* pszText, long lTextLen, BYTE* pBin, long lBinLen) {
	long i, iMax;
	TCHAR* p = pszText;
	iMax = lBinLen;
	memset (pBin, 0, lBinLen);
	for (i = 0; i < iMax; i++) {
		/* 先頭スペース飛ばし */
		while (1) {
			if (p - pszText >= lTextLen) {
				return i;
			}
			else if (_tcsncmp (p, _T(" "), 1) == 0 || _tcsncmp (p, _T("\t"), 1) == 0) {
				p++;
			}
			else if (*p == _T('\0')) {
				return i;
			}
			else {
				break;
			}
		}
		/* 該当1～2文字読み込み 20210106 修正　*/
		//if (!IsHexDigit (*p) || !IsHexDigit (*(p+1)) ||	IsHexDigit (*(p+2))) {
		if (!IsHexDigit (*p)) {
			//memset (pBin, 0, lBinLen);
			return i; // 20210106 正常入力できたところまでは設定して返す。
		}
		else if (IsHexDigit (*p) && !IsHexDigit (*(p+1))) {
			_stscanf_s (p, _T("%hhx"), (pBin + i));
			p += 1;
		}
		else if (IsHexDigit (*p) && IsHexDigit (*(p+1)) && !IsHexDigit (*(p+2))) { 
			_stscanf_s (p, _T("%hhx"), (pBin + i));
			p += 2;
		}
		else {
			TCHAR szTemp[3];
			memset (szTemp, 0, sizeof (szTemp));
			_tcsncpy_s (szTemp, 3, p, 2);
			_stscanf_s (szTemp, _T("%hhx"), (pBin + i));
			p += 2;
		}

	}
	return i;
}

/* '\t''\r''\n''\\'制御文字入りの文字列をアスキー文字列(C言語スタイル)に変換する　*/
/* 戻り値：出来上がった文字列のバイト数 */
long codestr2str (TCHAR* pszCodeStr, long lCodeStrLen, TCHAR* pszStr, long lStrLen) {
	TCHAR* p1 = pszCodeStr;
	TCHAR* p2 = pszStr;
	memset (pszStr, 0, lStrLen * sizeof (TCHAR));
	while (p1 - pszCodeStr < lCodeStrLen && p2 - pszStr < lStrLen) {
#ifndef UNICODE
		if (p1 - pszCodeStr < lCodeStrLen - 1 && p2 - pszStr < lStrLen - 1 &&
			_mbclen (p1) == 2) {
			*p2++ = *p1++;
			*p2++ = *p1++;
		}
		else 
#endif
		if (p2 - pszStr < lStrLen - 1 && *p1 == _T('\t')) {
			*p2++ = _T('\\');
			*p2++ = _T('t');
			p1++;
		}
		else if (p2 - pszStr < lStrLen - 1 && *p1 == _T('\r')) {
			*p2++ = _T('\\');
			*p2++ = _T('r');
			p1++;
		}
		else if (p2 - pszStr < lStrLen - 1 && *p1 == _T('\n')) {
			*p2++ = _T('\\');
			*p2++ = _T('n');
			p1++;
		}
		else if (p2 - pszStr < lStrLen - 1 && *p1 == _T('\\')) { // 20191012修正
			*p2++ = _T('\\');
			*p2++ = _T('\\');
			p1++;
		}
		else {
			*p2++ = *p1++;
		}
	}
	return INT_PTRtolong (p2 - pszStr);
}

/* アスキー文字列(C言語スタイル)を'\t''\r''\n''\\'制御文字入りの文字列に変換する */
/* 戻り値：出来上がった文字列のバイト数 */
long str2codestr (TCHAR* pszStr, long lStrLen, TCHAR* pszCodeStr, long lCodeStrLen) {
	TCHAR* p1 = pszStr;
	TCHAR* p2 = pszCodeStr;
	memset (pszCodeStr, 0, lCodeStrLen * sizeof (TCHAR));
	while (p1 - pszStr < lStrLen && p2 - pszCodeStr < lCodeStrLen) {
#ifndef UNICODE
		if (p1 - pszStr < lStrLen - 1 && p2 - pszCodeStr < lCodeStrLen - 1 &&
			_mbclen (p1) == 2) {
			*p2++ = *p1++;
			*p2++ = *p1++;
		}
		else 
#endif
		if (p1 - pszStr < lStrLen - 1 && *p1 == _T('\\') && *(p1 + 1) == _T('t')) {
			*p2++ = _T('\t');
			p1++;
			p1++;
		}
		else if (p1 - pszStr < lStrLen - 1 && *p1 == _T('\\') && *(p1 + 1) == _T('r')) {
			*p2++ = _T('\r');
			p1++;
			p1++;
		}
		else if (p1 - pszStr < lStrLen - 1 && *p1 == _T('\\') && *(p1 + 1) == _T('n')) {
			*p2++ = _T('\n');
			p1++;
			p1++;
		}
		else if (p1 - pszStr < lStrLen - 1 && *p1 == _T('\\') && *(p1 + 1) == _T('\\')) { // 20191012修正
			*p2++ = _T('\\');
			p1++;
			p1++;
		}
		else {
			*p2++ = *p1++;
		}
	}
	return INT_PTRtolong (p2 - pszCodeStr);
}


