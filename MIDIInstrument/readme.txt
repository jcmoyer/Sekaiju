/******************************************************************************/
/*                                                                            */
/*  MIDIInstrument���C�u�����u�͂��߂ɂ��ǂ݂��������v     (C)2002-2024 ����  */
/*                                                                            */
/******************************************************************************/

�@���̂��т́AMIDIInstrument���C�u�������_�E�����[�h���Ă��������A���͂��󂯎��
�ɂȂ��Ă��������A���ɂ��肪�Ƃ��������܂��B

�@MIDIInstrument���C�u�����́A�t���[�ŃI�[�v���\�[�X�́AMIDI�C���X�g�D�������g��
�`�̐���E�ҏW�p���C�u�����ł��B���̃��C�u�����́A�C���X�g�D�������g��`�̐����E
�t�@�C������(Cakewalk�p�C���X�g�D�������g��`�t�@�C��(*.ins))�A���F���̒ǉ��E�ύX�E
�Q�ƁE�폜�A�R���g���[���[���̒ǉ��E�ύX�E�Q�ƁE�폜�ȂǁAMIDI�C���X�g�D�������g
��`�̂�����v�f�ɐv���ɃA�N�Z�X����@�\��񋟂��܂��B

�y�Y�t�t�@�C���z

MIDIInstrument
��readme.txt                    �͂��߂ɂ��ǂ݂�������(���̃t�@�C��)
��license.txt                   ���C�Z���X(�����E�p��)
��MIDIInstrument.c              C�\�[�X�t�@�C��
��MIDIInstrument.h              C/C++�p�w�b�_�[�t�@�C��
��MIDIInstrument.def            C/C++�p���W���[����`�t�@�C��(dll�����Ƃ��ɕK�v)
��MIDIInstrument.sln            Visual Studio 2022 Community �p�\�����[�V�����t�@�C��
��MIDIInstrument.vcxproj        Visual Studio 2022 Community �p�v���W�F�N�g�t�@�C��
��MIDIInstrument.vcxproj.filter Visual Studio 2022 Community �p�v���W�F�N�g�t�@�C��
��MIDIInstrument.vcxproj.user   Visual Studio 2022 Community �p�v���W�F�N�g�t�@�C��
��MIDIInstrument.bas            Visual Basic 4.0/5.0/6.0�p�C���|�[�g���W���[��
��Debug
����MIDIInstrumentd.lib         �I�u�W�F�N�g���C�u�������W���[��(�f�o�b�O�p)(32bit)
����MIDIInstrumentd.dll         �_�C�i�~�b�N�����N���C�u����(�f�o�b�O�p)(32bit)
��Release
����MIDIInstrument.lib          �I�u�W�F�N�g���C�u�������W���[��(�����[�X�p)(32bit)
����MIDIInstrument.dll          �_�C�i�~�b�N�����N���C�u����(�����[�X�p)(32bit)
��x64
����Debug
������MIDIInstrumentd.lib       �I�u�W�F�N�g���C�u�������W���[��(�f�o�b�O�p)(64bit)
������MIDIInstrumentd.dll       �_�C�i�~�b�N�����N���C�u����(�f�o�b�O�p)(64bit)
����Release
���@��MIDIInstrument.lib        �I�u�W�F�N�g���C�u�������W���[��(�����[�X�p)(64bit)
���@��MIDIInstrument.dll        �_�C�i�~�b�N�����N���C�u����(�����[�X�p)(64bit)
��docs
�@��MIDIInstrument.html         �����K�C�h�u�b�N
�@��MIDIDR02.gif                �����K�C�h�u�b�N�Ŏg���Ă���}

�y�g�p���@�z

�E���ׂẴt�@�C�����𓀂��Ă��������B
�EMIDIInstrument.h��VisualC++���C���X�g�[�������t�H���_����include�t�H���_���ɃR�s�[���Ă��������B
�EMIDIInstrument.lib��VisualC++���C���X�g�[�������t�H���_����lib�t�H���_���ɃR�s�[���Ă��������B
�EMIDIInstrument.dll(32bit)��MIDIInstrumentd.dll(32bit)�t�@�C����c:\windows\SysWOW64\���ɃR�s�[���Ă��������B
�EMIDIInstrument.dll(64bit)��MIDIInstrumentd.dll(64bit)�t�@�C����c:\windows\System32\���ɃR�s�[���Ă��������B
�EMIDIInstrument���C�u�������g�p����\�[�X�ł́A#include "MIDIInstrument.h"�����s���Ă��������B
�EMIDIInstrument���C�u�������g�p����v���W�F�N�g�ł́AVisual Studio 2022�����g�p�̏ꍇ�A
�@�u�f�o�b�O(D)�v-�u(�v���W�F�N�g��)�̃v���p�e�B�v����u(�v���W�F�N�g��)�̃v���p�e�B�y�[�W�v�Ƃ���
�@�_�C�A���O��\�������A���̒��́u�\���ƃv���p�e�B�v�́u�����J�v�́u���́v�̒��ɁA
�@�u�ǉ��̈ˑ��t�@�C���v�Ƃ������ڂ�����̂ŁA������MIDIInstrumentd.lib������MIDIInstrument.lib����ǉ����Ă��������B
�E�A�v���P�[�V������z�z����ۂɂ́AMIDIInstrument.dll��exe�t�@�C���Ɠ����t�H���_�ɓY�t���Ă��������B
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

