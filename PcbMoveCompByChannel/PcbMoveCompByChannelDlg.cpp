
// PcbMoveCompByChannelDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "PcbMoveCompByChannel.h"
#include "PcbMoveCompByChannelDlg.h"
#include "afxdialogex.h"
#include "myDbxUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CPcbMoveCompByChannelDlg


CPcbMoveCompByChannelDlg::CPcbMoveCompByChannelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPcbMoveCompByChannelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPcbMoveCompByChannelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Edit1);
	DDX_Control(pDX, IDC_EDIT2, Edit2);
	DDX_Control(pDX, IDC_EDIT3, Edit3);
	DDX_Control(pDX, IDC_EDIT4, Edit4);
	DDX_Control(pDX, IDOK, OkButton);
}

BEGIN_MESSAGE_MAP(CPcbMoveCompByChannelDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPcbMoveCompByChannelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CPcbMoveCompByChannelDlg

BOOL CPcbMoveCompByChannelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	CString str;
	str = "1";
	Edit1.SetWindowTextW(str);
	Edit2.SetWindowTextW(str);
	str = "0.0";
	Edit3.SetWindowTextW(str);
	Edit4.SetWindowTextW(str);
	CheckDlgButton(IDC_RADIO_FIRSTCHAN, BST_CHECKED);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CPcbMoveCompByChannelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CPcbMoveCompByChannelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//========================================================================================
// рабочая структура
typedef struct COMPONENT_LIST_STRUCT {
	long no_mark;						// номер маркированного компонента
	long redfes_dig;					// цифровая часть обозначения
	char refdes_txt[DBX_MAX_NAME_LEN];	// текстовая часть обозначения
	char refdes[DBX_MAX_NAME_LEN];		// полное обозначение
} COMPONENT_LIST_STRUCT;
//========================================================================================

// сравнение двух элементов по:
//	- текстовой части RefDes
static long compareComponentListElementsByRefDesTxt(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	long result;
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	// сравнение по текстовой части RefDes
	result = strcmp(pComp1->refdes_txt,pComp2->refdes_txt);
	return result;
}

// сравнение двух элементов по:
//	- текстовой части RefDes
//	- цифровой части RefDes
static long compareComponentListElementsByRefDes(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	long result;
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	// сравнение по текстовой части RefDes
	result = strcmp(pComp1->refdes_txt,pComp2->refdes_txt);
	if(result != 0) return result;
	// сравнение по цифровой части RefDes
	result = pComp1->redfes_dig - pComp2->redfes_dig;
	return result;
}

// сортировка компонетов
static void sortComponentList(COMPONENT_LIST_STRUCT *pListComp, long *indexComponents, long num_components, 
	long(* pFunc)(COMPONENT_LIST_STRUCT *,long *, long, long))
{
	long i,j;
	// Гномья сортировка
	i = 1;
	j = 2;
	while(i < num_components)
	{
		if(pFunc(pListComp,indexComponents,i-1,i) < 0)
		{
			i = j;
			j++;
		}
		else
		{
			long k = indexComponents[i-1];
			indexComponents[i-1] = indexComponents[i];
			indexComponents[i] = k;
			i--;
			if(i == 0)
			{
				i = j;
				j++;
			}
		}
	}
}

// получаю число выделенных компонентов в базе
static long getNumberSelectedComponents(void)
{
	TItem myItem; // текущая запись
	long num_components = 0;
	//получаю первый выделенный элемент
	tStatus = TGetFirstSelectedItem(&tContext,&myItem);
	while (tStatus == DBX_OK)
	{
		if(myItem.itemType == DBX_COMPONENT)
			// это компонент !
			num_components++;
		//получаю следующий компонент
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	//возвращаю число компонентов
	return num_components;
}

// получаю число маркированных компонентов в базе
static long getNumberMarkedComponents(void)
{
	TComponent myComponent;	// текуший компонент
	long num_components = 0;
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while(tStatus == DBX_OK)
	{
		TAttribute myAttr;	// текуший компонент
		tStatus = TGetFirstCompAttribute(&tContext,myComponent.refDes,&myAttr);
		while(tStatus == DBX_OK)
		{
			if(strcmp(myAttr.type,attrDesMark) == 0)
			{	// комопнент маркирован !
				num_components++;
				break;
			}
			//получаю следующий атрибут
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext,&myComponent);
	}
	//возвращаю число компонентов
	return num_components;
}

// получаю число компонентов указанного канала группы
static long getNumberChannelComponents(long group, long channel)
{
	TComponent myComponent;	// текуший компонент
	long num_components = 0;
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while(tStatus == DBX_OK)
	{
		TAttribute myAttr;	// текуший компонент
		tStatus = TGetFirstCompAttribute(&tContext,myComponent.refDes,&myAttr);
		long no_channel = 0;
		long no_group = 0;
		while(tStatus == DBX_OK)
		{
			if( (strcmp(myAttr.type,attrNoChannelGroupType) == 0) ||
				(strcmp(myAttr.type,attrNoChannelGroupType1) == 0) )
			{	// атрибут номера группы каналов !
				sscanf_s(myAttr.value,"%d",&no_group);
			}
			else if((strcmp(myAttr.type,attrNoChannelInGroupType) == 0) ||
					(strcmp(myAttr.type,attrNoChannelInGroupType1) == 0) )
			{	// атрибут номера канала !
				sscanf_s(myAttr.value,"%d",&no_channel);
			}
			if( (no_group == group) &&
				(no_channel == channel) )
			{
				num_components++;
				break;
			}
			//получаю следующий атрибут
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext,&myComponent);
	}
	//возвращаю число компонентов
	return num_components;
}

// удаляю макрирование у всех еомпонентов
static void unmarkAllComponents(void)
{
	TComponent myComponent;	// текуший компонент
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while(tStatus == DBX_OK)
	{
		TAttribute myAttr;	// текуший компонент
		tStatus = TGetFirstCompAttribute(&tContext,myComponent.refDes,&myAttr);
		while(tStatus == DBX_OK)
		{
			if(strcmp(myAttr.type,attrDesMark) == 0)
			{	// комопнент маркирован !
				TDeleteCompAttribute(&tContext,myComponent.refDes,&myAttr);
				break;
			}
			//получаю следующий атрибут
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext,&myComponent);
	}
}

// получаю выделенные компоненты
static bool getSelectedComponents(COMPONENT_LIST_STRUCT *pCompList,long *pIndexComp,long *pNumComp)
{
	TItem myItem; // текущая запись
	long num_components = 0;
	//получаю первый выделенный элемент
	tStatus = TGetFirstSelectedItem(&tContext,&myItem);
	while (tStatus == DBX_OK)
	{
		if(myItem.itemType == DBX_COMPONENT)
		{
			// это компонент !
			strcpy_s(pCompList->refdes,DBX_MAX_NAME_LEN,myItem.component.refDes);
			strcpy_s(pCompList->refdes_txt,DBX_MAX_NAME_LEN,myItem.component.refDes);
			char *pStr = myStrpbrkDigit(pCompList->refdes_txt);
			// получаю номер и текстовую часть RefDes
			if(pStr == NULL)
				pCompList->redfes_dig = 0;
			else
			{
				sscanf_s(pStr,"%d",&pCompList->redfes_dig);
				*pStr = 0;
			}
			// инициализирую индекс
			*pIndexComp = num_components;
			num_components++;
			pCompList++;
			pIndexComp++;
		}
		//получаю следующий компонент
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	*pNumComp = num_components;
	return (num_components > 0);
}

// получаю маркированные компоненты
static bool getMarkedComponents(COMPONENT_LIST_STRUCT *pCompList,long *pIndexComp,long *pNumComp)
{
	TComponent myComp; // текущая запись
	long num_components = 0;
	//получаю первый выделенный элемент
	tStatus = TGetFirstComponent(&tContext,&myComp);
	while (tStatus == DBX_OK)
	{
		TAttribute myAttr; // текуший атрибут
		tStatus = TGetFirstCompAttribute(&tContext,myComp.refDes,&myAttr);
		while (tStatus == DBX_OK)
		{
			if(strcmp(myAttr.type,attrDesMark) == 0)
			{	// комопонент помечен !
				strcpy_s(pCompList->refdes,DBX_MAX_NAME_LEN,myComp.refDes);
				strcpy_s(pCompList->refdes_txt,DBX_MAX_NAME_LEN,myComp.refDes);
				char *pStr = myStrpbrkDigit(pCompList->refdes_txt);
				// получаю номер и текстовую часть RefDes
				if(pStr == NULL)
					pCompList->redfes_dig = 0;
				else
				{
					sscanf_s(pStr,"%d",&pCompList->redfes_dig);
					*pStr = 0;
				}
				// инициализирую индекс
				*pIndexComp = num_components;
				num_components++;
				pCompList++;
				pIndexComp++;
				break;
			}
			//получаю следующий атрибут
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext,&myComp);
	}
	*pNumComp = num_components;
	return (num_components > 0);
}

// получаю компоненты указанного канала группы
static bool getChannelComponents(long group, long channel, COMPONENT_LIST_STRUCT *pCompList,long *pIndexComp,long *pNumComp)
{
	TComponent myComp; // текущая запись
	long num_components = 0;
	//получаю первый выделенный элемент
	tStatus = TGetFirstComponent(&tContext,&myComp);
	while (tStatus == DBX_OK)
	{
		TAttribute myAttr; // текуший атрибут
		tStatus = TGetFirstCompAttribute(&tContext,myComp.refDes,&myAttr);
		long no_channel = 0;
		long no_group = 0;
		while (tStatus == DBX_OK)
		{
			if( (strcmp(myAttr.type,attrNoChannelGroupType) == 0) ||
				(strcmp(myAttr.type,attrNoChannelGroupType1) == 0) )
			{	// атрибут номера группы каналов !
				sscanf_s(myAttr.value,"%d",&no_group);
			}
			else if((strcmp(myAttr.type,attrNoChannelInGroupType) == 0) ||
					(strcmp(myAttr.type,attrNoChannelInGroupType1) == 0) )
			{	// атрибут номера канала !
				sscanf_s(myAttr.value,"%d",&no_channel);
			}
			if( (no_group == group) &&
				(no_channel == channel) )
			{	// комопонент первого канала нужной группы !
				strcpy_s(pCompList->refdes,DBX_MAX_NAME_LEN,myComp.refDes);
				strcpy_s(pCompList->refdes_txt,DBX_MAX_NAME_LEN,myComp.refDes);
				char *pStr = myStrpbrkDigit(pCompList->refdes_txt);
				// получаю номер и текстовую часть RefDes
				if(pStr == NULL)
					pCompList->redfes_dig = 0;
				else
				{
					sscanf_s(pStr,"%d",&pCompList->redfes_dig);
					*pStr = 0;
				}
				// инициализирую индекс
				*pIndexComp = num_components;
				num_components++;
				pCompList++;
				pIndexComp++;
				break;
			}
			//получаю следующий атрибут
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext,&myComp);
	}
	*pNumComp = num_components;
	return (num_components > 0);
}

// помечаю выбранные элементы их порядковыми номерами
static bool markSelectedComponents(COMPONENT_LIST_STRUCT *pCompList,long *pIndexComp,long *pNumComp)
{
	TAttribute myAttr = {0};	// текуший атрибут
	char strValue[DBX_MAX_NAME_LEN] = {0};
	// заношу тип атрибута
	strcpy_s(myAttr.type,DBX_MAX_NAME_LEN,attrDesMark);
	myAttr.typeLength = sizeof(myAttr.type);
	for(long i = 0; i < *pNumComp; i++)
	{
		sprintf_s(myAttr.value,DBX_MAX_NAME_LEN,"%d",pIndexComp[i]);
		myAttr.valueLength = sizeof(myAttr.value);
		TAddCompAttribute(&tContext,pCompList[pIndexComp[i]].refdes,&myAttr);
	}						
	return true;
}

// перемещениеи со смещением offset
static bool	moveComp(char * curRefDes, long offsetX, long offsetY)
{
	TComponent myCurComp;	// текущий компонент
	// текущий компонент
	tStatus = TGetCompByRefDes(&tContext,curRefDes,&myCurComp);
	if(tStatus == DBX_OK)
	{
		// перемещаю текущий компонент туда куда нужно
		myCurComp.refPoint.x += offsetX;
		myCurComp.refPoint.y += offsetY;
		TModifyComponent(&tContext,&myCurComp);
		return true;
	}
	else
		return false;
}

// перемещение компонента curRefDes относительно refRefDes со смещением offset
// 26.05.15 основное замечание - не умеет поворачивать компонент и переносить на другую сторону!!!
static bool	moveCompByRef(char * refRefDes, char * curRefDes, long offsetX, long offsetY)
{
	TComponent myRefComp;	// образцовый компонент
	TComponent myCurComp;	// текущий компонент
	TAttribute myAttr;
	TAttribute myAttrRefDes = {0};
	TAttribute myAttrValue = {0};
	TAttribute myAttrRefDes2 = {0};
	// образцовый компонент
	tStatus = TGetCompByRefDes(&tContext,refRefDes,&myRefComp);
	if(tStatus != DBX_OK) return false;
	// текущий компонент
	tStatus = TGetCompByRefDes(&tContext,curRefDes,&myCurComp);
	if(tStatus != DBX_OK) return false;
	// получаю первый атрибут 'опорного' компонента
	tStatus = TGetFirstCompAttribute(&tContext,refRefDes,&myAttr);
	while (tStatus == DBX_OK)
	{	// атрибут найден
		if(strcmp(myAttr.type,"RefDes") == 0)
			memcpy_s(&myAttrRefDes,sizeof(myAttr),&myAttr,sizeof(myAttr));
		else if(strcmp(myAttr.type,"Value") == 0)
			memcpy_s(&myAttrValue,sizeof(myAttr),&myAttr,sizeof(myAttr));
		else if(strcmp(myAttr.type,attrRefDes2) == 0)
			memcpy_s(&myAttrRefDes2,sizeof(myAttr),&myAttr,sizeof(myAttr));
		//получаю следующий атрибут 'опорного' компонента
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	// поворот компонента
	// изменение стороны установки компонента
	if( myCurComp.isFlipped != myRefComp.isFlipped )
	{
		TFlipComponent(&tContext, &myCurComp.refPoint, &myCurComp);
	}
	if( myCurComp.rotationAng != myRefComp.rotationAng )
	{
		long ang;
		if( myRefComp.isFlipped )
			ang = myCurComp.rotationAng - myRefComp.rotationAng;
		else
			ang = myRefComp.rotationAng - myCurComp.rotationAng;
		TRotateComponent(&tContext, ang, &myCurComp.refPoint, &myCurComp);
	}
	// перемещаю туда текущий компонент куда нужно
	myCurComp.refPoint.x = myRefComp.refPoint.x + offsetX;
	myCurComp.refPoint.y = myRefComp.refPoint.y + offsetY;
	TModifyComponent(&tContext,&myCurComp);
	// модифицирую атрибуты текущего компонента
	// получаю первый атрибут 'текущего' компонента
	tStatus = TGetFirstCompAttribute(&tContext,curRefDes,&myAttr);
	while (tStatus == DBX_OK)
	{	// компонент найден - 
		if(strcmp(myAttr.type,"RefDes") == 0)
			modifyCompAttrByRefAttr(&myAttrRefDes,&myAttr,curRefDes,offsetX,offsetY);
		else if(strcmp(myAttr.type,"Value") == 0)
			modifyCompAttrByRefAttr(&myAttrValue,&myAttr,curRefDes,offsetX,offsetY);
		else if(strcmp(myAttr.type,attrRefDes2) == 0)
			modifyCompAttrByRefAttr(&myAttrRefDes2,&myAttr,curRefDes,offsetX,offsetY);
		//получаю следующий атрибут текущего компонента
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	return true;
}

//========================================================================================
static WCHAR myErrorText[][255] = {
	_T("Нет ошибок"),
	_T("Не могу открыть базу PCB"),
	_T("Мало памяти для обработки базы"),
	_T("Число помеченных элементов не совпадает с числом выбранных"),
	_T("Нет помеченных элементов"),
	_T("Нет выбранных элементов"),
	_T("Типы помеченных и выбранных элементов не совпадают"),
	_T("Число элементов в первом и текущем каналах не совпадают"),
	_T("Нет элементов в первом канале"),
	_T("Нет элементов в текущем канале"),
	_T("Типы элементов в первом и текущем каналах не совпадают"),
};

// размещение элементов текущего канала группы относительно элементов первого канала группы
static long processMoveCompByChannel(long group, long channel, long offsetX, long offsetY)
{
	long result = 0;
	COMPONENT_LIST_STRUCT *pCompListCurr = NULL;
	COMPONENT_LIST_STRUCT *pCompListFirst = NULL;
	long *pIndexCompCurr = NULL;
	long *pIndexCompFirst = NULL;
	if((group < 1) || (channel < 1))
		return 1;
	// открываю базу
	if(!openDesignPcb()) return 1;
	while(true)
	{
		long numCompFirst = getNumberChannelComponents(group,1);
		long numCompCurr = getNumberChannelComponents(group,channel);
		if(numCompCurr != numCompFirst)
			{ result = 7; break; }
		else if(numCompFirst < 1)
			{ result = 8; break; }
		else if(numCompCurr < 1)
			{ result = 9; break; }
		pCompListFirst = new COMPONENT_LIST_STRUCT [numCompFirst];
		pCompListCurr = new COMPONENT_LIST_STRUCT [numCompCurr];
		pIndexCompFirst = new long [numCompFirst];
		pIndexCompCurr = new long [numCompCurr];
		if(	(pCompListFirst == NULL) || (pIndexCompFirst == NULL) ||
			(pCompListCurr == NULL) || (pIndexCompCurr == NULL) )
			{ result = 2; break; }
		getChannelComponents(group,1,pCompListFirst,pIndexCompFirst,&numCompFirst);
		getChannelComponents(group,channel,pCompListCurr,pIndexCompCurr,&numCompCurr);

		if(channel == 1)
		{	// первый канал - просто перемещаю
			// перемещаю текущий компонент туда куда нужно
			for(long i = 0; i < numCompFirst; i++)
				moveComp(pCompListFirst[pIndexCompFirst[i]].refdes, offsetX, offsetY);
		}
		else
		{
			// сортирую компоненты первого канала
			sortComponentList(pCompListFirst,pIndexCompFirst,numCompFirst,
				&compareComponentListElementsByRefDes);
			// сортирую компоненты текущего канала
			sortComponentList(pCompListCurr,pIndexCompCurr,numCompCurr,
				&compareComponentListElementsByRefDes);
			// сравниваю списки компонентов
			for(long i = 0; i < numCompCurr; i++)
			{
				if( strcmp(pCompListFirst[pIndexCompFirst[i]].refdes_txt, 
					pCompListCurr[pIndexCompCurr[i]].refdes_txt) != 0)
				{ result = 10; break; }
			}
			if(result != 0) break;
			for(long i = 0; i < numCompCurr; i++)
			{
				moveCompByRef(pCompListFirst[pIndexCompFirst[i]].refdes,
					pCompListCurr[pIndexCompCurr[i]].refdes,
					offsetX, offsetY);
			}
		}
		break;
	}
	delete pCompListFirst;
	delete pCompListCurr;
	delete pIndexCompFirst;
	delete pIndexCompCurr;
	// закрываю базу
	closeDesignPcb();
	return result;
}

// помечаю выбранные компоненты в порядке их refDes
static long processMarkSelectedComponents(void)
{
	long result = 0;
	COMPONENT_LIST_STRUCT *pCompList = NULL;
	long *pIndexComp = NULL;
	// открываю базу		
	if(!openDesignPcb())
		return 1;
	while(true)
	{
		// снимую пометку со всех компонентов
		unmarkAllComponents();
		//получаю число выделенных компонентов
		long numSelectedComp = getNumberSelectedComponents();
		if( numSelectedComp < 1) break;
		pCompList = new COMPONENT_LIST_STRUCT [numSelectedComp];
		if(pCompList == NULL) break;
		pIndexComp = new long [numSelectedComp];
		if(pIndexComp == NULL) break;
		// получаю выделенные компоненты		
		if(!getSelectedComponents(pCompList,pIndexComp,&numSelectedComp))
			break;
		// сортирую выделенные компоненты
		sortComponentList(pCompList,pIndexComp,numSelectedComp,
			&compareComponentListElementsByRefDes);
		// маркирую выделенные компоненты
		markSelectedComponents(pCompList,pIndexComp,&numSelectedComp);
		break;
	}
	delete pCompList;
	delete pIndexComp;
	// закрываю базу
	closeDesignPcb();
	return result;
}

// размещаю выбранные компоненты по типу помеченных
static long processMoveCompByMarked(long offsetX, long offsetY)
{
	long result = 0;
	COMPONENT_LIST_STRUCT *pCompListMark = NULL;
	COMPONENT_LIST_STRUCT *pCompListSlct = NULL;
	long *pIndexCompMark = NULL;
	long *pIndexCompSlct = NULL;
	// открываю базу
	if(!openDesignPcb()) return 1;
	while(true)
	{
		long numCompSlct = getNumberSelectedComponents();
		long numCompMark = getNumberMarkedComponents();
		if(numCompSlct != numCompMark)
			{ result = 3; break; }
		else if(numCompMark < 1)
			{ result = 4; break; }
		else if(numCompSlct < 1)
			{ result = 5; break; }
		pCompListSlct = new COMPONENT_LIST_STRUCT [numCompSlct];
		pCompListMark = new COMPONENT_LIST_STRUCT [numCompMark];
		pIndexCompSlct = new long [numCompSlct];
		pIndexCompMark = new long [numCompMark];
		if( (pCompListSlct == NULL) || (pIndexCompSlct == NULL) ||
			(pCompListMark == NULL) || (pIndexCompMark == NULL) )
			{ result = 2; break; }
		getSelectedComponents(pCompListSlct,pIndexCompSlct,&numCompSlct);
		getMarkedComponents(pCompListMark,pIndexCompMark,&numCompMark);
		// сортирую выделенные компоненты
		sortComponentList(pCompListSlct,pIndexCompSlct,numCompSlct,
			&compareComponentListElementsByRefDes);
		// сортирую помеченные компоненты
		sortComponentList(pCompListMark,pIndexCompMark,numCompMark,
			&compareComponentListElementsByRefDes);
		// сравниваю списки компонентов
		for(long i = 0; i < numCompSlct; i++)
		{
			if( strcmp(pCompListMark[pIndexCompMark[i]].refdes_txt, 
				pCompListSlct[pIndexCompSlct[i]].refdes_txt) != 0)
			{ result = 6; break; }
		}
		if(result != 0) break;
		for(long i = 0; i < numCompSlct; i++)
		{
			moveCompByRef(pCompListMark[pIndexCompMark[i]].refdes,
				pCompListSlct[pIndexCompSlct[i]].refdes,
				offsetX, offsetY);
		}
		break;
	}
	delete pCompListMark;
	delete pCompListSlct;
	delete pIndexCompMark;
	delete pIndexCompSlct;
	// закрываю базу
	closeDesignPcb();
	return result;
}

// перемещает выбранные компоненты
static long processMoveSelectedComponents(long offsetX, long offsetY)
{
	long result = 0;
	COMPONENT_LIST_STRUCT *pCompListSlct = NULL;
	long *pIndexCompSlct = NULL;
	// открываю базу
	if(!openDesignPcb()) return 1;
	while(true)
	{
		long numCompSlct = getNumberSelectedComponents();
		if(numCompSlct < 1)
			{ result = 5; break; }
		pCompListSlct = new COMPONENT_LIST_STRUCT [numCompSlct];
		pIndexCompSlct = new long [numCompSlct];
		if((pCompListSlct == NULL) || (pIndexCompSlct == NULL))
			{ result = 2; break; }
		getSelectedComponents(pCompListSlct,pIndexCompSlct,&numCompSlct);
		for(long i = 0; i < numCompSlct; i++)
			moveComp(pCompListSlct[i].refdes,offsetX, offsetY);
		break;
	}
	delete pCompListSlct;
	delete pIndexCompSlct;
	// закрываю базу
	closeDesignPcb();
	return result;
}

// снимает пометки
static long processUnmark(void)
{
	if(!openDesignPcb()) return 1;
	unmarkAllComponents();
	closeDesignPcb();
	return 0;
}

// возвращает смещение
static long str2offset(LPCWSTR cstr)
{
	int i;
	WCHAR str[10] = {0};
	LPCWSTR pstr;
	long offset = 0;
	bool minus = false;
	//
	do { 
		// ищу знак
		pstr = StrPBrkW(cstr,_T("-"));
		if( pstr != NULL )
		{
			cstr = pstr;
			minus = true;
		}
		// ищу начало целой части
		cstr = StrPBrkW(cstr,_T("0123456789.,"));
		if( cstr == NULL ) break;
		if( (cstr[0] != '.') && (cstr[0] != ',') )
		{
			// получаю целую часть
			offset += StrToIntW(cstr) * 100000;
			// ищу разделитель
			cstr = StrPBrkW(cstr,_T(".,"));
			if( cstr == NULL ) break;
		}
		// ищу начало дробной части
		cstr = StrPBrkW(cstr,_T("0123456789"));
		if( cstr == NULL ) break;
		// получаю дробную часть
		StrCpyN(str, cstr, 5);
		for( i = 0; i < 5; i++ )
		{
			if( str[i] == 0 )
				str[i] = '0';
		}
		offset += StrToIntW(str);
	} while(false);
	// учитываю знак 
	if( minus ) offset *= -1;
	return offset;
}

//===================================================================================
void CPcbMoveCompByChannelDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	long result = 0;
	// гашу кнопку
	OkButton.EnableWindow(false);
	// читаю настройки
	CString cstr;
	// смещение X
	Edit3.GetWindowTextW(cstr);
	long offsetX = str2offset(cstr.GetString());
	// смещение Y
	Edit4.GetWindowTextW(cstr);
	long offsetY = str2offset(cstr.GetString());
	//
	switch(GetCheckedRadioButton(IDC_RADIO_FIRSTCHAN,IDC_RADIO_UNMARK))
	{
	case IDC_RADIO_FIRSTCHAN:
		{
			// номер группы каналов
			Edit1.GetWindowTextW(cstr);
			long group = StrToIntW(cstr);
			// номер канала в группе каналов
			Edit2.GetWindowText(cstr);
			LPCWSTR str = cstr.GetString();
			long i = 1;
			while(str != NULL)
			{
				long channel,channel_end;
				// ищу начало субстроки
				str = StrPBrkW(str,_T("0123456789"));
				if(str == NULL) break;
				channel = StrToIntW(str);
				if(channel < 1) break;
				channel_end = channel;
				// ищу возможное указание диапазона каналов
				LPCWSTR	str1 = StrPBrkW(str,_T("-"));
				if(str1 != NULL)
				{
					str1 = StrPBrkW(str1,_T("0123456789"));
					if(str1 != NULL)
						channel_end = StrToIntW(str1);
					str = str1;
				}
				// перемещаю указанный канал	
				while(channel <= channel_end)
				{
					result = processMoveCompByChannel(group, channel, offsetX*i, offsetY*i);
					channel++;
					i++;
				}
				// ищу конец строки субстроки
				str = StrPBrkW(str,_T(" ;,."));
			}
		}
		break;
	case IDC_RADIO_MOVE:
		result = processMoveSelectedComponents(offsetX,offsetY);
		break;
	case IDC_RADIO_MAKEMARK:
		result = processMarkSelectedComponents();
		break;
	case IDC_RADIO_MOVESELMARK:
		result = processMoveCompByMarked(offsetX,offsetY);
		break;
	case IDC_RADIO_UNMARK:
		result = processUnmark();
		break;
	}
	if(result)
		MessageBox(myErrorText[result],_T("Ошибка"),MB_OK);
	//
	CDialogEx::OnOK();
}


