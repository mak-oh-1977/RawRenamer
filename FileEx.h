// FileEx.h: CFileEx クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEEX_H__389EB0B9_5ABA_445E_BB79_5E321160304C__INCLUDED_)
#define AFX_FILEEX_H__389EB0B9_5ABA_445E_BB79_5E321160304C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileEx : public CFile  
{
public:
	void Seek(int iOffset);
	CString ReadString();
	DWORD ReadDword();
	WORD ReadWord();
	CFileEx();
	virtual ~CFileEx();

};

#endif // !defined(AFX_FILEEX_H__389EB0B9_5ABA_445E_BB79_5E321160304C__INCLUDED_)
