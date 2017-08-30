
// PcbMoveCompByChannel.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CPcbMoveCompByChannelApp:
// О реализации данного класса см. PcbMoveCompByChannel.cpp
//

class CPcbMoveCompByChannelApp : public CWinApp
{
public:
	CPcbMoveCompByChannelApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CPcbMoveCompByChannelApp theApp;