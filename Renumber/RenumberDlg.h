
// RenumberDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CRenumberDlg
class CRenumberDlg : public CDialogEx
{
// ��������
public:
	CRenumberDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_RENUMBER_DIALOG };

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
	CButton OkButton;
	CEdit Edit1;
	CEdit Edit2;
	afx_msg void OnBnClickedRadioMakechanmanual();
	CEdit Edit3;
	CEdit Edit4;
	CButton CheckEco;
	afx_msg void OnBnClickedRadioNormal();
	afx_msg void OnBnClickedRadioModule();
	afx_msg void OnBnClickedRadioMakechan();
	afx_msg void OnBnClickedRadioAddrefdes();
	afx_msg void OnBnClickedCheckEco();
};
