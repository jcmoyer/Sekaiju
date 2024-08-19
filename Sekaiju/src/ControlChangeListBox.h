//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// コントロールチェンジリストボックスクラス
// (C)2002-2020 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _CONTROLCHANGELISTBOX_H_
#define _CONTROLCHANGELISTBOX_H_

class CControlChangeListBox : public CCheckListBox {
	DECLARE_DYNCREATE (CControlChangeListBox)

	//--------------------------------------------------------------------------
	// アトリビュート
	//--------------------------------------------------------------------------
protected:
	CDocument* m_pDocument;             // ドキュメントへのポインタ
	long m_lMenuID;                     // 右クリックしたときに現れるメニューのID
	long m_lLastRButtonDownIndex;       // 最後に右クリックした項目番号(0～)

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CControlChangeListBox ();               // コンストラクタ
	CControlChangeListBox (CDocument* pDocument, long lMenuID); // コンストラクタ
	virtual ~CControlChangeListBox ();      // デストラクタ

	//--------------------------------------------------------------------------
	// オペレーション
	//--------------------------------------------------------------------------
public:
	void CControlChangeListBox::SetDocument (CDocument* pDocument);
	CSekaijuDoc* GetDocument ();
	long  GetLastRButtonDownIndex ();

	//--------------------------------------------------------------------------
	// オーバーライド
	//--------------------------------------------------------------------------
protected:

	//--------------------------------------------------------------------------
	// メッセージマップ
	//--------------------------------------------------------------------------
protected:
	afx_msg void OnRButtonDown (UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP ()
};

#endif
