// CamFileFind.h: CCamFileFind クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMFILEFIND_H__1BFFDD9F_C67D_41A2_88F1_0B0CD26B4F0E__INCLUDED_)
#define AFX_CAMFILEFIND_H__1BFFDD9F_C67D_41A2_88F1_0B0CD26B4F0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCamFileFind  
{
public:
	CCamFileFind();
	virtual ~CCamFileFind();

	int Find(const CString& strDirName, CStringArray& strList, CStatic* pObjMsg, int* piStopFlag);

};

#endif // !defined(AFX_CAMFILEFIND_H__1BFFDD9F_C67D_41A2_88F1_0B0CD26B4F0E__INCLUDED_)
