// FolderSelect.cpp: CFolderSelect �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FolderSelect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CFolderSelect::CFolderSelect()
{

}

CFolderSelect::~CFolderSelect()
{

}



#ifndef	BIF_NEWDIALOGSTYLE
	#define		BIF_NEWDIALOGSTYLE		0x0040
#endif

#ifndef	BIF_USENEWUI
	#define		BIF_USENEWUI			0x0050
#endif

//	�����t�H���_�ݒ�p�̃R�[���o�b�N�֐�
int		CALLBACK	_SHBrowseForFolderCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if(uMsg == BFFM_INITIALIZED)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	return	0;
}


//
//	�t�H���_�[�I���_�C�A���O�̕\��
//
//		���ʂ�"c:\windows\"�̂悤�ɖ����ɕK��"\"���t������
//
bool CFolderSelect::Show(CString* lpstrFolder,CString strIniFolder,bool bAvailNewFolder)
{
	bool			ret;
	char			lpszPath[MAX_PATH];
	LPMALLOC		lpMalloc;
	BROWSEINFO		sInfo;
	LPITEMIDLIST	lpidlRoot;
	LPITEMIDLIST	lpidlBrowse;

	if(lpstrFolder == NULL)
		return	false;

	if(::SHGetMalloc(&lpMalloc) != NOERROR)
		return	false;

	ret = false;
	*lpstrFolder = "";
	if(strIniFolder != "")
	{
		if(strIniFolder.Right(1) == "\\")
			strIniFolder = strIniFolder.Left(strIniFolder.GetLength() - 1);			//������\\������
	}

	::SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &lpidlRoot);	//�I���\�t�H���_���擾

	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot		= lpidlRoot;
	sInfo.pszDisplayName = lpszPath;
	sInfo.lpszTitle		= _T("�t�H���_�̑I��");
	sInfo.ulFlags		= BIF_RETURNONLYFSDIRS;
	if(bAvailNewFolder == true)
		sInfo.ulFlags	|= BIF_EDITBOX | BIF_NEWDIALOGSTYLE | BIF_USENEWUI;
	sInfo.lpfn			= _SHBrowseForFolderCallbackProc;
	sInfo.lParam		= (LPARAM)strIniFolder.GetBuffer(0);

	lpidlBrowse = ::SHBrowseForFolder(&sInfo);			//�t�H���_�I���_�C�A���O�\��
	if(lpidlBrowse != NULL)
	{
		::SHGetPathFromIDList(lpidlBrowse,lpszPath);	//�t�H���_���̎擾
		*lpstrFolder = lpszPath;

		if(*lpstrFolder != "")
		{
			if(lpstrFolder->Right(1) != "\\")
				*lpstrFolder += "\\";			//������\\���t�����邱�Ƃ�ۏ�
		}

		ret = true;
	}

	if(lpidlBrowse != NULL)
		::CoTaskMemFree(lpidlBrowse);
	if(lpidlRoot != NULL)
		::CoTaskMemFree(lpidlRoot);

	lpMalloc->Release();

	return	ret;
}

