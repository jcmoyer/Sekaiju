/******************************************************************************/
/*                                                                            */
/* PtrArray.h 可変長ポインタ配列ヘッダーファイル            (C)2017-2024 kuzu */
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

#ifndef _PTRARRAY_H_
#define _PTRARRAY_H_

/* C++からも使用可能とする */
#ifdef __cplusplus
extern "C" {
#endif

/* PtrArray構造体 */
typedef struct tagPtrArray {
	INT_PTR m_nCount;
	INT_PTR m_nGrowSize;
	void** m_ppData;
} PtrArray;

PtrArray* __stdcall PtrArray_Create ();
INT_PTR __stdcall PtrArray_GetCount (PtrArray* pPtrArray);
INT_PTR __stdcall PtrArray_Add (PtrArray* pPtrArray, void* p);
void __stdcall PtrArray_RemoveAt (PtrArray* pPtrArray, INT_PTR nIndex);
void __stdcall PtrArray_SetAt (PtrArray* pPtrArray, INT_PTR nIndex, void* p);
void* __stdcall PtrArray_GetAt (PtrArray* pPtrArray, INT_PTR nIndex);
void __stdcall PtrArray_RemoveAll (PtrArray* pPtrArray);
void __stdcall PtrArray_Delete (PtrArray* pPtrArray);


#ifdef __cplusplus
}
#endif

#endif
