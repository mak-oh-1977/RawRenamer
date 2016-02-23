// RawRenamerDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_RAWRENAMERDLG_H__B46F0021_D609_4A98_90F9_1189878FFAFF__INCLUDED_)
#define AFX_RAWRENAMERDLG_H__B46F0021_D609_4A98_90F9_1189878FFAFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRawRenamerDlg �_�C�A���O
typedef struct {
	CString strFolder;
	int	iFormat;
	CStatic* pMsgObj;
	int iExecute;		// 0:��~�� 1:���s�� 2:��~�v��
	CButton* pBtnObj;
} RENAME_INFO;

class CRawRenamerDlg : public CDialog
{
// �\�z
public:
	CRawRenamerDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CRawRenamerDlg)
	enum { IDD = IDD_RAWRENAMER_DIALOG };
	CButton	m_btnStart;
	CStatic	m_objMsg;
	CString	m_strFolder;
	int		m_iFormat;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRawRenamerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CRawRenamerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnRef();
	afx_msg void OnEnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWinThread* m_pThread;
	RENAME_INFO m_Info;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RAWRENAMERDLG_H__B46F0021_D609_4A98_90F9_1189878FFAFF__INCLUDED_)
