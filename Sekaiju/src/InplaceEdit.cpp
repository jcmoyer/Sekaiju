//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// インプレースエディットクラス
// (C)2002-2023 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "stdafx.h"
#include "InplaceEdit.h"


// アロケーションの監視
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// メッセージマップ
IMPLEMENT_DYNCREATE (CInplaceEdit, CEdit)

BEGIN_MESSAGE_MAP (CInplaceEdit, CEdit)
	ON_WM_KILLFOCUS ()
	ON_WM_KEYDOWN ()
	ON_WM_CHAR ()
END_MESSAGE_MAP()

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
CInplaceEdit::CInplaceEdit () {
	m_bIsHexOnly = FALSE;
}

// デストラクタ
CInplaceEdit::~CInplaceEdit () {
}

//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------

// フォーカスが失われたとき
void CInplaceEdit::OnKillFocus (CWnd* pNewWnd) {
	_RPTF1 (_CRT_WARN, "CInplaceEditBox::OnKillFocus (pNewWnd=0x%08x)\n", pNewWnd);
	CWnd* pParentWnd = GetParent ();
	if (pParentWnd != pNewWnd) {
		pParentWnd->SendMessage (WM_KILLFOCUS, (WPARAM)pNewWnd, (LPARAM)0L);
	}
	else {
		//pParentWnd->SetFocus ();
	}
	CEdit::OnKillFocus (pNewWnd); //20080809追加(カレットの消失防止)
}

// キー押し下げ時
void CInplaceEdit::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags) {
	CWnd* pParentWnd = GetParent ();
	switch (nChar) {
	case VK_RETURN:
		//GetParent ()->SendMessage (WM_KEYDOWN, VK_RETURN, (nRepCnt << 16) | nFlags);
		pParentWnd->SetFocus ();
		pParentWnd->PostMessage (WM_KEYDOWN, VK_RETURN, (nRepCnt << 16) | nFlags);
		break;
	case VK_ESCAPE:
		//GetParent ()->SendMessage (WM_KEYDOWN, VK_ESCAPE, (nRepCnt << 16) | nFlags);
		pParentWnd->SetFocus ();
		pParentWnd->PostMessage (WM_KEYDOWN, VK_ESCAPE, (nRepCnt << 16) | nFlags);
		break;
	}
	CEdit::OnKeyDown (nChar, nRepCnt, nFlags);
}

// 文字入力時
void CInplaceEdit::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) {
	// Enterを押したときにプープー音が鳴るのを防ぐ
	switch (nChar) {
	case VK_RETURN:
		return;
	}
	// 16進数のみ入力可能な場合、異常文字は入力不可とする
	if (m_bIsHexOnly) {
		if (!('0' <= nChar && nChar <= '9' ||
			'A' <= nChar && nChar <= 'F' ||
			'a' <= nChar && nChar <= 'f' ||
			//nChar == ' ' || nChar == VK_BACK || nChar == VK_DELETE || nChar == VK_ESCAPE || nChar == VK_RETURN ||
			nChar <= ' ')) { // 20230103:VK_CONTROL等すべての制御キーが利くように修正。
			return;
		}	
	}
	CEdit::OnChar (nChar, nRepCnt, nFlags);
}
