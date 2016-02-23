// RawRenamerDlg.h : ヘッダー ファイル
//

#if !defined(AFX_RAWRENAMERDLG_H__B46F0021_D609_4A98_90F9_1189878FFAFF__INCLUDED_)
#define AFX_RAWRENAMERDLG_H__B46F0021_D609_4A98_90F9_1189878FFAFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRawRenamerDlg ダイアログ
typedef struct {
	CString strFolder;
	int	iFormat;
	CStatic* pMsgObj;
	int iExecute;		// 0:停止中 1:実行中 2:停止要求
	CButton* pBtnObj;
} RENAME_INFO;

class CRawRenamerDlg : public CDialog
{
// 構築
public:
	CRawRenamerDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRawRenamerDlg)
	enum { IDD = IDD_RAWRENAMER_DIALOG };
	CButton	m_btnStart;
	CStatic	m_objMsg;
	CString	m_strFolder;
	int		m_iFormat;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRawRenamerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
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
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RAWRENAMERDLG_H__B46F0021_D609_4A98_90F9_1189878FFAFF__INCLUDED_)
