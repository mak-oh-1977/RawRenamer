// FolderSelect.h: CFolderSelect クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERSELECT_H__BBCEBCFE_D985_4A02_94E4_A9BDB024A0D8__INCLUDED_)
#define AFX_FOLDERSELECT_H__BBCEBCFE_D985_4A02_94E4_A9BDB024A0D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFolderSelect  
{
public:
	CFolderSelect();
	virtual ~CFolderSelect();

	bool Show(CString* lpstrFolder,CString strIniFolder,bool bAvailNewFolder);

};

#endif // !defined(AFX_FOLDERSELECT_H__BBCEBCFE_D985_4A02_94E4_A9BDB024A0D8__INCLUDED_)
