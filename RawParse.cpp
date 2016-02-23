// RawParse.cpp: CRawParse クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RawRenamer.h"
#include "RawParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CRawParse::CRawParse()
{

}

CRawParse::~CRawParse()
{

}

int CRawParse::Identify(const CString &strName)
{
	m_timeCapt = -1;
    if (m_cf.Open(strName, CFile::modeRead | CFile::typeBinary) == FALSE)
	{
		return 1;
    }

	m_strModel = "";

	WORD wOrder;
	wOrder = m_cf.ReadWord();
	if (wOrder == 0x4949 || wOrder == 0x4d4d) 
	{
		char head[32];
		unsigned hlen, fsize;

		hlen = m_cf.ReadDword();
		m_cf.Seek(0);
		m_cf.Read(head, 32);
		fsize = m_cf.GetLength();
		if (!memcmp(head + 6,"HEAPCCDR",8)) 
		{
			ParseCiff(hlen, fsize - hlen);
		}
		else
		{
			ParseTiffFile(0);
		}
	}
    m_cf.Close();

	if (m_timeCapt == -1) 
	{
		return 1;
	}

	return 0;
}

int CRawParse::ParseCiff(int iBase, int iLength)
{
	int tboff;
	
	int aoff = 0;

	m_cf.Seek(iBase + iLength - 4);
	tboff = m_cf.ReadDword() + iBase;
	m_cf.Seek(tboff);

	int nrecs;
	nrecs = m_cf.ReadWord();
	for (int i = 0; i < nrecs; i++) 
	{
		int save;
		save = m_cf.GetPosition();
		
		int type;
		type = m_cf.ReadWord();

		int len;
		if (type & 0x4000) 
		{
			len = 8;
			type &= 0x3fff;
		}
		else 
		{
			len  = m_cf.ReadDword();

			int roff;
			roff = m_cf.ReadDword();
			aoff = iBase + roff;
			m_cf.Seek(aoff);
		}
		if (type == 0x0032)			/* display as words */
			type |= 0x1000;
		switch (type >> 8) 
		{
			case 0x28:
			case 0x30:
				ParseCiff(aoff, len);
				m_cf.Seek(save + 10);
				continue;
		}
		m_cf.Seek(save + 10);

		if (type == 0x080a)			/* Get the camera name */
		{
			m_cf.Seek(aoff);

//			char name[256];
			m_strMaker = m_cf.ReadString();

			m_strModel = m_cf.ReadString();
		}
		if (type == 0x180e)
		{
			m_cf.Seek(aoff);

			m_cf.Read(&m_timeCapt, sizeof(time_t));
			m_cf.Seek(save + 10);

/*
			struct tm *ptm;
			ptm = gmtime(&time);
			
			m_strCaptT, "%04d:%02d:%02d %02d:%02d:%02d",
					ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
					ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

*/
			break;
		}
	}

	return 0;
}

int CRawParse::ParseTiffFile(int iBase)
{
	int doff;

	m_cf.Seek(iBase);
	m_cf.ReadWord();
	m_cf.ReadWord();
	while (doff = m_cf.ReadDword()) 
	{
		m_cf.Seek(doff + iBase);
		ParseTiff(iBase);
		if (m_strMaker == "Canon") break;
	}

	return 0;
}

int CRawParse::ParseTiff(int iBase)
{
	int entries;

	entries = m_cf.ReadWord();
	while (entries--) 
	{
		int save;
		save = m_cf.GetPosition();

		int tag;
		tag  = m_cf.ReadWord();

		int type;
		type = m_cf.ReadWord();

		int count;
		count= m_cf.ReadDword();

		int slen;
		slen = count;
		if (slen > 128) 
			slen = 128;

		int size[] = { 1,1,1,2,4,8,1,1,2,4,8,4,8 };

		if (count * size[type < 13 ? type:0] > 4)
		{
			int iPos;
			iPos = m_cf.ReadDword() + iBase;

			m_cf.Seek(iPos);
		}

		switch (tag) 
		{
			case 0x10f:			/* Make tag */
				m_strMaker = m_cf.ReadString();
				break;
			case 0x110:			/* Model tag */
				m_strModel = m_cf.ReadString();
				break;
			case 0x132:
			{
				CString sRet;
				sRet = m_cf.ReadString();

				struct tm time;
				sscanf((LPCTSTR)sRet, "%04d:%02d:%02d %02d:%02d:%02d",
						&time.tm_year, &time.tm_mon, &time.tm_mday,
						&time.tm_hour, &time.tm_min, &time.tm_sec);
				time.tm_year -= 1900;
				time.tm_mon--;
				m_timeCapt = mktime(&time);

				time_t timeDiff;
				timeDiff = 60 * 60 * 9;
				m_timeCapt += timeDiff;
				break;
			}
//			case 0x14a:			/* SubIFD tag */
//			{
//				int save2;
//				save2 = ftell(ifp);
//				for (int i = 0; i < count; i++) 
//				{
//					printf("SubIFD #%d:\n", i+1);
//					fseek(ifp, save2 + i * 4, SEEK_SET);
//					fseek(ifp, fget4(ifp) + base, SEEK_SET);
//					parse_tiff(base);
//				}
//				break;
//			}
			case 0x8769:
				int iPos;
				iPos = m_cf.ReadDword() + iBase;
				m_cf.Seek(iPos);
				break;
		}
		m_cf.Seek(save + 12);
		
		if (m_timeCapt != -1)
			break;
	}

	return 0;
}

time_t CRawParse::GetCaptTime()
{
	return m_timeCapt;
}
