/******************************************************************************/
/*                                                                            */
/* IniData.c IniData���C�u�����\�[�X�t�@�C��                (C)2024-2024 kuzu */
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

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>
#include "PtrArray.h"
#include "IniData.h"

/* _ASSERT . _VERIFY �}�N���̒�` *********************************************/
#ifndef _VERIFY
#ifdef _DEBUG
#define _VERIFY(f)     _ASSERT(f)
#else
#define _VERIFY(f)     ((void)(f))
#endif
#endif

/* �ėp�}�N��(�ŏ��A�ő�A���ݍ���) *******************************************/
#ifndef MIN
#define MIN(A,B) ((A)>(B)?(B):(A))
#endif
#ifndef MAX
#define MAX(A,B) ((A)>(B)?(A):(B))
#endif
#ifndef CLIP
#define CLIP(A,B,C) ((A)>(B)?(A):((B)>(C)?(C):(B)))
#endif

/* Ini���ڃI�u�W�F�N�g�̐��� **************************************************/
IniItem* IniItem_Create (INT_PTR nType, const TCHAR* pszKey, const TCHAR* pszValue) {
	IniItem* pIniItem = calloc (sizeof (IniItem), 1);
	if (pIniItem == NULL) {
		return NULL;
	}
	INT_PTR nKeyLen = _tcslen (pszKey);
	pIniItem->m_pszKey = calloc (sizeof (TCHAR), nKeyLen + 1);
	if (pIniItem->m_pszKey == NULL) {
		free (pIniItem);
		return NULL;
	}
	_tcsncpy (pIniItem->m_pszKey, pszKey, nKeyLen);

	INT_PTR nValueLen = _tcslen (pszValue);
	pIniItem->m_pszValue = calloc (sizeof (TCHAR), nValueLen + 1);
	if (pIniItem->m_pszValue == NULL) {
		free (pIniItem->m_pszKey);
		free (pIniItem);
		return NULL;
	}
	_tcsncpy (pIniItem->m_pszValue, pszValue, nValueLen);
	return pIniItem;
}

/* Ini���ڃI�u�W�F�N�g�̍폜 **************************************************/
void IniItem_Delete (IniItem* pIniItem) {
	if (pIniItem == NULL) {
		return;
	}
	if (pIniItem->m_pszValue != NULL) {
		free(pIniItem->m_pszValue);
		pIniItem->m_pszValue = NULL;
	}
	if (pIniItem->m_pszKey != NULL) {
		free(pIniItem->m_pszKey);
		pIniItem->m_pszKey = NULL;
	}
	free(pIniItem);
	pIniItem = NULL;
	return;
}

/* Ini�Z�N�V�����I�u�W�F�N�g�̐��� *********************************************/
IniSection* IniSection_Create (const TCHAR* pszSectionName) {
	IniSection* pIniSection = calloc (sizeof (IniSection), 1);
	if (pIniSection == NULL) {
		return NULL;
	}
	pIniSection->m_pIniItemArray = PtrArray_Create();
	if (pIniSection->m_pIniItemArray == NULL) {
		IniSection_Delete(pIniSection);
		return NULL;
	}
	INT_PTR nSectionNameLen = _tcslen (pszSectionName);
	pIniSection->m_pszSectionName = calloc (sizeof (TCHAR), nSectionNameLen + 1);
	if (pIniSection->m_pszSectionName == NULL) {
		IniSection_Delete (pIniSection);
		return NULL;
	}
	_tcsncpy (pIniSection->m_pszSectionName, pszSectionName, nSectionNameLen);
	return pIniSection;
}

/* Ini�Z�N�V�����I�u�W�F�N�g�̍폜 *********************************************/
void IniSection_Delete (IniSection* pIniSection) {
	if (pIniSection == NULL) {
		return;
	}
	if (pIniSection->m_pIniItemArray != NULL) {
		INT_PTR nIniItemCount = PtrArray_GetCount(pIniSection->m_pIniItemArray);
		for (INT_PTR j = 0; j < nIniItemCount; j++) {
			IniItem* pIniItem = (IniItem*)PtrArray_GetAt(pIniSection->m_pIniItemArray, j);
			IniItem_Delete(pIniItem);
		}
		PtrArray_RemoveAll(pIniSection->m_pIniItemArray);
		PtrArray_Delete(pIniSection->m_pIniItemArray);
		pIniSection->m_pIniItemArray = NULL;
	}
	if (pIniSection->m_pszSectionName != NULL) {
		free(pIniSection->m_pszSectionName);
		pIniSection->m_pszSectionName = NULL;
	}
	free(pIniSection);
	pIniSection = NULL;
	return;
}


/* Ini�f�[�^�I�u�W�F�N�g�̐��� *********************************************/
IniData* IniData_Create (INT_PTR nFlags) {
	IniData* pIniData = calloc (sizeof (IniData), 1);
	if (pIniData == NULL) {
		return NULL;
	}
	// BOM��UTF-16LE��W���Ƃ���B
	pIniData->m_nBOMLen = 2;
	pIniData->m_byBOM[0] = 0xFF;
	pIniData->m_byBOM[1] = 0xFE;
	pIniData->m_pIniSectionArray = PtrArray_Create();
	if (pIniData->m_pIniSectionArray == NULL) {
		IniData_Delete (pIniData);
		return NULL;
	}
	return pIniData;
}

/* Ini�f�[�^�I�u�W�F�N�g�̍폜 *********************************************/
void IniData_Delete (IniData* pIniData) {
	if (pIniData == NULL) {
		return;
	}
	INT_PTR nSectionCount = PtrArray_GetCount(pIniData->m_pIniSectionArray);
	for (int i = 0; i < nSectionCount; i++) {
		IniSection* pIniSection = (IniSection*)PtrArray_GetAt (pIniData->m_pIniSectionArray, i);
		IniSection_Delete (pIniSection);
		pIniSection = NULL;
	}
	PtrArray_RemoveAll (pIniData->m_pIniSectionArray);
	PtrArray_Delete (pIniData->m_pIniSectionArray);
	pIniData->m_pIniSectionArray = NULL;
	free (pIniData);
	pIniData = NULL;
}

/* Ini�t�@�C������ǂݍ��� **************************************************/
IniData* IniData_Load (const TCHAR* pszFileName, INT_PTR nFlags) {
	// BOM�̓ǂݍ���
	BYTE byBOM[8];
	memset(byBOM, 0, sizeof(byBOM));
	INT_PTR nBOMLen = 0;
	FILE * pFile = NULL;
	errno_t nErr = _tfopen_s (&pFile, pszFileName, _T("rb"));
	if (pFile == NULL) {
		return NULL;
	}
	fread(byBOM, 1, 8, pFile);
	fclose(pFile);
	pFile = NULL;

	// BOM�ʃt�@�C���I�[�v������
	if (byBOM[0] == 0xFF && byBOM[1] == 0xFE) {
		nBOMLen = 2;
		errno_t nErr = _tfopen_s (&pFile, pszFileName, _T("rt, ccs=UTF-16LE"));
	}
	else if (byBOM[0] == 0xFE && byBOM[1] == 0xFF) {
		// UTF-16BE�͑Ή����Ă���܂���B
		return NULL;
	}
	else if (byBOM[0] == 0xEF && byBOM[1] == 0xBB && byBOM[2] == 0xBF) {
		nBOMLen = 3;
		errno_t nErr = _tfopen_s (&pFile, pszFileName, _T("rt, ccs=UTF-8"));
	}
	else {
		errno_t nErr = _tfopen_s (&pFile, pszFileName, _T("rt, ccs=UTF-8"));
	}
	if (pFile == NULL) {
		return NULL;
	}

	TCHAR szTextLine[16384];
	IniData* pIniData = NULL;
	IniSection* pCurSection = NULL;
	IniItem* pCurIniItem = NULL;
	pIniData = IniData_Create (nFlags);
	if (pIniData == NULL) {
		fclose (pFile);
		return NULL;
	}

	// BOM�̐ݒ�
	pIniData->m_nBOMLen = nBOMLen;
	memcpy (pIniData->m_byBOM, byBOM, nBOMLen);

	// BOM�̓ǂݔ�΂�
	//fread (byBOM, 1, nBOMLen, pFile);
	fseek (pFile, nBOMLen, STREAM_SEEK_SET);
	
	// �e�s�̓ǂݍ���
	while (!feof (pFile)) {
		TCHAR* pszT = NULL;
		INT_PTR nTextLineLen = 0;
		memset (szTextLine, 0, sizeof (szTextLine));
		_fgetts (szTextLine, 16384 - 1, pFile);
		nTextLineLen = _tcslen (szTextLine);
		// ���s�R�[�h����
		if (nTextLineLen > 2 && 
			szTextLine[nTextLineLen - 2] == _T('\r') &&
			szTextLine[nTextLineLen - 1] == _T('\n')) {
			szTextLine[nTextLineLen - 2] = szTextLine [nTextLineLen - 1] = _T('\0');
		}
		else if (nTextLineLen > 1 &&
			szTextLine[nTextLineLen - 1] == _T('\r') ||
			szTextLine[nTextLineLen - 1] == _T('\n')){
			szTextLine[nTextLineLen - 1] = _T('\0');
		}
		nTextLineLen = _tcslen (szTextLine);
		// �R�����g�s
		if (_tcsncmp (szTextLine, _T(";"), 1) == 0) {
			continue;
		}
		// �Z�N�V�����s
		else if (_tcsncmp (szTextLine, _T("["), 1) == 0) {
			IniSection* pIniSection = NULL;
			INT_PTR nSectionCount = PtrArray_GetCount(pIniData->m_pIniSectionArray);
			TCHAR szSectionName[16384];
			memset (szSectionName, 0, sizeof(szSectionName));
			if (_tcsncmp (szTextLine + nTextLineLen -1, _T("]"), 1) == 0) {
				_tcsncpy (szSectionName, szTextLine + 1, nTextLineLen - 2);
			}
			else {
				_tcsncpy (szSectionName, szTextLine + 1, nTextLineLen - 1);
			}
			INT_PTR i = 0;
			for (i = 0; i < nSectionCount; i++) {
				pIniSection = (IniSection*)PtrArray_GetAt (pIniData->m_pIniSectionArray, i);
				if (pIniSection != NULL && _tcscmp (pIniSection->m_pszSectionName, szSectionName) == 0) {
					break;
				}
			}
			// �����Z�N�V��������������
			if (i < nSectionCount) {
				pCurSection = pIniSection;
			}
			// �����Z�N�V������������Ȃ�����
			else {
				INT_PTR nSectionNameLen = _tcslen (szSectionName);
				pIniSection = (IniSection*)IniSection_Create (szSectionName);
				if (pIniSection == NULL) {
					continue;
				}
				INT_PTR nRet = PtrArray_Add (pIniData->m_pIniSectionArray, pIniSection);
				if (nRet < 0) {
					IniSection_Delete (pIniSection);
					continue;
				}
				pCurSection = pIniSection;
			}
		}
		// ���ڍs(Key=Value)
		else if (pszT = _tcschr(szTextLine, _T('='))) {
			TCHAR szKey[16384];
			TCHAR szValue[16384];
			memset (szKey, 0, sizeof (szKey));
			memset (szValue, 0, sizeof (szValue));
			INT_PTR nKeyLen = pszT - szTextLine;
			INT_PTR nValueLen = nTextLineLen - nKeyLen - 1;
			_tcsncpy (szKey, szTextLine, nKeyLen);
			_tcsncpy (szValue, pszT + 1, nValueLen);
			// [�Z�N�V����]��
			if (pCurSection != NULL) {
				INT_PTR nItemCount = PtrArray_GetCount (pCurSection->m_pIniItemArray);
				IniItem* pIniItem = NULL;
				INT_PTR j = 0;
				for (j = 0; j < nItemCount; j++) {
					pIniItem = (IniItem*)PtrArray_GetAt (pCurSection->m_pIniItemArray, j);
					if (pIniItem != NULL && _tcscmp (szKey, pIniItem->m_pszKey) == 0) {
						break;
					}
				}
				// �������ڂ���������
				if (j < nItemCount) {
					TCHAR* pszNewValue = calloc (nValueLen + 1, sizeof(TCHAR));
					if (pszNewValue == NULL) {
						continue;
					}
					_tcsncpy (pszNewValue, szValue, nValueLen);
					free (pIniItem->m_pszValue);
					pIniItem->m_pszValue = pszNewValue;
				}
				// �������ڂ�������Ȃ�����
				else {
					pIniItem = IniItem_Create (0, szKey, szValue);
					if (pIniItem == NULL) {
						continue;
					}
					INT_PTR nRet = PtrArray_Add (pCurSection->m_pIniItemArray, pIniItem);
					if (nRet < 0) {
						IniItem_Delete (pIniItem);
					}
				}
			}
			// [�Z�N�V����]�O
			else {
				// �����Ȃ�
			}
		}
		// Ini�t�@�C���K�i�𖞂����Ȃ��s
		else {
			// �����Ȃ�
		}
		// ���̍s��
	}
	// �t�@�C���I�[�ɒB����
	fclose (pFile);
	return pIniData;
}

/* Ini�f�[�^��Ini�t�@�C���֕ۑ�*****+*********************************************/
INT_PTR IniData_Save (IniData* pIniData, const TCHAR* pszFileName, INT_PTR nFlags) {
	FILE* pFile = NULL;
	// BOM�����o��
	if (pIniData->m_nBOMLen > 0) {
		errno_t nErr = _tfopen_s (&pFile, pszFileName, _T ("wb"));
		if (pFile == NULL) {
			return FALSE;
		}
		fwrite (pIniData->m_byBOM, 1, pIniData->m_nBOMLen, pFile);
		fclose (pFile);
		pFile = NULL;
	}

	// BOM�ʃt�@�C���J��
	if (pIniData->m_nBOMLen == 2 && pIniData->m_byBOM[0] == 0xFF && pIniData->m_byBOM[1] == 0xFE) {
		errno_t nErr = _tfopen_s (&pFile, pszFileName, _T("wt, ccs=UTF-16LE"));
	}
	else if (pIniData->m_nBOMLen == 2 && pIniData->m_byBOM[0] == 0xFE && pIniData->m_byBOM[1] == 0xFF) {
		// UTF-16BE�͑Ή����Ă���܂���B
		return FALSE;
	}
	else if (pIniData->m_nBOMLen == 3 && pIniData->m_byBOM[0] == 0xEF && pIniData->m_byBOM[1] == 0xBB && pIniData->m_byBOM[2] == 0xBF) {
		errno_t nErr = _tfopen_s (&pFile, pszFileName, _T("wt, ccs=UTF-8"));
	}
	else {
		errno_t nErr = _tfopen_s (&pFile, pszFileName, _T("wt, ccs=UTF-8"));
	}
	if (pFile == NULL) {
		return FALSE;
	}

	// �e�s�����o��
	INT_PTR nSectionCount = PtrArray_GetCount (pIniData->m_pIniSectionArray);
	for (int i = 0; i < nSectionCount; i++) {
		IniSection* pIniSection = PtrArray_GetAt (pIniData->m_pIniSectionArray, i);
		if (pIniSection == NULL) {
			continue;
		}
		_ftprintf (pFile, _T("[%s]\n"), pIniSection->m_pszSectionName);
		INT_PTR nItemCount = PtrArray_GetCount (pIniSection->m_pIniItemArray);
		for (int j = 0; j < nItemCount; j++) {
			IniItem* pIniItem = PtrArray_GetAt (pIniSection->m_pIniItemArray, j);
			if (pIniItem == NULL) {
				continue;
			}
			_ftprintf (pFile, _T("%s=%s\n"), pIniItem->m_pszKey, pIniItem->m_pszValue);
		}
	}
	fclose(pFile);
	return TRUE;
}

/* Ini�f�[�^�ɕ�����ݒ�(WritePrivateProfileString�̃�������) ********************/
INT_PTR IniData_SetString(IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszString) {
	INT_PTR nSectionCount = PtrArray_GetCount(pIniData->m_pIniSectionArray);
	for (int i = 0; i < nSectionCount; i++) {
		IniSection* pIniSection = PtrArray_GetAt(pIniData->m_pIniSectionArray, i);
		// �Y���Z�N�V��������������
		if (pIniSection != NULL && _tcscmp (pszSection, pIniSection->m_pszSectionName) == 0) {
			INT_PTR nItemCount = PtrArray_GetCount (pIniSection->m_pIniItemArray);
			for (int j = 0; j < nItemCount; j++) {
				IniItem* pIniItem = PtrArray_GetAt (pIniSection->m_pIniItemArray, j);
				// �Y���L�[����������
				if (pIniItem != NULL && _tcscmp (pszKey, pIniItem->m_pszKey) == 0) {
					INT_PTR nStringLen = _tcslen (pszString);
					TCHAR* pszNewValue = calloc (sizeof(TCHAR), nStringLen + 1);
					if (pszNewValue == NULL) {
						return FALSE;
					}
					_tcsncpy (pszNewValue, pszString, nStringLen);
					free (pIniItem->m_pszValue);
					pIniItem->m_pszValue = pszNewValue;
					return TRUE;
				}
			}
			// �Y���L�[��������Ȃ�����
			IniItem* pIniItem = IniItem_Create (0, pszKey, pszString);
			if (pIniItem == NULL) {
				return FALSE;
			}
			INT_PTR nRet = PtrArray_Add(pIniSection->m_pIniItemArray, pIniItem);
			if (nRet < 0) {
				return FALSE;
			}
			return TRUE;
		}
	}
	// �Y���Z�N�V������������Ȃ�����
	IniSection* pIniSection = IniSection_Create(pszSection);
	if (pIniSection == NULL) {
		return FALSE;
	}
	IniItem* pIniItem = IniItem_Create(0, pszKey, pszString);
	if (pIniItem == NULL) {
		return FALSE;
	}
	INT_PTR nRet = PtrArray_Add (pIniSection->m_pIniItemArray, pIniItem);
	if (nRet < 0) {
		return FALSE;
	}
	INT_PTR nRet2 = PtrArray_Add (pIniData->m_pIniSectionArray, pIniSection);
	if (nRet < 0) {
		return FALSE;
	}
	return TRUE;
}

/* Ini�f�[�^�ɐ����ݒ�(WritePrivateProfileInt�̃�������) ********************/
INT_PTR IniData_SetIntPtr (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, INT_PTR nValue) {
	TCHAR szValue[16384];
	memset (szValue, 0, sizeof(szValue));
#ifdef _WIN64
		_sntprintf (szValue, 16384 - 1, _T ("%I64d"), nValue);
#else
		_sntprintf (szValue, 16384 - 1, _T ("%I32d"), nValue);
#endif
	return IniData_SetString (pIniData, pszSection, pszKey, szValue);
}

/* Ini�f�[�^���當����擾(WritePrivateProfileString�̃�������) ********************/
INT_PTR IniData_GetString (IniData* pIniData, const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszDefault, TCHAR* pszBuf, INT_PTR nBufLen) {
	INT_PTR nSectionCount = PtrArray_GetCount(pIniData->m_pIniSectionArray);
	for (int i = 0; i < nSectionCount; i++) {
		IniSection* pIniSection = PtrArray_GetAt (pIniData->m_pIniSectionArray, i);
		// �Y���Z�N�V��������������
		if (_tcscmp (pszSection, pIniSection->m_pszSectionName) == 0) {
			INT_PTR nItemCount = PtrArray_GetCount (pIniSection->m_pIniItemArray);
			for (int j = 0; j < nItemCount; j++) {
				IniItem* pIniItem = PtrArray_GetAt (pIniSection->m_pIniItemArray, j);
				// �Y���L�[����������
				if (pIniItem != NULL && _tcscmp (pszKey, pIniItem->m_pszKey) == 0) {
					INT_PTR nValueLen = _tcslen (pIniItem->m_pszValue);
					INT_PTR nCopyLen = MIN (nValueLen, nBufLen - 1);
					memset (pszBuf, 0, nBufLen);
					_tcsncpy (pszBuf, pIniItem->m_pszValue, nCopyLen);
					return nCopyLen;
				}
			}
			// �Y���L�[��������Ȃ�����
			INT_PTR nValueLen = _tcslen (pszDefault);
			INT_PTR nCopyLen = MIN (nValueLen, nBufLen - 1);
			memset (pszBuf, 0, nBufLen);
			_tcsncpy (pszBuf, pszDefault, nCopyLen);
			return nCopyLen;
		}
	}
	// �Y���Z�N�V������������Ȃ�����
	INT_PTR nValueLen = _tcslen (pszDefault);
	INT_PTR nCopyLen = MIN (nValueLen, nBufLen - 1);
	memset (pszBuf, 0, nBufLen);
	_tcsncpy (pszBuf, pszDefault, nCopyLen);
	return nCopyLen;
}

/* Ini�f�[�^���琮���擾(WritePrivateProfileInt�̃�������) ********************/
INT_PTR IniData_GetIntPtr (IniData* pIniData, const TCHAR* pszSection, TCHAR* pszKey, INT_PTR nDefault) {
	TCHAR szValue[16384];
	TCHAR szDefault[16384];
	memset (szValue, 0, sizeof(szValue));
	memset (szDefault, 0, sizeof(szDefault));
#ifdef _WIN64
		_sntprintf (szDefault, 16384 - 1, _T ("%I64d"), nDefault);
#else
		_sntprintf (szDefault, 16384 - 1, _T ("%I32d"), nDefault);
#endif
	INT_PTR nRet = IniData_GetString (pIniData, pszSection, pszKey, szDefault, szValue, 16384 - 1);
#ifdef _WIN64
		return _ttoi64 (szValue);
#else
		return _ttoi (szValue);
#endif
}
