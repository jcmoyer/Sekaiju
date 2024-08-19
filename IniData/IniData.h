/******************************************************************************/
/*                                                                            */
/* IniData.h Iniデータライブラリヘッダーファイル            (C)2024-2024 kuzu */
/*                                                                            */
/******************************************************************************/

// このライブラリは、iniファイルの読み込み、書き出し、
// セクション・キー・値を指定した設定・取得を行う。
// GetPrivateProfileString
// GetPrivateProfileInt
// WritePrivateProfileString
// WriteProvateProfileInt
// に代わり、64bit, Unicodeに対応し、
// 一括で読み込み、書き出しを行うことで高速化することを目的とする。
// このファイルは可変長ポインタ配列PtrArray.hを必要とする。

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

#ifndef _IniData_H_
#define _IniData_H_

#include "PtrArray.h"

/* C++からも使用可能とする */
#ifdef __cplusplus
extern "C" {
#endif

/* IniItem構造体 */
typedef struct tagIniItem {
	INT_PTR m_nLineNo;
	INT_PTR m_nType;
	TCHAR* m_pszKey;
	TCHAR* m_pszValue;
} IniItem;

/* Ini項目オブジェクトの生成 */
IniItem* IniItem_Create (INT_PTR nType, const TCHAR* pszKey, const TCHAR* pszValue);

/* Ini項目オブジェクトの削除 */
void IniItem_Delete (IniItem* pIniItem);

/* IniSection構造体 */
typedef struct tagIniSection {
	INT_PTR m_nLineNo;
	TCHAR* m_pszSectionName;
	PtrArray* m_pIniItemArray;
} IniSection;

/* IniSectionオブジェクトの生成 */
IniSection* IniSection_Create (const TCHAR* pszSectionName);

/* IniSecitonオブジェクトの削除 */
void IniSection_Delete (IniSection* pIniSection);

/* IniData構造体 */
typedef struct tagIniData {
	INT_PTR m_nBOMLen;
	BYTE m_byBOM[8];
	PtrArray* m_pIniSectionArray;
	PtrArray* m_pCommentArray;
} IniData;

/* 空のIniDataオブジェクトの生成 */
IniData* IniData_Create (INT_PTR nFlags);

/* IniDataオブジェクトの削除 */
void IniData_Delete (IniData* pIniData);

/* Iniファイルから読み込み */
IniData* IniData_Load (const TCHAR* pszFileName, INT_PTR nFlags);

/* IniデータをIniファイルに保存 */
INT_PTR IniData_Save (IniData* pIniData, const TCHAR* pszFileName, INT_PTR nFlags);

/* Iniデータに文字列設定(WritePrivateProfileStringのメモリ版) */
INT_PTR IniData_SetString (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszString);

/* Iniデータに整数設定(WritePrivateProfileIntのメモリ版) */
INT_PTR IniData_SetIntPtr (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, INT_PTR n);

/* Iniデータから文字列取得(GetPrivateProfileStringのメモリ版) */
INT_PTR IniData_GetString (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pDefault, TCHAR* pszBuf, INT_PTR nBufLen);

/* Iniデータから整数取得(GetPrivateProfileIntのメモリ版) */
INT_PTR IniData_GetIntPtr (IniData* pIniData, const TCHAR* pszSection, TCHAR* pszKey, INT_PTR nDefault);

#ifdef __cplusplus
}
#endif

#endif
