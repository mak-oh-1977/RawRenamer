// RawRenamer.h : RAWRENAMER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_RAWRENAMER_H__EDAE6603_5D87_445A_BB5D_8A6386DC3B44__INCLUDED_)
#define AFX_RAWRENAMER_H__EDAE6603_5D87_445A_BB5D_8A6386DC3B44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CRawRenamerApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� RawRenamer.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CRawRenamerApp : public CWinApp
{
public:
	CRawRenamerApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRawRenamerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CRawRenamerApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RAWRENAMER_H__EDAE6603_5D87_445A_BB5D_8A6386DC3B44__INCLUDED_)
