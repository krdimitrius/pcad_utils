
// PcbMoveCompByChannelDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CPcbMoveCompByChannelDlg
class CPcbMoveCompByChannelDlg : public CDialogEx
{
// ��������
public:
	CPcbMoveCompByChannelDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_PCBMOVECOMPBYCHANNEL_DIALOG };

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
	CEdit Edit1;
	CEdit Edit2;
	CEdit Edit3;
	CEdit Edit4;
	CButton OkButton;
//	afx_msg void OnEnChangeEdit2();
};
