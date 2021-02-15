
// AddDesCommonDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CAddDesCommonDlg
class CAddDesCommonDlg : public CDialogEx
{
// ��������
public:
	CAddDesCommonDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_ADDDESCOMMON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox myCombo1;
	CComboBox myCombo2;
	WCHAR IniFilename[1024];
	CEdit EditList;
	CEdit EditFuncblock;
	CEdit EditFit;
	afx_msg void OnBnClickedRadioSelect();
	afx_msg void OnBnClickedRadioList();
	afx_msg void OnBnClickedGet();
	afx_msg void OnBnClickedSave2list();
	afx_msg void OnBnClickedGet2();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedDel2list();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedGet3();
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedGet4();
	afx_msg void OnBnClickedOk4();
};
