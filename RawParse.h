// RawParse.h: CRawParse クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAWPARSE_H__8BA204A9_1210_455E_87C0_746F8C6D2C22__INCLUDED_)
#define AFX_RAWPARSE_H__8BA204A9_1210_455E_87C0_746F8C6D2C22__INCLUDED_

#include "FileEx.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRawParse  
{
public:
	time_t GetCaptTime();
	int Identify(const CString& strName);
	CRawParse();
	virtual ~CRawParse();

private:
	time_t m_timeCapt;
	CString m_strModel;
	CString m_strMaker;
	CFileEx m_cf;
	int ParseTiff(int iBase);
	int ParseTiffFile(int iBase);
	int ParseCiff(int iBase, int iLength);
};

#endif // !defined(AFX_RAWPARSE_H__8BA204A9_1210_455E_87C0_746F8C6D2C22__INCLUDED_)
