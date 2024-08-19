//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// 色オプションページクラス
// (C)2002-2020 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "stdafx.h"
#include "resource.h"
#include "ColorOptionPage.h"

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
CColorOptionPage::CColorOptionPage () : CPropertyPage (CColorOptionPage::IDD) {
}

//------------------------------------------------------------------------------
// オペレーション
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// データエクスチェンジ
void CColorOptionPage::DoDataExchange (CDataExchange* pDX) {
	CDialog::DoDataExchange (pDX);
}

// ダイアログの初期化
BOOL CColorOptionPage::OnInitDialog () {
	BOOL bRet = CDialog::OnInitDialog ();
	// カラー選択コンボボックスの生成と位置調整と色サンプルの追加
	long i = 0;
	long r, g, b;
	// 前景色(トラックデフォルト色)
	for (i = 0; i < 8; i++) {
		m_theForeColorCombo[i].Create 
			(WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL, 
			CRect (10, 10, 300, 300), this, IDC_COLOROPTION_FORECOLOR_00 + 16 + i);
		CRect rcComboDummy;
		CWnd* pComboDummy = GetDlgItem (IDC_COLOROPTION_FORECOLOR_00 + i);
		pComboDummy->GetWindowRect (&rcComboDummy);
		if (rcComboDummy.Height () < 300) { // 20201221追加
			rcComboDummy.bottom = rcComboDummy.top + 300;
		}
		this->ScreenToClient (&rcComboDummy);
		m_theForeColorCombo[i].MoveWindow (&rcComboDummy);
		pComboDummy->DestroyWindow ();
		for (r = 0; r <= 256; r += 64) {
			for (g = 0; g <= 256; g += 64) {
				for (b = 0; b <= 256; b += 64) {
					m_theForeColorCombo[i].AddSampleColor (RGB (MIN (r, 255), MIN (g, 255), MIN (b, 255)));			
				}
			}
		}
		m_theForeColorCombo[i].AddSampleColor (COLORSELECTCOMBOBOX_OTHER);
	}
	// 背景色
	for (i = 0; i < 2; i++) {
		m_theBackColorCombo[i].Create 
			(WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL, 
			CRect (10, 10, 300, 300), this, IDC_COLOROPTION_BACKCOLOR_00 + 16 + i);
		CRect rcComboDummy;
		CWnd* pComboDummy = GetDlgItem (IDC_COLOROPTION_BACKCOLOR_00 + i);
		pComboDummy->GetWindowRect (&rcComboDummy);
		if (rcComboDummy.Height () < 300) { // 20201221追加
			rcComboDummy.bottom = rcComboDummy.top + 300;
		}
		this->ScreenToClient (&rcComboDummy);
		m_theBackColorCombo[i].MoveWindow (&rcComboDummy);
		pComboDummy->DestroyWindow ();
		for (r = 0; r <= 256; r += 64) {
			for (g = 0; g <= 256; g += 64) {
				for (b = 0; b <= 256; b += 64) {
					m_theBackColorCombo[i].AddSampleColor (RGB (MIN (r, 255), MIN (g, 255), MIN (b, 255)));			
				}
			}
		}
		m_theBackColorCombo[i].AddSampleColor (COLORSELECTCOMBOBOX_OTHER);
	}
	// 水平線色
	for (i = 0; i < 2; i++) {
		m_theHorzColorCombo[i].Create 
			(WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL, 
			CRect (10, 10, 300, 300), this, IDC_COLOROPTION_HORZCOLOR_00 + 16 + i);
		CRect rcComboDummy;
		CWnd* pComboDummy = GetDlgItem (IDC_COLOROPTION_HORZCOLOR_00 + i);
		pComboDummy->GetWindowRect (&rcComboDummy);
		if (rcComboDummy.Height () < 300) { // 20201221追加
			rcComboDummy.bottom = rcComboDummy.top + 300;
		}
		this->ScreenToClient (&rcComboDummy);
		m_theHorzColorCombo[i].MoveWindow (&rcComboDummy);
		pComboDummy->DestroyWindow ();
		for (r = 0; r <= 256; r += 64) {
			for (g = 0; g <= 256; g += 64) {
				for (b = 0; b <= 256; b += 64) {
					m_theHorzColorCombo[i].AddSampleColor (RGB (MIN (r, 255), MIN (g, 255), MIN (b, 255)));			
				}
			}
		}
		m_theHorzColorCombo[i].AddSampleColor (COLORSELECTCOMBOBOX_OTHER);
	}
	// 垂直線色
	for (i = 0; i < 2; i++) {
		m_theVertColorCombo[i].Create 
			(WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL, 
			CRect (10, 10, 300, 300), this, IDC_COLOROPTION_VERTCOLOR_00 + 16 + i);
		CRect rcComboDummy;
		CWnd* pComboDummy = GetDlgItem (IDC_COLOROPTION_VERTCOLOR_00 + i);
		pComboDummy->GetWindowRect (&rcComboDummy);
		if (rcComboDummy.Height () < 200) { // 20201221追加
			rcComboDummy.bottom = rcComboDummy.top + 200;
		}
		this->ScreenToClient (&rcComboDummy);
		m_theVertColorCombo[i].MoveWindow (&rcComboDummy);
		pComboDummy->DestroyWindow ();
		for (r = 0; r <= 256; r += 64) {
			for (g = 0; g <= 256; g += 64) {
				for (b = 0; b <= 256; b += 64) {
					m_theVertColorCombo[i].AddSampleColor (RGB (MIN (r, 255), MIN (g, 255), MIN (b, 255)));			
				}
			}
		}
		m_theVertColorCombo[i].AddSampleColor (COLORSELECTCOMBOBOX_OTHER);
	}
//	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
//	SendMessageToDescendants 
//		(WM_SETFONT, (WPARAM)(HFONT)(pSekaijuApp->m_theDefaultFont), MAKELPARAM(TRUE, 0));
	return bRet;
}

// 選択状態が変更されたとき
void CColorOptionPage::OnChange () {
	SetModified (TRUE);
}

//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP (CColorOptionPage, CPropertyPage)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_00 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_01 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_02 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_03 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_04 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_05 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_06 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_FORECOLOR_07 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_BACKCOLOR_00 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_BACKCOLOR_01 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_HORZCOLOR_00 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_HORZCOLOR_01 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_VERTCOLOR_00 + 16, OnChange)
	ON_CBN_SELCHANGE (IDC_COLOROPTION_VERTCOLOR_01 + 16, OnChange)
END_MESSAGE_MAP ()




