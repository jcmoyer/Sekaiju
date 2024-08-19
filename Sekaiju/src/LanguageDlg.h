﻿//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// 言語ダイアログクラス
// (C)2002-2017 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LANGUAGEDLG_H_
#define _LANGUAGEDLG_H_

class CLanguageDlg : public CDialog {
	//--------------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------------
public:
	CString m_strUserInterface;              // ユーザーインターフェイスの言語名
	CString m_strTextEncoding;          // 文字コード無指定時のテキストエンコーディング

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CLanguageDlg();                    // コンストラクタ
	enum {IDD = IDD_LANGUAGE};

	//--------------------------------------------------------------------------
	// オペレーション
	//--------------------------------------------------------------------------
	BOOL FillUserInterfaceCombo ();
	BOOL FillTextEncodingCombo ();

	//--------------------------------------------------------------------------
	// オーバーライド
	//--------------------------------------------------------------------------
protected:
	virtual void DoDataExchange (CDataExchange* pDX);    // DDX/DDV のサポート
	virtual BOOL OnInitDialog ();

	//--------------------------------------------------------------------------
	// メッセージマップ
	//--------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP ()
};

#endif
