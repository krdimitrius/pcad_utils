
// ComponentList.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CComponentListApp:
// � ���������� ������� ������ ��. ComponentList.cpp
//

class CComponentListApp : public CWinApp
{
public:
	CComponentListApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CComponentListApp theApp;