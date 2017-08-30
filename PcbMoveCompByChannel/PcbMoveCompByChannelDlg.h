
// PcbMoveCompByChannelDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"


// диалоговое окно CPcbMoveCompByChannelDlg
class CPcbMoveCompByChannelDlg : public CDialogEx
{
// Создание
public:
	CPcbMoveCompByChannelDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_PCBMOVECOMPBYCHANNEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
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
