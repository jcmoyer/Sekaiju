//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// イベントリストインデックスプロパティビュークラス
// (C)2002-2022 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _EVENTLISTINDEXPROPERTYVIEW_H_
#define _EVENTLISTINDEXPROPERTYVIEW_H_

#include "InplaceEdit.h"
#include "InplaceListBox.h"

class CEventListIndexPropertyView : public CSekaijuView {

	DECLARE_DYNCREATE (CEventListIndexPropertyView)

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CEventListIndexPropertyView();          // コンストラクタ
	virtual ~CEventListIndexPropertyView(); // デストラクタ


	//--------------------------------------------------------------------------
	// アトリビュート
	//--------------------------------------------------------------------------
public:
	long m_lCurRow;                     // 現在の行番号(0～)
	long m_lCurColumn;                  // 現在の列番号(0～)
	long m_lCurButtonState;             // 現在のボタン状態
	long m_lCurButtonInterval;          // 現在のボタンの増減間隔
	long m_lOldRowRealTimeInput;        // 前回のリアルタイム入力描画時の行番号(0～)
	long m_lOldVisibleEventCountRealTimeInput;       // 前回のリアルタイム入力時表示イベント数[tick]
	CInplaceEdit m_theTextBox;          // インプレーステキストボックス
	CInplaceListBox m_theListBox;       // インプレースリストボックス

protected:
	CPoint m_ptMouseDown;               // マウスが押されたときの座標
	CPoint m_ptMouseMove;               // マウスが動かされたときの前回の座標
	CPoint m_ptMouseDownM;              // マウスが押されたときの座標(中ボタン)
	CPoint m_ptMouseMoveM;              // マウスが動かされたときの前回の座標(中ボタン)
	MIDITrack* m_pCloneTrack;           // 一時的な複製されたトラックへのポインタ
	MIDIEvent* m_pCloneEvent;           // 一時的な複製されたイベントへのポインタ
	MIDIEvent* m_pLastEvent;            // 一時的な最後のイベントへのポインタ
	BOOL m_bSettingCellString;          // セルの文字列を設定中か
	long m_lTempMode;
	BOOL m_bUniversalScroll;            // ユニバーサルスクロール中か

	//--------------------------------------------------------------------------
	// オペレーション
	//--------------------------------------------------------------------------
protected:
	virtual BOOL GetCellFromPoint (CPoint pt, long* pRow, long* pColumn, long lLogPixelsX, long lLogPixelsY);
	virtual CRect GetRectFromCell (long lRow, long lColumn, long lLogPixelsX, long lLogPixelsY);

public:
	virtual BOOL AutoScrolltoShowCell (long lRow, long lColumn, long lLogPixelsX, long lLogPixelsY);
	virtual BOOL IsTextEditing ();
	virtual BOOL IsListSelecting ();
	virtual BOOL BeginTextEditing ();
	virtual BOOL BeginListSelecting ();
	virtual BOOL EndTextEditingOK ();
	virtual BOOL EndListSelectingOK ();
	virtual BOOL EndTextEditingCancel ();
	virtual BOOL EndListSelectingCancel ();
	virtual BOOL BeginValueUpDown ();
	virtual BOOL EndValueUpDown ();
	virtual BOOL AddValueOfCurCell (long lDeltaValue);
	virtual BOOL MoveTextBox (long lRow, long lColumn, long lLogPixelsX, long lLogPixelsY);
	virtual BOOL MoveListBox (long lRow, long lColumn, long lLogPixelsX, long lLogPixelsY);
	virtual BOOL UpdateParentToolbarControl ();
	virtual CString GetCellString (long lRow, long lColumn);
	virtual BOOL SetCellString (long lRow, long lColumn, CString strText);
	virtual BOOL ShowPopupMenu (CPoint point);
	virtual int DrawCurFrame (CDC* pDC, long lLogPixelsX, long lLogPixelsY);

	//--------------------------------------------------------------------------
	// オーバーライド
	//--------------------------------------------------------------------------
public:
	virtual void OnPrepareDC (CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnDraw (CDC* pDC);
	virtual void OnUpdate (CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnCmdMsg (UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);


	//--------------------------------------------------------------------------
	// メッセージマップ
	//--------------------------------------------------------------------------
protected:
	afx_msg BOOL OnCreate (LPCREATESTRUCT lpcs);
	afx_msg void OnDestroy ();
	afx_msg void OnKillFocus (CWnd* pNewWnd);
	afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnMouseMove (UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk (UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk (UINT nFlags, CPoint point);
	afx_msg void OnTimer (UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel (UINT nFlags, short zDelta, CPoint point);
	DECLARE_MESSAGE_MAP ();
};

#endif

