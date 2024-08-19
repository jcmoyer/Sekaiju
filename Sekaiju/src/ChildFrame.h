//******************************************************************************
// MIDI�V�[�P���T�[�\�t�g�w���E���x
// MDI�q�t���[���E�B���h�E�N���X
// (C)2002-2021 ���[�Ղ�MIDI�Ղ낶�����Ɓ^����
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _CHILDFRAME_H_
#define _CHILDFRAME_H_

class CChildFrame : public CMDIChildWnd {

	DECLARE_DYNCREATE (CChildFrame)

	//--------------------------------------------------------------------------
	// �\�z�Ɣj��
	//--------------------------------------------------------------------------
public:
	CChildFrame ();                     // �R���X�g���N�^
	virtual ~CChildFrame ();            // �f�X�g���N�^

	//--------------------------------------------------------------------------
	// �I�y���[�V����
	//--------------------------------------------------------------------------
public:
	CDocument* GetDocument ();          // �h�L�������g�ւ̃|�C���^�擾
	virtual long GetCurTrackIndex ();   // �������z�֐������B

	//--------------------------------------------------------------------------
	// �I�[�o�[���C�h
	//--------------------------------------------------------------------------
protected:
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
	virtual void PostNcDestroy ();


#ifdef _DEBUG
	virtual void AssertValid () const;
	virtual void Dump (CDumpContext& dc) const;
#endif

	//--------------------------------------------------------------------------
	// ���b�Z�[�W�}�b�v
	//--------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP ()
	afx_msg void OnMDIActivate (BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};

#endif
