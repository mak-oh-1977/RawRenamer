// RawRenamerDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "RawRenamer.h"
#include "RawRenamerDlg.h"
#include "FolderSelect.h"
#include "RawParse.h"
#include "CamFileFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRawRenamerDlg �_�C�A���O

CRawRenamerDlg::CRawRenamerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRawRenamerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRawRenamerDlg)
	m_strFolder = _T("");
	m_iFormat = -1;
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRawRenamerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRawRenamerDlg)
	DDX_Control(pDX, IDOK, m_btnStart);
	DDX_Control(pDX, IDC_MSG, m_objMsg);
	DDX_Text(pDX, IDC_FOLDER, m_strFolder);
	DDX_CBIndex(pDX, IDC_FORMAT, m_iFormat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRawRenamerDlg, CDialog)
	//{{AFX_MSG_MAP(CRawRenamerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REF, OnRef)
	ON_BN_CLICKED(IDC_END, OnEnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRawRenamerDlg ���b�Z�[�W �n���h��

BOOL CRawRenamerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	CWinApp* pApp = AfxGetApp();
	m_strFolder = pApp->GetProfileString("Data", "Folder", "");
	m_iFormat = pApp->GetProfileInt("Data", "Format", 0);

	m_Info.iExecute = 0;

	UpdateData(FALSE);

	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

void CRawRenamerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CRawRenamerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CRawRenamerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

UINT ThreadProcess( LPVOID pParam )
{
	ASSERT(pParam != NULL);

	RENAME_INFO* pInfo = (RENAME_INFO*)pParam;
	pInfo->iExecute = 1;

	CCamFileFind ff;
	CStringArray strList;
	ff.Find(pInfo->strFolder, strList, pInfo->pMsgObj, &pInfo->iExecute);	

	int iSize;
	iSize = strList.GetSize();
	for(int i = 0; i < iSize; i++)
	{
		if (pInfo->iExecute == 2)
		{
			pInfo->iExecute = 0;
			return 0;
		}

		CString strSrcFile;
		strSrcFile = strList.GetAt(i);
		CRawParse rp;
		rp.Identify(strSrcFile);

		time_t tm;
		tm = rp.GetCaptTime();
		if (tm < 0)
			continue;

		struct tm* pTime;
		pTime = gmtime(&tm);

		CString strTime;

		switch(pInfo->iFormat)
		{
			case 0:
				strTime.Format("%02d%02d%02d_%02d%02d%02d", 
						(pTime->tm_year + 1900) % 100, pTime->tm_mon +	1, pTime->tm_mday,
						pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
				break;
			case 1:
				strTime.Format("%02d%02d%02d", 
						pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
				break;
			default:
				break;
		}

		CString strDstDir;
		strDstDir = strSrcFile.Left(strSrcFile.ReverseFind('\\'));

		CString strExt;
		strExt = strSrcFile.Mid(strSrcFile.ReverseFind('.'));
		int iCnt = 0;
		while(1)
		{		
			if (pInfo->iExecute == 2)
			{
				pInfo->iExecute = 0;
				return 0;
			}

			CString strDstFile;

			if (iCnt == 0)
			{
				strDstFile = strDstDir + "\\" + strTime + strExt;
			}
			else
			{
				CString strCnt;
				strCnt.Format("_%d", iCnt);
				strDstFile = strDstDir + "\\" + strTime + strCnt + strExt;
			}

			if (::MoveFile(strSrcFile, strDstFile) == TRUE)
			{
				CString s;
				s.Format("%d/%d\n%s\n%s\n", 
						i + 1, 
						iSize, 
						strSrcFile, strDstFile);
				
				TRACE(s);
				pInfo->pMsgObj->SetWindowText(s);
				break;
			}
			else
			{
				iCnt++;
			}
		}


	}
	pInfo->iExecute = 0;
	pInfo->pBtnObj->SetWindowText("�J�n");

	AfxMessageBox("���l�[���I��", MB_ICONINFORMATION);

	return 0;
}

void CRawRenamerDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	UpdateData();

	if (m_Info.iExecute == 1)
	{
		m_Info.iExecute = 2;
		while(m_Info.iExecute != 0)
			Sleep(1);
		AfxMessageBox("���f���܂���", MB_ICONINFORMATION);
		m_btnStart.SetWindowText("�J�n");

		return;
	}

	if (m_strFolder.GetLength() == 0)
	{
		AfxMessageBox("�t�H���_���w�肵�Ă�������", MB_ICONEXCLAMATION);
		return;
	}

	m_Info.strFolder = m_strFolder;
	m_Info.iFormat = m_iFormat;
	m_Info.pMsgObj = &m_objMsg;
	m_Info.pBtnObj = &m_btnStart;

	m_pThread = AfxBeginThread(ThreadProcess, &m_Info);

	m_btnStart.SetWindowText("���f");
}

void CRawRenamerDlg::OnRef() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData();

	CFolderSelect fs;
	CString	strFolder;
	if (fs.Show(&strFolder, m_strFolder, false) == true)
		m_strFolder = strFolder;

	UpdateData(FALSE);
	
}

void CRawRenamerDlg::OnEnd() 
{
	UpdateData();

	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString("Data", "Folder", m_strFolder);
	pApp->WriteProfileInt("Data", "Format", m_iFormat);	

	CDialog::OnCancel();
}
