﻿//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// 譜面トラックタイムビュークラス
// (C)2002-2022 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MUSICALSCORETRACKTIMEVIEW_H_
#define _MUSICALSCORETRACKTIMEVIEW_H_

class CMusicalScoreTrackTimeView : public CSekaijuView {

	DECLARE_DYNCREATE (CMusicalScoreTrackTimeView)

	//--------------------------------------------------------------------------
	// アトリビュート
	//--------------------------------------------------------------------------
protected:
	long m_lCurTime;                    // 現在の描画タイム[tick]又は[サブフレーム]
	long m_lOldTime;                    // 前回の描画タイム[tick]又は[サブフレーム]
	long m_lOldTimeRealTimeInput;       // 前回のリアルタイム入力描画タイム[tick]
	long m_lOldX;                       // 前回の縦線x座標[pixel]
	long m_lOldY1;                      // 前回の縦線y上座標[pixel]
	long m_lOldY2;                      // 前回の縦線y下座標[pixel]
	BOOL m_bOldDraw;                    // 前回縦線を描画したか？
	long m_lMouseDownTime;              // マウスが押されたときの指すタイム[tick]又は[サブフレーム]
	long m_lMouseMoveTime;              // マウスが動かされたときの前回の指すタイム[tick]又は[サブフレーム]
	long m_lMouseDownKey;               // マウスが押されたときの指す音階(0～127)
	long m_lMouseMoveKey;               // マウスが動かされたときの前回の指す音階(0～127)
	CPoint m_ptMouseDown;               // マウスが押されたときの座標
	CPoint m_ptMouseMove;               // マウスが動かされたときの前回の座標
	CPoint m_ptMouseDownM;              // マウスが押されたときの座標(中ボタン)
	CPoint m_ptMouseMoveM;              // マウスが動かされたときの前回の座標(中ボタン)
	UINT m_nMouseDownFlags;             // マウスが押されたときのフラグ
	UINT m_nMouseMoveFlags;             // マウスが動かされたときの前回のフラグ
	long m_lTempTool;                   // 一時的なツール(0～)
	long m_lTempTrackIndex;             // 一時的なトラック番号(0～65535)
	long m_lTempSnap;                   // 一時的なスナップタイム[tick]
	long m_lTempVelocity;               // 一時的なベロシティ(0～127)
	long m_lTempDuration;               // 一時的な音長さ(0～)[tick]
	long m_lTempOutputPort;             // 一時的な出力ポート(0～15)
	long m_lTempChannel;                // 一時的なチャンネル(0～15)
	long m_lTempKey;                    // 一時的な音階(0～127)
	long m_lTempTime;                   // 一時的なタイム(0～)[tick]
	long m_lTempTimeNoteOn;             // 一時的なノートオンタイム(0～)[tick]
	long m_bTempTieInserted;             // 一時的なタイが入力されたか(FALSE/TRUE)
	MIDITrack* m_pTempTrack;            // 一時的なトラックへのポインタ
	MIDIEvent* m_pTempEvent;            // 一時的なイベントへのポインタ
	MIDIEvent* m_pLastEvent;            // 一時的な最後のイベントへのポインタ
	long m_lTempMode;                   // 一時的なモード
	CPtrArray m_theTempSelectedEventArray; // 一時的な選択されているイベントの配列
	BOOL m_bUniversalScroll;            // ユニバーサルスクロール中？

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CMusicalScoreTrackTimeView ();      // コンストラクタ
	virtual ~CMusicalScoreTrackTimeView (); // デストラクタ
	
	//--------------------------------------------------------------------------
	// オペレーション
	//--------------------------------------------------------------------------
protected:
	virtual CRect GetNoteRect (MIDIEvent* pNoteOnEvent, long lLogPixelsX, long lLogPixelsY);
	virtual CRect GetNoteRect (MusicalScoreNoteInfo* pNoteInfo, long lLogPixelsX, long lLogPixelsY);
	virtual void EraseOldLine (CDC* pDC, long lLogPixelsX);
	virtual void DrawCurLine (CDC* pDC, long lLogPixelsX);
	virtual BOOL ShowPopupMenu (CPoint ptMenu);
	virtual void DrawTadpole
		(CDC* pDC, long x, long y, long rx, long ry, long lFlags, long lLogPixelsX, long lLogPixelsY);
	virtual void DrawHorzAuxiliaryLine
		(CDC* pDC, long x, long y, long r, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawDot
		(CDC* pDC, long x, long y, long rx, long ry, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawTieHalf
		(CDC* pDC, long x1, long x2, long y, long rx, long ry, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawPole 
		(CDC* pDC, long x1, long x2, long y1, long y2, long rx, long ry, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawSingleFlag
		(CDC* pDC, long x1, long x2, long y1, long y2, long rx, long ry, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawChainedFlag 
		(CDC* pDC, long x1, long x2, long y1, long y2, long rx, long ry, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawTripletSign 
		(CDC* pDC, long x1, long x2, long y1, long y2, long rx, long ry, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawNote
		(CDC* pDC, long lTrackIndex, MusicalScoreNoteInfo* pNoteInfo, long lFlags, long lLogPixelsX, long lLogPixelsY);
	void DrawGClef 
		(CDC* pDC, long x, long y, long rx, long ry, long lLogPixelsX, long lLogPixelsY);
	void DrawFClef 
		(CDC* pDC, long x, long y, long rx, long ry, long lLogPixelsX, long lLogPixelsY);
	void DrawFlat 
		(CDC* pDC, long x, long y, long rx, long ry, long lLogPixelsX, long lLogPixelsY);
	void DrawNatural
		(CDC* pDC, long x, long y, long rx, long ry, long lLogPixelsX, long lLogPixelsY);
	void DrawSharp 
		(CDC* pDC, long x, long y, long rx, long ry, long lLogPixelsX, long lLogPixelsY);
	void DrawTimeAndKeySignature 
		(CDC* pDC, long lTrackIndex, long lTime, long lLogPixelsX, long lLogPixelsY);

	//--------------------------------------------------------------------------
	// オーバーライド
	//--------------------------------------------------------------------------
protected:
	virtual void OnPrepareDC (CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw (CDC* pDC);
	virtual void OnUpdate (CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);

	//--------------------------------------------------------------------------
	// メッセージマップ
	//--------------------------------------------------------------------------
protected:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy ();
	afx_msg void OnTimer (UINT_PTR nIDEvent);
	afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnMouseMove (UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel (UINT nFlags, short zDelta, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#endif

