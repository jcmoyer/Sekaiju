//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// 世界樹ファイルダイアログクラス
// (C)2002-2021 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "stdafx.h"
#include "SekaijuFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

/*CSekaijuFileDlg::CSekaijuFileDlg() {
}*/

// コンストラクタ1
CSekaijuFileDlg::CSekaijuFileDlg(BOOL bOpenFileDialog) :
	//20091018修正:MFC8.0以前においては、次のデフォルトコンストラクタを使用する。
	//CFileDialog (bOpenFileDialog) {
	//20091018修正:MFC9.0において、CFileDialogのm_bVistaStyleに強制的にFALSEを指定する。
//	CFileDialog (bOpenFileDialog, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		NULL, NULL, 0, FALSE) {;
	CFileDialog (bOpenFileDialog) {
}

// コンストラクタ2
CSekaijuFileDlg::CSekaijuFileDlg (BOOL bOpenFileDialog,
	LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags,
	LPCTSTR lpszFilter, CWnd* pParentWnd) : 
	//20091018修正:MFC8.0以前においては、次のデフォルトコンストラクタを使用する。
	//CFileDialog (bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd) {
	//20091018修正:MFC9.0において、CFileDialogのm_bVistaStyleに強制的にFALSEを指定する。
//	CFileDialog (bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd,
//		0, FALSE) {
	CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd) {
}

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// 注意事項：MSDN2002/4のOPENFILENAME構造体の説明
// For compatibility reasons, the Places Bar is hidden if Flags is set to 
// OFN_ENABLEHOOK and lStructSize is OPENFILENAME_SIZE_VERSION_400.
	
//int CSekaijuFileDlg::DoModal () {
	//m_ofn.Flags |= OFN_EXPLORER | OFN_ENABLEHOOK;
	//m_ofn.lpfnHook = (LPOFNHOOKPROC) SaveAsHookProc;
	//if (m_bOpenFileDialog) {
	//	return ::GetOpenFileName (&m_ofn);
	//}
	//else {
	//	return ::GetSaveFileName (&m_ofn);
	//}
//}

INT_PTR CSekaijuFileDlg::DoModal () {
	/*
	TCHAR* pszKeyPath[] = {
		_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRU"),
		_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRULegacy")
	};
	for (long i = 0; i < 1; i++) {
		HKEY hKey = 0;
		long lRet = RegOpenKeyEx (HKEY_CURRENT_USER, pszKeyPath[i], 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS) {
			_RPTF4 (_CRT_WARN, "RegOpenKeyEx (HKEY_CURRENT_USER, %s, %d, %d, 0x%p) failed.",
				pszKeyPath[i], 0, KEY_ALL_ACCESS, &hKey);
			continue;
		}
		long lIndex = 0;
		long j = 0;
		TCHAR szValue[1024];
		BYTE byData[1024];
		memset (szValue, 0, sizeof (szValue));
		memset (byData, 0, sizeof (byData));
		DWORD dwValueLen = TSIZEOF (szValue);
		DWORD dwDataLen = sizeof (byData);
		DWORD dwType = 0;

		while (RegEnumValue (hKey, j, szValue, &dwValueLen, NULL, &dwType, byData, &dwDataLen)
			== ERROR_SUCCESS) {
			if (_tcsicmp (szValue, _T("MRUListEx"))) {
				if (_tcsicmp ((WCHAR*)byData, _T("Sekaiju.exe")) == 0) {
					lIndex = _ttol (szValue);
					long lRet2 = RegDeleteValue (hKey, szValue);
					if (lRet2 != ERROR_SUCCESS) {
						_RPTF2 (_CRT_WARN, "RegDeleteValue (0x%p, %s) failed.", hKey, szValue);
						continue;
					}
					memset (szValue, 0, sizeof (szValue));
					memset (byData, 0, sizeof (byData));
					dwValueLen = TSIZEOF (szValue);
					dwDataLen = sizeof (byData);
					long lRet3 = RegQueryValueEx (hKey, _T("MRUListEx"), NULL, NULL, byData, &dwDataLen);
					if (lRet3 != ERROR_SUCCESS) {
						_RPTF4 (_CRT_WARN, "RegQueryValueEx (0x%p, %s, 0, 0, 0x%p, 0x%p) failed.",
							hKey, "MRUListEx, byData, &dwDataLen");
						continue;
					}
					long* p1 = (long*)(&byData);
					long* p2 = (long*)(&byData);
					while (*p2 != -1) {
						if (*p2 == lIndex) {
							*p2++;
							dwDataLen -= sizeof (long);
						}
						*p1++ = *p2++;
					}
					*p1 = *p2;
					long lRet4 = RegSetValueEx (hKey, _T("MRUListEx"), 0, REG_BINARY, byData, dwDataLen);
					if (lRet4 != ERROR_SUCCESS) {
						_RPTF4 (_CRT_WARN, "RegSetValueEx (0x%p, %s, 0, REG_BINARY, 0x%p, 0x%p) failed.",
							hKey, "MRUListEx, byData, &dwDataLen");
						continue;
					}
				}
			}
			memset (szValue, 0, sizeof (szValue));
			memset (byData, 0, sizeof (byData));
			dwValueLen = TSIZEOF (szValue);
			dwDataLen = sizeof (byData);
			dwType = 0;
			j++;	
		}
		lRet = RegCloseKey (hKey);
		if (lRet != ERROR_SUCCESS) {
			_RPTF1 (_CRT_WARN, "RegCloseKey (0x%p) failed.", hKey);
		}
	}*/
	INT_PTR nRet = CFileDialog::DoModal ();
	/*if (nRet == IDOK) {
		//TCHAR szPath[_MAX_PATH];
		TCHAR szDrive[_MAX_DRIVE];
		TCHAR szDir[_MAX_DIR];
		TCHAR szFileName[_MAX_FNAME];
		TCHAR szExt[_MAX_EXT];
		_tsplitpath_s (m_ofn.lpstrFile, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFileName, _MAX_FNAME, szExt, _MAX_EXT);
		_RPTF1 (_CRT_WARN, "%s\n", m_ofn.lpstrFile);
		_RPTF5 (_CRT_WARN, "%s, %s, %s, %s, %s\n", m_ofn.lpstrFile, szDrive, szDir, szFileName, szExt);
	}*/
	return nRet;
}

// ファイルタイプコンボボックスが変更されたとき
// 20210711 メモ帳と同じ挙動とするため、オーバーライドを廃止。
void CSekaijuFileDlg::OnTypeChange () {
	CFileDialog::OnTypeChange ();
}

