// CamFileFind.cpp: CCamFileFind �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CamFileFind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CCamFileFind::CCamFileFind()
{

}

CCamFileFind::~CCamFileFind()
{

}

int CCamFileFind::Find(const CString& strDirName, CStringArray& strList, CStatic* pObjMsg, int* piStopFlag)
{
	pObjMsg->SetWindowText(strDirName + "\n���������E�E�E");

	if (*piStopFlag == 2)
		return 0;

	CFileFind FileFind;

	// ���ׂẴt�@�C��������
	CString strSearchFile = strDirName + _T("\\*.*");

	if(!FileFind.FindFile(strSearchFile)) 
		return 0; 

	BOOL bContinue = TRUE;
	while(bContinue)
	{ 
		if (*piStopFlag == 2)
			return 0;

		bContinue = FileFind.FindNextFile();
    
		// �h�b�g("." , "..")�̏ꍇ ����
		if(FileFind.IsDots()) 
			continue; 
    
		// �f�B���N�g���̏ꍇ�A���̃f�B���N�g�������������邽�ߍċN�Ăяo��
		if(FileFind.IsDirectory()) 
		{
			Find(FileFind.GetFilePath(), strList, pObjMsg, piStopFlag); 
		}
		else 
		{
			CString strFileName;
			strFileName = FileFind.GetFilePath();
			CString strExt;
			int iIndex;
			iIndex = strFileName.ReverseFind('.');
			if (iIndex != -1)
			{
				strExt = strFileName.Mid(iIndex + 1);
				strExt.MakeUpper();
				if (strExt == "CRW" || strExt == "CR2")
					strList.Add(strFileName);
			}
		}
	}; 
	return 0;
}
