// desDlg.h : header file
//

#if !defined(AFX_DESDLG_H__70E4105E_95F2_47ED_8793_7474D107239E__INCLUDED_)
#define AFX_DESDLG_H__70E4105E_95F2_47ED_8793_7474D107239E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDesDlg dialog

class CDesDlg : public CDialog
{
// Construction
public:
	CDesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDesDlg)
	enum { IDD = IDD_DES_DIALOG };
	CButton	m_buttonDecrypt;         //���ܰ�ť
	CButton	m_buttonEncrypt;         //���ܰ�ť
	CString	m_editPath;              //�ļ�·��
	CString	m_editPsw1;              //��Կ1
	CString	m_editPsw2;              //��Կ2
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void cmCheck();                                       //����ļ���׺��,ȷ��������ܻ��ǽ��ܰ�ť
	// Generated message map functions
	//{{AFX_MSG(CDesDlg)
	virtual BOOL OnInitDialog();                          //�Ի����ʼ������
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam); 
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();                          //���ļ�ѡ��Ի�����Ӧ����
	afx_msg void OnDropFiles(HDROP hDropInfo);            //֧���ļ��ϷŹ�����Ӧ����
	afx_msg void OnButtonEncrypt();                       //���ܰ�ť��Ӧ����
	afx_msg void OnSetfocusEditPsw1();                    //��ԿһEDIT���ȡ������Ӧ����
	afx_msg void OnSetfocusEditPsw2();                    //��Կ��EDIT���ȡ������Ӧ����
	afx_msg void OnKillfocusEditPsw1();                   //��ԿһEDIT��ʧȥ������Ӧ����
	afx_msg void OnKillfocusEditPsw2();                   //��ԿһEDIT��ʧȥ������Ӧ����
	afx_msg void OnButtonDecrypt();                       //���ܰ�ť��Ӧ����
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESDLG_H__70E4105E_95F2_47ED_8793_7474D107239E__INCLUDED_)
