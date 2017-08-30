
// PcbAddRefDes2Dlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"


// диалоговое окно CPcbAddRefDes2Dlg
class CPcbAddRefDes2Dlg : public CDialogEx
{
// Создание
public:
	CPcbAddRefDes2Dlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_PCBADDREFDES2_DIALOG };

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
	CButton OkButton;
};
