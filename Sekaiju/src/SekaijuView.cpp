//******************************************************************************
// MIDI�V�[�P���T�[�\�t�g�w���E���x
// ���E���r���[�N���X
// (C)2002-2017 ���[�Ղ�MIDI�Ղ낶�����Ɓ^����
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// ���̃N���X�̖�����CSekaijuDoc* GetDocument()��񋟂��邱�ƂƁA
// MFC4.0����SDI�̈���v���r���[����������DoPrintPreview�̃I�[�o�[���C�h��
// OnEndPrintPreview�̃I�[�o�[���C�h���C���v�������g���邱�Ƃł���B
// ���p�I�ȃr���[��CSekaijuView����h�������č�邱�ƁB
// �Ȃ��A���̃N���X��Visible=FALSE�̃_�~�[�r���[�Ƃ��Ă��g����B

#include "stdafx.h"
#include "..\\..\\MIDIIO\\MIDIIO.h"
#include "..\\..\\MIDIData\\MIDIData.h"
#include "..\\..\\MIDIClock\\MIDIClock.h"
#include "..\\..\\MIDIStatus\\MIDIStatus.h"
#include "..\\..\\MIDIInstrument\\MIDIInstrument.h"
#include "HistoryRecord.h"
#include "HistoryUnit.h"
#include "SekaijuApp.h"
#include "SekaijuDoc.h"
#include "SekaijuToolBar.h"
#include "SekaijuStatusBar.h"
#include "MainFrame.h"
#include "SekaijuView.h"
#include "SekaijuPreviewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE (CSekaijuView, CView)

// ���b�Z�[�W�}�b�v
BEGIN_MESSAGE_MAP (CSekaijuView, CView)
	// �W������R�}���h
	ON_COMMAND (ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND (ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND (ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP ()

//------------------------------------------------------------------------------
// �\�z�Ɣj��
//------------------------------------------------------------------------------

// �R���X�g���N�^
CSekaijuView::CSekaijuView () {
}

// �f�X�g���N�^
CSekaijuView::~CSekaijuView () {
}

//------------------------------------------------------------------------------
// �I�y���[�V����
//------------------------------------------------------------------------------

// OnEndPrintPreview���Ăяo��
void CSekaijuView::EndPrintPreview
(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) {
	OnEndPrintPreview (pDC, pInfo, point, pView);
}

// OnEndPrinting���Ăяo��
void CSekaijuView::EndPrinting (CDC* pDC, CPrintInfo* pInfo) {
	OnEndPrinting (pDC, pInfo);
}

// OnActivateView���Ăяo��
void CSekaijuView::ActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView) {
	OnActivateView (bActivate, pActivateView, pDeactiveView);
}


//------------------------------------------------------------------------------
// �I�[�o�[���C�h
//------------------------------------------------------------------------------

// �E�B���h�E�X�^�C���̕ύX
BOOL CSekaijuView::PreCreateWindow (CREATESTRUCT& cs) {
	return CView::PreCreateWindow (cs);
}

// �`��(�_�~�[)
void CSekaijuView::OnDraw (CDC* /*pDC*/) {
}

// CSekaijuView ���
BOOL CSekaijuView::OnPreparePrinting (CPrintInfo* pInfo) {	// ����̈������
	return DoPreparePrinting (pInfo);
}

void CSekaijuView::OnBeginPrinting (CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CSekaijuView::OnEndPrinting (CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: �����̌㏈����ǉ����Ă��������B
}


// CSekaijuView �f�f

#ifdef _DEBUG
void CSekaijuView::AssertValid () const
{
	CView::AssertValid ();
}

void CSekaijuView::Dump (CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSekaijuDoc* CSekaijuView::GetDocument () const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf (RUNTIME_CLASS(CSekaijuDoc)));
	return (CSekaijuDoc*)m_pDocument;
}
#endif //_DEBUG



// ����v���r���[���Ƀ��C���t���[���̕���{�^���������ꂽ�Ƃ��ɗU������֐��B
// ����v���r���[��MFC4.0��(SDI����)�Ƃ���B
BOOL CALLBACK _AfxSekaijuPreviewCloseProc (CFrameWnd* pFrameWnd);

// CView::OnFilePrintPreview �̃I�[�o�[���C�h
// ����v���r���[��MFC4.0��(SDI����)�Ƃ���B
void CSekaijuView::OnFilePrintPreview () {
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.

	// must not create this on the frame. Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;
	pState->lpfnCloseProc = _AfxSekaijuPreviewCloseProc;

	if (!DoPrintPreview (AFX_IDD_PREVIEW_TOOLBAR, this,
		RUNTIME_CLASS (CSekaijuPreviewView), pState)) {
		// In derived classes, reverse special window handling
		// here for Preview failure case
		TRACE0("Error: DoPrintPreview failed");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;
	}
}


// CView::DoPrintPreview�̃I�[�o�[���C�h
// ����v���r���[��MFC4.0��(SDI����)�Ƃ���B
BOOL CSekaijuView::DoPrintPreview (UINT nIDResource, CView* pPrintView,
	CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState) {

	ASSERT_VALID_IDR (nIDResource);
	ASSERT_VALID (pPrintView);
	ASSERT (pPreviewViewClass != NULL);
	ASSERT (pPreviewViewClass->IsDerivedFrom (RUNTIME_CLASS (CSekaijuPreviewView)));
	ASSERT (pState != NULL);

	CFrameWnd* pParent = NULL;
	pParent = (CFrameWnd*)AfxGetThread ()->m_pMainWnd;
	ASSERT_VALID (pParent);
	ASSERT_KINDOF (CFrameWnd, pParent);

	CCreateContext context;
	context.m_pNewViewClass = pPreviewViewClass;
	context.m_pCurrentFrame = pParent;
	context.m_pCurrentDoc = GetDocument ();
	context.m_pLastView = this;

	// Create the preview view object

	CSekaijuPreviewView* pView = (CSekaijuPreviewView*)pPreviewViewClass->CreateObject ();
	if (pView == NULL) {
		TRACE0("Error: Failed to create preview view.\n");
		return FALSE;
	}
	ASSERT_KINDOF (CSekaijuPreviewView, pView);
	pView->SetPreviewState (pState); // save pointer

	pParent->OnSetPreviewMode (TRUE, pState); // Take over Frame Window

	// MFC4.0 (SDI�̈���v���r���[���)
	// Create the toolbar from the dialog resource
	CDialogBar* pDialogBar = new CDialogBar;
	pView->SetToolBar(pDialogBar);
	if (!pView->GetToolBar()->Create (pParent, MAKEINTRESOURCE (nIDResource),
		CBRS_TOP, AFX_IDW_PREVIEW_BAR)) {
		TRACE0 ("Error: Preview could not create toolbar dialog.\n");
		pParent->OnSetPreviewMode (FALSE, pState);   // restore Frame Window
		delete pView->GetToolBar ();
		pView->SetToolBar (NULL);
		pView->SetPreviewState (NULL); // do not delete state structure
		delete pView;
		return FALSE;
	}
	pView->GetToolBar ()->m_bAutoDelete = TRUE; // automatic cleanup

	// Create the preview view as a child of the App Main Window.  This
	// is a sibling of this view if this is an SDI app.  This is NOT a sibling
	// if this is an MDI app.

	if (!pView->Create (NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect (0, 0, 0, 0), pParent, AFX_IDW_PANE_FIRST, &context)) {
		TRACE0 ("Error: couldn't create preview view for frame.\n");
		pParent->OnSetPreviewMode (FALSE, pState);   // restore Frame Window
		pView->SetPreviewState (NULL); // do not delete state structure
		delete pView;
		return FALSE;
	}

	// Preview window shown now
	pState->pViewActiveOld = (pParent->GetActiveFrame ()->GetActiveView());
	CSekaijuView* pActiveView = (CSekaijuView*)(pParent->GetActiveFrame()->GetActiveView());
	if (pActiveView != NULL) {
		pActiveView->ActivateView (FALSE, pActiveView, pActiveView);
	}

	if (!pView->SetPrintView (pPrintView)) {
		pView->PreviewClose ();
		return TRUE; // signal that OnEndPrintPreview was called
	}

	// TODO:���̍s��CMDIFrameWnd::OnUpdateFrameTitle����GetActiveDocument�Ńo�O���N�����B
	// CMainFrame���A�N�e�B�u�ȃr���[�����͈̂���v���r���[���݂̂ł���B
	// ����v���r���[���I���ۂɂ�CMainFrame�̃A�N�e�B�u�ȃr���[��NULL�ɖ߂����ƁB
	pParent->SetActiveView (pView); // set active view - even for MDI

	// update toolbar and redraw everything
	pView->GetToolBar()->SendMessage (WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
	pParent->RecalcLayout (); // position and size everything
	pParent->UpdateWindow ();

	return TRUE;
}

// ����v���r���[���Ƀ��C���t���[���̕���{�^���������ꂽ�Ƃ��ɗU������֐��B
// ����v���r���[��MFC4.0��(SDI����)�Ƃ���B
BOOL CALLBACK _AfxSekaijuPreviewCloseProc (CFrameWnd* pFrameWnd) {
	ASSERT_VALID (pFrameWnd);
	CSekaijuPreviewView* pSekaijuPreviewView =
		(CSekaijuPreviewView*)pFrameWnd->GetDlgItem (AFX_IDW_PANE_FIRST);
	pSekaijuPreviewView->PreviewClose ();
	return FALSE;
}


// CView::EndPrintPreview�̃I�[�o�[���C�h
// ����v���r���[��MFC4.0��(SDI����)�Ƃ���B
void CSekaijuView::OnEndPrintPreview (CDC* pDC, CPrintInfo* pInfo, POINT, CPreviewView* pView) {
	ASSERT_VALID (pDC);
	ASSERT_VALID (pView);
	CSekaijuPreviewView* pSekaijuPreviewView = (CSekaijuPreviewView*)pView;

	if (pSekaijuPreviewView->GetPrintView() != NULL) {
		((CSekaijuView*)(pSekaijuPreviewView->GetPrintView()))->EndPrinting (pDC, pInfo);
	}
	CFrameWnd* pParent = (CFrameWnd*)AfxGetThread ()->m_pMainWnd;
	ASSERT_VALID (pParent);
	ASSERT_KINDOF (CFrameWnd, pParent);

	// restore the old main window
	pParent->OnSetPreviewMode (FALSE, pSekaijuPreviewView->GetPreviewState());

	// Force active view back to old one
	// TODO:���̍s��CMDIFrameWnd::OnUpdateFrameTitle����GetActiveDocument�Ńo�O���N�����B
	// CMainFrame���A�N�e�B�u�ȃr���[�����͈̂���v���r���[���݂̂ł���B
	// ����v���r���[���I���ۂɂ�CMainFrame�̃A�N�e�B�u�ȃr���[��NULL�ɖ߂����ƁB
	//pParent->SetActiveView (pSekaijuPreviewView->GetPreviewState()->pViewActiveOld);
	pParent->SetActiveView (NULL);
	if (pParent != GetParentFrame ()) {
		OnActivateView (TRUE, this, this); // re-activate view in real frame
	}
	pSekaijuPreviewView->DestroyWindow (); // destroy preview view
										   // C++ object will be deleted in PostNcDestroy

										   // restore main frame layout and idle message
	pParent->RecalcLayout ();
	pParent->SendMessage (WM_SETMESSAGESTRING, (WPARAM)AFX_IDS_IDLEMESSAGE, 0L);
	pParent->UpdateWindow ();
}
