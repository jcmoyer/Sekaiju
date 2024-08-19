//******************************************************************************
// MIDI�V�[�P���T�[�\�t�g�w���E���x
// ���ʃC���N���[�h�w�b�_�[�t�@�C��
// (C)2002-2021 ���[�Ղ�MIDI�Ղ낶�����Ɓ^����
//******************************************************************************

/* This Source Code Form is subject to the terms of the Mozilla Public */
/* License, v. 2.0. If a copy of the MPL was not distributed with this */
/* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN             // Windows�w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �ꕔ�� CString �R���X�g���N�^�[�͖����I�ł��B

// ��ʓI�Ŗ������Ă����S��MFC�̌x�����b�Z�[�W�̈ꕔ�̔�\�����������܂��B
#define _AFX_ALL_WARNINGS

#include <afxwin.h>               // MFC�̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>               // MFC�̊g������
#include <afxcmn.h>               // MFC��Windows�R�����R���g���[�� �T�|�[�g
#include <afxcontrolbars.h>       // MFC�ɂ����郊�{���ƃR���g���[���o�[�̃T�|�[�g

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


// MIN,MAX,CLIP�}�N��
#ifndef MIN
#define MIN(A,B) ((A)<(B)?(A):(B))
#endif
#ifndef MAX
#define MAX(A,B) ((A)>(B)?(A):(B))
#endif
#ifndef CLIP
#define CLIP(A,B,C) ((B)<(A)?(A):((B)>(C)?(C):(B)))
#endif

// TSIZEOF�}�N�� //20120211�ǉ�
#ifndef TSIZEOF
#define TSIZEOF(STR) (sizeof(STR)/sizeof(TCHAR))
#endif

// ���ʒ萔
#define MAXMIDIINDEVICENUM 16           // �ő�MIDI���̓f�o�C�X��
#define MAXMIDIOUTDEVICENUM 16          // �ő�MIDI�o�̓f�o�C�X��
#define MAXMIDITRACKNUM 65536           // �ő�MIDI�g���b�N��(1��MIDI�f�[�^�ɕt��)
#define MAXMIDIINSTRUMENTNUM 256        // �ő�MIDI�C���X�g�D�������g(*.ins)��
#define MAXTIMERESOLUTION 1920          // TPQN�x�[�X�ɂ�����4�������̍ő�̕���\

// 
