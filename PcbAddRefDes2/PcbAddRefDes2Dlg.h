
// PcbAddRefDes2Dlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CPcbAddRefDes2Dlg
class CPcbAddRefDes2Dlg : public CDialogEx
{
// ��������
public:
	CPcbAddRefDes2Dlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_PCBADDREFDES2_DIALOG };

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
};
