
// PcbMoveCompByChannel.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CPcbMoveCompByChannelApp:
// � ���������� ������� ������ ��. PcbMoveCompByChannel.cpp
//

class CPcbMoveCompByChannelApp : public CWinApp
{
public:
	CPcbMoveCompByChannelApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CPcbMoveCompByChannelApp theApp;