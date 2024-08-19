//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// イベントリストオプションページクラス
// (C)2002-2020 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "stdafx.h"
#include "resource.h"
#include "EventListOptionPage.h"
#include "..\\..\\MIDIIO\\MIDIIO.h"
#include "..\\..\\MIDIData\\MIDIData.h"
#include "..\\..\\MIDIClock\\MIDIClock.h"
#include "..\\..\\MIDIStatus\\MIDIStatus.h"
#include "..\\..\\MIDIInstrument\\MIDIInstrument.h"
#include "SekaijuApp.h"

#ifndef CLIP
#define CLIP(A,B,C) ((B)<(A)?(A):((B)>(C)?(C):(B)))
#endif

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
CEventListOptionPage::CEventListOptionPage () : CPropertyPage (CEventListOptionPage::IDD) {
	m_lDefRowZoom = 0;
	m_lDefColumnZoom = 0;
	m_lDefTrackWidth = 0;
	m_lDefMillisecWidth = 0;
	m_lDefTimeWidth = 0;
	m_lDefKindWidth = 0;
	m_lDefChWidth = 0;
	m_lDefVal1Width = 0;
	m_lDefVal2Width = 0;
	m_lDefVal3Width = 0;
	m_bInsertEventAfter = FALSE;
	m_bDuplicateEventAfter = FALSE;
	m_bDeleteEventAfter = FALSE;
}

//------------------------------------------------------------------------------
// オペレーション
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// データエクスチェンジ
void CEventListOptionPage::DoDataExchange (CDataExchange* pDX) {
	CDialog::DoDataExchange (pDX);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFROWZOOM, m_lDefRowZoom);
	DDV_MinMaxInt (pDX, m_lDefRowZoom, 16, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFCOLUMNZOOM, m_lDefColumnZoom);
	DDV_MinMaxInt (pDX, m_lDefColumnZoom, 2, 16);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFTRACKWIDTH, m_lDefTrackWidth);
	DDV_MinMaxInt (pDX, m_lDefTrackWidth, 1, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFMILLISECWIDTH, m_lDefMillisecWidth);
	DDV_MinMaxInt (pDX, m_lDefMillisecWidth, 1, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFTIMEWIDTH, m_lDefTimeWidth);
	DDV_MinMaxInt (pDX, m_lDefTimeWidth, 1, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFKINDWIDTH, m_lDefKindWidth);
	DDV_MinMaxInt (pDX, m_lDefKindWidth, 1, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFCHWIDTH, m_lDefChWidth);
	DDV_MinMaxInt (pDX, m_lDefChWidth, 1, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFVAL1WIDTH, m_lDefVal1Width);
	DDV_MinMaxInt (pDX, m_lDefVal1Width, 1, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFVAL2WIDTH, m_lDefVal2Width);
	DDV_MinMaxInt (pDX, m_lDefVal2Width, 1, 32);
	DDX_Text (pDX, IDC_EVENTLISTOPTION_DEFVAL3WIDTH, m_lDefVal3Width);
	DDV_MinMaxInt (pDX, m_lDefVal3Width, 1, 32);
	DDX_Radio (pDX, IDC_EVENTLISTOPTION_INSERTEVENTBEFORE, m_bInsertEventAfter);
	DDX_Radio (pDX, IDC_EVENTLISTOPTION_DUPLICATEEVENTBEFORE, m_bDuplicateEventAfter);
	DDX_Radio (pDX, IDC_EVENTLISTOPTION_DELETEEVENTBEFORE, m_bDeleteEventAfter);
	DDX_Check (pDX, IDC_EVENTLISTOPTION_ENABLEROWZOOMKEY, m_bEnableRowZoomKey);
	DDX_Check (pDX, IDC_EVENTLISTOPTION_ENABLECOLUMNZOOMKEY, m_bEnableColumnZoomKey);

}



// ダイアログの初期化
BOOL CEventListOptionPage::OnInitDialog () {
	BOOL bRet = CDialog::OnInitDialog ();
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFROWZOOMSP))->SetRange (16, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFCOLUMNZOOMSP))->SetRange (2, 16);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFTRACKWIDTHSP))->SetRange (1, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFMILLISECWIDTHSP))->SetRange (1, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFTIMEWIDTHSP))->SetRange (1, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFKINDWIDTHSP))->SetRange (1, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFCHWIDTHSP))->SetRange (1, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFVAL1WIDTHSP))->SetRange (1, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFVAL2WIDTHSP))->SetRange (1, 32);
	((CSpinButtonCtrl*)GetDlgItem (IDC_EVENTLISTOPTION_DEFVAL3WIDTHSP))->SetRange (1, 32);
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
//	SendMessageToDescendants 
//		(WM_SETFONT, (WPARAM)(HFONT)(pSekaijuApp->m_theDefaultFont), MAKELPARAM(TRUE, 0));
	return bRet;
}

// 状態が変更されたとき
void CEventListOptionPage::OnChange () {
	SetModified (TRUE);
}

//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP (CEventListOptionPage, CPropertyPage)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFROWZOOM, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFCOLUMNZOOM, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFTRACKWIDTH, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFMILLISECWIDTH, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFTIMEWIDTH, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFKINDWIDTH, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFCHWIDTH, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFVAL1WIDTH, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFVAL2WIDTH, OnChange)
	ON_EN_CHANGE (IDC_EVENTLISTOPTION_DEFVAL3WIDTH, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_INSERTEVENTBEFORE, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_INSERTEVENTAFTER, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_DUPLICATEEVENTBEFORE, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_DUPLICATEEVENTAFTER, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_DELETEEVENTBEFORE, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_DELETEEVENTAFTER, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_ENABLEROWZOOMKEY, OnChange)
	ON_BN_CLICKED (IDC_EVENTLISTOPTION_ENABLECOLUMNZOOMKEY, OnChange)
END_MESSAGE_MAP ()

