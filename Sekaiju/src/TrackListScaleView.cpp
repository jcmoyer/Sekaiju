﻿//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// トラックリストスケールビュークラス
// (C)2002-2017 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "stdafx.h"
#include "resource.h"
#include "..\\..\\MIDIIO\\MIDIIO.h"
#include "..\\..\\MIDIData\\MIDIData.h"
#include "..\\..\\MIDIClock\\MIDIClock.h"
#include "..\\..\\MIDIStatus\\MIDIStatus.h"
#include "..\\..\\MIDIInstrument\\MIDIInstrument.h"
#include "HistoryRecord.h"
#include "HistoryUnit.h"
#include "SekaijuApp.h"
#include "SekaijuDoc.h"
#include "SekaijuView.h"
#include "SekaijuToolbar.h"
#include "SekaijuStatusBar.h"
#include "MainFrame.h"
#include "ChildFrame.h"
#include "TrackListFrame.h"
#include "TrackListScaleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE (CTrackListScaleView, CSekaijuView)

// メッセージマップ
BEGIN_MESSAGE_MAP (CTrackListScaleView, CSekaijuView)
	ON_WM_KEYDOWN ()
	ON_WM_MOUSEWHEEL ()
END_MESSAGE_MAP ()

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
CTrackListScaleView::CTrackListScaleView () {
}

// デストラクタ
CTrackListScaleView::~CTrackListScaleView () {
}

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// 描画
void CTrackListScaleView::OnDraw (CDC* pDC) {
	CSekaijuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rcClient;
	GetClientRect (&rcClient);
	long lColorBtnFace = ::GetSysColor (COLOR_BTNFACE);
	pDC->FillSolidRect (&rcClient, lColorBtnFace);

}

// ビューの更新
void CTrackListScaleView::OnUpdate (CView* pSender, LPARAM lHint, CObject* pHint) {
	// クリティカルセクションはロックされているものとする。
	CTrackListFrame* pTrackListFrame = (CTrackListFrame*)GetParent ();
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd ();
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// 演奏開始した場合、リアルタイム入力開始した場合、位置移動した場合
	if ((lHint & SEKAIJUDOC_PLAYSTARTED) || 
		(lHint & SEKAIJUDOC_RECORDSTARTED) ||
		(lHint & SEKAIJUDOC_POSITIONCHANGED)) {
		if (pSekaijuApp->m_theGeneralOption.m_bEnableAutoPageUpdate) { // 20091224追加
			pTrackListFrame->m_bAutoPageUpdate = TRUE;
		}
	}
	// MIDIデータ又はMIDIトラック又はMIDIイベントが変更された場合
	if ((lHint & SEKAIJUDOC_MIDIDATACHANGED) ||
		(lHint & SEKAIJUDOC_MIDITRACKCHANGED) ||
		(lHint & SEKAIJUDOC_MIDIEVENTCHANGED)) {
		MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;
		long lEndTime = MIDIData_GetEndTime (pMIDIData);
		pMainFrame->SetPositionScrollRange (0, lEndTime, TRUE);
		pTrackListFrame->RecalcRowScrollInfo (lLogPixelsY);
		pTrackListFrame->RecalcColumnScrollInfo (lLogPixelsX);
		pTrackListFrame->RecalcTimeScrollInfo (lLogPixelsX);
	}
	CSekaijuView::OnUpdate (pSender, lHint, pHint);
}

//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------

// キー押し下げ時
void CTrackListScaleView::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags) {
	CTrackListFrame* pTrackListFrame = (CTrackListFrame*)GetParent ();
	pTrackListFrame->PostMessage (WM_KEYDOWN, nChar, (nFlags << 16) | nRepCnt);
}

// マウスホイールが回された時
BOOL CTrackListScaleView::OnMouseWheel (UINT nFlags, short zDelta, CPoint point) {
	CTrackListFrame* pTrackListFrame = (CTrackListFrame*)GetParent ();
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lDelta = zDelta;
	long lFlags = nFlags;
	if (lFlags & MK_CONTROL) {
		if (lDelta > 0 && pSekaijuApp->m_theGeneralOption.m_bInvertCtrlMouseWheel == 0 ||
			lDelta < 0 && pSekaijuApp->m_theGeneralOption.m_bInvertCtrlMouseWheel != 0) {
			pTrackListFrame->PostMessage (WM_COMMAND, ID_CONTROL_PREVMEASURE);
		}
		else {
			pTrackListFrame->PostMessage (WM_COMMAND, ID_CONTROL_NEXTMEASURE);
		}
	}
	else {
		long lRowScrollPos = pTrackListFrame->GetRowScrollPos ();
		long lRowZoom = pTrackListFrame->GetRowZoom ();
		lRowScrollPos -= lRowZoom * lLogPixelsY / 96 * lDelta / 120;
		pTrackListFrame->SetRowScrollPos (lRowScrollPos);
	}
	return TRUE;
}
