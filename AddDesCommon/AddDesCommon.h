
// AddDesCommon.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CAddDesCommonApp:
// � ���������� ������� ������ ��. AddDesCommon.cpp
//

class CAddDesCommonApp : public CWinApp
{
public:
	CAddDesCommonApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CAddDesCommonApp theApp;