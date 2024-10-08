﻿//******************************************************************************
// MIDIシーケンサーソフト『世界樹』
// 音長さの変更ダイアログクラス
// (C)2002-2017 おーぷんMIDIぷろじぇくと／くず
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "stdafx.h"
#include "resource.h"
#include "EditDurationDlg.h"

#ifndef CLIP
#define CLIP(A,B,C) ((B)<(A)?(A):((B)>(C)?(C):(B)))
#endif

//------------------------------------------------------------------------------
// 構築と破壊
//------------------------------------------------------------------------------

// コンストラクタ
CEditDurationDlg::CEditDurationDlg () : CDialog (CEditDurationDlg::IDD) {
	m_nAmount = 0;
	m_nUnit = 0;
}

//------------------------------------------------------------------------------
// オペレーション
//------------------------------------------------------------------------------

BOOL CEditDurationDlg::SetAmountRange () {
	CButton* pAbsoluteUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_ABSOLUTEUNIT);
	CButton* pRelativeUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_RELATIVEUNIT);
	CButton* pPercentUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_PERCENTUNIT);
	CButton* pRandomUpDownUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_RANDOMUPDOWNUNIT);
	CString strValue;
	GetDlgItem (IDC_EDITDURATION_AMOUNT)->GetWindowText (strValue);
	long lValue = _ttol (strValue);
	if (pAbsoluteUnitButton->GetCheck ()) {
		((CSpinButtonCtrl*)GetDlgItem (IDC_EDITDURATION_AMOUNTSP))->SetRange (1, 16383);
		((CSpinButtonCtrl*)GetDlgItem (IDC_EDITDURATION_AMOUNTSP))->SetPos (CLIP (1, lValue, 16383));
	}
	else if (pRelativeUnitButton->GetCheck () || pRandomUpDownUnitButton->GetCheck ()) {
		((CSpinButtonCtrl*)GetDlgItem (IDC_EDITDURATION_AMOUNTSP))->SetRange (-16383, 16383);
		((CSpinButtonCtrl*)GetDlgItem (IDC_EDITDURATION_AMOUNTSP))->SetPos (CLIP (-16383, lValue, 16383));
	}
	else if (pPercentUnitButton->GetCheck ()) {
		((CSpinButtonCtrl*)GetDlgItem (IDC_EDITDURATION_AMOUNTSP))->SetRange (0, 1000);
		((CSpinButtonCtrl*)GetDlgItem (IDC_EDITDURATION_AMOUNTSP))->SetPos (CLIP (0, lValue, 1000));
	}
	return TRUE;
}

//------------------------------------------------------------------------------
// オーバーライド
//------------------------------------------------------------------------------

// データエクスチェンジ
void CEditDurationDlg::DoDataExchange (CDataExchange* pDX) {
	CDialog::DoDataExchange (pDX);
	DDX_Text (pDX, IDC_EDITDURATION_AMOUNT, m_nAmount);
	DDX_Radio (pDX, IDC_EDITDURATION_ABSOLUTEUNIT, m_nUnit);
	CButton* pAbsoluteUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_ABSOLUTEUNIT);
	CButton* pRelativeUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_RELATIVEUNIT);
	CButton* pPercentUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_PERCENTUNIT);
	CButton* pRandomUpDownUnitButton = (CButton*)GetDlgItem (IDC_EDITDURATION_RANDOMUPDOWNUNIT);
	if (pAbsoluteUnitButton->GetCheck ()) {
		DDV_MinMaxInt (pDX, m_nAmount, 0, 16383);
	}
	else if (pRelativeUnitButton->GetCheck () || pRandomUpDownUnitButton->GetCheck ()) {
		DDV_MinMaxInt (pDX, m_nAmount, -16383, 16383);
	}
	else if (pPercentUnitButton->GetCheck ()) {
		DDV_MinMaxInt (pDX, m_nAmount, 0, 1000);
	}
}

// ダイアログ初期化時
BOOL CEditDurationDlg::OnInitDialog () {
	BOOL bRet = CDialog::OnInitDialog ();
	SetAmountRange ();
	return bRet;
}


//------------------------------------------------------------------------------
// メッセージマップ
//------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP (CEditDurationDlg, CDialog)
	ON_CONTROL_RANGE (BN_CLICKED,  IDC_EDITDURATION_ABSOLUTEUNIT, IDC_EDITDURATION_RANDOMUPDOWNUNIT, OnChangeUnit)
END_MESSAGE_MAP ()

// 単位が変更された
void CEditDurationDlg::OnChangeUnit (UINT nID) {
	SetAmountRange ();
}


