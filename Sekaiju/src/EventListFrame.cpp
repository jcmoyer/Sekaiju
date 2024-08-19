//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// イベントリストフレームウィンドウクラス
// (C)2002-2023 おーぷんMIDIぷろじぇくと／くず
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
#include "stdint.h"
#include "resource.h"
#include "ColorfulComboBox.h"
#include "ColorfulCheckListBox.h"
#include "HistoryRecord.h"
#include "HistoryUnit.h"
#include "SekaijuApp.h"
#include "SekaijuDoc.h"
#include "SekaijuView.h"
#include "SekaijuToolBar.h"
#include "SekaijuStatusBar.h"
#include "SekaijuFileDlg.h"
#include "MainFrame.h"
#include "ChildFrame.h"
#include "EventListFrame.h"
#include "EventListPrintView.h"
#include "EventListScaleView.h"
#include "EventListIndexScaleView.h"
#include "EventListPropertyScaleView.h"
#include "EventListIndexPropertyView.h"
#include "TrackListBox.h"
#include "EventKindListBox.h"
#include "ControlChangeListBox.h"
#include "TextFile.h"
#include "common.h"

// アロケーションの監視
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 子ウィンドウのサイズ
#define EVENTLISTFRAME_SCALEHEIGHT 16
#define EVENTLISTFRAME_SCALEWIDTH 64
#define EVENTLISTFRAME_PROPERTYWIDTH 600
#define EVENTLISTFRAME_TRACKLISTWIDTH 200
#define EVENTLISTFRAME_INDEXHEIGHT 256
#define EVENTLISTFRAME_SCROLLBARHEIGHT 16
#define EVENTLISTFRAME_SCROLLBARWIDTH 16
#define EVENTLISTFRAME_BORDERWIDTH 2
#define EVENTLISTFRAME_BORDERHEIGHT 2
#define EVENTLISTFRAME_SPLITTERWIDTH 4
#define EVENTLISTFRAME_SPLITTERHEIGHT 4
#define EVENTLISTFRAME_TRACKLISTHEIGHT 128
#define EVENTLISTFRAME_EVENTKINDLISTHEIGHT 128
#define EVENTLISTFRAME_CONTROLCHANGELISTHEIGHT 128

// 子ウィンドウIDを定義
#define EVENTLISTFRAME_DUMMYVIEW         (AFX_IDW_PANE_FIRST + 0)
#define EVENTLISTFRAME_PRINTVIEW         (AFX_IDW_PANE_FIRST + 31)
#define EVENTLISTFRAME_SCALEVIEW         (AFX_IDW_PANE_FIRST + 32)
#define EVENTLISTFRAME_PROPERTYSCALEVIEW (AFX_IDW_PANE_FIRST + 33)
#define EVENTLISTFRAME_INDEXSCALEVIEW    (AFX_IDW_PANE_FIRST + 34)
#define EVENTLISTFRAME_INDEXPROPERTYVIEW (AFX_IDW_PANE_FIRST + 35)
#define EVENTLISTFRAME_ROWSCROLL         (AFX_IDW_PANE_FIRST + 48)
#define EVENTLISTFRAME_COLUMNSCROLL      (AFX_IDW_PANE_FIRST + 49)
#define EVENTLISTFRAME_SIZEBOX           (AFX_IDW_PANE_FIRST + 51)
#define EVENTLISTFRAME_ROWZOOMDOWN       (AFX_IDW_PANE_FIRST + 52)
#define EVENTLISTFRAME_ROWZOOMUP         (AFX_IDW_PANE_FIRST + 53)
#define EVENTLISTFRAME_COLUMNZOOMDOWN    (AFX_IDW_PANE_FIRST + 54)
#define EVENTLISTFRAME_COLUMNZOOMUP      (AFX_IDW_PANE_FIRST + 55)
#define EVENTLISTFRAME_TRACKLIST         (AFX_IDW_PANE_FIRST + 61)
#define EVENTLISTFRAME_EVENTKINDLIST     (AFX_IDW_PANE_FIRST + 62)
#define EVENTLISTFRAME_CONTROLCHANGELIST (AFX_IDW_PANE_FIRST + 63)

//
// イベントリストフレームのクライアント領域に配置されたオブジェクト
//	　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　 　
//                                                            m_lVSc  ┃
//                  ┃←m_lScale→│← m_lPropertyWidth →│←rollBa→★
//                      Width                          　　　 rWidth  ┃　　　  
//		　─								                   
//        ↑         ┏───────────────────────────────────┓
// m_lToolBar1Height ┃CSekaijuToolBar                                                       ┃
//        ↓         ┃m_wndToolBar1                                                         ┃
//        ━         ┣━━━━━━┯━━━━━━━━━━━━━━┯━┳━━━━━━━━━┯━┫
//        ↑         ┃CView*      │CView*                      │↑┃                  │↑┃
//  m_lScaleHeight   ┃m_pScaleView│m_pPrepertyScaleView    　　├─┨CCheckListBox     ├─┨
//        ↓         ┠──────┼──────────────┤　┃m_wndTrackList    │□┃
//        ─         ┃CView*      │CView*           　 　　　　│□★(with ScrollBar)  ├─┨
//        ↑         ┃m_pIndexScal│m_pPrepertyIndexView    　　│  ┃                  │↓┃
//                   ┃eView       │　　　　　　　　　　　　　　│  ┠─┬─────┬─┼─┨
//                   ┃　　　      │　                          │  ┃←│□        │→│  ┃
//  m_lIndexHeight   ┃　　　      │　　　　　　　　　　　　　　├─╂━┷━━━★━┷━┿━┫
//                   ┃　　　      │ 　CScrollBar m_wndRowScroll│↓┃                  │↑┃
//                   ┃　　　      │　　　　　　　　　　　　　　├─┨CCheckListBox     ├─┨
//                   ┃　　　      │    CButton m_wndRowZoomDwon│－★m_wndEventKindList│□┃
//        ↓         ┃　　　      │　　　　　　　　　　　　　　├─┨(with ScrollBar)  ├─┨
//        ─         ┃　　　      │  　  CButton m_wndRowZoomUp│＋┃                  │↓┃
//        ↑         ┠─┬────┴────────┬─┬─┬─┼─╂─┬─────┬─┼─┨     
//m_lHScrollBarHeight┃←│　　　□　　　　　　　　　│→│－│＋│⊿┃←│□        │→│  ┃
//        ↓         ┗━┷━━━━━━━━━━━━━┷━┷━┷━┷━┻━┷━━━━━┷━┷━┛
//        ━           CScrollBar                  CButton CButton
//                     m_wndColumn                 m_wndCo m_wndCo
//                     Scroll                      lumnZoo lumnZoo
//                                                 mDown   mUp
//
// (あ)―――：単純な境界(0px)。
// (い)━━━：太く立体的な境界線。BORDERWIDTH(2px)又はBORDERHEIGHT(2px)で示す幅を占領
// (う)━★━：スプリッター境界線。(い)*2+SPRITTERWIDTH(4px)又はSPRITTERHEIGHT(4px)で示す幅を占領。




// 関数マクロ
#ifndef CLIP
#define CLIP(A,B,C) ((A)>(B)?(A):((B)>(C)?(C):(B)))
#endif

// メッセージマップ
IMPLEMENT_DYNCREATE(CEventListFrame, CChildFrame)

BEGIN_MESSAGE_MAP(CEventListFrame, CChildFrame)
	ON_WM_CREATE ()
	ON_WM_DESTROY ()
	ON_WM_SIZE ()
	ON_WM_TIMER ()
	ON_WM_ERASEBKGND ()
	ON_WM_MDIACTIVATE ()
	ON_WM_CLOSE ()
	ON_WM_PAINT ()	
	ON_WM_KEYDOWN ()
	ON_WM_LBUTTONDOWN ()	
	ON_WM_RBUTTONDOWN ()	
	ON_WM_LBUTTONUP ()	
	ON_WM_RBUTTONUP ()	
	ON_WM_MOUSEMOVE ()
	ON_WM_HSCROLL ()
	ON_WM_VSCROLL ()
	ON_BN_CLICKED (EVENTLISTFRAME_COLUMNZOOMDOWN, OnColumnZoomDown)
	ON_BN_CLICKED (EVENTLISTFRAME_COLUMNZOOMUP, OnColumnZoomUp)
	ON_BN_CLICKED (EVENTLISTFRAME_ROWZOOMDOWN, OnRowZoomDown)
	ON_BN_CLICKED (EVENTLISTFRAME_ROWZOOMUP, OnRowZoomUp)
	ON_COMMAND (ID_EVENTLIST_INSERTEVENT, OnEventListInsertEvent)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_INSERTEVENT, OnUpdateEventListInsertEventUI)
	ON_COMMAND (ID_EVENTLIST_DUPLICATEEVENT, OnEventListDuplicateEvent)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_DUPLICATEEVENT, OnUpdateEventListDuplicateEventUI)
	ON_COMMAND (ID_EVENTLIST_DELETEEVENT, OnEventListDeleteEvent)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_DELETEEVENT, OnUpdateEventListDeleteEventUI)
	ON_COMMAND (ID_EVENTLIST_MOVEUPEVENT, OnEventListMoveUpEvent)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_MOVEUPEVENT, OnUpdateEventListMoveUpEventUI)
	ON_COMMAND (ID_EVENTLIST_MOVEDOWNEVENT, OnEventListMoveDownEvent)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_MOVEDOWNEVENT, OnUpdateEventListMoveDownEventUI)
	ON_COMMAND (ID_EVENTLIST_ONLYCURTRACK, OnEventListOnlyCurTrack)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_ONLYCURTRACK, OnUpdateEventListOnlyCurTrackUI)
	ON_COMMAND (ID_EVENTLIST_SHOWALLTRACK, OnEventListShowAllTrack)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_SHOWALLTRACK, OnUpdateEventListShowAllTrackUI)
	ON_COMMAND (ID_EVENTLIST_ONLYCUREVENTKIND, OnEventListOnlyCurEventKind)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_ONLYCUREVENTKIND, OnUpdateEventListOnlyCurEventKindUI)
	ON_COMMAND (ID_EVENTLIST_SHOWALLEVENTKIND, OnEventListShowAllEventKind)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_SHOWALLEVENTKIND, OnUpdateEventListShowAllEventKindUI)
	ON_COMMAND (ID_EVENTLIST_ONLYCURCONTROLCHANGE, OnEventListOnlyCurControlChange)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_ONLYCURCONTROLCHANGE, OnUpdateEventListOnlyCurControlChangeUI)
	ON_COMMAND (ID_EVENTLIST_SHOWALLCONTROLCHANGE, OnEventListShowAllControlChange)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_SHOWALLCONTROLCHANGE, OnUpdateEventListShowAllControlChangeUI)
	ON_COMMAND (ID_EVENTLIST_AUTOPAGEUPDATE, OnEventListAutoPageUpdate)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_AUTOPAGEUPDATE, OnUpdateEventListAutoPageUpdateUI)
	ON_COMMAND (ID_EVENTLIST_SAVEAS, OnEventListSaveAs)
	ON_UPDATE_COMMAND_UI (ID_EVENTLIST_SAVEAS, OnUpdateEventListSaveAsUI)
	ON_COMMAND (ID_POPUP_TRACKVISIBLEON, OnPopupTrackVisibleOn)
	ON_UPDATE_COMMAND_UI (ID_POPUP_TRACKVISIBLEON, OnUpdatePopupTrackVisibleOnUI) // 20100429追加
	ON_COMMAND (ID_POPUP_TRACKVISIBLEOFF, OnPopupTrackVisibleOff)
	ON_UPDATE_COMMAND_UI (ID_POPUP_TRACKVISIBLEOFF, OnUpdatePopupTrackVisibleOffUI) // 20100429追加
	ON_COMMAND (ID_POPUP_TRACKVISIBLEALL, OnPopupTrackVisibleAll)
	ON_UPDATE_COMMAND_UI (ID_POPUP_TRACKVISIBLEALL, OnUpdatePopupTrackVisibleAllUI) // 20100429追加
	ON_COMMAND (ID_POPUP_EVENTKINDVISIBLEON, OnPopupEventKindVisibleOn)
	ON_UPDATE_COMMAND_UI (ID_POPUP_EVENTKINDVISIBLEON, OnUpdatePopupEventKindVisibleOnUI) // 20100429追加
	ON_COMMAND (ID_POPUP_EVENTKINDVISIBLEOFF, OnPopupEventKindVisibleOff)
	ON_UPDATE_COMMAND_UI (ID_POPUP_EVENTKINDVISIBLEOFF, OnUpdatePopupEventKindVisibleOffUI) // 20100429追加
	ON_COMMAND (ID_POPUP_EVENTKINDVISIBLEALL, OnPopupEventKindVisibleAll)
	ON_UPDATE_COMMAND_UI (ID_POPUP_EVENTKINDVISIBLEALL, OnUpdatePopupEventKindVisibleAllUI) // 20100429追加
	ON_COMMAND (ID_POPUP_CONTROLCHANGEVISIBLEON, OnPopupControlChangeVisibleOn)
	ON_UPDATE_COMMAND_UI (ID_POPUP_CONTROLCHANGEVISIBLEON, OnUpdatePopupControlChangeVisibleOnUI) // 20201212追加
	ON_COMMAND (ID_POPUP_CONTROLCHANGEVISIBLEOFF, OnPopupControlChangeVisibleOff)
	ON_UPDATE_COMMAND_UI (ID_POPUP_CONTROLCHANGEVISIBLEOFF, OnUpdatePopupControlChangeVisibleOffUI) // 20201212追加
	ON_COMMAND (ID_POPUP_CONTROLCHANGEVISIBLEALL, OnPopupControlChangeVisibleAll)
	ON_UPDATE_COMMAND_UI (ID_POPUP_CONTROLCHANGEVISIBLEALL, OnUpdatePopupControlChangeVisibleAllUI) // 20201212追加

	ON_CBN_SELENDOK (IDC_EVENTTRACKCOMBO, OnTrackComboSelEndOK)	
	ON_CLBN_CHKCHANGE (EVENTLISTFRAME_TRACKLIST, OnTrackListChkChange)
	ON_LBN_SELCHANGE (EVENTLISTFRAME_TRACKLIST, OnTrackListSelChange)
	ON_CBN_SELENDOK (IDC_EVENTKINDCOMBO, OnEventKindComboSelEndOK)	
	ON_CLBN_CHKCHANGE (EVENTLISTFRAME_EVENTKINDLIST, OnEventKindListChkChange)
	ON_LBN_SELCHANGE (EVENTLISTFRAME_EVENTKINDLIST, OnEventKindListSelChange)
	ON_CLBN_CHKCHANGE (EVENTLISTFRAME_CONTROLCHANGELIST, OnControlChangeListChkChange)
	ON_LBN_SELCHANGE (EVENTLISTFRAME_CONTROLCHANGELIST, OnControlChangeListSelChange)
END_MESSAGE_MAP()


//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
CEventListFrame::CEventListFrame () {
	long i;
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	m_lIndexHeight = EVENTLISTFRAME_INDEXHEIGHT;
	m_lScaleHeight = EVENTLISTFRAME_SCALEHEIGHT;
	m_lScaleWidth = EVENTLISTFRAME_SCALEWIDTH;
	m_lPropertyWidth = EVENTLISTFRAME_PROPERTYWIDTH;
	m_lTrackListWidth = EVENTLISTFRAME_TRACKLISTWIDTH;
	m_lTrackListHeight = EVENTLISTFRAME_TRACKLISTHEIGHT;
	m_lEventKindListHeight = EVENTLISTFRAME_EVENTKINDLISTHEIGHT;
	m_lControlChangeListHeight = EVENTLISTFRAME_CONTROLCHANGELISTHEIGHT;
	m_lHScrollBarHeight = ::GetSystemMetrics (SM_CYHSCROLL);
	m_lVScrollBarWidth = ::GetSystemMetrics (SM_CXVSCROLL);
	m_lRowZoom = pSekaijuApp->m_theEventListOption.m_lDefRowZoom;
	m_lColumnZoom = pSekaijuApp->m_theEventListOption.m_lDefColumnZoom;
	m_lRowScrollPos = 0;
	m_lColumnScrollPos = 0;
	// 列幅の定義
	m_lColumnBaseWidth[0] = pSekaijuApp->m_theEventListOption.m_lDefTrackWidth;
	m_lColumnBaseWidth[1] = pSekaijuApp->m_theEventListOption.m_lDefMillisecWidth;
	m_lColumnBaseWidth[2] = pSekaijuApp->m_theEventListOption.m_lDefTimeWidth;
	m_lColumnBaseWidth[3] = pSekaijuApp->m_theEventListOption.m_lDefKindWidth;
	m_lColumnBaseWidth[4] = pSekaijuApp->m_theEventListOption.m_lDefChWidth;
	m_lColumnBaseWidth[5] = pSekaijuApp->m_theEventListOption.m_lDefVal1Width;
	m_lColumnBaseWidth[6] = pSekaijuApp->m_theEventListOption.m_lDefVal2Width;
	m_lColumnBaseWidth[7] = pSekaijuApp->m_theEventListOption.m_lDefVal3Width;
	// 列タイトルの定義
	VERIFY (m_strColumnTitle[0].LoadString (IDS_TRACK));
	VERIFY (m_strColumnTitle[1].LoadString (IDS_HOUR_MINUTE_SECOND_MILLISEC));
	VERIFY (m_strColumnTitle[2].LoadString (IDS_MEASURE_BEAT_TICK));
	VERIFY (m_strColumnTitle[3].LoadString (IDS_EVENT_KIND));
	VERIFY (m_strColumnTitle[4].LoadString (IDS_CHANNEL));
	VERIFY (m_strColumnTitle[5].LoadString (IDS_VALUE1));
	VERIFY (m_strColumnTitle[6].LoadString (IDS_VALUE2));
	VERIFY (m_strColumnTitle[7].LoadString (IDS_VALUE3));
	m_bAutoPageUpdate = FALSE;
	m_bOnlyCurTrack = FALSE;
	m_bShowAllTrack = FALSE;
	for (i = 0; i < MAXMIDITRACKNUM; i++) {
		m_bTrackVisible[i] = TRUE;
		m_pTrackListTrack[i] = NULL;
		m_pTrackComboTrack[i] = NULL;
	}
	m_bOnlyCurEventKind = FALSE;
	m_bShowAllEventKind = FALSE;
	for (i = 0; i < 256; i++) {
		m_bEventKindVisible[i] = TRUE;
	}
	m_bOnlyCurControlChange = FALSE;
	m_bShowAllControlChange = FALSE;
	for (i = 0; i < 256; i++) {
		m_bControlChangeVisible[i] = TRUE;
	}

}

// デストラクタ
CEventListFrame::~CEventListFrame () {
}



//------------------------------------------------------------------------------
// オペレーション
//------------------------------------------------------------------------------

// ドキュメントの取得
CSekaijuDoc* CEventListFrame::GetDocument () {
	ASSERT (m_pDummyView);
	return (CSekaijuDoc*)m_pDummyView->GetDocument ();
}

// 最も上に表示されている行を取得
long CEventListFrame::GetVisibleTopRow (long lLogPixelsY) {
	return m_lRowScrollPos * 96 / lLogPixelsY / m_lRowZoom;
}

// 最も下に表示されている行を取得
long CEventListFrame::GetVisibleBottomRow (long lLogPixelsY) {
	CRect rcClient;
	m_pIndexScaleView->GetClientRect (&rcClient);
	return (m_lRowScrollPos * 96 / lLogPixelsY + rcClient.Height ()) / m_lRowZoom + 1;
}

// 列方向のズーム倍率取得
long CEventListFrame::GetColumnZoom () {
	return m_lColumnZoom;
}

// 行方向のズーム倍率取得
long CEventListFrame::GetRowZoom () {
	return m_lRowZoom;
}

// 指定した列の基本幅を取得
long CEventListFrame::GetColumnBaseWidth (long lColumn) {
	ASSERT (0 <= lColumn && lColumn < 8);
	return m_lColumnBaseWidth[lColumn];
}

// 指定した列の基本幅を設定
long CEventListFrame::SetColumnBaseWidth (long lColumn, long lBaseWidth) {
	ASSERT (0 <= lColumn && lColumn < 8);
	m_lColumnBaseWidth[lColumn] = lBaseWidth;
	return 1;
}

// 指定した列のタイトルを取得
CString CEventListFrame::GetColumnTitle (long lColumn) {
	ASSERT (0 <= lColumn && lColumn < 8);
	return m_strColumnTitle[lColumn];
}

// 指定した列のタイトルを取得
long CEventListFrame::SetColumnTitle (long lColumn, const TCHAR* pszColumnTitle) {
	ASSERT (0 <= lColumn && lColumn < 8);
	m_strColumnTitle[lColumn] = pszColumnTitle;
	return 1;
}


// 指定の列の左座標を取得
long CEventListFrame::GetColumnLeft (long lColumn, long lLogPixelsX) {
	ASSERT (0 <= lColumn && lColumn < 8);
	long lSum = 0;
	for (long j = 0; j < lColumn; j++) {
		lSum += m_lColumnBaseWidth[j] * m_lColumnZoom * lLogPixelsX / 96;
	}
	return lSum;
}

// 指定の列の幅を取得
long CEventListFrame::GetColumnWidth (long lColumn, long lLogPixelsX) {
	ASSERT (0 <= lColumn && lColumn < 8);
	//long lTempWidth = m_lColumnBaseWidth[lColumn] * m_lColumnZoom;
	//if (lColumn == 7) {
	//	if (m_lPropertyWidth - GetColumnLeft (7) - m_lColumnBaseWidth[lColumn] * m_lColumnZoom > 0) {
	//		return m_lPropertyWidth - GetColumnLeft (7);
	//	}
	//}
	return m_lColumnBaseWidth[lColumn] * m_lColumnZoom * lLogPixelsX / 96;
}

// y座標をインデックスに変換
long CEventListFrame::YtoRow (long y, long lLogPixelsY) {
	return (y * 96 / lLogPixelsY) / m_lRowZoom;
}

// インデックスをy座標に変換
long CEventListFrame::RowtoY (long lRow, long lLogPixelsY) {
	return m_lRowZoom * lRow * lLogPixelsY / 96;
}

// x座標からプロパティを取得
long CEventListFrame::XtoColumn (long x, long lLogPixelsX) {
	long lSum = 0;
	long lNextSum = 0;
	for (long j = 0; j < 8; j++) {		
		lNextSum += m_lColumnBaseWidth[j] * m_lColumnZoom * lLogPixelsX / 96;
		if (lSum <= x && x < lNextSum) {
			return j;
		}
		lSum = lNextSum;
	}
	return -1;
}

// プロパティをx座標に変換
long CEventListFrame::ColumntoX (long lColumn, long lLogPixelsX) {
	return GetColumnLeft (lColumn, lLogPixelsX);
}

// 列方向のスクロールポジションを取得
long CEventListFrame::GetColumnScrollPos () {
	return m_lColumnScrollPos;
}

// 行方向のスクロールポジションを取得
long CEventListFrame::GetRowScrollPos () {
	return m_lRowScrollPos;
}

// 列方向スクロールポジションの設定
long CEventListFrame::SetColumnScrollPos (long lColumnScrollPos) {
	long lOldColumnScrollPos = m_lColumnScrollPos;
	m_wndColumnScroll.SetScrollPos (lColumnScrollPos);
	m_lColumnScrollPos = m_wndColumnScroll.GetScrollPos ();
	long lDeltaColumnScrollPos = m_lColumnScrollPos - lOldColumnScrollPos;
	m_pPropertyScaleView->ScrollWindow (-lDeltaColumnScrollPos, 0);
	m_pIndexPropertyView->ScrollWindow (-lDeltaColumnScrollPos, 0);
	m_pPropertyScaleView->UpdateWindow ();
	m_pIndexPropertyView->UpdateWindow ();
	return m_lColumnScrollPos;
}

// 行方向スクロールポジションの設定
long CEventListFrame::SetRowScrollPos (long lRowScrollPos) {
	long lOldRowScrollPos = m_lRowScrollPos;
	m_wndRowScroll.SetScrollPos (lRowScrollPos);
	m_lRowScrollPos = m_wndRowScroll.GetScrollPos ();
	long lDeltaRowScrollPos = m_lRowScrollPos - lOldRowScrollPos;
	m_pIndexScaleView->ScrollWindow (0, -lDeltaRowScrollPos);
	m_pIndexPropertyView->ScrollWindow (0, -lDeltaRowScrollPos);
	m_pIndexScaleView->UpdateWindow ();
	m_pIndexPropertyView->UpdateWindow ();
	return m_lRowScrollPos;
}

// 可視のMIDIイベント数を取得
INT_PTR CEventListFrame::GetVisibleEventCount () {
	return m_theVisibleEventArray.GetSize ();
}

// 可視のMIDIイベントを取得
MIDIEvent* CEventListFrame::GetVisibleEvent (long lIndex) {
	if (0 <= lIndex && lIndex < m_theVisibleEventArray.GetSize ()) {
		return (MIDIEvent*)(m_theVisibleEventArray.GetAt (lIndex));
	}
	return NULL;
}

// スプリッターキャプターの描画
void CEventListFrame::DrawSplitterCaptor (CDC* pDC, CPoint pt) {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	CRect rcClient;
	GetClientRect (&rcClient);
	CPen pen;
	CPen* pOldPen;
	pen.CreatePen (PS_SOLID, EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96, ::GetSysColor(COLOR_BTNSHADOW));
	pDC->SetROP2 (R2_XORPEN);
	pOldPen = pDC->SelectObject (&pen);
	if (m_bSplitterMovingH || m_bSplitterMovingH2) {
		pDC->MoveTo (0, pt.y);
		pDC->LineTo (rcClient.Width (), pt.y);
	}
	if (m_bSplitterMovingV) {
		pDC->MoveTo (pt.x, 0);
		pDC->LineTo (pt.x, rcClient.Height ());
	}
	pDC->SelectObject (pOldPen);
}



/*		"0シーケンス番号",
		"1テキストイベント",
		"2著作権",
		"3シーケンス名／トラック名",
		"4インストゥルメント名",
		"5歌詞",
		"6マーカー",
		"7キューポイント",
		"8プログラム名",
		"9デバイス名",
		"10チャンネルプリフィックス",
		"11ポートプリフィックス",
		"12エンドオブトラック",
		"13テンポ設定",
		"14SMPTEオフセット",
		"15拍子記号",
		"16調性記号",
		"17シーケンサ独自のイベント",
		"18ノートオフ",
		"19ノートオン",
		"20キーアフタータッチ",
		"21コントローラー",
		"22プログラムチェンジ",
		"23チャンネルアフタータッチ",
		"24ピッチベンド",
		"25システムエクスクルーシヴ",
		"26不明な種類のイベント"};
*/

// 可視のイベント配列の作成
BOOL CEventListFrame::MakeVisibleEventArray (long lLogPixelsX, long lLogPixelsY) {
 	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;
	MIDITrack* pMIDITrack = pMIDIData->m_pFirstTrack;
	MIDIEvent* pMIDIEvent = NULL;

	// 旧選択イベントをpOldMIDIEventに保持しておく
	INT_PTR lOldVisibleEventCount = GetVisibleEventCount ();
	long lOldRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	MIDIEvent* pOldMIDIEvent = NULL;
	if (0 <= lOldRow && lOldRow < lOldVisibleEventCount) {
		pOldMIDIEvent = (MIDIEvent*)m_theVisibleEventArray.GetAt (lOldRow);
	}
	
	// 現在配列の初期化
	m_theVisibleEventArray.RemoveAll ();
	MIDIEvent* pTempEvent[MAXMIDITRACKNUM];
	long lTime = 0;
	int64_t llMinimumTime = 0;
	long lMinimumTrackIndex = 0;
	long lTrackNum = 0;
	long i = 0;
	// 各トラック用の一時イベント保持スペースを初期化
	forEachTrack (pMIDIData, pMIDITrack) {
		pTempEvent[i] = MIDITrack_GetFirstEvent (pMIDITrack);
		i++;
		if (i >= MAXMIDITRACKNUM) break;
	}
	// 各トラックのイベントをタイム順に配列に登録する
	while (1) {
		llMinimumTime = 0x7FFFFFFFFFFFFFFF;
		i = 0;
		forEachTrack (pMIDIData, pMIDITrack) {
			if (IsTrackVisible (i)) {
				if (pTempEvent[i] != NULL) {
					lTime = pTempEvent[i]->m_lTime;
					if ((int64_t)lTime < llMinimumTime) {
						llMinimumTime = lTime;
						lMinimumTrackIndex = i;
					}
				}
			}
			i++;
			if (i >= MAXMIDITRACKNUM) break;
		}
		if (lMinimumTrackIndex < MAXMIDITRACKNUM && llMinimumTime != 0x7FFFFFFFFFFFFFFF) {
			for (pMIDIEvent = pTempEvent[lMinimumTrackIndex];
				pMIDIEvent; pMIDIEvent = pMIDIEvent->m_pNextEvent) {
				if ((int64_t)pMIDIEvent->m_lTime == llMinimumTime) {
					long lEventKind = MIDIEvent_GetKind (pMIDIEvent);
					if (MIDIEvent_IsNoteOff (pMIDIEvent)) {
						lEventKind &= 0x0F;
						lEventKind |= 0x80;
					}
					long lListIndex = EventKindtoListIndex (lEventKind);
					ASSERT (0 <= lListIndex && lListIndex <= 0xFF);
					if (IsEventKindVisible (lListIndex)) {
						if (MIDIEvent_IsControlChange (pMIDIEvent)) {
							long lControlChange = MIDIEvent_GetNumber (pMIDIEvent);
							if (IsControlChangeVisible (lControlChange)) {
								m_theVisibleEventArray.Add (pMIDIEvent);
							}
						}
						else {
							m_theVisibleEventArray.Add (pMIDIEvent);
						}
					}
				}
				else {
					break;
				}
			}
			pTempEvent[lMinimumTrackIndex] = pMIDIEvent;
		}
		else {
			break;
		}
	}
	// 行スクロールバーの再調整
	RecalcRowScrollInfo (lLogPixelsY);

	// 旧イベントにフォーカスを合わせる
	long lNewCount = INT_PTRtolong (GetVisibleEventCount ());
	long lNewRow = CLIP (0, lOldRow, lNewCount); // 20220130:リアルタイム入力時用に次の1行まで許容。
	if (lNewRow < 0) {
		lNewRow = 0; // lNewCount == 0の場合に備える
	}
	if (pOldMIDIEvent) {
		// 一致するイベントが見つかった場合、そのイベントにフォーカスを合わせる
		for (i = 0; i < lNewCount; i++) {
			if (m_theVisibleEventArray.GetAt (i) == pOldMIDIEvent) {
				break;
			}
		}
		if (i < lNewCount) { //2022/01/30 見つからなかったとしても
			lNewRow = i;
		}
		// 一致するイベントがない場合、時刻が同じかその次のイベントにフォーカスを合わせる
		// 一致するイベントが無い場合、m_lCurRowはそのままの値とする
		//else {
			//for (i = 0; i < lNewCount; i++) {
			//	MIDIEvent* pTempEvent = (MIDIEvent*)m_theVisibleEventArray.GetAt (i);
			//	if (MIDIEvent_GetTime (pTempEvent) >= MIDIEvent_GetTime (pOldMIDIEvent)) {
			//		break;
			//	}
			//}
			//lNewRow = i;
			//lNewRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
		//}
	}
	if (((CEventListIndexPropertyView*)m_pIndexPropertyView)->IsTextEditing ()) {
		((CEventListIndexPropertyView*)m_pIndexPropertyView)->EndTextEditingCancel ();
	}
	if (((CEventListIndexPropertyView*)m_pIndexPropertyView)->IsListSelecting ()) {
		((CEventListIndexPropertyView*)m_pIndexPropertyView)->EndListSelectingCancel ();
	}
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = lNewRow;
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lNewRow, lCurColumn);
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lNewRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lNewRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	return TRUE;
}

BOOL CEventListFrame::ReplaceVisibleEvent (MIDIEvent* pOldEvent, MIDIEvent* pNewEvent) {
	long lCount = 0;
	INT_PTR lVisibleEventCount = GetVisibleEventCount ();
	pOldEvent = MIDIEvent_GetFirstCombinedEvent (pOldEvent);
	pNewEvent = MIDIEvent_GetFirstCombinedEvent (pNewEvent);
	while (pOldEvent && pNewEvent) {
		INT_PTR i = 0;
		for (i = 0; i < lVisibleEventCount; i++) {
			if (m_theVisibleEventArray.GetAt (i) == pOldEvent) {
				m_theVisibleEventArray.SetAt (i, pNewEvent);	
				lCount++;
			}
		}
		pOldEvent = pOldEvent->m_pNextCombinedEvent;
		pNewEvent = pNewEvent->m_pNextCombinedEvent;
	}
	return lCount;
}


// 現在のトラックのインデックスを取得
long CEventListFrame::GetCurTrackIndex () {
	return m_pTrackListBox->GetCurSel ();
}

// 現在のイベントの種類を取得
long CEventListFrame::GetCurEventKind () {
	return m_pEventKindListBox->GetCurSel ();
}

// 現在のコントロールチェンジを取得
long CEventListFrame::GetCurControlChange () {
	return m_pControlChangeListBox->GetCurSel ();
}


// 現在のトラックのインデックスを設定
BOOL CEventListFrame::SetCurTrackIndex (long lCurTrackIndex, long lLogPixelsX, long lLogPixelsY) {
	ASSERT (0 <= lCurTrackIndex && lCurTrackIndex < MAXMIDITRACKNUM);
	m_wndEventTrackCombo.SetCurSel (lCurTrackIndex);
	m_pTrackListBox->SetCurSel (lCurTrackIndex);
	if (m_bOnlyCurTrack) {
		long lCount = m_pTrackListBox->GetCount ();
		for (long i = 0; i < lCount; i++) {
			m_pTrackListBox->SetCheck (i, (i == lCurTrackIndex ? 1 : 0));
		}
		MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
		long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
		long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
		((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
		m_pIndexScaleView->Invalidate ();
		m_pIndexPropertyView->Invalidate ();
	}
	return TRUE;
}

// 現在のイベントの種類を設定
BOOL CEventListFrame::SetCurEventKind (long lCurEventKind, long lLogPixelsX, long lLogPixelsY) {
	ASSERT (0 <= lCurEventKind && lCurEventKind < 256);
	m_wndEventKindCombo.SetCurSel (lCurEventKind);
	m_pEventKindListBox->SetCurSel (lCurEventKind);
	if (m_bOnlyCurEventKind) {
		long lCount = m_pEventKindListBox->GetCount ();
		for (long i = 0; i < lCount; i++) {
			m_pEventKindListBox->SetCheck (i, (i == lCurEventKind ? 1 : 0));
		}
		MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
		long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
		long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
		((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
		m_pIndexScaleView->Invalidate ();
		m_pIndexPropertyView->Invalidate ();
	}
	return TRUE;
}

// 現在のチャンネルを設定
BOOL CEventListFrame::SetCurChannel (long lCurChannel) {
	ASSERT (-1 <= lCurChannel && lCurChannel < 16);
	m_wndEventChannelCombo.SetCurSel (lCurChannel + 1);
	return TRUE;
}

// 指定インデックスのトラックが表示状態か調べる
BOOL CEventListFrame::IsTrackVisible (long lTrackIndex) {
	// (1)現在のトラックのみ表示がONのときは、現在のトラックのみがVisible、他はUnVisible。
	// (2)すべてのトラックを表示がONのときは、全てのトラックがVisible。
	// (3)その他の場合(通常時)は、m_bTrackVisible[MAXMIDITRACKNUM]の値に従う。
	ASSERT (0 <= lTrackIndex && lTrackIndex < MAXMIDITRACKNUM);
	if (m_bOnlyCurTrack == TRUE &&
		GetCurTrackIndex () == lTrackIndex ||
		m_bShowAllTrack == TRUE ||
		m_bShowAllTrack == FALSE &&
		m_bOnlyCurTrack == FALSE &&
		m_bTrackVisible[lTrackIndex] == TRUE) {
		return TRUE;
	}
	return FALSE;
}

// 指定インデックスのトラックを表示状態にする
BOOL CEventListFrame::SetTrackVisible (long lTrackIndex) {
	// (1)現在のトラックのみ表示がONのときは、現在のトラックを指定トラックに変更する
	// (2)すべてのトラックを表示がONのときは、何もしない。
	// (3)その他の場合(通常時)は、m_bTrackVisible[lTrackIndex]をチェック・可視化する。
	ASSERT (0 <= lTrackIndex && lTrackIndex < MAXMIDITRACKNUM);
	if (m_bOnlyCurTrack == TRUE) {
		m_wndEventTrackCombo.SetCurSel (lTrackIndex);
		m_pTrackListBox->SetCurSel (lTrackIndex);
	}
	else if (m_bShowAllTrack == TRUE) {
		;
	}
	else {
		m_pTrackListBox->SetCheck (lTrackIndex, TRUE);
		m_bTrackVisible[lTrackIndex] = TRUE;
	}
	return TRUE;
}

// 指定種類のイベントが表示状態か調べる
BOOL CEventListFrame::IsEventKindVisible (long lEventKind) {
	// (1)現在のイベント種類のみ表示がONのときは、現在のグラフのみがVisible、他はUnVisible。
	// (2)すべてのイベント種類を表示がONのときは、全てのグラフがVisible。
	// (3)その他の場合(通常時)は、m_bEventKindVisible[MAXMIDITRACKNUM]の値に従う。
	ASSERT (0 <= lEventKind && lEventKind < 128);
	if (m_bOnlyCurEventKind == TRUE &&
		GetCurEventKind () == lEventKind ||
		m_bShowAllEventKind == TRUE ||
		m_bShowAllEventKind == FALSE &&
		m_bOnlyCurEventKind == FALSE &&
		m_bEventKindVisible[lEventKind] == TRUE) {
		return TRUE;
	}
	return FALSE;
}

// 指定種類のイベントを表示状態にする
BOOL CEventListFrame::SetEventKindVisible (long lEventKind) {
	// (1)現在のイベント種類のみ表示がONのときは、現在のイベントの種類を変更する
	// (2)すべてのイベント種類を表示がONのときは、何もしない。
	// (3)その他の場合(通常時)は、m_bEventKindVisible[lEventKind]をチェック・可視化する。
	ASSERT (0 <= lEventKind && lEventKind < m_pEventKindListBox->GetCount ());
	if (m_bOnlyCurEventKind == TRUE) {
		m_wndEventKindCombo.SetCurSel (lEventKind);
		m_pEventKindListBox->SetCurSel (lEventKind);
	}
	else if (m_bShowAllEventKind == TRUE) {
		;
	}
	else {
		m_pEventKindListBox->SetCheck (lEventKind, TRUE);
		m_bEventKindVisible[lEventKind] = TRUE;
	}
	return TRUE;
}

// 指定種類のコントロールチェンジが表示状態か調べる
BOOL CEventListFrame::IsControlChangeVisible (long lControlChange) {
	// (1)現在のグラフのみ表示がONのときは、現在のグラフのみがVisible、他はUnVisible。
	// (2)すべてのグラフを表示がONのときは、全てのグラフがVisible。
	// (3)その他の場合(通常時)は、m_bGraphVisible[MAXMIDITRACKNUM]の値に従う。
	ASSERT (0 <= lControlChange && lControlChange < 256);
	if (m_bOnlyCurControlChange == TRUE &&
		GetCurControlChange () == lControlChange ||
		m_bShowAllControlChange == TRUE ||
		m_bShowAllControlChange == FALSE &&
		m_bOnlyCurControlChange == FALSE &&
		m_bControlChangeVisible[lControlChange] == TRUE) {
		return TRUE;
	}
	return FALSE;
}

// 指定種類のコントロールチェンジを表示状態にする
BOOL CEventListFrame::SetControlChangeVisible (long lControlChange) {
	// (1)現在のイベント種類のみ表示がONのときは、現在のイベントの種類を変更する
	// (2)すべてのイベント種類を表示がONのときは、何もしない。
	// (3)その他の場合(通常時)は、m_bEventKindVisible[lEventKind]をチェック・可視化する。
	ASSERT (0 <= lControlChange && lControlChange < m_pControlChangeListBox->GetCount ());
	if (m_bOnlyCurEventKind == TRUE) {
		//m_wndEventKindCombo.SetCurSel (lEventKind);
		m_pControlChangeListBox->SetCurSel (lControlChange);
	}
	else if (m_bShowAllEventKind == TRUE) {
		;
	}
	else {
		m_pControlChangeListBox->SetCheck (lControlChange, TRUE);
		m_bControlChangeVisible[lControlChange] = TRUE;
	}
	return TRUE;
}

// トラックコンボボックスの充満
BOOL CEventListFrame::UpdateTrackCombo () {
	CSekaijuDoc* pSekaijuDoc = (CSekaijuDoc*)(m_pDummyView->GetDocument ());
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	//pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;
	MIDITrack* pMIDITrack = NULL;
	BOOL bTrackZeroOrigin = pSekaijuApp->m_theGeneralOption.m_bTrackZeroOrigin;

	// 旧状態の保持
	BOOL bOldTrackVisible[MAXMIDITRACKNUM];
	memcpy (bOldTrackVisible, m_bTrackVisible, sizeof (BOOL) * MAXMIDITRACKNUM);
	long lOldCurSel = m_wndEventTrackCombo.GetCurSel ();
	long lOldCount = m_wndEventTrackCombo.GetCount ();
	MIDITrack* pOldCurTrack = NULL;
	if (0 <= lOldCurSel && lOldCurSel < __min (lOldCount, MAXMIDITRACKNUM)) {
		pOldCurTrack = m_pTrackComboTrack[lOldCurSel];
	}

	// コンボの初期化
	m_wndEventTrackCombo.RemoveAllItem ();

	// コンボに項目追加
	TCHAR szTrackName1[1024];
	TCHAR szTrackName2[1024];
	CString strText;
	long i = 0;
	forEachTrack (pMIDIData, pMIDITrack) {
		if (i >= MAXMIDITRACKNUM) {
			break;
		}
		memset (szTrackName1, 0, sizeof (szTrackName1));
		memset (szTrackName2, 0, sizeof (szTrackName2));
		MIDITrack_GetName (pMIDITrack, szTrackName1, TSIZEOF (szTrackName1) - 1);
		codestr2str (szTrackName1, size_ttolong (_tcslen (szTrackName1)), szTrackName2, TSIZEOF (szTrackName2) - 1);
		strText.Format (_T("%d-%s"), i + (bTrackZeroOrigin ? 0 : 1), szTrackName2);
		long lForeColor = MIDITrack_GetForeColor (pMIDITrack);
		long lBackColor = ::GetSysColor (COLOR_WINDOW);
		m_wndEventTrackCombo.AddItem (strText, lForeColor, lBackColor);
		
		// 現在のトラックである場合選択
		if (pMIDITrack == pOldCurTrack) {
			m_wndEventTrackCombo.SetCurSel (i);
		}
		i++;
	}

	// 現在選択しているものがない場合は強制選択
	long lNewCount = m_wndEventTrackCombo.GetCount ();
	long lNewCurSel = m_wndEventTrackCombo.GetCurSel ();
	if (m_wndEventTrackCombo.GetCurSel () == CB_ERR) {
		if (0 <= lOldCurSel && lOldCurSel < lNewCount) {
			m_wndEventTrackCombo.SetCurSel (lOldCurSel);
		}
		else if (lNewCount >= 2) {
			m_wndEventTrackCombo.SetCurSel (1);
		}
		else {
			m_wndEventTrackCombo.SetCurSel (0);
		}
		lNewCurSel = m_wndEventTrackCombo.GetCurSel ();
	}

	// 次回のアップデート呼び出しに備えて現状を保持する。
	i = 0;
	memset (m_pTrackComboTrack, 0, sizeof (MIDITrack*) * MAXMIDITRACKNUM);
	forEachTrack (pMIDIData, pMIDITrack) {
		if (i >= MAXMIDITRACKNUM) {
			break;
		}
		m_pTrackComboTrack[i] = pMIDITrack;
		i++;
	}
	
	//pSekaijuDoc->m_theCriticalSection.Unlock ();
	return TRUE;
}

// トラックリストボックスの更新
BOOL CEventListFrame::UpdateTrackList () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	//pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;
	MIDITrack* pMIDITrack = NULL;
	BOOL bTrackZeroOrigin = pSekaijuApp->m_theGeneralOption.m_bTrackZeroOrigin;
	// 旧チェックボックス状態の保持
	BOOL bOldTrackVisible[MAXMIDITRACKNUM];
	memcpy (bOldTrackVisible, m_bTrackVisible, sizeof (BOOL) * MAXMIDITRACKNUM);
	long lOldCurSel = m_pTrackListBox->GetCurSel ();
	long lOldCount = m_pTrackListBox->GetCount ();
	MIDITrack* pOldCurTrack = NULL;
	if (0 <= lOldCurSel && lOldCurSel < __min (lOldCount, MAXMIDITRACKNUM)) {
		pOldCurTrack = m_pTrackListTrack[lOldCurSel];
	}
	// リストの初期化
	((CTrackListBox*)m_pTrackListBox)->RemoveAllItem ();

	// リストに項目を追加
	long i = 0;
	long j = 0;
	TCHAR szTrackName1[1024];
	TCHAR szTrackName2[1024];
	CString strText;
	forEachTrack (pMIDIData, pMIDITrack) {
		if (i >= MAXMIDITRACKNUM) {
			break;
		}
		memset (szTrackName1, 0, sizeof (szTrackName1));
		memset (szTrackName2, 0, sizeof (szTrackName2));
		MIDITrack_GetName (pMIDITrack, szTrackName1, TSIZEOF (szTrackName1) - 1);
		codestr2str (szTrackName1, size_ttolong (_tcslen (szTrackName1)), szTrackName2, TSIZEOF (szTrackName2) - 1);
		strText.Format (_T("%d-%s"), i + (bTrackZeroOrigin ? 0 : 1), szTrackName2);
		long lForeColor = MIDITrack_GetForeColor (pMIDITrack);
		long lBackColor = ::GetSysColor (COLOR_WINDOW);
		((CTrackListBox*)m_pTrackListBox)->AddItem (strText, lForeColor, lBackColor);
		// チェック状態変数の更新 20201222修正
		m_bTrackVisible[i] = 1;
		for (j = 0; j < lOldCount; j++) {
			if (m_pTrackListTrack[j] == pMIDITrack) {
				m_bTrackVisible[i] = bOldTrackVisible[j];
				break;
			}
		}
		// 現在のトラックである場合選択
		if (pMIDITrack == pOldCurTrack) {
			m_pTrackListBox->SetCurSel (i);
		}
		i++;
	}

	// 現在選択しているものがない場合は強制選択
	long lNewCount = m_pTrackListBox->GetCount ();
	long lNewCurSel = m_pTrackListBox->GetCurSel ();
	if (m_pTrackListBox->GetCurSel () == LB_ERR) {
		if (0 <= lOldCurSel && lOldCurSel < lNewCount) {
			m_pTrackListBox->SetCurSel (lOldCurSel);
		}
		else if (lNewCount >= 2) {
			m_pTrackListBox->SetCurSel (1);
		}
		else {
			m_pTrackListBox->SetCurSel (0);
		}
		lNewCurSel = m_pTrackListBox->GetCurSel ();
	}

	// チェックボックスの完全更新
	if (m_bShowAllTrack) {
		for (i = 0; i < lNewCount; i++) {
			m_pTrackListBox->SetCheck (i, 1);
		}
	}
	else if (m_bOnlyCurTrack) {
		for (i = 0; i < lNewCount; i++) {
			m_pTrackListBox->SetCheck (i, 0);
		}
		if (0 <= lNewCurSel && lNewCurSel < lNewCount) {
			m_pTrackListBox->SetCheck (lNewCurSel, 1);
		}
	}
	else {
		for (i = 0; i < lNewCount; i++) {
			m_pTrackListBox->SetCheck (i, m_bTrackVisible[i]);
		}
	}
	// 次回のアップデート呼び出しに備えてチェックボックス現状を保持する。
	i = 0;
	memset (m_pTrackListTrack, 0, sizeof (MIDITrack*) * MAXMIDITRACKNUM);
	forEachTrack (pMIDIData, pMIDITrack) {
		if (i >= MAXMIDITRACKNUM) {
			break;
		}
		m_pTrackListTrack[i] = pMIDITrack;
		i++;
	}
	//pSekaijuDoc->m_theCriticalSection.Unlock ();
	return TRUE;
}

// コントロールチェンジリストの更新
BOOL CEventListFrame::UpdateControlChangeList () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	//pSekaijuDoc->m_theCriticalSection.Lock ();
	CString strText;
	long i;
	// チェックボックスの状態保持
	BOOL bOldControlChangeVisible[256];
	long lOldCount = m_pControlChangeListBox->GetCount ();
	for (i = 0; i < 256; i++) {
		bOldControlChangeVisible[i] = m_bControlChangeVisible[i];
	}
	long lOldCurSel = m_pControlChangeListBox->GetCurSel ();
	if (lOldCurSel == LB_ERR) {
		lOldCurSel = 0;
	}
	// リストクリア
	m_pControlChangeListBox->ResetContent ();
	// コントロールチェンジ名の取得
	TCHAR szName[1024];
	long lTrackIndex = GetCurTrackIndex ();
	MIDITrack* pMIDITrack = pSekaijuDoc->GetTrack (lTrackIndex);
	long lPortNumber = MIDITrack_GetOutputPort (pMIDITrack);
	MIDIInstrumentDefinition* pMIDIInstDefNorm = NULL;
	MIDIControllerNameTable* pMIDIControllerNameTable = NULL;
	if (0 <= lPortNumber && lPortNumber < MAXMIDIOUTDEVICENUM) {
		pMIDIInstDefNorm = ((CSekaijuApp*)AfxGetApp())->m_pMIDIInstDefNorm[lPortNumber];
		if (pMIDIInstDefNorm) {
			pMIDIControllerNameTable = MIDIInstrumentDefinition_GetControllerNameTable (pMIDIInstDefNorm);
		}
	}
	// リストボックスの充満
	for (long i = 0; i < 128; i++) {
		memset (szName, 0, sizeof (szName));
		if (pMIDIControllerNameTable) {
			MIDIControllerNameTable_GetName (pMIDIControllerNameTable, i, szName, TSIZEOF (szName) - 1);
		}
		CString strFormat;
		VERIFY (strFormat.LoadString (IDS_CC_D_S));
		strText.Format (strFormat, i, szName);
		m_pControlChangeListBox->AddString (strText);
	}
	// 選択状態の更新
	long lNewCount = m_pControlChangeListBox->GetCount ();
	if (0 <= lOldCurSel && lOldCurSel <lNewCount) {
		m_pControlChangeListBox->SetCurSel (lOldCurSel);
	}
	// チェックボックスの完全更新
	for (i = 0; i < 256; i++) {
		m_bControlChangeVisible[i] = bOldControlChangeVisible[i];
	}
	if (m_bShowAllControlChange) {
		for (i = 0; i < lNewCount; i++) {
			m_pControlChangeListBox->SetCheck (i, 1);
		}
	}
	else if (m_bOnlyCurControlChange) {
		for (i = 0; i < lNewCount; i++) {
			m_pControlChangeListBox->SetCheck (i, 0);
		}
		if (0 <= lOldCurSel && lOldCurSel < lNewCount) {
			m_pControlChangeListBox->SetCheck (lOldCurSel, 1);
		}
	}
	else {
		for (i = 0; i < lNewCount; i++) {
			m_pControlChangeListBox->SetCheck (i, m_bControlChangeVisible[i]);
		}
	}
	//pSekaijuDoc->m_theCriticalSection.Unlock ();
	return TRUE;
}

// イベントの種類からリストインデックスを取得
long CEventListFrame::EventKindtoListIndex (long lEventKind) {
	long lEventKindtoListIndex[256] = {
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 27, 27, 27, 27, 27, 27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
		10, 11, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 12,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
		27, 13, 27, 27, 14, 27, 27, 27, 15, 16, 27, 27, 27, 27, 27, 27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 17,
		18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
		19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
		20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
		21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
		22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
		23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
		24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
		25, 27, 27, 27, 27, 27, 27, 26, 27, 27, 27, 27, 27, 27, 27, 27
	};
	ASSERT (0 <= lEventKind && lEventKind <= 0xFF);
	if (0 <= lEventKind && lEventKind < 256) {
		return lEventKindtoListIndex[lEventKind];
	}
	return -1;
}

// リストインデックスからイベントの種類を取得
long CEventListFrame::ListIndextoEventKind (long lListIndex) {
	ASSERT (0 <= lListIndex && lListIndex <= 0xFF);
	for (long i = 0; i < 256; i++) {
		if (EventKindtoListIndex (i) == lListIndex) {
			return i;
		}
	}
	return -1;
}


// 行方向スクロールバー(縦)のデザイン設定
void CEventListFrame::RecalcRowScrollInfo (long lLogPixelsY) {
	SCROLLINFO si;
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = (int)CLIP(0, (GetVisibleEventCount () + 4) * m_lRowZoom * lLogPixelsY / 96, 0x7FFFFFFF);
	si.nPage = m_lIndexHeight;
	m_wndRowScroll.SetScrollInfo (&si, TRUE);
	m_lRowScrollPos = m_wndRowScroll.GetScrollPos ();
}

// 列方向スクロールバー(横)のデザイン設定
void CEventListFrame::RecalcColumnScrollInfo (long lLogPixelsX) {
	SCROLLINFO si;
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	long lSum = 0;
	for (long j = 0; j < 8; j++) {
		lSum += GetColumnWidth (j, lLogPixelsX);
	}
	si.nMax = lSum;
	si.nPage = m_lPropertyWidth;
	m_wndColumnScroll.SetScrollInfo (&si, TRUE);
	m_lColumnScrollPos = m_wndColumnScroll.GetScrollPos ();
}







//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// ウィンドウ生成直前の構造体設定
BOOL CEventListFrame::PreCreateWindow (CREATESTRUCT& cs) {
	return CWnd::PreCreateWindow (cs);
}

// ウィンドウタイトルの自動設定(CMDIChildWnd::OnUpdateFrameTitleのオーバーライド)
void CEventListFrame::OnUpdateFrameTitle (BOOL bAddToTitle) {
	// update our parent window first
	GetMDIFrame()->OnUpdateFrameTitle (bAddToTitle);
	if ((GetStyle() & FWS_ADDTOTITLE) == 0) {
		return;     // leave child window alone!
	}
	CDocument* pDocument = GetActiveDocument();
	if (bAddToTitle && pDocument != NULL) {
		CString strEventList;
		strEventList.LoadString (IDS_EVENTLIST);
		CString strTitle;
		if (m_nWindow > 0) {
			strTitle.Format (_T("%s:%d(%s)"), pDocument->GetTitle (), m_nWindow, strEventList);
		}
		else {
			strTitle.Format (_T("%s(%s)"), pDocument->GetTitle (), strEventList);
		}
		this->SetWindowText (strTitle);
	}
}

// 再配置用関数(CFrameWnd::RecalcLayoutのオーバーライド)
void CEventListFrame::RecalcLayout (BOOL bNotify) {

	CRect rcClient;
	GetClientRect (&rcClient);

	// 基本クラスの関数を処理
	CFrameWnd::RecalcLayout (bNotify);

	// アイコン化時には各コントロールのサイズを再計算しない。
	if (rcClient.Width () == 0 || rcClient.Height () == 0) {
		return;
	}

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// ツールバー1の高さ取得
	CRect rcToolBar1;
	m_wndToolBar1.GetWindowRect (rcToolBar1); 
	m_lToolBar1Height = rcToolBar1.Height ();

	// 高さ方向の位置計算
	if (rcClient.Height () < 
		m_lToolBar1Height + 
		EVENTLISTFRAME_SCALEHEIGHT * lLogPixelsY / 96 + 
		m_lHScrollBarHeight +
		EVENTLISTFRAME_BORDERHEIGHT * 2) {
		m_lScaleHeight = rcClient.Height () - m_lHScrollBarHeight -
			EVENTLISTFRAME_BORDERHEIGHT * 2 - m_lToolBar1Height;
		m_lIndexHeight = 0;
	}
	else {
		m_lScaleHeight = EVENTLISTFRAME_SCALEHEIGHT * lLogPixelsY / 96;
		m_lIndexHeight = rcClient.Height () - 
			m_lScaleHeight - m_lHScrollBarHeight -
			EVENTLISTFRAME_BORDERHEIGHT * 2 - m_lToolBar1Height;
	}
	if (rcClient.Height () <
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 6 +
		EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 + 
		m_lTrackListHeight) {
		m_lTrackListHeight = rcClient.Height () -
			m_lToolBar1Height - EVENTLISTFRAME_BORDERHEIGHT * 6 -
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96;
		m_lEventKindListHeight = 0;
		m_lControlChangeListHeight = 0;
	}
	else if (rcClient.Height () <
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 6 +
		EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 * 2 + 
		m_lTrackListHeight +
		m_lEventKindListHeight) {
		m_lTrackListHeight = m_lTrackListHeight;
		m_lEventKindListHeight = rcClient.Height () -
			m_lToolBar1Height - EVENTLISTFRAME_BORDERHEIGHT * 6 -
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 * 2 - 
			m_lTrackListHeight;
		m_lControlChangeListHeight = 0;
	}
	else {
		m_lTrackListHeight = m_lTrackListHeight;
		m_lEventKindListHeight = m_lEventKindListHeight;
		m_lControlChangeListHeight = rcClient.Height () -
			m_lToolBar1Height - EVENTLISTFRAME_BORDERHEIGHT * 6 -
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 * 2 - 
			m_lTrackListHeight -
			m_lEventKindListHeight;
	}

	// 幅方向の位置計算
	if (rcClient.Width () <
		EVENTLISTFRAME_SCALEWIDTH * lLogPixelsX / 96 + 
		m_lVScrollBarWidth + 
		EVENTLISTFRAME_BORDERWIDTH * 4 + 
		EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96) {
		m_lScaleWidth = rcClient.Width () - 
			m_lVScrollBarWidth - 
			EVENTLISTFRAME_BORDERWIDTH * 4 - 
			EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96;
		m_lTrackListWidth = 0;
		m_lPropertyWidth = 0;
	}
	else if (rcClient.Width () <
		EVENTLISTFRAME_SCALEWIDTH * lLogPixelsX / 96 + 
		m_lVScrollBarWidth + 
		EVENTLISTFRAME_BORDERWIDTH * 4 + 
		EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96 + 
		m_lTrackListWidth) {
		m_lScaleWidth = EVENTLISTFRAME_SCALEWIDTH;
		m_lPropertyWidth = 0;
		m_lTrackListWidth = rcClient.Width () - m_lScaleWidth -
			m_lVScrollBarWidth - EVENTLISTFRAME_BORDERWIDTH * 4 - 
			EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96;

	}
	else {
		m_lScaleWidth = EVENTLISTFRAME_SCALEWIDTH * lLogPixelsX / 96;
		m_lTrackListWidth = m_lTrackListWidth; 
		m_lPropertyWidth = rcClient.Width () - m_lScaleWidth - m_lTrackListWidth -
			m_lVScrollBarWidth - 
			EVENTLISTFRAME_BORDERWIDTH * 4 - 
			EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96;
	}

	// ビューの整列
	if (m_pScaleView) {
		m_pScaleView->MoveWindow (EVENTLISTFRAME_BORDERWIDTH, 
			m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT, 
			m_lScaleWidth, m_lScaleHeight);
	}

	if (m_pPropertyScaleView) {
		m_pPropertyScaleView->MoveWindow (EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth, 
			m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT, 
			m_lPropertyWidth, m_lScaleHeight);
	}

	if (m_pIndexScaleView) {
		m_pIndexScaleView->MoveWindow (EVENTLISTFRAME_BORDERWIDTH, 
			m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight, 
			m_lScaleWidth, m_lIndexHeight);
	}

	if (m_pIndexPropertyView) {
		m_pIndexPropertyView->MoveWindow (EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth,
			m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight, 
			m_lPropertyWidth, m_lIndexHeight);
	}

	// スクロールバーの整列
	m_wndColumnScroll.MoveWindow 
		(EVENTLISTFRAME_BORDERWIDTH,
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight + m_lIndexHeight,
		m_lScaleWidth + m_lPropertyWidth - m_lVScrollBarWidth * 2, 
		m_lHScrollBarHeight);

	m_wndRowScroll.MoveWindow 
		(EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth + m_lPropertyWidth, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT,
		m_lVScrollBarWidth, 
		m_lScaleHeight + m_lIndexHeight - m_lVScrollBarWidth * 2);

	m_wndSizeScroll.MoveWindow 
		(EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth + m_lPropertyWidth, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight + m_lIndexHeight, 
		m_lVScrollBarWidth, m_lHScrollBarHeight);

	// ズームボタンの整列
	m_wndColumnZoomDown.MoveWindow 
		(EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth +
		m_lPropertyWidth - m_lVScrollBarWidth * 2, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight + m_lIndexHeight,
		m_lVScrollBarWidth, m_lHScrollBarHeight);
	
	m_wndColumnZoomUp.MoveWindow 
		(EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth +
		m_lPropertyWidth - m_lVScrollBarWidth, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight + m_lIndexHeight, 
		m_lVScrollBarWidth, m_lHScrollBarHeight);

	m_wndRowZoomDown.MoveWindow
		(EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth + m_lPropertyWidth, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight + m_lIndexHeight -
		m_lVScrollBarWidth * 2, 
		m_lVScrollBarWidth, m_lHScrollBarHeight);

	m_wndRowZoomUp.MoveWindow
		(EVENTLISTFRAME_BORDERWIDTH + m_lScaleWidth + m_lPropertyWidth, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT + m_lScaleHeight + m_lIndexHeight -
		m_lVScrollBarWidth, 
		m_lVScrollBarWidth, m_lHScrollBarHeight);

	// トラックリストの整列
	m_pTrackListBox->MoveWindow
		(EVENTLISTFRAME_BORDERWIDTH * 3 + m_lScaleWidth + 
		m_lPropertyWidth + m_lVScrollBarWidth + 
			EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT, 
		m_lTrackListWidth, m_lTrackListHeight);

	// イベントの種類リストの整列
	m_pEventKindListBox->MoveWindow
		(EVENTLISTFRAME_BORDERWIDTH * 3 + m_lScaleWidth +
		m_lPropertyWidth + m_lVScrollBarWidth + 
			EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 3 + m_lTrackListHeight +
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96, 
		m_lTrackListWidth, m_lEventKindListHeight);

	// コントロールチェンジリストの整列
	m_pControlChangeListBox->MoveWindow
		(EVENTLISTFRAME_BORDERWIDTH * 3 + m_lScaleWidth +
		m_lPropertyWidth + m_lVScrollBarWidth + 
			EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96, 
		m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 5 + m_lTrackListHeight + 
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 + 
			m_lEventKindListHeight + 
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96, 
		m_lTrackListWidth, m_lControlChangeListHeight);

	// スクロールバーのサイズが変化したので、バーのデザインを再調整する。
	RecalcRowScrollInfo (lLogPixelsY);
	RecalcColumnScrollInfo (lLogPixelsX);

}



// クライアント領域の生成(CFrameWnd::OnCreateClientのオーバーライド)
BOOL CEventListFrame::OnCreateClient (LPCREATESTRUCT lpcs, CCreateContext* pContext) {

	// サイズ調整用のダミービュー生成(Visible = FALSE)
	CWnd* pWnd = NULL;
	m_pDummyView = (CView*)CFrameWnd::CreateView (pContext, EVENTLISTFRAME_DUMMYVIEW);
	if (m_pDummyView == NULL) {
			return FALSE;
	}
	m_pDummyView->ShowWindow (SW_HIDE);
	
	// 印刷用のビュー生成(Visible = FALSE)
	pContext->m_pNewViewClass = RUNTIME_CLASS (CEventListPrintView);
	m_pPrintView = (CView*)CFrameWnd::CreateView (pContext, EVENTLISTFRAME_PRINTVIEW);
	if (m_pPrintView == NULL) {
			return FALSE;
	}
	m_pPrintView->ShowWindow (SW_HIDE);

	// 左上ビューの生成
	pContext->m_pNewViewClass = RUNTIME_CLASS (CEventListScaleView);
	m_pScaleView = (CView*)CFrameWnd::CreateView (pContext, EVENTLISTFRAME_SCALEVIEW);
	if (m_pScaleView == NULL) {
			return FALSE;
	}
	m_pScaleView->ModifyStyleEx (WS_EX_CLIENTEDGE, 0);

	// 上部項目名部ビューの生成
	pContext->m_pNewViewClass = RUNTIME_CLASS (CEventListPropertyScaleView);
	m_pPropertyScaleView = (CView*)CFrameWnd::CreateView (pContext, EVENTLISTFRAME_PROPERTYSCALEVIEW);
	if (m_pPropertyScaleView == NULL) {
			return FALSE;
	}
	m_pPropertyScaleView->ModifyStyleEx (WS_EX_CLIENTEDGE, 0);

	// 左部番号部ビューの生成
	pContext->m_pNewViewClass = RUNTIME_CLASS (CEventListIndexScaleView);
	m_pIndexScaleView = (CView*)CFrameWnd::CreateView (pContext, EVENTLISTFRAME_INDEXSCALEVIEW);
	if (m_pIndexScaleView == NULL) {
			return FALSE;
	}
	m_pIndexScaleView->ModifyStyleEx (WS_EX_CLIENTEDGE, 0);

	// リスト部ビューの生成
	pContext->m_pNewViewClass = RUNTIME_CLASS (CEventListIndexPropertyView);
	m_pIndexPropertyView = (CView*)CFrameWnd::CreateView (pContext, EVENTLISTFRAME_INDEXPROPERTYVIEW);
	if (m_pIndexPropertyView == NULL) {
			return FALSE;
	}
	m_pIndexPropertyView->ModifyStyleEx (WS_EX_CLIENTEDGE, 0);

	// スクロールバーの生成
	m_wndColumnScroll.Create   
		(WS_CHILD|WS_VISIBLE|SBS_HORZ, CRect(0,0,0,0), this, EVENTLISTFRAME_COLUMNSCROLL);
	m_wndRowScroll.Create    
		(WS_CHILD|WS_VISIBLE|SBS_VERT, CRect(0,0,0,0), this, EVENTLISTFRAME_ROWSCROLL);
	m_wndSizeScroll.Create   
		(WS_CHILD|WS_VISIBLE|SBS_SIZEBOX, CRect(0,0,0,0), this, EVENTLISTFRAME_SIZEBOX);
	
	// ズームボタン類の生成
	m_wndColumnZoomDown.Create 
		(_T("-"), WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, EVENTLISTFRAME_COLUMNZOOMDOWN);
	m_wndColumnZoomUp.Create   
		(_T("+"), WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, EVENTLISTFRAME_COLUMNZOOMUP);
	m_wndRowZoomDown.Create  
		(_T("-"), WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, EVENTLISTFRAME_ROWZOOMDOWN);
	m_wndRowZoomUp.Create    
		(_T("+"), WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, EVENTLISTFRAME_ROWZOOMUP);

	// トラックリストの生成
	m_pTrackListBox =
		new CTrackListBox (pContext->m_pCurrentDoc, IDR_POPUPMENU23);
	m_pTrackListBox->Create
		(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|
		LBS_NOTIFY|LBS_DISABLENOSCROLL|LBS_OWNERDRAWFIXED|LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT, 
		CRect(0,0,0,0), this, EVENTLISTFRAME_TRACKLIST);

	// イベントの種類リストの生成
	m_pEventKindListBox = 
		new CEventKindListBox (pContext->m_pCurrentDoc, IDR_POPUPMENU24);
	m_pEventKindListBox->Create
		(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|
		LBS_NOTIFY|LBS_DISABLENOSCROLL|LBS_OWNERDRAWFIXED|LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT, 
		CRect(0,0,0,0), this, EVENTLISTFRAME_EVENTKINDLIST);

	// コントロールチェンジリストの生成
	m_pControlChangeListBox = 
		new CControlChangeListBox (pContext->m_pCurrentDoc, IDR_POPUPMENU27);
	m_pControlChangeListBox->Create
		(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|
		LBS_NOTIFY|LBS_DISABLENOSCROLL|LBS_OWNERDRAWFIXED|LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT, 
		CRect(0,0,0,0), this, EVENTLISTFRAME_CONTROLCHANGELIST);

	// フォーカスの設定
	SetActiveView ((CView*)m_pIndexPropertyView);

	// コントロールの位置合わせはWM_SIZEなどによるRecalcLaoyoutに任せる。
	return TRUE;

}

// 印刷用のコマンドをトラップ(CFrameWnd::OnCmdMsgのオーバーライド)
BOOL CEventListFrame::OnCmdMsg (UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	// 印刷用のコマンドの場合、強制的にCEventListPrintViewに渡す。
	if ((nID == ID_FILE_PRINT || nID == ID_FILE_PRINT_DIRECT || nID == ID_FILE_PRINT_PREVIEW) &&
		pSekaijuApp->m_bRecording == FALSE &&
		pSekaijuApp->m_bSALRunning == FALSE) {
		if (m_pPrintView) {
			return ((CEventListPrintView*)m_pPrintView)->OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);
		}
		return FALSE;
	}
	// その他のコマンドはデフォルトの処理とする。
	return CFrameWnd::OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);
}



//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------

// ウィンドウ生成時
int CEventListFrame::OnCreate (LPCREATESTRUCT lpCreateStruct) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CRect rcTemp;

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);
	m_lTrackListWidth = EVENTLISTFRAME_TRACKLISTWIDTH * lLogPixelsX / 96;

	// ツールバー1の作成
	if (!m_wndToolBar1.CreateEx (this, 0,
		WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP,
		CRect (4, 4, 4, 4)) ||
		!m_wndToolBar1.LoadToolBar (IDR_EVENTLIST1)) {
		TRACE0 ("Failed to create toolbar\n");
		return -1;
	}
	m_wndToolBar1.AdjustToHighResolution ();
	m_wndToolBar1.ModifyStyle (0, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT);
	//m_wndToolBar1.EnableDocking (CBRS_ALIGN_ANY);
	//EnableDocking (CBRS_ALIGN_ANY);
	//DockControlBar (&m_wndToolBar1);

	LoadAccelTable (MAKEINTRESOURCE (IDR_EVENTLIST));

	// イベントトラックコンボボックスの作成
	m_wndToolBar1.SetButtonInfo (6, IDC_EVENTTRACKCOMBO, TBBS_SEPARATOR, 160 * lLogPixelsX / 96);
	m_wndToolBar1.GetItemRect (6, &rcTemp);
	if (!m_wndEventTrackCombo.CreateEx (
		WS_EX_CLIENTEDGE, _T("COMBOBOX"), NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST,
		rcTemp.left, rcTemp.top + 1, rcTemp.Width (), rcTemp.Height () - 2, 
		m_wndToolBar1.GetSafeHwnd (), (HMENU)IDC_EVENTTRACKCOMBO)) {
		TRACE0 ("Failed to create edit box\n");
		return -1;
	}
	//m_wndEventTrackCombo.SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_wndEventTrackCombo.SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_wndEventTrackCombo.SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);
	
	// イベントタイムエディットの作成
	m_wndToolBar1.SetButtonInfo (8, IDC_EVENTTIMEEDIT, TBBS_SEPARATOR, 120 * lLogPixelsX / 96);
	m_wndToolBar1.GetItemRect (8, &rcTemp);
	if (!m_wndEventTimeEdit.CreateEx (
		WS_EX_CLIENTEDGE, _T("EDIT"), NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		rcTemp.left, rcTemp.top + 1, rcTemp.Width (), rcTemp.Height () - 2, 
		m_wndToolBar1.GetSafeHwnd (), (HMENU)IDC_EVENTTIMEEDIT)) {
		TRACE0 ("Failed to create edit box\n");
		return -1;
	}
	// m_wndEventTimeEdit.SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_wndEventTimeEdit.SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_wndEventTimeEdit.SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);

	// イベント種類コンボボックスの作成
	m_wndToolBar1.SetButtonInfo (10, IDC_EVENTKINDCOMBO, TBBS_SEPARATOR, 160 * lLogPixelsX / 96);
	m_wndToolBar1.GetItemRect (10, &rcTemp);
	if (!m_wndEventKindCombo.CreateEx (
		WS_EX_CLIENTEDGE, _T("COMBOBOX"), NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST,
		rcTemp.left, rcTemp.top + 1, rcTemp.Width (), rcTemp.Height () - 2, 
		m_wndToolBar1.GetSafeHwnd (), (HMENU)IDC_EVENTKINDCOMBO)) {
		TRACE0 ("Failed to create edit box\n");
		return -1;
	}
	//m_wndEventKindCombo.SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_wndEventKindCombo.SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_wndEventKindCombo.SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);

	// イベントチャンネルコンボボックスの作成
	m_wndToolBar1.SetButtonInfo (12, IDC_EVENTCHANNELCOMBO, TBBS_SEPARATOR, 60 * lLogPixelsX / 96);
	m_wndToolBar1.GetItemRect (12, &rcTemp);
	if (!m_wndEventChannelCombo.CreateEx (
		WS_EX_CLIENTEDGE, _T("COMBOBOX"), NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST,
		rcTemp.left, rcTemp.top + 1, rcTemp.Width (), rcTemp.Height () - 2, 
		m_wndToolBar1.GetSafeHwnd (), (HMENU)IDC_EVENTCHANNELCOMBO)) {
		TRACE0 ("Failed to create combo box\n");
		return -1;
	}
	//m_wndEventChannelCombo.SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_wndEventChannelCombo.SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_wndEventChannelCombo.SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);

	// 親クラスの関数呼び出し
	int nRet = CChildFrame::OnCreate (lpCreateStruct);	
	


	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;
	MIDITrack* pMIDITrack = NULL;

	// トラックコンボの充満
	UpdateTrackCombo ();
	//m_wndEventTrackCombo.SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_wndEventTrackCombo.SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_wndEventTrackCombo.SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);

	// イベントの時刻エディットの充満
	CString strText;
	strText.Format (_T("%05d:%02d:%03d"), 1, 1, 0);
	m_wndEventTimeEdit.SetWindowText (strText);

	// イベントの種類コンボの充満
	m_wndEventKindCombo.ResetContent ();
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x00]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x01]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x02]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x03]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x04]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x05]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x06]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x07]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x08]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x09]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x20]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x21]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x2F]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x51]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x54]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x58]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x59]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x7F]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x80]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0x90]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0xA0]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0xB0]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0xC0]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0xD0]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0xE0]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0xF0]);
	m_wndEventKindCombo.AddString (pSekaijuApp->m_strEventKindName[0xF7]);
	m_wndEventKindCombo.SetCurSel (0);
	//m_wndEventKindCombo.SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_wndEventKindCombo.SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_wndEventKindCombo.SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);

	// イベントのチャンネルコンボの充満
	strText = _T("n/a");
	m_wndEventChannelCombo.AddString (strText);
	int i = 0;
	for (i = 0; i < 16; i++) {
		strText.Format (_T("%d"), i + 1);
		m_wndEventChannelCombo.AddString (strText);
	}
	m_wndEventChannelCombo.SetCurSel (0);
	//m_wndEventChannelCombo.SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_wndEventChannelCombo.SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_wndEventChannelCombo.SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);

	// トラックリストの充満
	UpdateTrackList ();
	//m_pTrackListBox->SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_pTrackListBox->SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_pTrackListBox->SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);

	long lCount = m_pTrackListBox->GetCount ();
	i = 0;
	if (pSekaijuDoc->m_pTempTrack) {
		forEachTrack (pMIDIData, pMIDITrack) {
			if (0 <= i && i < lCount) {
				m_pTrackListBox->SetCheck (i, pMIDITrack == pSekaijuDoc->m_pTempTrack ? TRUE : FALSE);
				m_bTrackVisible[i] = (pMIDITrack == pSekaijuDoc->m_pTempTrack ? TRUE : FALSE);
			}
			i++;
		}
	}
	else {
		forEachTrack (pMIDIData, pMIDITrack) {
			if (0 <= i && i < lCount) {
				m_pTrackListBox->SetCheck (i, TRUE);
				m_bTrackVisible[i] = (TRUE);
			}
			i++;
		}
	}
	m_bOnlyCurTrack = FALSE;
	m_bShowAllTrack = FALSE;

	// カレントトラックとカレントチャンネルを更新
	long lTrackIndex = 0;
	if (pSekaijuDoc->m_pTempTrack) {
		lTrackIndex = pSekaijuDoc->GetTrackIndex (pSekaijuDoc->m_pTempTrack);
	}
	else if (MIDIData_GetFormat (pMIDIData) == 1 && lCount >= 2) {
		lTrackIndex = 1;
	}
	ASSERT (0 <= lTrackIndex && lTrackIndex < lCount);
	if (m_bTrackVisible[lTrackIndex]) {
		SetCurTrackIndex (lTrackIndex, lLogPixelsX, lLogPixelsY);
		pMIDITrack = pSekaijuDoc->GetTrack (lTrackIndex);
		if (pMIDITrack) {
			long lOutputChannel = MIDITrack_GetOutputChannel (pMIDITrack);
			if (0 <= lOutputChannel && lOutputChannel <= 15) {
				SetCurChannel (lOutputChannel);
			}
		}
	}

	// イベントの種類リストの充満
	CString strIncludingVelocity0NoteOn;
	CString strUnknownEventKind;
	VERIFY (strIncludingVelocity0NoteOn.LoadString (IDS_INCLUDING_VELOCITY0_NOTEON));
	VERIFY (strUnknownEventKind.LoadString (IDS_UNKNOWN_EVENT_KIND));
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x00]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x01]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x02]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x03]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x04]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x05]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x06]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x07]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x08]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x09]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x20]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x21]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x2F]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x51]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x54]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x58]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x59]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x7F]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x80] + strIncludingVelocity0NoteOn);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0x90]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0xA0]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0xB0]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0xC0]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0xD0]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0xE0]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0xF0]);
	m_pEventKindListBox->AddString (pSekaijuApp->m_strEventKindName[0xF7]);
	m_pEventKindListBox->AddString (strUnknownEventKind);
	m_pEventKindListBox->SetCurSel (0);
	//m_pEventKindListBox->SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_pEventKindListBox->SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_pEventKindListBox->SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);
	lCount = m_pEventKindListBox->GetCount ();
	for (i = 0; i < lCount; i++) {
		m_pEventKindListBox->SetCheck (i, IsEventKindVisible (i) ? 1 : 0);
	}

	// カレントチャンネルの自動選択
	if (pSekaijuDoc->m_pTempTrack) {
		long lOutputChannel = MIDITrack_GetOutputChannel (pSekaijuDoc->m_pTempTrack);
		if (0 <= lOutputChannel && lOutputChannel <= 15) {
			SetCurChannel (lOutputChannel);
		}
	}

	// コントロールチェンジリストの充満
	UpdateControlChangeList ();
	m_pControlChangeListBox->SetCurSel (1);
	//m_pControlChangeListBox->SetFont (CFont::FromHandle ((HFONT)::GetStockObject (DEFAULT_GUI_FONT)));
	m_pControlChangeListBox->SetFont (&(pSekaijuApp->m_theDefaultFont));
	m_pControlChangeListBox->SendMessage (CB_SETITEMHEIGHT, -1, 23 * lLogPixelsY / 96 - 8);
	lCount = m_pControlChangeListBox->GetCount ();
	for (i = 0; i < lCount; i++) {
		m_pControlChangeListBox->SetCheck (i, IsControlChangeVisible (i) ? 1 : 0);
	}

	// 可視のイベントリストの作成	
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);

	// 自動ページ更新の設定
	if (pSekaijuApp->m_theGeneralOption.m_bEnableAutoPageUpdate) {
		m_bAutoPageUpdate = TRUE;
	}

	SetActiveView (m_pIndexPropertyView, FALSE);
	m_pIndexPropertyView->SetFocus ();

	pSekaijuDoc->m_theCriticalSection.Unlock ();
	
	return nRet;
}

// ウィンドウ破棄時
void CEventListFrame::OnDestroy () {
	m_pTrackListBox->DestroyWindow ();
	delete m_pTrackListBox;
	m_pEventKindListBox->DestroyWindow ();
	delete m_pEventKindListBox;
	m_pControlChangeListBox->DestroyWindow ();
	delete m_pControlChangeListBox;
	CChildFrame::OnDestroy ();
}

// ウィンドウサイズ変更時
void CEventListFrame::OnSize (UINT nType, int cx, int cy) {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	// 基本クラスの関数呼び出し
	CChildFrame::OnSize (nType, cx, cy);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
}

// タイマー呼び出し時
void CEventListFrame::OnTimer (UINT_PTR nIDEvent) {
	;
}

// 背景消去(CFrameWnd::OnEraseBkgndのオーバーライド)
BOOL CEventListFrame::OnEraseBkgnd (CDC* pDC) {
	return 0;
}

// ウィンドウがアクティブになったとき
void CEventListFrame::OnMDIActivate (BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) {
	CChildFrame::OnMDIActivate (bActivate, pActivateWnd, pDeactivateWnd);
}

// 閉じるボタンが押されたとき
void CEventListFrame::OnClose () {
	_RPTF0 (_CRT_WARN, ("CEventListFrame::OnClose ()\n"));
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// インプレースエディット及びインプレースリストボックスの終了
	if (m_pIndexPropertyView) {
		CEventListIndexPropertyView* pIndexPropertyView = (CEventListIndexPropertyView*)m_pIndexPropertyView;
		if (pIndexPropertyView->IsTextEditing ()) {
			pIndexPropertyView->EndTextEditingOK ();
			pSekaijuDoc->SetModifiedFlag (TRUE);
			pSekaijuDoc->UpdateAllViews (NULL, SEKAIJUDOC_MIDIEVENTCHANGED | SEKAIJUDOC_MIDITRACKCHANGED);
		}
		if (pIndexPropertyView->IsListSelecting ()) {
			pIndexPropertyView->EndListSelectingOK ();
			pSekaijuDoc->SetModifiedFlag (TRUE);
			pSekaijuDoc->UpdateAllViews (NULL, SEKAIJUDOC_MIDIEVENTCHANGED | SEKAIJUDOC_MIDITRACKCHANGED);
		}
	}
	CChildFrame::OnClose ();
}

// 描画するとき
void CEventListFrame::OnPaint () {
	CPaintDC dc (this);

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	CRect rcClient;
	GetClientRect (&rcClient);
	// ツールバー部の背景描画
	CRect rcToolBar1 (rcClient);
	m_wndToolBar1.GetWindowRect (&rcToolBar1);
	rcToolBar1 = CRect (0, 0, rcToolBar1.Width (), rcToolBar1.Height ());
	dc.FillSolidRect (rcToolBar1, ::GetSysColor (COLOR_3DFACE));
	// 左部分のくぼみ描画
	CRect rcClient1 (rcClient);
	rcClient1.top = m_lToolBar1Height;
	rcClient1.right = EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + 
		m_lPropertyWidth + m_lVScrollBarWidth;
	dc.Draw3dRect (&rcClient1, RGB (128, 128, 128), RGB (255, 255, 255));
	rcClient1.InflateRect (-1, -1);
	dc.Draw3dRect (&rcClient1, RGB (0, 0, 0), RGB (192, 192, 192));
	// 右上部分のくぼみ描画
	CRect rcClient2 (rcClient);
	rcClient2.top = m_lToolBar1Height;
	rcClient2.left = EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + 
		m_lPropertyWidth + m_lVScrollBarWidth + 
		EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96;
	rcClient2.bottom = m_lToolBar1Height + 
		EVENTLISTFRAME_BORDERHEIGHT * 2 + m_lTrackListHeight;
	dc.Draw3dRect (&rcClient2, RGB (128, 128, 128), RGB (255, 255, 255));
	rcClient2.InflateRect (-1, -1);
	dc.Draw3dRect (&rcClient2, RGB (0, 0, 0), RGB (192, 192, 192));
	// 右中部分のくぼみ描画
	CRect rcClient3 (rcClient);
	rcClient3.top = m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 2 + 
		EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 + 
		m_lTrackListHeight;
	rcClient3.left = EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + 
		m_lPropertyWidth + m_lVScrollBarWidth + 
		EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96;
	rcClient3.bottom = m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 4 + 
		EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 + 
		m_lTrackListHeight + m_lEventKindListHeight;
	dc.Draw3dRect (&rcClient3, RGB (128, 128, 128), RGB (255, 255, 255));
	rcClient3.InflateRect (-1, -1);
	dc.Draw3dRect (&rcClient3, RGB (0, 0, 0), RGB (192, 192, 192));
	// 右下部分のくぼみ描画
	CRect rcClient4 (rcClient);
	rcClient4.top = m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 4 + 
		EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 + m_lTrackListHeight +
		EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 + m_lEventKindListHeight;
	rcClient4.left = EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + 
		m_lPropertyWidth + m_lVScrollBarWidth + 
		EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96;
	dc.Draw3dRect (&rcClient4, RGB (128, 128, 128), RGB (255, 255, 255));
	rcClient4.InflateRect (-1, -1);
	dc.Draw3dRect (&rcClient4, RGB (0, 0, 0), RGB (192, 192, 192));

	// 横境界部分の描画
	CBrush brush;
	brush.CreateSolidBrush (::GetSysColor (COLOR_3DFACE));
	CRect rcClient5 (rcClient);
	rcClient5.left = rcClient2.left - 1;
	rcClient5.top = rcClient2.bottom + 1;
	rcClient5.bottom = rcClient3.top - 1;
	dc.FillRect (&rcClient5, &brush);
	CRect rcClient6 (rcClient);
	rcClient6.left = rcClient2.left - 1;
	rcClient6.top = rcClient3.bottom + 1;
	rcClient6.bottom = rcClient4.top - 1;
	dc.FillRect (&rcClient6, &brush);
	// 縦境界部分の描画
	CRect rcClient7 (rcClient);
	rcClient7.left = rcClient1.right + 1;
	rcClient7.right = rcClient2.left - 1;
	dc.FillRect (&rcClient7, &brush);


}

// キー押し下げ時
void CEventListFrame::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd ();
	CWnd* pOldFocus = GetFocus ();
	switch (nChar) {
	// ↑
	case VK_UP:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_VSCROLL, (WPARAM)SB_LINEUP, 
				(LPARAM)(m_wndRowScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// ↓
	case VK_DOWN:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_VSCROLL, (WPARAM)SB_LINEDOWN, 
				(LPARAM)(m_wndRowScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// PageUp
	case VK_PRIOR:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_VSCROLL, (WPARAM)SB_PAGEUP, 
				(LPARAM)(m_wndRowScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// PageDown
	case VK_NEXT:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_VSCROLL, (WPARAM)SB_PAGEDOWN, 
				(LPARAM)(m_wndRowScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// ←
	case VK_LEFT:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_HSCROLL, (WPARAM)SB_LINEUP, 
				(LPARAM)(m_wndColumnScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// →
	case VK_RIGHT:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_HSCROLL, (WPARAM)SB_LINEDOWN, 
				(LPARAM)(m_wndColumnScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// Home
	case VK_HOME:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_HSCROLL, (WPARAM)SB_PAGEUP, 
				(LPARAM)(m_wndColumnScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// End
	case VK_END:
		if (GetCapture () == NULL) {
			this->PostMessage (WM_HSCROLL, (WPARAM)SB_PAGEDOWN, 
				(LPARAM)(m_wndColumnScroll.GetSafeHwnd ()));
			this->PostMessage (WM_SETFOCUS, (WPARAM)(pOldFocus->GetSafeHwnd ()), 0);
		}
		break;
	// '-'(ズームダウン)
	case 189:
	case VK_SUBTRACT:
		if (GetCapture () == NULL && ::GetKeyState (VK_CONTROL) < 0) {
			if (pSekaijuApp->m_theEventListOption.m_bEnableRowZoomKey) {
				this->PostMessage (WM_COMMAND, EVENTLISTFRAME_ROWZOOMDOWN, 0);
			}
			if (pSekaijuApp->m_theEventListOption.m_bEnableColumnZoomKey) {
				this->PostMessage (WM_COMMAND, EVENTLISTFRAME_COLUMNZOOMDOWN, 0);
			}
		}
		break;
	// '+'(ズームアップ)
	case 187:
	case VK_ADD:
		if (GetCapture () == NULL && ::GetKeyState (VK_CONTROL) < 0) {
			if (pSekaijuApp->m_theEventListOption.m_bEnableRowZoomKey) {
				this->PostMessage (WM_COMMAND, EVENTLISTFRAME_ROWZOOMUP, 0);
			}
			if (pSekaijuApp->m_theEventListOption.m_bEnableColumnZoomKey) {
				this->PostMessage (WM_COMMAND, EVENTLISTFRAME_COLUMNZOOMUP, 0);
			}
		}
		break;
	default:
		pMainFrame->PostMessage (WM_KEYDOWN, nChar, MAKELPARAM (nRepCnt, nFlags));
		break;
	}
}

// マウス左ボタン押された時  
void CEventListFrame::OnLButtonDown (UINT nFlags, CPoint point) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	// 上半分(トラックリスト部)と下半分(イベントの種類部)の境界線上をドラッグすると、境界線が上下に移動
	if (m_bSplitterMovingH || m_bSplitterMovingH2 || m_bSplitterMovingV) {
		SetCapture ();
		m_ptMouseDown = m_ptMouseMoveOld = point;
		CDC* pDC = GetDC ();
		DrawSplitterCaptor (pDC, point);
		ReleaseDC (pDC);
		if (m_bSplitterMovingH && m_bSplitterMovingV ||
			m_bSplitterMovingH2 && m_bSplitterMovingV) {
			::SetCursor (pSekaijuApp->m_hCursorResizeAll);
		}
		else if (m_bSplitterMovingH || m_bSplitterMovingH2) {
			::SetCursor (pSekaijuApp->m_hCursorResizeNS);
		}
		else if (m_bSplitterMovingV) {
			::SetCursor (pSekaijuApp->m_hCursorResizeWE);
		}
	}

}

// マウス右ボタン押された時  
void CEventListFrame::OnRButtonDown (UINT nFlags, CPoint point) {

}

// マウス左ボタン離されたとき
void CEventListFrame::OnLButtonUp (UINT nFlags, CPoint point) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	if (GetCapture () == this) {
		CDC* pDC = GetDC ();
		DrawSplitterCaptor (pDC, m_ptMouseMoveOld);
		ReleaseDC (pDC);
		ReleaseCapture ();
		::SetCursor (pSekaijuApp->m_hCursorArrow);
		CPoint ptDelta = point - m_ptMouseDown;
		if (m_bSplitterMovingH) {
			m_lTrackListHeight = CLIP (0, (m_lTrackListHeight + ptDelta.y), 1200);
		}
		if (m_bSplitterMovingH2) {
			m_lEventKindListHeight = CLIP (0, (m_lEventKindListHeight + ptDelta.y), 1200);
		}
		if (m_bSplitterMovingV) {
			m_lTrackListWidth = CLIP (0, (m_lTrackListWidth - ptDelta.x), 1600);
		}
		RecalcLayout ();
		m_bSplitterMovingH = FALSE;
		m_bSplitterMovingH2 = FALSE;
		m_bSplitterMovingV = FALSE;
		Invalidate ();
	}

}

// マウス右ボタン離されたとき
void CEventListFrame::OnRButtonUp (UINT nFlags, CPoint point) {

}

// マウスが動かされたとき
void CEventListFrame::OnMouseMove (UINT nFlags, CPoint point) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// キャプター中
	if (GetCapture () == this) {
		CRect rcClient;
		GetClientRect (&rcClient);
		CDC* pDC = GetDC ();
		DrawSplitterCaptor (pDC, m_ptMouseMoveOld);
		DrawSplitterCaptor (pDC, point);
		ReleaseDC (pDC);
		m_ptMouseMoveOld = point;
	}
	// 非キャプター中
	else {
		// カーソルが水平スプリッター上にあるか
		m_bSplitterMovingH =
			m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 2 + m_lTrackListHeight <= point.y &&
			point.y < m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 2 + m_lTrackListHeight + 
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsX / 96 &&
			point.x >= EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + m_lPropertyWidth + m_lVScrollBarWidth;
		// カーソルが水平スプリッター2上にあるか
		m_bSplitterMovingH2 =
			m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 4 + 
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 + 
			m_lTrackListHeight +m_lEventKindListHeight <= point.y &&
			point.y < m_lToolBar1Height + EVENTLISTFRAME_BORDERHEIGHT * 4 + m_lTrackListHeight + 
			EVENTLISTFRAME_SPLITTERHEIGHT * lLogPixelsY / 96 * 2 + m_lEventKindListHeight &&
			point.x >= EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + m_lPropertyWidth + m_lVScrollBarWidth;
		// カーソルが垂直スプリッター上にあるか
		m_bSplitterMovingV =
			EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + m_lPropertyWidth + m_lVScrollBarWidth <= point.x &&
			point.x < EVENTLISTFRAME_BORDERWIDTH * 2 + m_lScaleWidth + m_lPropertyWidth + m_lVScrollBarWidth +
			EVENTLISTFRAME_SPLITTERWIDTH * lLogPixelsX / 96;
		// カーソルが水平スプリッターと垂直スプリッターの交差部にある場合
		if (m_bSplitterMovingH && m_bSplitterMovingV ||
			m_bSplitterMovingH2 && m_bSplitterMovingV) {
			::SetCursor (pSekaijuApp->m_hCursorResizeAll);
		}
		// カーソルが水平スプリッター上にある場合
		else if (m_bSplitterMovingH || m_bSplitterMovingH2) {
			::SetCursor (pSekaijuApp->m_hCursorResizeNS);
		}
		// カーソルが垂直スプリッター上にある場合
		else if (m_bSplitterMovingV) {
			::SetCursor (pSekaijuApp->m_hCursorResizeWE);
		}
		// カーソルがスプリッターにない場合
		else {
			::SetCursor (pSekaijuApp->m_hCursorArrow);
		}
	}

}

// 列方向ズームダウン(20091220:左端位置保持機能追加)
void CEventListFrame::OnColumnZoomDown () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lOldColumnZoom = m_lColumnZoom;
	long lOldColumnPos = m_wndColumnScroll.GetScrollPos ();
	long lNewColumnZoom = CLIP (2, m_lColumnZoom - 1, 16);
	long lNewColumnPos = lOldColumnPos * lNewColumnZoom / lOldColumnZoom;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	m_lColumnZoom = lNewColumnZoom;
	RecalcColumnScrollInfo (lLogPixelsX);
	m_wndColumnScroll.SetScrollPos (lNewColumnPos);
	m_lColumnScrollPos = m_wndColumnScroll.GetScrollPos ();
	m_pPropertyScaleView->Invalidate ();
	//long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	//long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lCurRow, lCurColumn);
	m_pIndexPropertyView->Invalidate ();
	m_pIndexPropertyView->SetFocus ();
	pSekaijuDoc->m_theCriticalSection.Unlock ();
}

// 列方向ズームアップ(20091220:左端位置保持機能追加)
void CEventListFrame::OnColumnZoomUp () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lOldColumnZoom = m_lColumnZoom;
	long lOldColumnPos = m_wndColumnScroll.GetScrollPos ();
	long lNewColumnZoom = CLIP (2, m_lColumnZoom + 1, 16);
	long lNewColumnPos = lOldColumnPos * lNewColumnZoom / lOldColumnZoom;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	m_lColumnZoom = lNewColumnZoom;
	RecalcColumnScrollInfo (lLogPixelsX);
	m_wndColumnScroll.SetScrollPos (lNewColumnPos);
	m_lColumnScrollPos = m_wndColumnScroll.GetScrollPos ();
	m_pPropertyScaleView->Invalidate ();
	//long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	//long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lCurRow, lCurColumn);
	m_pIndexPropertyView->Invalidate ();
	m_pIndexPropertyView->SetFocus ();
	pSekaijuDoc->m_theCriticalSection.Unlock ();
}

// 行方向ズームダウン(20091220:上端位置保持機能追加、自動ページ更新自動オフ追加)
void CEventListFrame::OnRowZoomDown () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lOldRowZoom = m_lRowZoom;
	long lOldRowPos = m_wndRowScroll.GetScrollPos ();
	long lNewRowZoom = CLIP (16, m_lRowZoom - 2, 32);
	long lNewRowPos = lOldRowPos * lNewRowZoom / lOldRowZoom;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	m_bAutoPageUpdate = FALSE;
	m_lRowZoom = lNewRowZoom;
	RecalcRowScrollInfo (lLogPixelsY);
	m_wndRowScroll.SetScrollPos (lNewRowPos);
	m_lRowScrollPos = m_wndRowScroll.GetScrollPos ();
	m_pIndexScaleView->Invalidate ();
	//long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	//long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lCurRow, lCurColumn);
	m_pIndexPropertyView->Invalidate ();
	m_pIndexPropertyView->SetFocus ();
	pSekaijuDoc->m_theCriticalSection.Unlock ();
}

// 行方向ズームアップ(20091220:上端位置保持機能追加、自動ページ更新自動オフ追加)
void CEventListFrame::OnRowZoomUp () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();

	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lOldRowZoom = m_lRowZoom;
	long lOldRowPos = m_wndRowScroll.GetScrollPos ();
	long lNewRowZoom = CLIP (16, m_lRowZoom + 2, 32);
	long lNewRowPos = lOldRowPos * lNewRowZoom / lOldRowZoom;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	m_bAutoPageUpdate = FALSE;
	m_lRowZoom = lNewRowZoom;
	RecalcRowScrollInfo (lLogPixelsY);
	m_wndRowScroll.SetScrollPos (lNewRowPos);
	m_lRowScrollPos = m_wndRowScroll.GetScrollPos ();
	m_pIndexScaleView->Invalidate ();
	//long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	//long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lCurRow, lCurColumn);
	//((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lCurRow, lCurColumn);
	m_pIndexPropertyView->Invalidate ();
	m_pIndexPropertyView->SetFocus ();
	pSekaijuDoc->m_theCriticalSection.Unlock ();
}

// 水平スクロール
void CEventListFrame::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	if (pScrollBar == &m_wndColumnScroll) {
		SCROLLINFO si;
		pScrollBar->GetScrollInfo (&si, SIF_ALL);
		long lNewPos = m_lColumnScrollPos;
		switch (nSBCode) {
		case SB_LINELEFT:
			lNewPos = m_lColumnScrollPos - m_lColumnZoom;
			break;
		case SB_LINERIGHT:
			lNewPos = m_lColumnScrollPos + m_lColumnZoom;
			break;
		case SB_PAGELEFT:
			lNewPos = m_lColumnScrollPos - m_lColumnZoom * 4;
			break;
		case SB_PAGERIGHT:
			lNewPos = m_lColumnScrollPos + m_lColumnZoom * 4;
			break;
		case SB_LEFT:
			lNewPos = si.nMin;
			break;
		case SB_RIGHT:
			lNewPos = si.nMax;
			break;
		case SB_THUMBTRACK:
			lNewPos = si.nTrackPos;
			break;
		}
		SetColumnScrollPos (CLIP (0, lNewPos, 0x7FFFFFFF));
		m_pIndexPropertyView->SetFocus ();
	}
	pSekaijuDoc->m_theCriticalSection.Unlock ();
}

// 垂直スクロール
void CEventListFrame::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	if (pScrollBar == &m_wndRowScroll) {
		SCROLLINFO si;
		pScrollBar->GetScrollInfo (&si, SIF_ALL);
		long lNewPos = m_lRowScrollPos;
		switch (nSBCode) {
		case SB_LINEUP:
			lNewPos = m_lRowScrollPos - m_lRowZoom * lLogPixelsY / 96;
			break;
		case SB_LINEDOWN:
			lNewPos = m_lRowScrollPos + m_lRowZoom * lLogPixelsY / 96;
			break;
		case SB_PAGEUP:
			lNewPos = m_lRowScrollPos -
				__max (1, GetVisibleBottomRow (lLogPixelsY) - GetVisibleTopRow (lLogPixelsY)) * m_lRowZoom;
			break;
		case SB_PAGEDOWN:
			lNewPos = m_lRowScrollPos + 
				__max (1, GetVisibleBottomRow (lLogPixelsY) - GetVisibleTopRow (lLogPixelsY)) * m_lRowZoom;
			break;
		case SB_TOP:
			lNewPos = si.nMin;
			break;
		case SB_BOTTOM:
			lNewPos = si.nMax;
			break;
		case SB_THUMBTRACK:
			lNewPos = si.nTrackPos;
			break;
		}
		SetRowScrollPos (CLIP (0, lNewPos, 0x7FFFFFFF));
		m_bAutoPageUpdate = FALSE;
		m_pIndexPropertyView->SetFocus ();
	}
	pSekaijuDoc->m_theCriticalSection.Unlock ();
}


// 『ツール(&T)』-『イベントの挿入(&I)』
void CEventListFrame::OnEventListInsertEvent () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();

	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		return;
	}
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	CString strText;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;

	// 挿入トラック
	long lTargetTrackIndex = m_wndEventTrackCombo.GetCurSel ();
	MIDITrack* pTargetTrack = pSekaijuDoc->GetTrack (lTargetTrackIndex);
	if (pTargetTrack == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_INSERT_THE_EVENT_TO_THIS_TRACK));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 挿入時刻
	long lTargetTime = 0;
	m_wndEventTimeEdit.GetWindowText (strText);
	long lErrorID = pSekaijuDoc->StringTimeToLongTime (pMIDIData, strText, &lTargetTime);
	if (lErrorID > 0) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (lErrorID));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 挿入イベントの種類
	long lTargetKindIndex = m_wndEventKindCombo.GetCurSel ();
	long lTargetKind = ListIndextoEventKind (lTargetKindIndex);
	ASSERT (0x00 <= lTargetKind && lTargetKind <= 0xFF);
	
	// 既にEOTがある場合、EOTの二重挿入はできない。
	if (lTargetKind == MIDIEVENT_ENDOFTRACK) {
		MIDIEvent* pLastEvent = MIDITrack_GetLastEvent (pTargetTrack);
		if (pLastEvent) {
			if (MIDIEvent_IsEndofTrack (pLastEvent)) {
				pSekaijuDoc->m_theCriticalSection.Unlock ();
				CString strMsg;
				VERIFY (strMsg.LoadString (IDS_UNABLE_TO_INSERT_ENDOFTRACK_TO_THIS_TRACK_ANY_MORE));
				AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
				return;
			}
		}
	}

	// MIDIチャンネルイベントの場合はチャンネル情報無視
	if (0x80 <= lTargetKind && lTargetKind <= 0xEF) {
		lTargetKind &= 0xF0; 
	}

	// フォーマット1のMIDIデータに対するイベント種類の正当性検査
	long lFormat = MIDIData_GetFormat (pMIDIData);
	if (lFormat == 1) {
		// 最初のトラックの場合
		if (pTargetTrack == MIDIData_GetFirstTrack (pMIDIData)) {
			if (0x80 <= lTargetKind && lTargetKind <= 0xEF) {
				pSekaijuDoc->m_theCriticalSection.Unlock ();
				CString strMsg;
				VERIFY (strMsg.LoadString (IDS_UNABLE_TO_INSERT_THIS_EVENT_TO_THE_FIRST_TRACK_IN_FORMAT1_MIDIDATA));
				AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
				return;
			}
		}
		// 2番目以降のトラックの場合
		else {
			if (lTargetKind == MIDIEVENT_TEMPO ||
				lTargetKind == MIDIEVENT_SMPTEOFFSET ||
				lTargetKind == MIDIEVENT_TIMESIGNATURE ||
				lTargetKind == MIDIEVENT_KEYSIGNATURE) {
				pSekaijuDoc->m_theCriticalSection.Unlock ();
				CString strMsg;
				VERIFY (strMsg.LoadString (IDS_UNABLE_TO_INSERT_THIS_EVENT_TO_THE_SECOND_TRACK_IN_FORMAT1_MIDIDATA));
				AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
				return;
			}
		}
	}
	
	// ノートオフはノートオン+ノートオフイベントに修正
	if (0x80 <=lTargetKind && lTargetKind <= 0x8F) {
		lTargetKind = MIDIEVENT_NOTEONNOTEOFF;
	}
	// ノートオンはノートオン+ノートオン0イベントに修正
	else if (0x90 <=lTargetKind && lTargetKind <= 0x9F) {
		lTargetKind = MIDIEVENT_NOTEONNOTEON0;
	}

	// 挿入チャンネル
	long lTargetCh = m_wndEventChannelCombo.GetCurSel () - 1;

	long i = 0;
	long lRet = 0;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;

	// 新しいイベントの作成
	MIDIEvent* pNewMIDIEvent = MIDIEvent_CreateTextEvent (lTargetTime, _T(""));
	if (pNewMIDIEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_INSUFFICIENT_MEMORY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	// イベントの種類を変更
	MIDIEvent_SetKind (pNewMIDIEvent, lTargetKind);

	// MIDIイベントの場合チャンネルを変更する。
	if (MIDIEvent_IsMIDIEvent (pNewMIDIEvent) && 0 <= lTargetCh && lTargetCh < 16) {
		MIDIEvent_SetChannel (pNewMIDIEvent, lTargetCh);
	}

	// ノートイベントで長さ0以下の場合長さは4分音符とする。
	if (MIDIEvent_IsNoteOn (pNewMIDIEvent) && MIDIEvent_IsNote (pNewMIDIEvent)) {
		if (MIDIEvent_GetDuration (pNewMIDIEvent) <= 0) {
			long lNewDuration = MIDIData_GetTimeResolution (pSekaijuDoc->m_pMIDIData);
			MIDIEvent_SetDuration (pNewMIDIEvent, CLIP (1, lNewDuration, 65535));
		}
	}

	// 履歴の保持
	CHistoryUnit* pCurHistoryUnit = NULL;
	CString strHistoryName;
	VERIFY (strHistoryName.LoadString (IDS_INSERT_EVENT));
	VERIFY (pSekaijuDoc->AddHistoryUnit (strHistoryName));
	VERIFY (pCurHistoryUnit = pSekaijuDoc->GetCurHistoryUnit ());
	MIDIEvent* pLastEvent = MIDITrack_GetLastEvent (pTargetTrack);
	MIDIEvent* pNewLastEvent = NULL;
	if (pLastEvent) {
		if (MIDIEvent_IsEndofTrack (pLastEvent)) {
			VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_REMOVEEVENT, pLastEvent));
			VERIFY (pNewLastEvent = pSekaijuDoc->ReplaceMIDIEvent (pLastEvent));
			this->ReplaceVisibleEvent (pLastEvent, pNewLastEvent);
		}
	}

	// ターゲットタイムより挿入する直前又は直後のイベントを取得(20100226修正)
	MIDIEvent* pTargetMIDIEvent = NULL;
	// 同時刻イベントの後方に挿入する場合(20100226修正)
	if (pSekaijuApp->m_theEventListOption.m_bInsertEventAfter) {
		MIDIEvent* pEvent = NULL;
		forEachEventInverse (pTargetTrack, pEvent) {
			long lTime = MIDIEvent_GetTime (pEvent);
			if (lTime <= lTargetTime && !MIDIEvent_IsEndofTrack (pEvent)) {
				break;
			}
		}
		pTargetMIDIEvent = pEvent;
	}
	// 同時刻イベントの前方に挿入する場合(20100226修正)
	else {
		MIDIEvent* pEvent = NULL;
		forEachEvent (pTargetTrack, pEvent) {
			long lTime = MIDIEvent_GetTime (pEvent);
			if (lTime == lTargetTime && !MIDIEvent_IsNoteOff (pEvent) ||
				lTime > lTargetTime) {
				break;
			}
		}
		pTargetMIDIEvent = pEvent;
	}

	// ターゲットトラックへ新しいイベントを挿入する(20100226修正)
	if (pSekaijuApp->m_theEventListOption.m_bInsertEventAfter) { // 20090226追加
		lRet = MIDITrack_InsertEventAfter (pTargetTrack, pNewMIDIEvent, pTargetMIDIEvent);
	}
	else { // 20090226追加
		lRet = MIDITrack_InsertEventBefore (pTargetTrack, pNewMIDIEvent, pTargetMIDIEvent);
	}
	if (lRet == 0) {
		MIDIEvent_Delete (pNewMIDIEvent);
		if (pNewLastEvent) {
			VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewLastEvent));
		}
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_INSERT_EVENT_FAILED));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	
	// 履歴の保持
	VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewMIDIEvent));
	if (pNewLastEvent) {
		VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewLastEvent));
	}

	// 指定したトラックが非表示の場合、表示状態にする。
	if (IsTrackVisible (lTargetTrackIndex) == FALSE) {
		this->SetTrackVisible (lTargetTrackIndex);
	}
	// 指定したイベントの種類が非表示の場合、表示状態にする。
	if (IsEventKindVisible (lTargetKindIndex) == FALSE) {
		this->SetEventKindVisible (lTargetKindIndex);
	}
	// ビューの更新
	pSekaijuDoc->UpdateAllViews (NULL, SEKAIJUDOC_MIDIEVENTCHANGED);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// 行方向スクロール情報の更新
	this->RecalcRowScrollInfo (lLogPixelsY);
	// フォーカスを新しいイベントに合わせる。
	INT_PTR lCount = GetVisibleEventCount ();
	for (i = 0; i < lCount; i++) {
		if (m_theVisibleEventArray.GetAt (i) == pNewMIDIEvent) {
			long j = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = i;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (i, j, lLogPixelsX, lLogPixelsY);
			m_bAutoPageUpdate = FALSE;
			break;
		}
	}
	return;
}

// 『ツール(&T)』-『イベントの挿入(&I)』
void CEventListFrame::OnUpdateEventListInsertEventUI (CCmdUI* pCmdUI) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		pCmdUI->Enable (FALSE);
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		pCmdUI->Enable (FALSE);
		return;
	}
	INT_PTR lCount = GetVisibleEventCount ();
	INT_PTR lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	if (0 <= lCurRow && lCurRow < lCount) {
		pCmdUI->Enable (TRUE);
	}
	else {
		pCmdUI->Enable (FALSE);
	}
}

// 『ツール(&T)』-『イベントの複写(&D)』
void CEventListFrame::OnEventListDuplicateEvent () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording) {
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		return;
	}
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);
	
	CString strText;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;

	long i = 0;
	long lRet = 0;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	MIDIEvent* pSrcMIDIEvent = NULL;
	MIDIEvent* pSrcPrevEvent = NULL;
	MIDIEvent* pSrcNextEvent = NULL;
	MIDITrack* pSrcMIDITrack = NULL;
	MIDIEvent* pNewMIDIEvent = NULL;
	pSrcMIDIEvent = GetVisibleEvent (lCurRow);
	
	// 複写元イベントチェック
	if (pSrcMIDIEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_CURRENT_MIDIEVENT_IS_EMPTY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	pSrcMIDIEvent = MIDIEvent_GetFirstCombinedEvent (pSrcMIDIEvent); // 20100226追加
	pSrcPrevEvent = GetVisibleEvent (lCurRow - 1);
	pSrcNextEvent = GetVisibleEvent (lCurRow + 1);
	pSrcMIDITrack = MIDIEvent_GetParent (pSrcMIDIEvent);
	long lSrcTime = MIDIEvent_GetTime (pSrcMIDIEvent);
	long lSrcTrackIndex = pSekaijuDoc->GetTrackIndex (pSrcMIDITrack);
	long lSrcEventKind = MIDIEvent_GetKind (pSrcMIDIEvent);
	long lSrcKindIndex = EventKindtoListIndex (lSrcEventKind);

	// 既にEOTがある場合、EOTの二重挿入はできない。
	if (lSrcEventKind == MIDIEVENT_ENDOFTRACK) {
		MIDIEvent* pLastEvent = MIDITrack_GetLastEvent (pSrcMIDITrack);
		if (pLastEvent) {
			if (MIDIEvent_IsEndofTrack (pLastEvent)) {
				pSekaijuDoc->m_theCriticalSection.Unlock ();
				CString strMsg;
				VERIFY (strMsg.LoadString (IDS_UNABLE_TO_INSERT_ENDOFTRACK_TO_THIS_TRACK_ANY_MORE));
				AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
				return;
			}
		}
	}

	// 新しいイベントの作成
	pNewMIDIEvent = MIDIEvent_CreateClone (pSrcMIDIEvent);
	if (pNewMIDIEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_INSUFFICIENT_MEMORY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// ノートイベントで長さ0以下の場合長さは4分音符とする。
	if (MIDIEvent_IsNoteOn (pNewMIDIEvent) && MIDIEvent_IsNote (pNewMIDIEvent)) {
		if (MIDIEvent_GetDuration (pNewMIDIEvent) <= 0) {
			long lNewDur = MIDIData_GetTimeResolution (pSekaijuDoc->m_pMIDIData);
			MIDIEvent_SetDuration (pNewMIDIEvent, CLIP (1, lNewDur, 65535));
		}
	}

	// 履歴の保持
	CHistoryUnit* pCurHistoryUnit = NULL;
	CString strHistoryName;
	VERIFY (strHistoryName.LoadString (IDS_INSERT_EVENT));
	VERIFY (pSekaijuDoc->AddHistoryUnit (strHistoryName));
	VERIFY (pCurHistoryUnit = pSekaijuDoc->GetCurHistoryUnit ());
	MIDIEvent* pLastEvent = MIDITrack_GetLastEvent (pSrcMIDITrack);
	MIDIEvent* pNewLastEvent = NULL;
	if (pLastEvent) {
		if (MIDIEvent_IsEndofTrack (pLastEvent)) {
			VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_REMOVEEVENT, pLastEvent));
			VERIFY (pNewLastEvent = pSekaijuDoc->ReplaceMIDIEvent (pLastEvent));
			this->ReplaceVisibleEvent (pLastEvent, pNewLastEvent);
		}
	}

	// ReplaceEventによるイベント交換が起こったため複写元イベント再設定
	pSrcMIDIEvent = GetVisibleEvent (lCurRow);
	pSrcMIDIEvent = MIDIEvent_GetFirstCombinedEvent (pSrcMIDIEvent); // 20100226追加
	pSrcPrevEvent = GetVisibleEvent (lCurRow - 1);
	pSrcNextEvent = GetVisibleEvent (lCurRow + 1);
	lSrcTime = MIDIEvent_GetTime (pSrcMIDIEvent);
	if (pSrcMIDIEvent) {
		pSrcMIDITrack = MIDIEvent_GetParent (pSrcMIDIEvent);
	}

	// 挿入先トラックへ新しいイベントを挿入する
	if (pSekaijuApp->m_theEventListOption.m_bDuplicateEventAfter) { // 20100226追加
		lRet = MIDITrack_InsertEventAfter (pSrcMIDITrack, pNewMIDIEvent, pSrcMIDIEvent);
	}
	else { // 20100226追加
		lRet = MIDITrack_InsertEventBefore (pSrcMIDITrack, pNewMIDIEvent, pSrcMIDIEvent);
	}
	if (lRet == 0) {
		MIDIEvent_Delete (pNewMIDIEvent);
		if (pNewLastEvent) {
			VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewLastEvent));
		}
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_MIDIEVENT_DUPLICATE_FAILED));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 履歴の保持
	VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewMIDIEvent));
	if (pNewLastEvent) {
		VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewLastEvent));
	}

	// 指定したトラックが非表示の場合、表示状態にする。
	if (IsTrackVisible (lSrcTrackIndex) == FALSE) {
		this->SetTrackVisible (lSrcTrackIndex);
	}
	// 指定したイベントの種類が非表示の場合、表示状態にする。
	if (IsEventKindVisible (lSrcKindIndex) == FALSE) {
		this->SetEventKindVisible (lSrcKindIndex);
	}
	// ビューの更新
	pSekaijuDoc->UpdateAllViews (NULL, SEKAIJUDOC_MIDIEVENTCHANGED);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// 行方向スクロール情報の更新
	this->RecalcRowScrollInfo (lLogPixelsY);
	// フォーカスを新しいイベントに合わせる。
	INT_PTR lCount = GetVisibleEventCount ();
	for (i = 0; i < lCount; i++) {
		if (m_theVisibleEventArray.GetAt (i) == pNewMIDIEvent) {
			long j = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = i;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (i, j, lLogPixelsX, lLogPixelsY);
			m_bAutoPageUpdate = FALSE;
			break;
		}
	}
	return;
}


// 『ツール(&T)』-『イベントの複写(&D)』
void CEventListFrame::OnUpdateEventListDuplicateEventUI (CCmdUI* pCmdUI) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		pCmdUI->Enable (FALSE);
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		pCmdUI->Enable (FALSE);
		return;
	}
	INT_PTR lCount = GetVisibleEventCount ();
	INT_PTR lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	if (0 <= lCurRow && lCurRow < lCount) {
		pCmdUI->Enable (TRUE);
	}
	else {
		pCmdUI->Enable (FALSE);
	}
}


// 『ツール(&T)』-『イベントを1行削除(&D)』
void CEventListFrame::OnEventListDeleteEvent () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		return;
	}
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	MIDIEvent* pSrcMIDIEvent = NULL;
	MIDIEvent* pSrcPrevEvent = NULL;
	MIDIEvent* pSrcPrevPrevEvent = NULL;
	MIDIEvent* pSrcNextEvent = NULL;
	MIDIEvent* pSrcNextNextEvent = NULL;
	long lCount = INT_PTRtolong (GetVisibleEventCount ());
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	// 削除するイベントの特定
	if (0 <= lCurRow && lCurRow < lCount) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		pSekaijuDoc->m_theCriticalSection.Lock ();
		pSrcMIDIEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow));
		if (lCurRow >= 1) {
			pSrcPrevEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow - 1));
		}
		if (lCurRow >= 2) {
			pSrcPrevPrevEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow - 2));
		}
		if (lCurRow < lCount - 1) {
			pSrcNextEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow + 1));
		}
		if (lCurRow < lCount - 2) {
			pSrcNextNextEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow + 2));
		}
		// トラック最後のエンドオブトラックイベントは削除できない。
		if (MIDIEvent_IsEndofTrack (pSrcMIDIEvent) && MIDIEvent_GetNextEvent (pSrcMIDIEvent) == NULL) {
			pSekaijuDoc->m_theCriticalSection.Unlock ();
			CString strMsg;
			VERIFY (strMsg.LoadString (IDS_UNABLE_TO_DELETE_THE_LAST_ENDOFTRACK_IN_A_TRACK));
			AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
			return;
		}
		// 履歴記録
		CHistoryUnit* pCurHistoryUnit = NULL;
		CString strHistoryName;
		VERIFY (strHistoryName.LoadString (IDS_DELETE_EVENT));
		VERIFY (pSekaijuDoc->AddHistoryUnit (strHistoryName));
		VERIFY (pCurHistoryUnit = pSekaijuDoc->GetCurHistoryUnit ());
		VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_REMOVEEVENT, pSrcMIDIEvent));

		// イベントを除去
		MIDITrack* pSrcMIDITrack = MIDIEvent_GetParent (pSrcMIDIEvent);
		MIDITrack_RemoveEvent (pSrcMIDITrack, pSrcMIDIEvent);
		// ビューの更新
		pSekaijuDoc->UpdateAllViews (NULL, SEKAIJUDOC_MIDIEVENTCHANGED);
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		// 行方向スクロール情報の更新
		RecalcRowScrollInfo (lLogPixelsY);	
		// 直前のイベントにフォーカスを合わせる
		if (!pSekaijuApp->m_theEventListOption.m_bDeleteEventAfter) {
			// 前のイベントがあればそれにフォーカスを合わせる。
			if (pSrcPrevEvent != NULL) {
				long Count = INT_PTRtolong (GetVisibleEventCount ());
				for (long i = 0; i < lCount; i++) {
					if (m_theVisibleEventArray.GetAt (i) == pSrcPrevEvent) {
						long lRow = i;
						long lCol = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = lRow;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lRow, lCol, lLogPixelsX, lLogPixelsY);
						m_bAutoPageUpdate = FALSE;
						break;
					}
				}
			}
			// 前のイベントはないが、前の前のイベントがあればそれにフォーカスを合わせる。
			else if (pSrcPrevPrevEvent != NULL) {
				long lCount = INT_PTRtolong (GetVisibleEventCount ());
				for (long i = 0; i < lCount; i++) {
					if (m_theVisibleEventArray.GetAt (i) == pSrcPrevPrevEvent) {
						long lRow = i;
						long lCol = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = lRow;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lRow, lCol, lLogPixelsX, lLogPixelsY);
						m_bAutoPageUpdate = FALSE;
						break;
					}
				}
			}
			// 上記のいずれでもない場合、同じインデックスのものにフォーカスを合わせる。
		}
		// 直後のイベントにフォーカスを合わせる
		else {
			// 次のイベントがあればそれにフォーカスを合わせる。
			if (pSrcNextEvent != NULL) {
				long lCount = INT_PTRtolong (GetVisibleEventCount ());
				for (long i = 0; i < lCount; i++) {
					if (m_theVisibleEventArray.GetAt (i) == pSrcNextEvent) {
						long lRow = i;
						long lCol = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = lRow;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lRow, lCol, lLogPixelsX, lLogPixelsY);
						m_bAutoPageUpdate = FALSE;
						break;
					}
				}
			}
			// 次のイベントはないが、次の次のイベントがあればそれにフォーカスを合わせる。
			else if (pSrcNextNextEvent != NULL) {
				long lCount = INT_PTRtolong (GetVisibleEventCount ());
				for (long i = 0; i < lCount; i++) {
					if (m_theVisibleEventArray.GetAt (i) == pSrcNextNextEvent) {
						long lRow = i;
						long lCol = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = lRow;
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (lRow, lCol, lLogPixelsX, lLogPixelsY);
						((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lRow, lCol, lLogPixelsX, lLogPixelsY);
						m_bAutoPageUpdate = FALSE;
						break;
					}
				}
			}
			// 上記のいずれでもない場合、同じインデックスのものにフォーカスを合わせる。
		}
		// 20201102:テンポイベントが削除された場合は、時:分:秒:ミリ秒と演奏速度を更新する。
		if (MIDIEvent_IsTempo (pSrcMIDIEvent)) {
			// MIDIクロックの状態更新
			if (pSekaijuApp->m_bPlaying) {
				MIDIClock_Stop (pSekaijuDoc->m_pMIDIClock);
			}
			long lValue = 60000000;
			long lCurTime = MIDIClock_GetTickCount (pSekaijuDoc->m_pMIDIClock);
			long lMillisec = MIDIData_TimeToMillisec (pSekaijuDoc->m_pMIDIData, lCurTime);
			MIDIClock_SetMillisec (pSekaijuDoc->m_pMIDIClock, lMillisec);
			MIDIData_FindTempo (pSekaijuDoc->m_pMIDIData, lCurTime, &lValue); // 20200822修正
			MIDIClock_SetTempo (pSekaijuDoc->m_pMIDIClock, lValue);
			if (pSekaijuApp->m_bPlaying) {
				MIDIClock_Start (pSekaijuDoc->m_pMIDIClock);
			}
		}

	}
	// 何もない行は削除できない。
	else {
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_CURRENT_MIDIEVENT_IS_EMPTY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
}

// 『ツール(&T)』-『イベントを1行削除(&D)』
void CEventListFrame::OnUpdateEventListDeleteEventUI (CCmdUI* pCmdUI) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		pCmdUI->Enable (FALSE);
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		pCmdUI->Enable (FALSE);
		return;
	}
	MIDIEvent* pMIDIEvent = NULL;
	INT_PTR lCount = GetVisibleEventCount ();
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	if (0 <= lCurRow && lCurRow < CLIP (0, lCount, 0x7FFFFFFF)) {
		pMIDIEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow));
		if (MIDIEvent_IsEndofTrack (pMIDIEvent) && MIDIEvent_GetNextEvent (pMIDIEvent) == NULL) {
			pCmdUI->Enable (FALSE);
		}
		else {
			pCmdUI->Enable (TRUE);
		}
	}
	else {
		pCmdUI->Enable (FALSE);
	}

}


void CEventListFrame::OnEventListMoveUpEvent () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		return;
	}
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);
	
	CString strText;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;

	long i = 0;
	long lRet = 0;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	INT_PTR lCount = GetVisibleEventCount ();
	MIDIEvent* pMIDIEvent = NULL;
	MIDIEvent* pPrevEvent = NULL;
	MIDITrack* pMIDITrack = NULL;
	MIDIEvent* pNewMIDIEvent = NULL;

	// 移動元イベントの取得
	pMIDIEvent = GetVisibleEvent (lCurRow);
	if (pMIDIEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_CURRENT_MIDIEVENT_IS_EMPTY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	
	// 結合されたイベント(ノートオン+ノートオフなど)は移動不可能
	if (MIDIEvent_IsCombined (pMIDIEvent)) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_MOVE_THIS_EVENT));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;		
	};

	// 最後のEOTは移動できない
	if (MIDIEvent_IsEndofTrack (pMIDIEvent) && 
		MIDIEvent_GetPrevEvent (pMIDIEvent) == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_MOVE_THIS_EVENT));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// MIDIトラックの取得
	pMIDITrack = MIDIEvent_GetParent (pMIDIEvent);
	if (pMIDITrack == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_MIDIEVENT_MOVE_FAILED));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 移動先ターゲットイベントの取得(同一トラック内で)
	for (i = lCurRow - 1; i >= 0; i--) {
		pPrevEvent = GetVisibleEvent (i);
		if (MIDIEvent_GetParent (pPrevEvent) == pMIDITrack &&
			MIDIEvent_GetFirstCombinedEvent (pPrevEvent) != pMIDIEvent) {
			break;
		}
		pPrevEvent = NULL; // 20230103:修正追加
	}

	// 前のイベントがない場合、それ以上移動できない。
	if (pPrevEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_MOVE_THIS_EVENT_ANY_MORE));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 新しいイベントの作成
	pNewMIDIEvent = MIDIEvent_CreateClone (pMIDIEvent);
	if (pNewMIDIEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_INSUFFICIENT_MEMORY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 履歴の保持
	CHistoryUnit* pCurHistoryUnit = NULL;
	CString strHistoryName;
	VERIFY (strHistoryName.LoadString (IDS_MOVE_EVENT));
	VERIFY (pSekaijuDoc->AddHistoryUnit (strHistoryName));
	VERIFY (pCurHistoryUnit = pSekaijuDoc->GetCurHistoryUnit ());

	// 移動元イベントを除去
	VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_REMOVEEVENT, pMIDIEvent));
	lRet = MIDITrack_RemoveEvent (pMIDITrack, pMIDIEvent);

	// 新しいイベントを前の行に挿入
	lRet = MIDITrack_InsertEventBefore (pMIDITrack, pNewMIDIEvent, pPrevEvent);
	if (lRet == 0) {
		MIDIEvent_Delete (pNewMIDIEvent);
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_MIDIEVENT_MOVE_FAILED));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewMIDIEvent));

	// ビューの更新
	pSekaijuDoc->UpdateAllViews (NULL, SEKAIJUDOC_MIDIEVENTCHANGED);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// 行方向スクロール情報の更新
	this->RecalcRowScrollInfo (lLogPixelsY);
	// フォーカスを新しいイベントに合わせる。
	lCount = GetVisibleEventCount ();
	for (i = 0; i < lCount; i++) {
		if (m_theVisibleEventArray.GetAt (i) == pNewMIDIEvent) {
			long j = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = i;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (i, j, lLogPixelsX, lLogPixelsY);
			m_bAutoPageUpdate = FALSE;
			break;
		}
	}
	return;

}

// 『ツール(&T)』-『イベントを1行上へ(&D)』
void CEventListFrame::OnUpdateEventListMoveUpEventUI (CCmdUI* pCmdUI) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		pCmdUI->Enable (FALSE);
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		pCmdUI->Enable (FALSE);
		return;
	}
	MIDIEvent* pMIDIEvent = NULL;
	INT_PTR lCount = GetVisibleEventCount ();
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	if (0 <= lCurRow && lCurRow < CLIP(0, lCount, 0x7FFFFFFF)) {
		pMIDIEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow));
		if (MIDIEvent_IsEndofTrack (pMIDIEvent) && MIDIEvent_GetNextEvent (pMIDIEvent) == NULL) {
			pCmdUI->Enable (FALSE);
		}
		else {
			pCmdUI->Enable (TRUE);
		}
	}
	else {
		pCmdUI->Enable (FALSE);
	}

}

// 『ツール(&T)』-『イベントを1行下へ(&D)』
void CEventListFrame::OnEventListMoveDownEvent () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		return;
	}
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);
	
	CString strText;
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDIData* pMIDIData = pSekaijuDoc->m_pMIDIData;

	long i = 0;
	long lRet = 0;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	INT_PTR lCount = GetVisibleEventCount ();
	MIDIEvent* pMIDIEvent = NULL;
	MIDIEvent* pNextEvent = NULL;
	MIDITrack* pMIDITrack = NULL;
	MIDIEvent* pNewMIDIEvent = NULL;

	// 移動先イベントの取得
	pMIDIEvent = GetVisibleEvent (lCurRow);
	if (pMIDIEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_CURRENT_MIDIEVENT_IS_EMPTY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	
	// 結合されたイベント(ノートオン+ノートオフなど)は移動不可能
	if (MIDIEvent_IsCombined (pMIDIEvent)) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_MOVE_THIS_EVENT));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;		
	};

	// 最後のEOTは移動できない
	if (MIDIEvent_IsEndofTrack (pMIDIEvent) && 
		MIDIEvent_GetPrevEvent (pMIDIEvent) == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_MOVE_THIS_EVENT));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// MIDIトラックの取得
	pMIDITrack = MIDIEvent_GetParent (pMIDIEvent);
	if (pMIDITrack == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_MIDIEVENT_MOVE_FAILED));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 移動先ターゲットイベントの取得(同一トラック内で)
	for (i = lCurRow + 1; i < lCount; i++) {
		pNextEvent = GetVisibleEvent (i);
		if (MIDIEvent_GetParent (pNextEvent) == pMIDITrack &&
			MIDIEvent_GetFirstCombinedEvent (pNextEvent) != pMIDIEvent) {
			break;
		}
		pNextEvent = NULL; // 20230103:修正追加
	}

	// 次のイベントがない場合、それ以上移動できない。
	if (pNextEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_MOVE_THIS_EVENT_ANY_MORE));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 次のイベントが最後のEOTの場合、それ以上移動できない。
	if (MIDIEvent_IsEndofTrack (pNextEvent) &&
		MIDIEvent_GetNextEvent (pNextEvent) == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_UNABLE_TO_MOVE_THIS_EVENT_ANY_MORE));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 新しいイベントの作成
	pNewMIDIEvent = MIDIEvent_CreateClone (pMIDIEvent);
	if (pNewMIDIEvent == NULL) {
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_INSUFFICIENT_MEMORY));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 履歴の保持
	CHistoryUnit* pCurHistoryUnit = NULL;
	CString strHistoryName;
	VERIFY (strHistoryName.LoadString (IDS_MOVE_EVENT));
	VERIFY (pSekaijuDoc->AddHistoryUnit (strHistoryName));
	VERIFY (pCurHistoryUnit = pSekaijuDoc->GetCurHistoryUnit ());

	// 移動元イベントを除去
	VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_REMOVEEVENT, pMIDIEvent));
	lRet = MIDITrack_RemoveEvent (pMIDITrack, pMIDIEvent);

	// 新しいイベントを前の行に挿入
	lRet = MIDITrack_InsertEventAfter (pMIDITrack, pNewMIDIEvent, pNextEvent);
	if (lRet == 0) {
		MIDIEvent_Delete (pNewMIDIEvent);
		pSekaijuDoc->m_theCriticalSection.Unlock ();
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_MIDIEVENT_MOVE_FAILED));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	VERIFY (pCurHistoryUnit->AddHistoryRecord (HISTORYRECORD_INSERTEVENT, pNewMIDIEvent));

	// ビューの更新
	pSekaijuDoc->UpdateAllViews (NULL, SEKAIJUDOC_MIDIEVENTCHANGED);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// 行方向スクロール情報の更新
	this->RecalcRowScrollInfo (lLogPixelsY);
	// フォーカスを新しいイベントに合わせる。
	lCount = GetVisibleEventCount ();
	for (i = 0; i < lCount; i++) {
		if (m_theVisibleEventArray.GetAt (i) == pNewMIDIEvent) {
			long j = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow = i;
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveTextBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->MoveListBox (i, j, lLogPixelsX, lLogPixelsY);
			((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (i, j, lLogPixelsX, lLogPixelsY);
			m_bAutoPageUpdate = FALSE;
			break;
		}
	}
	return;
}

// 『ツール(&T)』-『イベントを1行下へ(&D)』
void CEventListFrame::OnUpdateEventListMoveDownEventUI (CCmdUI* pCmdUI) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		pCmdUI->Enable (FALSE);
		return;
	}
	// MIDIデータが編集ロックされている場合は何もしない。
	if (pSekaijuDoc->m_bEditLocked) {
		pCmdUI->Enable (FALSE);
		return;
	}
	MIDIEvent* pMIDIEvent = NULL;
	INT_PTR lCount = GetVisibleEventCount ();
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	if (0 <= lCurRow && lCurRow < CLIP (0, lCount, 0x7FFFFFFF)) {
		pMIDIEvent = (MIDIEvent*)(m_theVisibleEventArray.GetAt (lCurRow));
		if (MIDIEvent_IsEndofTrack (pMIDIEvent) && MIDIEvent_GetNextEvent (pMIDIEvent) == NULL) {
			pCmdUI->Enable (FALSE);
		}
		else {
			pCmdUI->Enable (TRUE);
		}
	}
	else {
		pCmdUI->Enable (FALSE);
	}

}


// 『ツール(&T)』-『現在のトラックのみ表示(&C)』
void CEventListFrame::OnEventListOnlyCurTrack () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	int nCount = m_pTrackListBox->GetCount ();
	int nCurSel = m_pTrackListBox->GetCurSel ();
	if (m_bOnlyCurTrack) {
		m_bOnlyCurTrack = FALSE;
		m_bShowAllTrack = FALSE;
	}
	else {
		m_bOnlyCurTrack = TRUE;
		m_bShowAllTrack = FALSE;
	}
	for (int i = 0; i < nCount; i++) {
		m_pTrackListBox->SetCheck (i, IsTrackVisible (i) ? 1 : 0);
	}
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ツール(&T)』-『現在のトラックのみ表示(&C)』
void CEventListFrame::OnUpdateEventListOnlyCurTrackUI (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_bOnlyCurTrack);
}

// 『ツール(&T)』-『全てのトラックを表示(&A)』
void CEventListFrame::OnEventListShowAllTrack () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	int nCount = m_pTrackListBox->GetCount ();
	int nCurSel = m_pTrackListBox->GetCurSel ();
	if (m_bShowAllTrack) {
		m_bOnlyCurTrack = FALSE;
		m_bShowAllTrack = FALSE;
	}
	else {
		m_bOnlyCurTrack = FALSE;
		m_bShowAllTrack = TRUE;
	}
	for (int i = 0; i < nCount; i++) {
		m_pTrackListBox->SetCheck (i, IsTrackVisible (i) ? 1 : 0);
	}
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();

}	


// 『ツール(&T)』-『全てのトラックを表示(&A)』
void CEventListFrame::OnUpdateEventListShowAllTrackUI (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_bShowAllTrack);
}

// 『ツール(&T)』-『現在のイベントの種類のみ表示(&C)』
void CEventListFrame::OnEventListOnlyCurEventKind () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	int nCount = m_pEventKindListBox->GetCount ();
	int nCurSel = m_pEventKindListBox->GetCurSel ();
	if (m_bOnlyCurEventKind) {
		m_bOnlyCurEventKind = FALSE;
		m_bShowAllEventKind = FALSE;
	}
	else {
		m_bOnlyCurEventKind = TRUE;
		m_bShowAllEventKind = FALSE;
	}
	for (int i = 0; i < nCount; i++) {
		m_pEventKindListBox->SetCheck (i, IsEventKindVisible (i) ? 1 : 0);
	}
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ツール(&T)』-『現在のイベントの種類のみ表示(&C)』
void CEventListFrame::OnUpdateEventListOnlyCurEventKindUI (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_bOnlyCurEventKind);
}


// 『ツール(&T)』-『全てのイベントの種類を表示(&A)』
void CEventListFrame::OnEventListShowAllEventKind () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	int nCount = m_pEventKindListBox->GetCount ();
	int nCurSel = m_pEventKindListBox->GetCurSel ();
	if (m_bShowAllEventKind) {
		m_bOnlyCurEventKind = FALSE;
		m_bShowAllEventKind = FALSE;
	}
	else {
		m_bOnlyCurEventKind = FALSE;
		m_bShowAllEventKind = TRUE;
	}
	for (int i = 0; i < nCount; i++) {
		m_pEventKindListBox->SetCheck (i, IsEventKindVisible (i) ? 1 : 0);
	}
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ツール(&T)』-『全てのイベントの種類を表示(&A)』
void CEventListFrame::OnUpdateEventListShowAllEventKindUI (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_bShowAllEventKind);
}

// 『ツール(&T)』-『現在のコントロールチェンジのみ表示(&C)』
void CEventListFrame::OnEventListOnlyCurControlChange () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	int nCount = m_pControlChangeListBox->GetCount ();
	int nCurSel = m_pControlChangeListBox->GetCurSel ();
	if (m_bOnlyCurControlChange) {
		m_bOnlyCurControlChange = FALSE;
		m_bShowAllControlChange = FALSE;
	}
	else {
		m_bOnlyCurControlChange = TRUE;
		m_bShowAllControlChange = FALSE;
	}
	for (int i = 0; i < nCount; i++) {
		m_pControlChangeListBox->SetCheck (i, IsControlChangeVisible (i) ? 1 : 0);
	}
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ツール(&T)』-『現在のコントロールチェンジのみ表示(&C)』
void CEventListFrame::OnUpdateEventListOnlyCurControlChangeUI (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_bOnlyCurControlChange);
}

// 『ツール(&T)』-『全てのコントロールチェンジを表示(&A)』
void CEventListFrame::OnEventListShowAllControlChange () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	int nCount = m_pControlChangeListBox->GetCount ();
	int nCurSel = m_pControlChangeListBox->GetCurSel ();
	if (m_bShowAllControlChange) {
		m_bOnlyCurControlChange = FALSE;
		m_bShowAllControlChange = FALSE;
	}
	else {
		m_bOnlyCurControlChange = FALSE;
		m_bShowAllControlChange = TRUE;
	}
	for (int i = 0; i < nCount; i++) {
		m_pControlChangeListBox->SetCheck (i, IsControlChangeVisible (i) ? 1 : 0);
	}
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ツール(&T)』-『全てのコントロールチェンジを表示(&A)』
void CEventListFrame::OnUpdateEventListShowAllControlChangeUI (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_bShowAllControlChange);
}

// 『自動ページ更新』
void CEventListFrame::OnEventListAutoPageUpdate () {
	m_bAutoPageUpdate = !m_bAutoPageUpdate;
}

// 『自動ページ更新』
void CEventListFrame::OnUpdateEventListAutoPageUpdateUI (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_bAutoPageUpdate);
}

// 『イベントリストをCSV又はテキストで保存』
void CEventListFrame::OnEventListSaveAs () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		return;
	}

	CString strFileName;
	CSekaijuFileDlg theFileDlg (FALSE);

	CString strTitle;
	VERIFY (strTitle.LoadString (AFX_IDS_APP_TITLE));

	// 注意事項：MSDN2002/4のOPENFILENAME構造体の説明
	// For compatibility reasons, the Places Bar is hidden if Flags is set to 
	// OFN_ENABLEHOOK and lStructSize is OPENFILENAME_SIZE_VERSION_400.
	// CFileDialogクラスでは強制的にOFN_ENABLEHOOKでAfxCommDlgProcにフックする。

	// 20081028 : m_ofnの値の設定(76or88)は次による
	//#ifndef OPENFILENAME_SIZE_VERSION_400
	//    theFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME); //=76(Windows95/98/ME style)
	//#else
	//    theFileDlg.m_ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400; //=76(Windows95/98/ME style)
	//#endif
	
	#if (_WIN32_WINNT >= 0x0500)
	    theFileDlg.m_ofn.lStructSize = 88; //=88(With placebar)
		theFileDlg.m_ofn.pvReserved = NULL;
		theFileDlg.m_ofn.dwReserved = 0;
		theFileDlg.m_ofn.FlagsEx = 0;
	#else
	    theFileDlg.m_ofn.lStructSize = 76; //=76(Without placebar if OFN_ENABLEHOOK used)
	#endif

	theFileDlg.m_ofn.nMaxFileTitle = _MAX_PATH;
	
	//theFileDlg.m_ofn.Flags |= lFlags;

	CString strFilter;
	CString strDefault;
	CString strFilterCSV[3];
	CString strFilterTXT[3];
	VERIFY (strFilterCSV[0].LoadString (IDS_COMMA_SEPARATED_TEXT_FILES_AD_CSV));
	VERIFY (strFilterCSV[1].LoadString (IDS_AD_CSV));
	VERIFY (strFilterCSV[2].LoadString (IDS_D_CSV));
	VERIFY (strFilterTXT[0].LoadString (IDS_TAB_SEPARATED_TEXT_FILES_AD_TXT));
	VERIFY (strFilterTXT[1].LoadString (IDS_AD_TXT));
	VERIFY (strFilterTXT[2].LoadString (IDS_D_TXT));

	// 拡張子フィルター追加した部分
	strFilter += strFilterCSV[0]; // カンマ区切りテキストファイル(*.csv)
	strFilter += (TCHAR)_T('\0');
	strFilter += strFilterCSV[1]; // *.csv
	strFilter += (TCHAR)_T('\0');
	strFilter += strFilterTXT[0]; // タブ区切りテキストファイル(*.txt)
	strFilter += (TCHAR)_T('\0');
	strFilter += strFilterTXT[1]; // *.txt
	strFilter += (TCHAR)_T('\0');
	strFilter += (TCHAR)_T('\0');
	theFileDlg.m_ofn.nMaxCustFilter = 1024;

	theFileDlg.m_ofn.lpstrFilter = strFilter;
#ifndef _MAC
	theFileDlg.m_ofn.lpstrTitle = strTitle;
#else
	theFileDlg.m_ofn.lpstrPrompt = strTitle;
#endif

	// デフォルトの拡張子設定
	theFileDlg.m_strDefExt = strFilterCSV[2];
	theFileDlg.m_ofn.lpstrDefExt = theFileDlg.m_strDefExt;

	// フィルターコンボボックスのデフォルト選択
	if ((strFileName.Right (4)).CompareNoCase (strFilterCSV[2]) == 0) { // .csv
		theFileDlg.m_ofn.nFilterIndex = 1;
	}
	else if ((strFileName.Right (4)).CompareNoCase (strFilterTXT[2]) == 0) { // .txt
		theFileDlg.m_ofn.nFilterIndex = 2;
	}
	
	theFileDlg.m_ofn.lpstrFile = strFileName.GetBuffer(_MAX_PATH);

	// ファイルダイアログ.DoModal
	BOOL bResult = theFileDlg.DoModal() == IDOK ? TRUE : FALSE;

	strFileName.ReleaseBuffer();

	// 拡張子が付いていない場合は、選択したファイルタイプの拡張子を自動的に付ける
	if (theFileDlg.m_ofn.nFilterIndex == 1 &&
		(strFileName.Right (4)).CompareNoCase (strFilterCSV[2]) != 0) { // .csv
		strFileName += strFilterCSV[2];
	}
	else if (theFileDlg.m_ofn.nFilterIndex == 2 &&
		(strFileName.Right (4)).CompareNoCase (strFilterTXT[2]) != 0) { // .txt
		strFileName += strFilterTXT[2];
	}

	// キャンセルが押された場合は却下
	if (bResult == FALSE) {
		return;
	}

	// ビューがない場合は却下
	if (m_pIndexPropertyView == NULL) {
		CString strMsg;
		VERIFY (strMsg.LoadString (IDS_CURRENT_VIEW_IS_NOT_EXIST));
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION);
		return;
	}
	CEventListIndexPropertyView* pIndexPropertyView = (CEventListIndexPropertyView*)m_pIndexPropertyView;

	// 文字列バッファ確保
	CString strTextLine;
	CString strCell;
	CString strSeparator;
	if (theFileDlg.m_ofn.nFilterIndex == 1) {
		strSeparator = _T(", ");
	}
	else {
		strSeparator = _T("\t");
	}

	// テキストエンコーディングの取得
	CString strTextEncoding = pSekaijuApp->m_theLanguageDlgStatus.m_strTextEncoding;
	int nCodePage = _ttoi (strTextEncoding);

	// ファイルオープン
	CTextFile theFile;
	BOOL bRet = theFile.Open (strFileName, CFile::modeCreate | CFile::modeWrite);
	if (bRet == FALSE) {
		CString strMsg;
		CString strFormat;
		VERIFY (strFormat.LoadString (IDS_S_N_FILE_OPEN_FAILED));
		strMsg.Format (strFormat, strFileName);
		AfxMessageBox (strMsg, MB_ICONEXCLAMATION);
		return;
	}

	// BOMの書き込み
	theFile.WriteBOM (nCodePage);

	// 先頭行の文字列書き込み
	long j = 0;
	long jMax = 0;
	strTextLine.Format (_T(""));
	strTextLine += strSeparator;
	for (j = 0; j < 8; j++) {
		strCell = GetColumnTitle (j);
		strTextLine += strCell;
		if (j < 7) {
			strTextLine += strSeparator;
		}
		else {
			strTextLine += _T("\r\n");
		}
	}
	theFile.WriteText (strTextLine, nCodePage);

	// 各行の文字列書き込み
	long lRowCount = INT_PTRtolong (m_theVisibleEventArray.GetCount ());
	for (long i = 0; i < lRowCount; i++) {
		strTextLine.Format (_T("%d"), i + 1);
		strTextLine += strSeparator;
		MIDIEvent* pMIDIEvent = (MIDIEvent*)m_theVisibleEventArray.GetAt (i);
		long lKind = MIDIEvent_GetKind (pMIDIEvent);
		if (!MIDIEvent_IsMIDIEvent (pMIDIEvent)) {
			jMax = 6;
		}
		else {
			jMax = 8;
		}
		for (j = 0; j < jMax; j++) {
			strCell = pIndexPropertyView->GetCellString (i, j);
			strTextLine += strCell;
			if (j < jMax - 1) {
				strTextLine += strSeparator;
			}
			else {
				strTextLine += _T("\r\n");
			}
		}
		theFile.WriteText (strTextLine, nCodePage);
	}

	// ファイルクローズ
	theFile.Close ();
}	

// 『イベントリストをCSV又はテキストで保存』
void CEventListFrame::OnUpdateEventListSaveAsUI (CCmdUI* pCmdUI) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	// リアルタイム入力中は何もしない。
	if (pSekaijuApp->m_bRecording ||
		pSekaijuApp->m_bInplaceEditing ||
		pSekaijuApp->m_bInplaceListing ||
		pSekaijuApp->m_bValueUpDowning ||
		pSekaijuApp->m_bSALRunning) {
		pCmdUI->Enable (FALSE);
		return;
	}
}



// トラックコンボボックスが選択され終わった時
void CEventListFrame::OnTrackComboSelEndOK () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// カレントトラックを更新する
	long lCurTrackIndex = m_wndEventTrackCombo.GetCurSel ();
	SetCurTrackIndex (lCurTrackIndex, lLogPixelsX, lLogPixelsY);
	SetTrackVisible (lCurTrackIndex);
	// カレントチャンネルも更新する
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDITrack* pMIDITrack = pSekaijuDoc->GetTrack (lCurTrackIndex);
	if (pMIDITrack) {
		long lOutputChannel = MIDITrack_GetOutputChannel (pMIDITrack);
		if (0 <= lOutputChannel && lOutputChannel <= 15) {
			SetCurChannel (lOutputChannel);
		}
	}
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// ビューの作り直しと再描画
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();

}

// トラックインデックスリストのチェックボックスが変化したとき
void CEventListFrame::OnTrackListChkChange () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// トラックの表示／非表示をチェックボックスの状態に合わせる
	long lCount = m_pTrackListBox->GetCount ();
	long lCurSel = m_pTrackListBox->GetCurSel ();
	if (m_bOnlyCurTrack) {
		m_bOnlyCurTrack = FALSE;
	}
	for (long i = 0; i < lCount; i++) {
		m_bTrackVisible[i] = m_pTrackListBox->GetCheck (i);
		if (m_bTrackVisible[i] == FALSE) {
			m_bShowAllTrack = FALSE;
		}
	}
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// トラックインデックスの選択項目が変化したとき
void CEventListFrame::OnTrackListSelChange () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// カレントトラックを変更する
	long lCurTrackIndex = GetCurTrackIndex ();
	SetCurTrackIndex (lCurTrackIndex, lLogPixelsX, lLogPixelsY);
	// カレントチャンネルも更新する
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MIDITrack* pMIDITrack = pSekaijuDoc->GetTrack (lCurTrackIndex);
	if (pMIDITrack) {
		long lOutputChannel = MIDITrack_GetOutputChannel (pMIDITrack);
		if (0 <= lOutputChannel && lOutputChannel <= 15) {
			SetCurChannel (lOutputChannel);
		}
	}
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// ビューの作り直しと再描画
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// イベントの種類コンボボックスが選択され終わった時
void CEventListFrame::OnEventKindComboSelEndOK () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lCurEventKind = m_wndEventKindCombo.GetCurSel ();
	SetCurEventKind (lCurEventKind, lLogPixelsX, lLogPixelsY);
	SetEventKindVisible (lCurEventKind);
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// イベントの種類リストのチェックボックスが変化したとき
void CEventListFrame::OnEventKindListChkChange () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// グラフの表示／非表示をチェックボックスの状態に合わせる
	long lCount = m_pEventKindListBox->GetCount ();
	long lCurSel = m_pEventKindListBox->GetCurSel ();
	if (m_bOnlyCurEventKind) {
		m_bOnlyCurEventKind = FALSE;
	}
	//else { // 20110122削除
	for (long i = 0; i < lCount; i++) {
		m_bEventKindVisible[i] = m_pEventKindListBox->GetCheck (i);
		if (m_bEventKindVisible[i] == FALSE) {
			m_bShowAllEventKind = FALSE;
		}
	}
	//} // 20110122削除
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// イベントの種類リストの選択項目が変化したとき
void CEventListFrame::OnEventKindListSelChange () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// カレントイベントの種類を変更する。
	long lCurEventKind = GetCurEventKind ();
	SetCurEventKind (lCurEventKind, lLogPixelsX, lLogPixelsY);
}

// コントロールチェンジコンボボックスが選択され終わった時
/*void CEventListFrame::OnEventKindComboSelEndOK () {
	long lCurEventKind = m_wndEventKindCombo.GetCurSel ();
	SetCurEventKind (lCurEventKind);
	SetEventKindVisible (lCurEventKind);
	MakeVisibleEventArray ();
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}*/

// コントロールチェンジリストのチェックボックスが変化したとき
void CEventListFrame::OnControlChangeListChkChange () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	// グラフの表示／非表示をチェックボックスの状態に合わせる
	long lCount = m_pControlChangeListBox->GetCount ();
	long lCurSel = m_pControlChangeListBox->GetCurSel ();
	if (m_bOnlyCurControlChange) {
		m_bOnlyCurControlChange = FALSE;
	}
	//else { // 20110122削除
	for (long i = 0; i < lCount; i++) {
		m_bControlChangeVisible[i] = m_pControlChangeListBox->GetCheck (i);
		if (m_bControlChangeVisible[i] == FALSE) {
			m_bShowAllControlChange = FALSE;
		}
	}
	//} // 20110122削除
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// コントロールチェンジリストの選択項目が変化したとき
void CEventListFrame::OnControlChangeListSelChange () {
	// カレントコントロールチェンジを変更する。
	//long lCurControlChange = GetCurEventKind ();
	//SetCurControlChange (lCurControlChange);
}



// 『ポップアップ』-『このトラックのみ表示ON』
void CEventListFrame::OnPopupTrackVisibleOn () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	if (pSekaijuDoc->m_pTempTrack == NULL) {
		return;
	}
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lTrackIndex = pSekaijuDoc->GetTrackIndex (pSekaijuDoc->m_pTempTrack);
	long lCount = m_pTrackListBox->GetCount ();
	ASSERT (0 <= lTrackIndex && lTrackIndex < lCount);
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pTrackListBox->SetCheck (i, i == lTrackIndex ? 1 : 0);
		m_bTrackVisible[i] = (i == lTrackIndex ? TRUE : FALSE);
	}
	m_bOnlyCurTrack = FALSE;
	m_bShowAllTrack = FALSE;
	// カレントトラックとカレントチャンネルを更新
	if (m_bTrackVisible[lTrackIndex]) {
		SetCurTrackIndex (lTrackIndex, lLogPixelsX, lLogPixelsY);
		long lOutputChannel = MIDITrack_GetOutputChannel (pSekaijuDoc->m_pTempTrack);
		if (0 <= lOutputChannel && lOutputChannel <= 15) {
			SetCurChannel (lOutputChannel);
		}
	}
	// イベントリストの作り直し
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『このトラックのみ表示ON』
void CEventListFrame::OnUpdatePopupTrackVisibleOnUI (CCmdUI* pCmdUI) {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	if (pSekaijuDoc->m_pTempTrack == NULL) {
		pCmdUI->Enable (FALSE);
	}
}

// 『ポップアップ』-『このトラックのみ表示OFF』
void CEventListFrame::OnPopupTrackVisibleOff () {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	if (pSekaijuDoc->m_pTempTrack == NULL) {
		return;
	}
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lTrackIndex = pSekaijuDoc->GetTrackIndex (pSekaijuDoc->m_pTempTrack);
	long lCount = m_pTrackListBox->GetCount ();
	ASSERT (0 <= lTrackIndex && lTrackIndex < lCount);
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pTrackListBox->SetCheck (i, i == lTrackIndex ? 0 : 1);
		m_bTrackVisible[i] = (i == lTrackIndex ? FALSE : TRUE);
	}
	m_bOnlyCurTrack = FALSE;
	m_bShowAllTrack = FALSE;
	// カレントトラックとカレントチャンネルを更新
	if (m_bTrackVisible[lTrackIndex]) {
		SetCurTrackIndex (lTrackIndex, lLogPixelsX, lLogPixelsY);
		long lOutputChannel = MIDITrack_GetOutputChannel (pSekaijuDoc->m_pTempTrack);
		if (0 <= lOutputChannel && lOutputChannel <= 15) {
			SetCurChannel (lOutputChannel);
		}
	}
	// イベントリストの作り直し
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『このトラックのみ表示OFF』 // 20100429追加
void CEventListFrame::OnUpdatePopupTrackVisibleOffUI (CCmdUI* pCmdUI) {
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	if (pSekaijuDoc->m_pTempTrack == NULL) {
		pCmdUI->Enable (FALSE);
	}
}

// 『ポップアップ』-『全トラック表示ON』
void CEventListFrame::OnPopupTrackVisibleAll () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);
	
	long lCount = m_pTrackListBox->GetCount ();
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pTrackListBox->SetCheck (i, 1);
		m_bTrackVisible[i] = TRUE;
	}
	m_bOnlyCurTrack = FALSE;
	m_bShowAllTrack = FALSE;
	// イベントリストの作り直し
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『全トラック表示ON』
void CEventListFrame::OnUpdatePopupTrackVisibleAllUI (CCmdUI* pCmdUI) {
}


// 『ポップアップ』-『このイベントの種類のみ表示ON』
void CEventListFrame::OnPopupEventKindVisibleOn () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lListIndex = 0;
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		long lEventKind = MIDIEvent_GetKind (pSekaijuDoc->m_pTempEvent);
		lListIndex = EventKindtoListIndex (lEventKind);
	}
	else if (GetFocus () == m_pEventKindListBox) {
		lListIndex = ((CEventKindListBox*)m_pEventKindListBox)->GetLastRButtonDownIndex ();
	}
	else {
		return;
	}
	long lCount = m_pEventKindListBox->GetCount ();
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pEventKindListBox->SetCheck (i, (i == lListIndex ? 1 : 0));
		m_bEventKindVisible[i] = (i == lListIndex ? TRUE : FALSE);
	}
	if (m_bEventKindVisible[lListIndex]) {
		m_wndEventKindCombo.SetCurSel (lListIndex);
		m_pEventKindListBox->SetCurSel (lListIndex);
	}
	m_bOnlyCurEventKind = FALSE;
	m_bShowAllEventKind = FALSE;
	// イベントリストの作り直し
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『このイベントの種類のみ表示ON』
void CEventListFrame::OnUpdatePopupEventKindVisibleOnUI (CCmdUI* pCmdUI) {
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		if (pSekaijuDoc->m_pTempEvent == NULL) {
			pCmdUI->Enable (FALSE);
		}
	}
}

// 『ポップアップ』-『このイベントの種類のみ表示OFF』
void CEventListFrame::OnPopupEventKindVisibleOff () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lListIndex = 0;
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		long lEventKind = MIDIEvent_GetKind (pSekaijuDoc->m_pTempEvent);
		lListIndex = EventKindtoListIndex (lEventKind);
	}
	else if (GetFocus () == m_pEventKindListBox) {
		lListIndex = ((CEventKindListBox*)m_pEventKindListBox)->GetLastRButtonDownIndex ();
	}
	else {
		return;
	}
	long lCount = m_pEventKindListBox->GetCount ();
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pEventKindListBox->SetCheck (i, (i == lListIndex ? 0 : 1));
		m_bEventKindVisible[i] = (i == lListIndex ? FALSE : TRUE);
	}
	if (m_bEventKindVisible[lListIndex]) {
		m_wndEventKindCombo.SetCurSel (lListIndex);
		m_pEventKindListBox->SetCurSel (lListIndex);
	}
	m_bOnlyCurEventKind = FALSE;
	m_bShowAllEventKind = FALSE;
	// イベントリストの作り直し
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『このイベントの種類のみ表示OFF』
void CEventListFrame::OnUpdatePopupEventKindVisibleOffUI (CCmdUI* pCmdUI) {
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		if (pSekaijuDoc->m_pTempEvent == NULL) {
			pCmdUI->Enable (FALSE);
		}
	}
}

// 『ポップアップ』-『全イベントの種類表示ON』
void CEventListFrame::OnPopupEventKindVisibleAll () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lCount = m_pEventKindListBox->GetCount ();
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pEventKindListBox->SetCheck (i, 1);
		m_bEventKindVisible[i] = TRUE;
	}
	// イベントリストの作り直し
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『全イベントの種類表示ON』 // 20100429追加
void CEventListFrame::OnUpdatePopupEventKindVisibleAllUI (CCmdUI* pCmdUI) {
}



// 『ポップアップ』-『このコントロールチェンジのみ表示ON』
void CEventListFrame::OnPopupControlChangeVisibleOn () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lListIndex = 0;
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		if (pSekaijuDoc->m_pTempEvent != NULL) {
			if (MIDIEvent_IsControlChange (pSekaijuDoc->m_pTempEvent)) {
				lListIndex = MIDIEvent_GetNumber (pSekaijuDoc->m_pTempEvent);
			}
			else {
				return;
			}
		}
		else {
			return;
		}
	}
	else if (GetFocus () == m_pControlChangeListBox) {
		lListIndex = ((CControlChangeListBox*)m_pControlChangeListBox)->GetLastRButtonDownIndex ();
	}
	else {
		return;
	}
	long lCount = m_pControlChangeListBox->GetCount ();
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pControlChangeListBox->SetCheck (i, (i == lListIndex ? 1 : 0));
		m_bControlChangeVisible[i] = (i == lListIndex ? TRUE : FALSE);
	}
	if (m_bControlChangeVisible[lListIndex]) {
		//m_wndEventKindCombo.SetCurSel (lListIndex);
		m_pControlChangeListBox->SetCurSel (lListIndex);
	}
	m_bOnlyCurControlChange = FALSE;
	m_bShowAllControlChange = FALSE;
	// イベントリストの作り直し
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『このコントロールチェンジのみ表示ON』
void CEventListFrame::OnUpdatePopupControlChangeVisibleOnUI (CCmdUI* pCmdUI) {
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		if (pSekaijuDoc->m_pTempEvent == NULL) {
			pCmdUI->Enable (FALSE);
		}
	}
}

// 『ポップアップ』-『このコントロールチェンジのみ表示OFF』
void CEventListFrame::OnPopupControlChangeVisibleOff () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lListIndex = 0;
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		if (pSekaijuDoc->m_pTempEvent != NULL) {
			if (MIDIEvent_IsControlChange (pSekaijuDoc->m_pTempEvent)) {
				lListIndex = MIDIEvent_GetNumber (pSekaijuDoc->m_pTempEvent);
			}
			else {
				return;
			}
		}
		else {
			return;
		}
	}
	else if (GetFocus () == m_pControlChangeListBox) {
		lListIndex = ((CControlChangeListBox*)m_pControlChangeListBox)->GetLastRButtonDownIndex ();
	}
	else {
		return;
	}
	long lCount = m_pControlChangeListBox->GetCount ();
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pControlChangeListBox->SetCheck (i, (i == lListIndex ? 0 : 1));
		m_bControlChangeVisible[i] = (i == lListIndex ? FALSE : TRUE);
	}
	if (m_bControlChangeVisible[lListIndex]) {
		//m_wndEventKindCombo.SetCurSel (lListIndex);
		m_pControlChangeListBox->SetCurSel (lListIndex);
	}
	m_bOnlyCurControlChange = FALSE;
	m_bShowAllControlChange = FALSE;
	// イベントリストの作り直し
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『このコントロールチェンジのみ表示OFF』
void CEventListFrame::OnUpdatePopupControlChangeVisibleOffUI (CCmdUI* pCmdUI) {
	if (GetFocus () == m_pIndexPropertyView) {
		CSekaijuDoc* pSekaijuDoc = GetDocument ();
		if (pSekaijuDoc->m_pTempEvent == NULL) {
			pCmdUI->Enable (FALSE);
		}
	}
}

// 『ポップアップ』-『全コントロールチェンジ表示ON』
void CEventListFrame::OnPopupControlChangeVisibleAll () {
	// 画面のdpi取得
	HDC hDC = ::GetDC (this->GetSafeHwnd ());
	long lLogPixelsX = ::GetDeviceCaps (hDC, LOGPIXELSX);
	long lLogPixelsY = ::GetDeviceCaps (hDC, LOGPIXELSY);
	::ReleaseDC (this->GetSafeHwnd (), hDC);

	long lCount = m_pControlChangeListBox->GetCount ();
	long i = 0;
	for (i = 0; i < lCount; i++) {
		m_pControlChangeListBox->SetCheck (i, 1);
		m_bControlChangeVisible[i] = TRUE;
	}
	// イベントリストの作り直し
	CSekaijuDoc* pSekaijuDoc = GetDocument ();
	pSekaijuDoc->m_theCriticalSection.Lock ();
	MakeVisibleEventArray (lLogPixelsX, lLogPixelsY);
	pSekaijuDoc->m_theCriticalSection.Unlock ();
	long lCurColumn = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurColumn;
	long lCurRow = ((CEventListIndexPropertyView*)m_pIndexPropertyView)->m_lCurRow;
	((CEventListIndexPropertyView*)m_pIndexPropertyView)->AutoScrolltoShowCell (lCurRow, lCurColumn, lLogPixelsX, lLogPixelsY);
	// 再描画
	m_pIndexScaleView->Invalidate ();
	m_pIndexPropertyView->Invalidate ();
}

// 『ポップアップ』-『全コントロールチェンジ表示ON』 // 20100429追加
void CEventListFrame::OnUpdatePopupControlChangeVisibleAllUI (CCmdUI* pCmdUI) {
}
