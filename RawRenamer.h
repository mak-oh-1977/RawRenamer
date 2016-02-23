// RawRenamer.h : RAWRENAMER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_RAWRENAMER_H__EDAE6603_5D87_445A_BB5D_8A6386DC3B44__INCLUDED_)
#define AFX_RAWRENAMER_H__EDAE6603_5D87_445A_BB5D_8A6386DC3B44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CRawRenamerApp:
// このクラスの動作の定義に関しては RawRenamer.cpp ファイルを参照してください。
//

class CRawRenamerApp : public CWinApp
{
public:
	CRawRenamerApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRawRenamerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CRawRenamerApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RAWRENAMER_H__EDAE6603_5D87_445A_BB5D_8A6386DC3B44__INCLUDED_)
