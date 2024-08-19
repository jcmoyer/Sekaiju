//******************************************************************************
// MIDI�V�[�P���T�[�\�t�g�w���E���x
// �r���[�N���X
// (C)2002-2021 ���[�Ղ�MIDI�Ղ낶�����Ɓ^����
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// ���̃N���X�̖�����CSekaijuDoc* GetDocument()��񋟂��邱�ƂƁA
// MFC4.0����SDI�̈���v���r���[����������DoPrintPreview�̃I�[�o�[���C�h��
// OnEndPrintPreview�̃I�[�o�[���C�h���C���v�������g���邱�Ƃł���B
// ���p�I�ȃr���[��CSekaijuView����h�������č�邱�ƁB
// �Ȃ��A���̃N���X��Visible=FALSE�̃_�~�[�r���[�Ƃ��Ă��g����B

#ifndef _SEKAIJUVIEW_H_
#define _SEKAIJUVIEW_H_

#pragma once


class CSekaijuView : public CView {

	DECLARE_DYNCREATE (CSekaijuView)

	//--------------------------------------------------------------------------
	// �\�z�Ɣj��
	//--------------------------------------------------------------------------
public:
	CSekaijuView ();                    // �R���X�g���N�^
	virtual ~CSekaijuView ();           // �f�X�g���N�^

	//--------------------------------------------------------------------------
	// �I�y���[�V����
	//--------------------------------------------------------------------------
public:
	CSekaijuDoc* GetDocument () const;  // �h�L�������g�̎擾
	void ActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView);


	void EndPrintPreview (CDC* pDC, CPrintInfo* pInfo, POINT point,
		CPreviewView* pView);
	void EndPrinting (CDC* pDC, CPrintInfo* pInfo);



	//--------------------------------------------------------------------------
	// �I�[�o�[���C�h
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
// ���b�Z�[�W�}�b�v
//--------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP ()

};

#ifndef _DEBUG  // SekaijuView.cpp �̃f�o�b�O �o�[�W����
inline CSekaijuDoc* CSekaijuView::GetDocument() const
   { return reinterpret_cast<CSekaijuDoc*>(m_pDocument); }
#endif

#endif
