/******************************************************************************/
/*                                                                            */
/*  MIDIStatus���C�u�����u�͂��߂ɂ��ǂ݂��������v         (C)2002-2024 ����  */
/*                                                                            */
/******************************************************************************/

�@���̂��т́AMIDIStatus���C�u�������_�E�����[�h���Ă��������A���͂��󂯎���
�Ȃ��Ă��������A���ɂ��肪�Ƃ��������܂��B

�@MIDIStatus���C�u�����́A�t���[�ŃI�[�v���\�[�X�́AMIDI�����̏�ԕێ��E�Q�Ɨp��
�C�u�����ł��B���̃��C�u�����́AMIDI�����̊e���Ղ̉������A�R���g���[���[��v
���O�����i���o�[��s�b�`�x���h�Ȃǂ̏�ԁA�}�X�^�[�{�����[���E�}�X�^�[���o�[�u�E
�}�X�^�[�R�[���X�Ȃǂ̏�Ԃ��L������\���̂��Ǘ����A���ł���Ԃ�ݒ�E�Q�Ƃ���
���Ƃ��ł��܂��B���A���^�C���ŏ�Ԃ��L�^����ɂ́AMIDIStatus�I�u�W�F�N�g�ɑ΂���
MIDI���b�Z�[�W��^���邾���ł��BMIDIStatus�I�u�W�F�N�g�́AMIDI1.0/GM/GM2/GS/XG��
��`�����قƂ�ǂ�MIDI���b�Z�[�W(�V�X�e���G�N�X�N���[�V�u�܂�)��F���ł��܂��B


�y�Y�t�t�@�C���z

MIDIStatus
��readme.txt                  �͂��߂ɂ��ǂ݂�������(���̃t�@�C��)
��license.txt                 ���C�Z���X(�����E�p��)
��MIDIStatus.c                C�\�[�X�t�@�C��
��MIDIStatus.h                C/C++�p�w�b�_�[�t�@�C��
��MIDIStatus.def              C/C++�p���W���[����`�t�@�C��(dll�����Ƃ��ɕK�v)
��MIDIStatus.sln              Visual Studio 2022 Community �p�\�����[�V�����t�@�C��
��MIDIStatus.vcxproj          Visual Studio 2022 Community �p�v���W�F�N�g�t�@�C��
��MIDIStatus.vcxproj.filter   Visual Studio 2022 Community �p�v���W�F�N�g�t�@�C��
��MIDIStatus.vcxproj.user     Visual Studio 2022 Community �p�v���W�F�N�g�t�@�C��
��MIDIStatus.bas              Visual Basic 4.0/5.0/6.0�p�C���|�[�g���W���[��
��Debug
����MIDIStatusd.lib           �I�u�W�F�N�g���C�u�������W���[��(�f�o�b�O�p)(32bit)
����MIDIStatusd.dll           �_�C�i�~�b�N�����N���C�u����(�f�o�b�O�p)(32bit)
��Release
����MIDIStatus.lib            �I�u�W�F�N�g���C�u�������W���[��(�����[�X�p)(32bit)
����MIDIStatus.dll            �_�C�i�~�b�N�����N���C�u����(�����[�X�p)(32bit)
��x64
����Debug
������MIDIStatusd.lib         �I�u�W�F�N�g���C�u�������W���[��(�f�o�b�O�p)(64bit)
������MIDIStatusd.dll         �_�C�i�~�b�N�����N���C�u����(�f�o�b�O�p)(64bit)
����Release
���@��MIDIStatus.lib          �I�u�W�F�N�g���C�u�������W���[��(�����[�X�p)(64bit)
���@��MIDIStatus.dll          �_�C�i�~�b�N�����N���C�u����(�����[�X�p)(64bit)
��docs
�@��MIDIStatus.html           �����K�C�h�u�b�N
�@��MIDIStatus_Fig1-1-1.gif   �����K�C�h�u�b�N�Ŏg���Ă���}


�y�g�p���@�z

�E���ׂẴt�@�C�����𓀂��Ă��������B
�EMIDIStatus.h��VisualC++���C���X�g�[�������t�H���_����include�t�H���_���ɃR�s�[���Ă��������B
�EMIDIStatus.lib��VisualC++���C���X�g�[�������t�H���_����lib�t�H���_���ɃR�s�[���Ă��������B
�EMIDIStatus.dll(32bit)��MIDIStatusd.dll(32bit)�t�@�C����c:\windows\SysWOW64\���ɃR�s�[���Ă��������B
�EMIDIStatus.dll(64bit)��MIDIStatusd.dll(64bit)�t�@�C����c:\windows\System32\���ɃR�s�[���Ă��������B
�EMIDIStatus���C�u�������g�p����\�[�X�ł́A#include "MIDIStatus.h"�����s���Ă��������B
�EMIDIStatus���C�u�������g�p����v���W�F�N�g�ł́AVisual Studio 2022�����g�p�̏ꍇ�A
�@�u�f�o�b�O(D)�v-�u(�v���W�F�N�g��)�̃v���p�e�B�v����u(�v���W�F�N�g��)�̃v���p�e�B�y�[�W�v�Ƃ���
�@�_�C�A���O��\�������A���̒��́u�\���ƃv���p�e�B�v�́u�����J�v�́u���́v�̒��ɁA
�@�u�ǉ��̈ˑ��t�@�C���v�Ƃ������ڂ�����̂ŁA������MIDIStatud.lib������MIDIStatus.lib����ǉ����Ă��������B
�E�A�v���P�[�V������z�z����ۂɂ́AMIDIStatus.dll��exe�t�@�C���Ɠ����t�H���_�ɓY�t���Ă��������B
�E�ڂ����́A���[�Ղ�MIDI�Ղ낶�����Ƃ̎�������FAQ�̃y�[�W���Q�Ƃ��Ă��������B
���p�X�͂��g�p�̊��ɍ��킹�ċL�q���Ă��������B

�y���C�Z���X�z

�@���̃��C�u�����́AGNU �򓙈�ʌ��O���p�����_��(LGPL)�Ɋ�Â��Ĕz�z����܂��B
�E���Ȃ��͂��̃��C�u�������ALGPL�Ɋ�Â��A�����E�]�ځE�z�z���邱�Ƃ��ł��܂��B
�E���Ȃ��͂��̃��C�u���������ς��邱�Ƃ��ł��A�����LGPL�Ɋ�Â��z�z���邱�Ƃ��ł��܂��B
�E���Ȃ��͂��̃��C�u������DLL�𗘗p����(�_�C�i�~�b�N�����N�Ɍ���)�A���Ȃ��Ǝ���
�@���C�Z���X�̃A�v���P�[�V�����𐻍�E�z�z���邱�Ƃ��ł��܂��B
�E������̏ꍇ����҂ɋ��𓾂�K�v�͂���܂���B
�E���̃��C�u�����͑S���̖��ۏ؂ł��B
�@���̃��C�u�������g�p�������ʐ��������Q�ɂ��܂��č�҂͈�ؐӔC�𕉂��܂���B
�@���炩���߂��������������B
���ڂ����́ALGPL�̓��{���(http://www.opensource.gr.jp/lesser/lgpl.ja.html)�����Q�Ƃ��������B

�y�A����z

�E���[���A�h���X(��) ee65051@yahoo.co.jp
�E�v���W�F�N�g�z�[���y�[�W https://openmidiproject.opal.ne.jp/

