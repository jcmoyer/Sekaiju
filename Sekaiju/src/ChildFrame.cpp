//******************************************************************************
// MIDI�V�[�P���T�[�\�t�g�w���E���x
// MDI�q�t���[���E�B���h�E�N���X
// (C)2002-2021 ���[�Ղ�MIDI�Ղ낶�����Ɓ^����
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "stdafx.h"
#include "..\\..\\MIDIIO\\MIDIIO.h"
#include "..\\..\\MIDIData\\MIDIData.h"
#include "..\\..\\MIDIClock\\MIDIClock.h"
#include "..\\..\\MIDIStatus\\MIDIStatus.h"
#include "..\\..\\MIDIInstrument\\MIDIInstrument.h"
#include "SekaijuApp.h"
#include "SekaijuToolBar.h"
#include "SekaijuStatusBar.h"
#include "MainFrame.h"
#include "ChildFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE (CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP (CChildFrame, CMDIChildWnd)
	ON_WM_MDIACTIVATE ()
END_MESSAGE_MAP ()

//------------------------------------------------------------------------------
// �\�z�Ɣj��
//------------------------------------------------------------------------------

// �R���X�g���N�^
CChildFrame::CChildFrame () {
}

// �f�X�g���N�^
CChildFrame::~CChildFrame () {
}

//------------------------------------------------------------------------------
// �I�y���[�V����
//------------------------------------------------------------------------------

// �h�L�������g�ւ̃|�C���^�擾
CDocument* CChildFrame::GetDocument () {
	CView* pActiveView = GetActiveView ();
	if (pActiveView) {
		return pActiveView->GetDocument ();
	}
	else {
		return NULL;
	}
}


// ���̉��z�֐��̓I�[�o�[���C�h���Ă��������B
long CChildFrame::GetCurTrackIndex () {
	return 0;
}

//------------------------------------------------------------------------------
// �I�[�o�[���C�h
//------------------------------------------------------------------------------
BOOL CChildFrame::PreCreateWindow (CREATESTRUCT& cs) {
	if (!CMDIChildWnd::PreCreateWindow (cs)) {
		return FALSE;
	}
	return TRUE;
}


// �E�B���h�E���j�����ꂽ��
void CChildFrame::PostNcDestroy () {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp();
	pSekaijuApp->UpdateCurWndAndDocPtr ();
	CMDIChildWnd::PostNcDestroy ();
}


// CChildFrame �f�f

#ifdef _DEBUG
void CChildFrame::AssertValid () const {
	CMDIChildWnd::AssertValid ();
}

void CChildFrame::Dump (CDumpContext& dc) const {
	CMDIChildWnd::Dump (dc);
}
#endif //_DEBUG

//------------------------------------------------------------------------------
// ���b�Z�[�W�}�b�v
//------------------------------------------------------------------------------

// �E�B���h�E���A�N�e�B�u�ɂȂ����Ƃ�
void CChildFrame::OnMDIActivate (BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) {
	CSekaijuApp* pSekaijuApp = (CSekaijuApp*)AfxGetApp ();
	if (bActivate == TRUE) {
		pSekaijuApp->UpdateCurWndAndDocPtr ();
	}
	CMDIChildWnd::OnMDIActivate (bActivate, pActivateWnd, pDeactivateWnd); // 20210607 BugFix
}



