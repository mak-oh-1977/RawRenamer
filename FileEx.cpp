// FileEx.cpp: CFileEx クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RawRenamer.h"
#include "FileEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFileEx::CFileEx()
{

}

CFileEx::~CFileEx()
{

}

WORD CFileEx::ReadWord()
{
	WORD wRet;
	wRet = 0;
	
	Read(&wRet, sizeof(WORD));

	return wRet;
}

DWORD CFileEx::ReadDword()
{
	DWORD dwRet;
	dwRet = 0;

	Read(&dwRet, sizeof(DWORD));

	return dwRet;
}

CString CFileEx::ReadString()
{
	CString strRet;
	strRet = "";

	char pcBuff[64];
	Read(pcBuff, sizeof(pcBuff));

	strRet = pcBuff;
	CFile::Seek((sizeof(pcBuff)  - strRet.GetLength() - 1) * -1, CFile::current);

	return strRet;
}

void CFileEx::Seek(int iOffset)
{
	CFile::Seek(iOffset, CFile::begin);
}
