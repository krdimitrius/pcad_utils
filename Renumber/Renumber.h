
// Renumber.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CRenumberApp:
// � ���������� ������� ������ ��. Renumber.cpp
//

class CRenumberApp : public CWinApp
{
public:
	CRenumberApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CRenumberApp theApp;