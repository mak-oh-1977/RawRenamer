// FolderSelect.cpp: CFolderSelect クラスのインプリメンテーション
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
// 構築/消滅
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

//	初期フォルダ設定用のコールバック関数
int		CALLBACK	_SHBrowseForFolderCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if(uMsg == BFFM_INITIALIZED)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	return	0;
}


//
//	フォルダー選択ダイアログの表示
//
//		結果は"c:\windows\"のように末尾に必ず"\"が付加する
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
			strIniFolder = strIniFolder.Left(strIniFolder.GetLength() - 1);			//末尾の\\を除去
	}

	::SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &lpidlRoot);	//選択可能フォルダ名取得

	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot		= lpidlRoot;
	sInfo.pszDisplayName = lpszPath;
	sInfo.lpszTitle		= _T("フォルダの選択");
	sInfo.ulFlags		= BIF_RETURNONLYFSDIRS;
	if(bAvailNewFolder == true)
		sInfo.ulFlags	|= BIF_EDITBOX | BIF_NEWDIALOGSTYLE | BIF_USENEWUI;
	sInfo.lpfn			= _SHBrowseForFolderCallbackProc;
	sInfo.lParam		= (LPARAM)strIniFolder.GetBuffer(0);

	lpidlBrowse = ::SHBrowseForFolder(&sInfo);			//フォルダ選択ダイアログ表示
	if(lpidlBrowse != NULL)
	{
		::SHGetPathFromIDList(lpidlBrowse,lpszPath);	//フォルダ名の取得
		*lpstrFolder = lpszPath;

		if(*lpstrFolder != "")
		{
			if(lpstrFolder->Right(1) != "\\")
				*lpstrFolder += "\\";			//末尾に\\が付加することを保証
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

