/******************************************************************************/
/*                                                                            */
/* PtrArray.c 可変長ポインタ配列ソースファイル              (C)2017-2024 くず */
/*                                                                            */
/******************************************************************************/

// 可変長ポインタ配列
// このプログラムは、MFCのCPtrArrayクラスのC言語ヴァージョンである。
// 仕様はMFCのCPtrArrayに準ずる。

// This library is free software; you can redistribute it and/or 
// modify it under the terms of the GNU Lesser General Public 
// License as published by the Free Software Foundation; either 
// version 2.1 of the License, or (at your option) any later version. 

// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
// Lesser General Public License for more details. 

// You should have received a copy of the GNU Lesser General Public 
// License along with this library; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <tchar.h>
#include <windowsx.h>
#include <windows.h>
#include <commctrl.h>
#include <crtdbg.h>
#include <locale.h>
#include "PtrArray.h"

/* _ASSERT . _VERIFY マクロの定義 *********************************************/
#ifndef _VERIFY
#ifdef _DEBUG
#define _VERIFY(f)     _ASSERT(f)
#else
#define _VERIFY(f)     ((void)(f))
#endif
#endif

/* 汎用マクロ(最小、最大、挟み込み) *******************************************/
#ifndef MIN
#define MIN(A,B) ((A)>(B)?(B):(A))
#endif
#ifndef MAX
#define MAX(A,B) ((A)>(B)?(A):(B))
#endif
#ifndef CLIP
#define CLIP(A,B,C) ((A)>(B)?(A):((B)>(C)?(C):(B)))
#endif

/* TSIZEOFマクロ **************************************************************/
#define TSIZEOF(STRING) (sizeof(STRING)/sizeof(TCHAR))

/******************************************************************************/
/* 汎用関数                                                                   */
/******************************************************************************/

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

/* size_tをintに変換 */
int size_ttoint (size_t n) {
	if (n > INT_MAX) {
		return INT_MAX;
	}
	else if (n < 0) {
		return 0;
	}
	return (int)n;
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

/* INT_PTRをintに変換 */
int INT_PTRtoint (INT_PTR n) {
	if (n > INT_MAX) {
		return INT_MAX;
	}
	else if (n < LONG_MIN) {
		return INT_MIN;
	}
	return (int)n;
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

/******************************************************************************/
/* DLLMain                                                                    */
/******************************************************************************/

HINSTANCE g_hInstance;

BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) { 
        case DLL_PROCESS_ATTACH:
			g_hInstance = hInstance;
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}


/******************************************************************************/
/* 可変長ポインタ配列クラス                                                   */
/******************************************************************************/

/* 可変長ポインタ配列の生成 */
PtrArray* __stdcall PtrArray_Create () {
	PtrArray* pPtrArray = calloc (sizeof (PtrArray), 1);
	if (pPtrArray == NULL) {
		return NULL;
	}
	pPtrArray->m_nCount = 0;
	pPtrArray->m_nGrowSize = 256;
	pPtrArray->m_ppData = NULL;
	return pPtrArray;
}

/* 可変長ポインタ配列の配列数取得 */
INT_PTR __stdcall PtrArray_GetCount (PtrArray* pPtrArray) {
	return pPtrArray->m_nCount;
}

/* 可変長ポインタ配列にポインタを追加 */
INT_PTR __stdcall PtrArray_Add (PtrArray* pPtrArray, void* p) {
	if (pPtrArray->m_nCount % pPtrArray->m_nGrowSize == 0) {
		INT_PTR nNewSize = pPtrArray->m_nCount + pPtrArray->m_nGrowSize;
		void** ppNewData = calloc (sizeof (void*), nNewSize);
		if (ppNewData == NULL) {
			return -1;
		}
		if (pPtrArray->m_ppData != NULL) {
			memcpy (ppNewData, pPtrArray->m_ppData, sizeof (void*) * pPtrArray->m_nCount);
			free (pPtrArray->m_ppData);
		}
		pPtrArray->m_ppData = ppNewData;
	}
	*(pPtrArray->m_ppData + pPtrArray->m_nCount) = p;
	pPtrArray->m_nCount++;
	return pPtrArray->m_nCount - 1;
}

/* 可変長ポインタ配列からポインタを削除 */
void __stdcall PtrArray_RemoveAt (PtrArray* pPtrArray, INT_PTR nIndex) {
	if (0 <= nIndex && nIndex < pPtrArray->m_nCount - 1) {
		INT_PTR i;
		for (i = nIndex; i < pPtrArray->m_nCount; i++) {
			*(pPtrArray->m_ppData + i) = *(pPtrArray->m_ppData + i + 1);
		}
	}
	if (0 <= nIndex && nIndex < pPtrArray->m_nCount) {
		pPtrArray->m_nCount--;
		return;
	}
	_ASSERT (0);
	return;
}

/* 可変長ポインタ配列中のポインタを設定 */
void __stdcall PtrArray_SetAt (PtrArray* pPtrArray, INT_PTR nIndex, void* p) {
	if (0 <= nIndex && nIndex < pPtrArray->m_nCount) {
		*(pPtrArray->m_ppData + nIndex) = p;
		return;
	}
	_ASSERT (0);
	return;
}

/* 可変長ポインタ配列中のポインタを取得 */
void* __stdcall PtrArray_GetAt (PtrArray* pPtrArray, INT_PTR nIndex) {
	if (0 <= nIndex && nIndex < pPtrArray->m_nCount) {
		return *(pPtrArray->m_ppData + nIndex);
	}
	_ASSERT (0);
	return NULL;
}

/* 可変長ポインタ配列中のポインタをすべて除去 */
void __stdcall PtrArray_RemoveAll (PtrArray* pPtrArray) {
	if (pPtrArray->m_ppData != NULL) {
		free (pPtrArray->m_ppData);
		pPtrArray->m_ppData = NULL;
	}
	pPtrArray->m_nCount = 0;
}

/* 可変長ポインタ配列を削除 */
void __stdcall PtrArray_Delete (PtrArray* pPtrArray) {
	if (pPtrArray != NULL) {
		if (pPtrArray->m_ppData != NULL) {
			free (pPtrArray->m_ppData);
			pPtrArray->m_ppData = NULL;
		}
		pPtrArray->m_nCount = 0;
	}
	free (pPtrArray);
	pPtrArray = NULL;
}














