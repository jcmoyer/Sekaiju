//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// ビュークラス
// (C)2002-2021 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// このクラスの役割はCSekaijuDoc* GetDocument()を提供することと、
// MFC4.0風のSDIの印刷プレビューを実現するDoPrintPreviewのオーバーライドと
// OnEndPrintPreviewのオーバーライドをインプリメントすることである。
// 実用的なビューはCSekaijuViewから派生させて作ること。
// なお、このクラスはVisible=FALSEのダミービューとしても使える。

#ifndef _SEKAIJUVIEW_H_
#define _SEKAIJUVIEW_H_

#pragma once


class CSekaijuView : public CView {

	DECLARE_DYNCREATE (CSekaijuView)

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CSekaijuView ();                    // コンストラクタ
	virtual ~CSekaijuView ();           // デストラクタ

	//--------------------------------------------------------------------------
	// オペレーション
	//--------------------------------------------------------------------------
public:
	CSekaijuDoc* GetDocument () const;  // ドキュメントの取得
	void ActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView);


	void EndPrintPreview (CDC* pDC, CPrintInfo* pInfo, POINT point,
		CPreviewView* pView);
	void EndPrinting (CDC* pDC, CPrintInfo* pInfo);



	//--------------------------------------------------------------------------
	// オーバーライド
	//--------------------------------------------------------------------------
protected:
	virtual void OnDraw (CDC* pDC);
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting (CPrintInfo* pInfo);
	virtual void OnBeginPrinting (CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting (CDC* pDC, CPrintInfo* pInfo);

	virtual void OnFilePrintPreview ();
	virtual BOOL DoPrintPreview (UINT nIDResource, CView* pPrintView,
		CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState);
	virtual void OnEndPrintPreview (CDC* pDC, CPrintInfo* pInfo, POINT point,
		CPreviewView* pView);


#ifdef _DEBUG
	virtual void AssertValid () const;
	virtual void Dump (CDumpContext& dc) const;
#endif

//--------------------------------------------------------------------------
// メッセージマップ
//--------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP ()

};

#ifndef _DEBUG  // SekaijuView.cpp のデバッグ バージョン
inline CSekaijuDoc* CSekaijuView::GetDocument() const
   { return reinterpret_cast<CSekaijuDoc*>(m_pDocument); }
#endif

#endif
