/******************************************************************************/
/*                                                                            */
/*  IniData���C�u�����u�͂��߂ɂ��ǂ݂��������v            (C)2002-2024 ����  */
/*                                                                            */
/******************************************************************************/

���̂��т́AIniData���C�u�������_�E�����[�h���Ă��������A���͂��󂯎��ɂȂ���
���������A���ɂ��肪�Ƃ��������܂��B

�wIniData���C�u�����x�́A�t���[�ŃI�[�v���\�[�X�́Aini�t�@�C���쐬�E�ҏW�p���C�u
�����ł��B���̃��C�u�����́A*.ini�t�@�C���ւ̍����ȓ��o�́A�X�y�[�X�I���������
����Ȑݒ�E�擾�AUTF-16LE(BOM�t)�EUTF8�ւ̑Ή��A64bit�ւ̑Ή����������ׂ��A�]��
�� GetPrivateProfileString / GetPrivateProfileInt / WritePrivateProfileString ��
��֊֐���񋟂��AIniData_Load�ňꊇ�ǂݍ��݁AIniData_Save
�ňꊇ�ۑ�����@�\��L���܂��B

�{���C�u�����́AC����ŋL�q����Ă���A�������̃Z�N�V�������E���ڐ���ini�t�@�C��
�ɑΉ����Ă���܂��B�ȕւ̂��߁A�R�����g�̓ǂݍ��݂ƕۑ��͏ȗ����Ă��܂��BBOM�Ȃ�
ini�t�@�C���́AANSI�ł͂Ȃ�UTF-8�Ƃ��Ď�舵���܂��B


�y�Y�t�t�@�C���z

IniData
��readme.txt                �͂��߂ɂ��ǂ݂�������(���{��)
��license.txt               ���C�Z���X(�����E�p��)
��PtrArray.c                �ϒ��|�C���^�z��pC�\�[�X�t�@�C��
��PtrArray.h                �ϒ��|�C���^�z��pC/C++�p�w�b�_�[�t�@�C��
��IniData.c                 C�\�[�X�t�@�C��
��IniData.h                 C/C++�p�w�b�_�[�t�@�C��
��IniData.def               C/C++�p���W���[����`�t�@�C��(dll�����Ƃ��ɕK�v)
��IniData.sln               Visual Studio 2022 Community �p�\�����[�V�����t�@�C��
��IniData.vcxproj           Visual Studio 2022 Community �p�v���W�F�N�g���[�N�X�y�[�X
��IniIData.vcxproj.filter   Visual Studio 2022 Community �p�v���W�F�N�g���[�N�X�y�[�X
��IniData.vcxproj.user      Visual Studio 2022 Community �p�v���W�F�N�g���[�N�X�y�[�X
��Debug
����IniDatad.lib            �I�u�W�F�N�g���C�u�������W���[��(�f�o�b�O�p)(32bit)
����IniDatad.dll            �_�C�i�~�b�N�����N���C�u����(�f�o�b�O�p)(32bit)
��Release
����IniData.lib             �I�u�W�F�N�g���C�u�������W���[��(�����[�X�p)(32bit)
����IniData.dll             �_�C�i�~�b�N�����N���C�u����(�����[�X�p)(32bit)
��x64
����Debug
������IniDatad.lib          �I�u�W�F�N�g���C�u�������W���[��(�f�o�b�O�p)(64bit)
������IniDatad.dll          �_�C�i�~�b�N�����N���C�u����(�f�o�b�O�p)(64bit)
����Release
���@��IniData.lib           �I�u�W�F�N�g���C�u�������W���[��(�����[�X�p)(64bit)
���@��IniData.dll           �_�C�i�~�b�N�����N���C�u����(�����[�X�p)(64bit)
��docs
�@��IniData.html            �����K�C�h�u�b�N(���{��)

�y�g�p���@�z

�E���ׂẴt�@�C�����𓀂��Ă��������B
�EIniData.h��VisualC++���C���X�g�[�������t�H���_����include�t�H���_���ɃR�s�[���Ă��������B
�EIniData.lib��VisualC++���C���X�g�[�������t�H���_����lib�t�H���_���ɃR�s�[���Ă��������B
�EIniData.dll(32bit)��IniDatad.dll(32bit)�t�@�C����c:\windows\SysWOW64\���ɃR�s�[���Ă��������B
�EIniData.dll(64bit)��IniDatad.dll(64bit)�t�@�C����c:\windows\System32\���ɃR�s�[���Ă��������B
�EIniData���C�u�������g�p����\�[�X�ł́A#include "IniData.h"�����s���Ă��������B
�EIniData���C�u�������g�p����v���W�F�N�g�ł́AVisual Studio 2022�����g�p�̏ꍇ�A
�@�u�f�o�b�O(D)�v-�u(�v���W�F�N�g��)�̃v���p�e�B�v����u(�v���W�F�N�g��)�̃v���p�e�B�y�[�W�v�Ƃ���
�@�_�C�A���O��\�������A���̒��́u�\���ƃv���p�e�B�v�́u�����J�v�́u���́v�̒��ɁA
�@�u�ǉ��̈ˑ��t�@�C���v�Ƃ������ڂ�����̂ŁA������IniDatad.lib������IniData.lib����ǉ����Ă��������B
�E�A�v���P�[�V������z�z����ۂɂ́AIniData.dll��exe�t�@�C���Ɠ����t�H���_�ɓY�t���Ă��������B
���p�X�͂��g�p�̊��ɍ��킹�ċL�q���Ă��������B

�y���C�Z���X�z

�E���̃��C�u�����́AGNU �򓙈�ʌ��O���p�����_��(LGPL)�Ɋ�Â��Ĕz�z����܂��B
�E���̃��C�u�����͑S���̖��ۏ؂ł��B
�E���̃��C�u�������g�p�������ʐ��������Q�ɂ��܂��č�҂͈�ؐӔC�𕉂��܂���B
�@���炩���߂��������������B
���ڂ����́ALGPL�̓��{���(http://www.opensource.gr.jp/lesser/lgpl.ja.html)�����Q�Ƃ��������B

�y�A����z

�E���[���A�h���X(��) ee65051@yahoo.co.jp
�E�v���W�F�N�g�E�F�u�T�C�g https://openmidiproject.opal.ne.jp/

