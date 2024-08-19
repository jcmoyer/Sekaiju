//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// MDI子フレームウィンドウクラス
// (C)2002-2021 おーぷんMIDIぷろじぇくと／くず
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
#include "SekaijuApp.h"
#include "SekaijuToolBar.h"
#include "SekaijuStatusBar.h"
#include "MainFrame.h"
#include "ChildFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE (CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP (CChildFrame, CMDIChildWnd)
	ON_WM_MDIACTIVATE ()
END_MESSAGE_MAP ()

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
CChildFrame::CChildFrame () {
}

// デストラクタ
CChildFrame::~CChildFrame () {
}

//------------------------------------------------------------------------------
// オペレーション
//------------------------------------------------------------------------------

// ドキュメントへのポインタ取得
CDocument* CChildFrame::GetDocument () {
	CView* pActiveView = GetActiveView ();
	if (pActiveView) {
		return pActiveView->GetDocument ();
	}
	else {
		return NULL;
	}
}


// 次の仮想関数はオーバーライドしてください。
long CChildFrame::GetCurTrackIndex () {
	return 0;
}

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------
BOOL CChildFrame::PreCreateWindow (CREATESTRUCT& cs) {
	if (!CMDIChildWnd::PreCreateWindow (cs)) {
		return FALSE;
	}
	return TRUE;
}


// ウィンドウが破棄された後
void CChildFrame::PostNcDestroy () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp();
	pSekaijuApp->UpdateCurWndAndDocPtr ();
	CMDIChildWnd::PostNcDestroy ();
}


// CChildFrame 診断

#ifdef _DEBUG
void CChildFrame::AssertValid () const {
	CMDIChildWnd::AssertValid ();
}

void CChildFrame::Dump (CDumpContext& dc) const {
	CMDIChildWnd::Dump (dc);
}
#endif //_DEBUG

//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------

// ウィンドウがアクティブになったとき
void CChildFrame::OnMDIActivate (BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	if (bActivate == TRUE) {
		pSekaijuApp->UpdateCurWndAndDocPtr ();
	}
	CMDIChildWnd::OnMDIActivate (bActivate, pActivateWnd, pDeactivateWnd); // 20210607 BugFix
}



