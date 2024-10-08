﻿//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// メトロノームダイアログクラス
// (C)2002-2021 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _METRONOMEDLG_H_
#define _METRONOMEDLG_H_

class CMetronomeDlg : public CDialog {
	//--------------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------------
public:
	int m_nOn;                          // オン(0=オフ、1=ON)
	int m_nOnWhilePlaying;              // 演奏時オン
	int m_nOutputPort;                  // 出力ポート(0～15)
	int m_nOutputChannel;               // 出力チャンネル(0～15)
	int m_nNoteKey1;                    // ノートキー強打(0～127)
	int m_nNoteVel1;                    // ノートベロシティ強打(1～127)
	int m_nNoteKey2;                    // ノートキー弱打(0～127)
	int m_nNoteVel2;                    // ノーとベロシティ弱打(0～127)

	//--------------------------------------------------------------------------
	// 構築と破壊
	//--------------------------------------------------------------------------
public:
	CMetronomeDlg();                    // コンストラクタ
	enum {IDD = IDD_METRONOME};

	//--------------------------------------------------------------------------
	// オペレーション
	//--------------------------------------------------------------------------
	BOOL FillOutputPortCombo ();
	BOOL FillNoteKeyCombo ();

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
	afx_msg void OnChangeOutput ();
	DECLARE_MESSAGE_MAP ()
};

#endif
