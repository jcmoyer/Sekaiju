﻿//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// MDI親フレームウィンドウクラス
// (C)2002-2023 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

class CMainFrame : public CMDIFrameWnd {
	DECLARE_DYNAMIC (CMainFrame)

	//--------------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------------
public:
	CString     m_strWndClass;          // ウィンドウクラス名
	CString     m_strTempFileName;      // 一時的なファイル名格納場所
		
	//--------------------------------------------------------------------------
	// ツールバーとステータスバーとその内部のウィンドウ
	//--------------------------------------------------------------------------
public:  
	CSekaijuStatusBar  m_wndStatusBar;  // ステータスバー
	CSekaijuToolBar m_wndToolBar1;      // ツールバー1
	CSekaijuToolBar m_wndToolBar2;      // ツールバー2
	CEdit       m_wndMillisecEdit;      // 時:分:秒:ミリ秒用エディット(読み取り専用)
	CEdit       m_wndTimeEdit;          // 小節:拍:ティックorフレーム:サブフレーム用エディット(読み取り専用)
	CScrollBar  m_wndPositionScroll;    // 位置スクロールバー
	CComboBox   m_wndStepTimeCombo;     // ステップタイム用コンボボックス
	CComboBox   m_wndKeyShiftCombo;     // キーシフト用コンボボックス
	CEdit       m_wndMeasureEdit;       // 拍子記号・調性記号用エディット(読み取り専用)
	CEdit       m_wndTempoEdit;         // テンポ用エディット(読み取り専用)

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CMainFrame ();                      // コンストラクタ
	virtual ~CMainFrame();              // デストラクタ

	//--------------------------------------------------------------------------
	// オペレーション
	//--------------------------------------------------------------------------
public:
	void SetPositionScrollRange (long lStartTime, long lEndTime, BOOL bRedraw);
	int SetWindowTextWhenDifferent (CWnd* pWnd, LPCTSTR lpszText);
	BOOL UpdateStepTimeCombo (long lTimeMode, long lTimeResolution);

	//--------------------------------------------------------------------------
	// オーバーライド
	//--------------------------------------------------------------------------
public:
	virtual CFrameWnd* GetActiveFrame ();
protected:
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
#if 0
	// 印刷用仮
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
#endif

	//--------------------------------------------------------------------------
	// メッセージマップ
	//--------------------------------------------------------------------------
protected:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy ();
	afx_msg void OnClose();
	afx_msg void OnTimer (UINT_PTR nIDEvent);
	afx_msg void OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel (UINT nFlags, short zDelta, CPoint point);
	afx_msg void OnSize (UINT nType, int cx, int cy);

	afx_msg void OnViewToolbar1 ();
	afx_msg void OnUpdateViewToolbar1UI (CCmdUI* pCmdUI);
	afx_msg void OnViewToolbar2 ();
	afx_msg void OnUpdateViewToolbar2UI (CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorInputVelocityUI (CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorOutputVelocityUI (CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorFormatUI (CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorNumTracksUI (CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorTimeBaseUI (CCmdUI* pCmdUI);
	
	afx_msg LRESULT OnCommandWakeUp (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCommandReadShm (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCommandFileOpen (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCommandUpdateAllViews (WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnSALPause (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALMessage (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALGetInt (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALGetString (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALGetTime (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALSendMIDI (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALInsert (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALDelete (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALGetValue (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALSetValue (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALGetForEachEventArray (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSALEnd (WPARAM wParam, LPARAM lParam);

	afx_msg void OnDrawItem (int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP ()

};

#endif
