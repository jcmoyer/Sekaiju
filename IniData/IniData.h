/******************************************************************************/
/*                                                                            */
/* IniData.h Ini�f�[�^���C�u�����w�b�_�[�t�@�C��            (C)2024-2024 kuzu */
/*                                                                            */
/******************************************************************************/

// ���̃��C�u�����́Aini�t�@�C���̓ǂݍ��݁A�����o���A
// �Z�N�V�����E�L�[�E�l���w�肵���ݒ�E�擾���s���B
// GetPrivateProfileString
// GetPrivateProfileInt
// WritePrivateProfileString
// WriteProvateProfileInt
// �ɑ���A64bit, Unicode�ɑΉ����A
// �ꊇ�œǂݍ��݁A�����o�����s�����Ƃō��������邱�Ƃ�ړI�Ƃ���B
// ���̃t�@�C���͉ϒ��|�C���^�z��PtrArray.h��K�v�Ƃ���B

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

/* C++������g�p�\�Ƃ��� */
#ifdef __cplusplus
extern "C" {
#endif

/* IniItem�\���� */
typedef struct tagIniItem {
	INT_PTR m_nLineNo;
	INT_PTR m_nType;
	TCHAR* m_pszKey;
	TCHAR* m_pszValue;
} IniItem;

/* Ini���ڃI�u�W�F�N�g�̐��� */
IniItem* IniItem_Create (INT_PTR nType, const TCHAR* pszKey, const TCHAR* pszValue);

/* Ini���ڃI�u�W�F�N�g�̍폜 */
void IniItem_Delete (IniItem* pIniItem);

/* IniSection�\���� */
typedef struct tagIniSection {
	INT_PTR m_nLineNo;
	TCHAR* m_pszSectionName;
	PtrArray* m_pIniItemArray;
} IniSection;

/* IniSection�I�u�W�F�N�g�̐��� */
IniSection* IniSection_Create (const TCHAR* pszSectionName);

/* IniSeciton�I�u�W�F�N�g�̍폜 */
void IniSection_Delete (IniSection* pIniSection);

/* IniData�\���� */
typedef struct tagIniData {
	INT_PTR m_nBOMLen;
	BYTE m_byBOM[8];
	PtrArray* m_pIniSectionArray;
	PtrArray* m_pCommentArray;
} IniData;

/* ���IniData�I�u�W�F�N�g�̐��� */
IniData* IniData_Create (INT_PTR nFlags);

/* IniData�I�u�W�F�N�g�̍폜 */
void IniData_Delete (IniData* pIniData);

/* Ini�t�@�C������ǂݍ��� */
IniData* IniData_Load (const TCHAR* pszFileName, INT_PTR nFlags);

/* Ini�f�[�^��Ini�t�@�C���ɕۑ� */
INT_PTR IniData_Save (IniData* pIniData, const TCHAR* pszFileName, INT_PTR nFlags);

/* Ini�f�[�^�ɕ�����ݒ�(WritePrivateProfileString�̃�������) */
INT_PTR IniData_SetString (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszString);

/* Ini�f�[�^�ɐ����ݒ�(WritePrivateProfileInt�̃�������) */
INT_PTR IniData_SetIntPtr (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, INT_PTR n);

/* Ini�f�[�^���當����擾(GetPrivateProfileString�̃�������) */
INT_PTR IniData_GetString (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pDefault, TCHAR* pszBuf, INT_PTR nBufLen);

/* Ini�f�[�^���琮���擾(GetPrivateProfileInt�̃�������) */
INT_PTR IniData_GetIntPtr (IniData* pIniData, const TCHAR* pszSection, TCHAR* pszKey, INT_PTR nDefault);

#ifdef __cplusplus
}
#endif

#endif
