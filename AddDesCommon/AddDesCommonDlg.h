
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
	WCHAR IniFilename[1024];
	long numDesCommon;
	CEdit EditList;
	afx_msg void OnBnClickedRadioSelect();
	afx_msg void OnBnClickedRadioList();
};
