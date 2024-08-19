//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// オプション(全般)プロパティページクラス
// (C)2002-2020 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "stdafx.h"
#include "resource.h"
#include "GeneralOptionPage.h"
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
CGeneralOptionPage::CGeneralOptionPage () : CPropertyPage (CGeneralOptionPage::IDD) {
	m_bEnableMultiExec = FALSE;
	m_bEnableMultiOpen = TRUE;
	m_bRestoreWindowPlacement = TRUE;
	m_bExecOpen = FALSE; 
	m_bOpenPlay = FALSE;
	m_bPlayUpdate = TRUE;
	m_bSearchUpdate = TRUE;
	m_bEnableCC111Loop = TRUE;
	m_bPatchSearch = TRUE;
	m_bInvertCtrlMouseWheel = FALSE;
	m_bTrackZeroOrigin = FALSE;
	m_bEventZeroOrigin = FALSE;
	m_lSpeedSlow = 50;
	m_lSpeedNormal = 100;
	m_lSpeedFast = 200;
	m_lPlayRecordInterval = 5;
	m_lOctaveSignature = 5;
}

//------------------------------------------------------------------------------
// オペレーション
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// データエクスチェンジ
void CGeneralOptionPage::DoDataExchange (CDataExchange* pDX) {
	CDialog::DoDataExchange (pDX);
	DDX_Check (pDX, IDC_GENERALOPTION_ENABLEMULTIEXEC, m_bEnableMultiExec);
	DDX_Check (pDX, IDC_GENERALOPTION_ENABLEMULTIOPEN, m_bEnableMultiOpen);
	DDX_Check (pDX, IDC_GENERALOPTION_RESTOREWINDOWPLACEMENT, m_bRestoreWindowPlacement);
	DDX_Check (pDX, IDC_GENERALOPTION_EXECOPEN, m_bExecOpen);
	DDX_Check (pDX, IDC_GENERALOPTION_OPENPLAY, m_bOpenPlay);
	DDX_Check (pDX, IDC_GENERALOPTION_PLAYUPDATE, m_bPlayUpdate);
	DDX_Check (pDX, IDC_GENERALOPTION_SEARCHUPDATE, m_bSearchUpdate);
	DDX_Check (pDX, IDC_GENERALOPTION_CHANGEUPDATE, m_bChangeUpdate);
	DDX_Check (pDX, IDC_GENERALOPTION_ENABLECC111LOOP, m_bEnableCC111Loop);
	DDX_Check (pDX, IDC_GENERALOPTION_PATCHSEARCH, m_bPatchSearch);
	DDX_Check (pDX, IDC_GENERALOPTION_INVERTCTRLMOUSEWHEEL, m_bInvertCtrlMouseWheel);
	DDX_Check (pDX, IDC_GENERALOPTION_TRACKZEROORIGIN, m_bTrackZeroOrigin);
	DDX_Check (pDX, IDC_GENERALOPTION_EVENTZEROORIGIN, m_bEventZeroOrigin);
	DDX_Check (pDX, IDC_GENERALOPTION_ENABLEAUTOPAGEUPDATE, m_bEnableAutoPageUpdate);
	DDX_Check (pDX, IDC_GENERALOPTION_SENDNOTEOFFHOLDOFFATEND, m_bSendNoteOffHoldOffAtEnd);
	// DDV_MinMaxXXXは各々のDDX_TEXTの直後に配置すること(20090501訂正)
	DDX_Text (pDX, IDC_GENERALOPTION_SPEEDSLOW, m_lSpeedSlow);
	DDV_MinMaxInt (pDX, m_lSpeedSlow, 1, 1000);
	DDX_Text (pDX, IDC_GENERALOPTION_SPEEDNORMAL, m_lSpeedNormal);
	DDV_MinMaxInt (pDX, m_lSpeedNormal, 1, 1000);
	DDX_Text (pDX, IDC_GENERALOPTION_SPEEDFAST, m_lSpeedFast);
	DDV_MinMaxInt (pDX, m_lSpeedFast, 1, 1000);
	DDX_Text (pDX, IDC_GENERALOPTION_PLAYRECORDINTERVAL, m_lPlayRecordInterval);
	DDV_MinMaxInt (pDX, m_lPlayRecordInterval, 1, 1000);
	DDX_Text (pDX, IDC_GENERALOPTION_OCTAVESIGNATURE, m_lOctaveSignature);
	DDV_MinMaxInt (pDX, m_lOctaveSignature, 3, 5);
}

// ダイアログの初期化
BOOL CGeneralOptionPage::OnInitDialog () {
	BOOL bRet = CDialog::OnInitDialog ();
	((CSpinButtonCtrl*)GetDlgItem (IDC_GENERALOPTION_SPEEDSLOWSP))->SetRange (1, 1000);
	((CSpinButtonCtrl*)GetDlgItem (IDC_GENERALOPTION_SPEEDNORMALSP))->SetRange (1, 1000);
	((CSpinButtonCtrl*)GetDlgItem (IDC_GENERALOPTION_SPEEDFASTSP))->SetRange (1, 1000);
	((CSpinButtonCtrl*)GetDlgItem (IDC_GENERALOPTION_PLAYRECORDINTERVALSP))->SetRange (1, 1000); //20200205修正
	((CSpinButtonCtrl*)GetDlgItem (IDC_GENERALOPTION_OCTAVESIGNATURESP))->SetRange (3, 5);
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
//	SendMessageToDescendants 
//		(WM_SETFONT, (WPARAM)(HFONT)(pSekaijuApp->m_theDefaultFont), MAKELPARAM(TRUE, 0));
	return bRet;
}

// 選択状態が変更されたとき
void CGeneralOptionPage::OnChange () {
	SetModified (TRUE);
}

//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP (CGeneralOptionPage, CPropertyPage)
	ON_BN_CLICKED (IDC_GENERALOPTION_ENABLEMULTIEXEC, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_ENABLEMULTIOPEN, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_RESTOREWINDOWPLACEMENT, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_EXECOPEN, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_OPENPLAY, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_PLAYUPDATE, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_SEARCHUPDATE, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_CHANGEUPDATE, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_ENABLECC111LOOP, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_PATCHSEARCH, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_INVERTCTRLMOUSEWHEEL, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_TRACKZEROORIGIN, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_EVENTZEROORIGIN, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_ENABLEAUTOPAGEUPDATE, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_SENDNOTEOFFHOLDOFFATEND, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_ENABLEMULTIEXEC, OnChange)
	ON_BN_CLICKED (IDC_GENERALOPTION_ENABLEMULTIEXEC, OnChange)
	ON_EN_CHANGE (IDC_GENERALOPTION_SPEEDSLOW, OnChange)
	ON_EN_CHANGE (IDC_GENERALOPTION_SPEEDNORMAL, OnChange)
	ON_EN_CHANGE (IDC_GENERALOPTION_SPEEDFAST, OnChange)
	ON_EN_CHANGE (IDC_GENERALOPTION_PLAYRECORDINTERVAL, OnChange)
	ON_EN_CHANGE (IDC_GENERALOPTION_OCTAVESIGNATURE, OnChange)
END_MESSAGE_MAP ()




