
// ComponentList.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CComponentListApp:
// О реализации данного класса см. ComponentList.cpp
//

class CComponentListApp : public CWinApp
{
public:
	CComponentListApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CComponentListApp theApp;