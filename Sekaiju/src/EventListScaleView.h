﻿//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// イベントリストスケールビュークラス
// (C)2002-2021 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _EVENTLISTSCALEVIEW_H_
#define _EVENTLISTSCALEVIEW_H_

class CEventListScaleView : public CSekaijuView {
	DECLARE_DYNCREATE (CEventListScaleView)

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CEventListScaleView ();             // コンストラクタ
	virtual ~CEventListScaleView ();    // デストラクタ
	
	//--------------------------------------------------------------------------
	// オーバーライド
	//--------------------------------------------------------------------------
public:
	virtual void OnDraw (CDC* pDC);
	virtual void OnUpdate (CView* pSender, LPARAM lHint, CObject* pHint);

	//--------------------------------------------------------------------------
	// メッセージマップ
	//--------------------------------------------------------------------------
protected:
	afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel (UINT nFlags, short zDelta, CPoint point);
	DECLARE_MESSAGE_MAP ()
};

#endif


