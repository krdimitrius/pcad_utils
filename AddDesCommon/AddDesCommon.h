
// AddDesCommon.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CAddDesCommonApp:
// О реализации данного класса см. AddDesCommon.cpp
//

class CAddDesCommonApp : public CWinApp
{
public:
	CAddDesCommonApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CAddDesCommonApp theApp;