//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// オプションプロパティシートクラス
// (C)2002-2020 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "stdafx.h"
#include "..\\..\\MIDIIO\\MIDIIO.h"
#include "..\\..\\MIDIData\\MIDIData.h"
#include "..\\..\\MIDIClock\\MIDIClock.h"
#include "..\\..\\MIDIStatus\\MIDIStatus.h"
#include "..\\..\\MIDIInstrument\\MIDIInstrument.h"
#include "Resource.h"
#include "SekaijuApp.h"
#include "ColorSelectComboBox.h"
#include "OptionSheet.h"

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
COptionSheet::COptionSheet (CWnd* pParentWnd) :
CPropertySheet (IDS_OPTIONS, pParentWnd) {
	AddPage (&m_theGeneralOptionPage);
	AddPage (&m_theColorOptionPage);
	AddPage (&m_theFontOptionPage);
	AddPage (&m_theTrackListOption1Page);
	AddPage (&m_theTrackListOption2Page);
	AddPage (&m_thePianoRollOptionPage);
	AddPage (&m_theEventListOptionPage);
	AddPage (&m_theMusicalScoreOptionPage);
}

// デストラクタ
COptionSheet::~COptionSheet () {
}

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// 初期化時
BOOL COptionSheet::OnInitDialog() {
	BOOL bResult = CPropertySheet::OnInitDialog();
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	SetActivePage (pSekaijuApp->m_theCurrentPage.m_lOption);
	CTabCtrl* pTabCtrl = GetTabControl ();
	ASSERT (pTabCtrl);
//	pTabCtrl->SetFont (&(pSekaijuApp->m_theDefaultFont));
//	pTabCtrl->SendMessageToDescendants 
//		(WM_SETFONT, (WPARAM)(HFONT)(pSekaijuApp->m_theDefaultFont), MAKELPARAM(TRUE, 0));
	// リセットボタン 20210314追加
	CString strReset;
	strReset.LoadString (IDS_RESET);
	CRect rcButton;
	GetDlgItem (IDOK)->GetWindowRect (&rcButton);
	this->ScreenToClient (&rcButton);
	rcButton.OffsetRect (-rcButton.left + 5, 0);
	m_theResetButton.Create (strReset, WS_VISIBLE | WS_CHILD, rcButton, this, IDC_OPTION_RESETBUTTON);
	m_theResetButton.SetFont (GetDlgItem (IDOK)->GetFont ());

	return bResult;
}

// コマンド時
BOOL COptionSheet::OnCommand (WPARAM wParam, LPARAM lParam) {
	// 『OK』又は『キャンセル』ボタンが押された
	if (LOWORD (wParam) == IDOK || LOWORD (wParam) == IDCANCEL) {
		CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
		pSekaijuApp->m_theCurrentPage.m_lOption = GetActiveIndex ();
	}
	return CPropertySheet::OnCommand(wParam, lParam);
}

// DoModal時
INT_PTR COptionSheet::DoModal () {
	// オーバーライドされたコールバック関数を使用するように指示。
	m_psh.dwFlags |= PSH_USECALLBACK;
	m_psh.pfnCallback = PropSheetProc;
	return CPropertySheet::DoModal ();
}

class COptionDialogTemplate : public CDialogTemplate {
	friend class COptionSheet;
};

// 各ページの構築時
void COptionSheet::BuildPropPageArray () {
	CPropertySheet::BuildPropPageArray ();
	// リソースで指定したプロパティページのフォントフェイスとフォントサイズは
	// 無視されるので、ここで強制指定する。
	CString strFontName;
	strFontName.LoadString (IDS_DEFAULTFONTNAME);
	LPCPROPSHEETPAGE ppsp = m_psh.ppsp;
	for (int nPage = 0; nPage < m_pages.GetSize (); nPage++) {
		const DLGTEMPLATE* pResource = ppsp->pResource;
		CDialogTemplate dlgTemplate;
		dlgTemplate.m_hTemplate = ::GlobalHandle (pResource);
		dlgTemplate.m_dwTemplateSize = COptionDialogTemplate::GetTemplateSize (pResource);
		dlgTemplate.SetFont (strFontName, 9);
		//memmove ((void*)pResource, dlgTemplate.m_hTemplate, dlgTemplate.m_dwTemplateSize);
		DLGTEMPLATE* pNewDlgTemplate = (DLGTEMPLATE*)dlgTemplate.Detach (); //20210808修正
		(BYTE*&)ppsp += ppsp->dwSize;
	}
}

// コールバック関数
int CALLBACK COptionSheet::PropSheetProc (HWND hwndDlg, UINT uMsg, LPARAM lParam) {
	switch (uMsg) {
	case PSCB_PRECREATE:
		{
		// リソースで指定したプロパティシートのフォントフェイスとフォントサイズは
		// 無視されるので、ここで強制指定する。
			CString strFontName;
			strFontName.LoadString (IDS_DEFAULTFONTNAME);
			LPDLGTEMPLATE pResource = (LPDLGTEMPLATE)lParam;
			CDialogTemplate dlgTemplate;
			dlgTemplate.m_hTemplate = ::GlobalHandle (pResource);
			dlgTemplate.m_dwTemplateSize = COptionDialogTemplate::GetTemplateSize (pResource);
			dlgTemplate.SetFont (strFontName, 9);
			//memmove ((void*)lParam, dlgTemplate.m_hTemplate, dlgTemplate.m_dwTemplateSize);
			DLGTEMPLATE* pNewDlgTemplate = (DLGTEMPLATE*)dlgTemplate.Detach (); //20210808修正
			break;
		}
	default:
		break;
	}
	return 0;
}


//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP (COptionSheet, CPropertySheet)
	ON_BN_CLICKED (ID_APPLY_NOW, OnApplyNow)
	ON_BN_CLICKED (IDC_OPTION_RESETBUTTON, OnReset)
END_MESSAGE_MAP ()


// 『適用』ボタンが押された
void COptionSheet::OnApplyNow () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	GetActivePage ()->UpdateData (TRUE);
	pSekaijuApp->ApplyOptionSheet (this);
	m_theGeneralOptionPage.SetModified (FALSE);
	m_theColorOptionPage.SetModified (FALSE);
	m_theFontOptionPage.SetModified (FALSE);
	m_theTrackListOption1Page.SetModified (FALSE);
	m_theTrackListOption2Page.SetModified (FALSE);
	m_thePianoRollOptionPage.SetModified (FALSE);
	m_theEventListOptionPage.SetModified (FALSE);
	m_theMusicalScoreOptionPage.SetModified (FALSE);
	CString strClose;
	VERIFY (strClose.LoadString (IDS_CLOSE));
	GetDlgItem (IDCANCEL)->SetWindowText (strClose); // 20201223追加
}



//　『リセット』ボタンが押された 20200314追加
void COptionSheet::OnReset () {

	if (GetActivePage () == &m_theGeneralOptionPage) {
		m_theGeneralOptionPage.m_bEnableMultiExec = FALSE;
		m_theGeneralOptionPage.m_bEnableMultiOpen = TRUE;
		m_theGeneralOptionPage.m_bRestoreWindowPlacement = TRUE;
		m_theGeneralOptionPage.m_bExecOpen = FALSE;
		m_theGeneralOptionPage.m_bOpenPlay = FALSE;
		m_theGeneralOptionPage.m_bSearchUpdate = TRUE;
		m_theGeneralOptionPage.m_bPlayUpdate = TRUE;
		m_theGeneralOptionPage.m_bChangeUpdate = TRUE;
		m_theGeneralOptionPage.m_bEnableCC111Loop = TRUE;
		m_theGeneralOptionPage.m_bPatchSearch = TRUE;
		m_theGeneralOptionPage.m_bInvertCtrlMouseWheel = FALSE;
		m_theGeneralOptionPage.m_bTrackZeroOrigin = FALSE;
		m_theGeneralOptionPage.m_bEventZeroOrigin = FALSE;
		m_theGeneralOptionPage.m_bEnableAutoPageUpdate = TRUE;
		m_theGeneralOptionPage.m_bSendNoteOffHoldOffAtEnd = TRUE;
		m_theGeneralOptionPage.m_lSpeedSlow = 50;
		m_theGeneralOptionPage.m_lSpeedNormal = 100;
		m_theGeneralOptionPage.m_lSpeedFast = 200;
		m_theGeneralOptionPage.m_lPlayRecordInterval = 5;
		m_theGeneralOptionPage.m_lOctaveSignature = 3;
		m_theGeneralOptionPage.UpdateData (FALSE);
		m_theGeneralOptionPage.SetModified (FALSE);
	}

	if (GetActivePage () == &m_theColorOptionPage) {
		m_theColorOptionPage.m_theForeColorCombo[0].SetCurColor (0x00FF0000);
		m_theColorOptionPage.m_theForeColorCombo[1].SetCurColor (0x00808000);
		m_theColorOptionPage.m_theForeColorCombo[2].SetCurColor (0x00008000);
		m_theColorOptionPage.m_theForeColorCombo[3].SetCurColor (0x00008080);
		m_theColorOptionPage.m_theForeColorCombo[4].SetCurColor (0x000000F0);
		m_theColorOptionPage.m_theForeColorCombo[5].SetCurColor (0x008000F0);
		m_theColorOptionPage.m_theForeColorCombo[6].SetCurColor (0x00800080);
		m_theColorOptionPage.m_theForeColorCombo[7].SetCurColor (0x00FF0080);
		m_theColorOptionPage.m_theBackColorCombo[0].SetCurColor (0x00FFFFFF);
		m_theColorOptionPage.m_theBackColorCombo[1].SetCurColor (0x00C0FFFF);
		m_theColorOptionPage.m_theHorzColorCombo[0].SetCurColor (0x00C0C0C0);
		m_theColorOptionPage.m_theHorzColorCombo[1].SetCurColor (0x00FF8080);
		m_theColorOptionPage.m_theVertColorCombo[0].SetCurColor (0x00C0C0C0);
		m_theColorOptionPage.m_theVertColorCombo[1].SetCurColor (0x00FF8080);
		m_theColorOptionPage.SetModified (FALSE);
	}


	if (GetActivePage () == &m_theFontOptionPage) {
		m_theFontOptionPage.m_strFontName[0] = _T("(Default)");
		m_theFontOptionPage.m_lFontSize[0] = 12;
		m_theFontOptionPage.m_strFontName[1] =  _T("(Default)");
		m_theFontOptionPage.m_lFontSize[1] = 20;
		m_theFontOptionPage.m_strFontName[2] = _T("(Default)");
		m_theFontOptionPage.m_lFontSize[2] = 24;
		m_theFontOptionPage.m_strFontName[3] = _T("(Default)");
		m_theFontOptionPage.m_lFontSize[3] = 40;
		m_theFontOptionPage.UpdateData (FALSE);
		m_theFontOptionPage.SetModified (FALSE);
	}

	if (GetActivePage () == &m_theTrackListOption1Page) {
		m_theTrackListOption1Page.m_lDefRowZoom = 24;
		m_theTrackListOption1Page.m_lDefColumnZoom = 6;
		m_theTrackListOption1Page.m_lDefTimeZoom = 6;
		m_theTrackListOption1Page.m_lDefNameWidth = 12;
		m_theTrackListOption1Page.m_lDefColorWidth = 2;
		m_theTrackListOption1Page.m_lDefInputOnWidth = 4;
		m_theTrackListOption1Page.m_lDefInputPortWidth = 16;
		m_theTrackListOption1Page.m_lDefInputChWidth = 5;
		m_theTrackListOption1Page.m_lDefOutputOnWidth = 4;
		m_theTrackListOption1Page.m_lDefOutputPortWidth = 16;
		m_theTrackListOption1Page.m_lDefOutputChWidth = 5;
		m_theTrackListOption1Page.m_lDefViewModeWidth = 5;
		m_theTrackListOption1Page.UpdateData (FALSE);
		m_theTrackListOption1Page.SetModified (FALSE);
	}

	if (GetActivePage () == &m_theTrackListOption2Page) {
		m_theTrackListOption2Page.m_lDefCC000Width = 5;
		m_theTrackListOption2Page.m_lDefCC032Width = 5;
		m_theTrackListOption2Page.m_lDefPCWidth = 16;
		m_theTrackListOption2Page.m_lDefCC007Width = 5;
		m_theTrackListOption2Page.m_lDefCC010Width = 5;
		m_theTrackListOption2Page.m_lDefCC091Width = 5;
		m_theTrackListOption2Page.m_lDefCC093Width = 5;
		m_theTrackListOption2Page.m_lDefCC094Width = 5;
		m_theTrackListOption2Page.m_lDefKeyShiftWidth = 5;
		m_theTrackListOption2Page.m_lDefVelShiftWidth = 5;
		m_theTrackListOption2Page.m_lDefTimeShiftWidth = 5;
		m_theTrackListOption2Page.m_lDefNumEventWidth = 8;
		m_theTrackListOption2Page.m_bEnableRowZoomKey = 1;
		m_theTrackListOption2Page.m_bEnableColumnZoomKey = 0;
		m_theTrackListOption2Page.m_bEnableTimeZoomKey = 0;
		m_theTrackListOption2Page.UpdateData (FALSE);
		m_theTrackListOption2Page.SetModified (FALSE);
	}

	if (GetActivePage () == &m_thePianoRollOptionPage) {
		m_thePianoRollOptionPage.m_lDefKeyZoom = 6;
		m_thePianoRollOptionPage.m_lDefVelZoom = 1;
		m_thePianoRollOptionPage.m_lDefTimeZoom = 6;
		m_thePianoRollOptionPage.m_bEnableKeyZoomKey = 1;
		m_thePianoRollOptionPage.m_bEnableVelZoomKey = 0;
		m_thePianoRollOptionPage.m_bEnableTimeZoomKey = 0;
		m_thePianoRollOptionPage.m_bSpeakerModeVisibleTrack = 0;
		m_thePianoRollOptionPage.m_lGraphLineWidth = 1;
		m_thePianoRollOptionPage.UpdateData (FALSE);
		m_thePianoRollOptionPage.SetModified (FALSE);
	}

	if (GetActivePage () == &m_theEventListOptionPage) {
		m_theEventListOptionPage.m_lDefRowZoom = 20;
		m_theEventListOptionPage.m_lDefColumnZoom = 6;
		m_theEventListOptionPage.m_lDefTrackWidth = 16;
		m_theEventListOptionPage.m_lDefMillisecWidth = 16;
		m_theEventListOptionPage.m_lDefTimeWidth = 16;
		m_theEventListOptionPage.m_lDefKindWidth = 16;
		m_theEventListOptionPage.m_lDefChWidth = 8;
		m_theEventListOptionPage.m_lDefVal1Width = 16;
		m_theEventListOptionPage.m_lDefVal2Width = 16;
		m_theEventListOptionPage.m_lDefVal3Width = 16;
		m_theEventListOptionPage.m_bInsertEventAfter = 0;
		m_theEventListOptionPage.m_bDuplicateEventAfter = 0;
		m_theEventListOptionPage.m_bDeleteEventAfter = 1;
		m_theEventListOptionPage.m_bEnableRowZoomKey = 1;
		m_theEventListOptionPage.m_bEnableColumnZoomKey = 0;
		m_theEventListOptionPage.UpdateData (FALSE);
		m_theEventListOptionPage.SetModified (FALSE);
	}

	if (GetActivePage () == &m_theMusicalScoreOptionPage) {
		m_theMusicalScoreOptionPage.m_lDefTrackZoom = 4;
		m_theMusicalScoreOptionPage.m_lDefTimeZoom = 8;
		m_theMusicalScoreOptionPage.m_bEnableTrackZoomKey = 1;
		m_theMusicalScoreOptionPage.m_bEnableTimeZoomKey = 0;
		m_theMusicalScoreOptionPage.m_bSpeakerModeVisibleTrack = 0;
		m_theMusicalScoreOptionPage.UpdateData (FALSE);
		m_theMusicalScoreOptionPage.SetModified (FALSE);
	}

}


