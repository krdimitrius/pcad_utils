
// RenumberDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Renumber.h"
#include "RenumberDlg.h"
#include "afxdialogex.h"
#include "dbx32.h"
#include "myDbxUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const char sVersion[] = "1.0.0.5";
static const char sName[] = "Renumber Utility";

// диалоговое окно CRenumberDlg
CRenumberDlg::CRenumberDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRenumberDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, OkButton);
	DDX_Control(pDX, IDC_EDIT1, Edit1);
	DDX_Control(pDX, IDC_EDIT2, Edit2);
	DDX_Control(pDX, IDC_EDIT3, Edit3);
	DDX_Control(pDX, IDC_EDIT4, Edit4);
	DDX_Control(pDX, IDC_CHECK_ECO, CheckEco);
}

BEGIN_MESSAGE_MAP(CRenumberDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRenumberDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_MAKECHANMANUAL, &CRenumberDlg::OnBnClickedRadioMakechanmanual)
	ON_BN_CLICKED(IDC_RADIO_NORMAL, &CRenumberDlg::OnBnClickedRadioNormal)
	ON_BN_CLICKED(IDC_RADIO_MODULE, &CRenumberDlg::OnBnClickedRadioModule)
	ON_BN_CLICKED(IDC_RADIO_MAKECHAN, &CRenumberDlg::OnBnClickedRadioMakechan)
	ON_BN_CLICKED(IDC_RADIO_ADDREFDES, &CRenumberDlg::OnBnClickedRadioAddrefdes)
	ON_BN_CLICKED(IDC_CHECK_ECO, &CRenumberDlg::OnBnClickedCheckEco)
END_MESSAGE_MAP()


// обработчики сообщений CRenumberDlg

BOOL CRenumberDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	CString name;
	name = sName;
	name += _T(" v.");
	name += sVersion;

	CDialogEx::SetWindowTextW(name);

	CheckDlgButton(IDC_RADIO_NORMAL, BST_CHECKED);
	CheckDlgButton(IDC_RADIO_DIRECTION1, BST_CHECKED);

	Edit1.ShowWindow(0);
	Edit2.ShowWindow(0);
	Edit3.ShowWindow(0);
	Edit4.ShowWindow(0);
	CheckEco.ShowWindow(1);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CRenumberDlg::OnPaint()
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
HCURSOR CRenumberDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//========================================================================================
// рабочая структура
typedef struct COMPONENT_LIST_STRUCT {
	long coord1;						// координата привязки 1
	long coord2;						// координата привязки 1
	long sheet;							// номер листа
	long channel;						// номер каналa в группе 
	long group;							// номер группы каналов
	char refdes_txt[DBX_MAX_NAME_LEN];	// текстовая часть обозначения
	char refdes_old[DBX_MAX_NAME_LEN];	// старое обозначение
	union {
		char refdes_new[DBX_MAX_NAME_LEN];	// новое обозначение
		char link[DBX_MAX_NAME_LEN];	//link
	};
} COMPONENT_LIST_STRUCT;
//========================================================================================

/**
 * @brief Получение имени файла
 * @param pFilename_p  Указатель на имя файла.
 * @return true, если имя получено.
 */
static bool
getDesignFilename(char * pFilename_p)
{
	TDesign tDesignInfo;
	//получаю информацию о базе
	tStatus = TGetDesignInfo(&tContext, &tDesignInfo);
	if(tStatus == DBX_OK)
		strncpy_s(pFilename_p, DBX_MAX_NAME_LEN, tDesignInfo.designName, DBX_MAX_NAME_LEN);
	else
		strcpy_s(pFilename_p, DBX_MAX_NAME_LEN, "design");
	return true;
}

/**
 * @brief Получение имени ECO-файла из имени файла
 * @param pFilename_p  Указатель на имя файла.
 * @return true, если имя получено.
 */
static bool
getEcoFilename(char * pFilename_p)
{
	bool result = true;
	TDesign tDesignInfo;
	//получаю информацию о базе
	tStatus = TGetDesignInfo(&tContext, &tDesignInfo);
	if(tStatus == DBX_OK) {
		char *pStr;
		strncpy_s(pFilename_p, DBX_MAX_NAME_LEN, tDesignInfo.designName, DBX_MAX_NAME_LEN);
		pStr = strrchr(pFilename_p, '.');
		if(pStr != NULL)
			*pStr = 0;			
	}
	else
		strcpy_s(pFilename_p, DBX_MAX_NAME_LEN, "design");

	// добавляю расширение
	strcat_s(pFilename_p, DBX_MAX_NAME_LEN, ".ECO");

	return result;
}

/**
 * @brief Функция открытия ECO-файла
 * @return true, если файл открыт
 */
static FILE *
openEcoFile(void)
{
	bool result = true;
	char sFilename[DBX_MAX_NAME_LEN*5];
	char sEcoFilename[DBX_MAX_NAME_LEN*5];
	FILE * hEcoFile = NULL;

	// получаю имя базы
	if (result)
		result = getDesignFilename(sFilename);

	// получаю имя ECO
	if (result)
		result = getEcoFilename(sEcoFilename);

	// открываю ECO
	if (result)
		result = (fopen_s(&hEcoFile, sEcoFilename, "a") == 0);

	// пишу заголовок
	if (result) 
		fprintf(hEcoFile, "; %s Version %s [%s]\n", sName, sVersion, sFilename);

	return (result) ? (hEcoFile) : (NULL);
}

/**
 * @brief Запись строки в ECO-файл
 * @param pStr_p  Указатель на строку.
 * @param idx_p   Индекс записи:
 *   0 - первая часть;
 *   1 - вторая часть.
 */
static void
writeEcoFile(FILE * hEcoFile_p, char * pStr_p, int idx_p)
{
	if (hEcoFile_p != NULL) {
		if (idx_p == 0)
			fprintf(hEcoFile_p, "RefdesChange \"%s\" ", pStr_p);
		else
			fprintf(hEcoFile_p, "\"%s\"\n", pStr_p);
	}
}

/**
 * @brief Закрытие ECO-файла
 */
static void
closeEcoFile(FILE * hEcoFile_p)
{
	if (hEcoFile_p != NULL)
		fclose(hEcoFile_p);
}

/*
// сравнение двух элементов по Id (для сортировки по уменьшению)
static long compareComponentListElementsByIdDecrease(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	if( pComp1->id > pComp2->id ) return -1;
	if( pComp1->id < pComp2->id ) return 1;
	return 0;
}

// сравнение двух элементов по Id (для сортировки по увеличению)
static long compareComponentListElementsByIdIncrease(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	if( pComp1->id > pComp2->id ) return 1;
	if( pComp1->id < pComp2->id ) return -1;
	return 0;
}
*/
// сравнение двух элементов по положению в схеме
static long compareComponentListElementsByPlacement(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	long result;
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	// сравнение по странице
	result = pComp1->sheet - pComp2->sheet;
	if(result != 0) return result;
	// сравнение по координате 2
	result = pComp1->coord2 - pComp2->coord2;
	if(result != 0) return result;
	// сравнение по координате 1
	result = pComp1->coord1 - pComp2->coord1;
	return result;
}

// сравнение двух элементов по:
//	- текстовой части RefDes
//	- группе каналов
//	- номеру канала внутри группы каналов
//	- положению в схеме
static long compareComponentListElementsByChannels(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	long result;
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	// сравнение по RefDes
	result = strcmp(pComp1->refdes_txt,pComp2->refdes_txt);
	if(result != 0) return result;
	// сравнение по группам каналов
	result = pComp1->group - pComp2->group;
	if(result != 0) return result;
	// сравнение по каналу внутри группы
	result = pComp1->channel - pComp2->channel;
	if(result != 0) return result;
	// сравнение по положению в схеме
	return compareComponentListElementsByPlacement(listComp,indexComponents,index1,index2);
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

// открываю базу
static bool openDesign(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "sch",&tContext) == DBX_OK)
		return true;
	MessageBox(NULL,_T("Ошибка открытия базы !"),_T("Ошибка"),MB_OK);
	return false;
}

// закрываю базу
static bool closeDesign(void)
{
	TCloseDesign(&tContext,"");
	return true;
}

// возвращает true если компонент - виртуальный канал
static bool isChannelNormalComponent(TComponent *pComponent)
{
	if(pComponent->connectionType == DBX_COMPONENT_CONNECTION_NORMAL)
	{	
		TAttribute myAttr;	// текуший атрибут компонента
		// получаю первый атрибут
		tStatus = TGetFirstCompAttribute(&tContext,pComponent->refDes,&myAttr);
		while (tStatus == DBX_OK)
		{
			// атрибут с номером канала в группе
			if(strcmp(myAttr.type, attrDesChannel) == 0)
				return true;
			//получаю следующий атрибут
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
	}
	return false;
}

// возвращает true если компонент соответствует заданному типу
static bool isProcessComponent(long connectionType,TComponent *pComponent)
{
	if(connectionType == DBX_COMPONENT_CONNECTION_NORMAL)
	{
		return ((pComponent->connectionType == DBX_COMPONENT_CONNECTION_NORMAL) &&
			(isChannelNormalComponent(pComponent) == false));
	}
	else if(connectionType == DBX_COMPONENT_CONNECTION_MODULE)
	{
		return ((pComponent->connectionType == DBX_COMPONENT_CONNECTION_MODULE) ||
			(isChannelNormalComponent(pComponent) == true));
	}
	else 
		return (pComponent->connectionType == DBX_COMPONENT_CONNECTION_LINK);
	return false;
}

// получаю число компонентов в базе
static long getNumberComponents(long connectionType)
{
	TComponent myComponent;
	long num_components = 0;
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while (tStatus == DBX_OK)
	{
		// компонент соответствует заданному типу ?
		if(isProcessComponent(connectionType,&myComponent))
			num_components++;
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext,&myComponent);
	}
	//возвращаю число компонентов
	return num_components;
}

// инициализация индексов	
static void initIndex(long *pIndexComponents, long num_components) 
{	
	for(long i = 0; i < num_components; i++)
		pIndexComponents[i] = i;
}

// получаю символ
static bool getSymbol(COMPONENT_LIST_STRUCT *pListCur,TSymbol *pSymbol,bool bDirection)
{
	// получаю страницу, где находится символ
	TLayer myLayer;
	TGetLayerById(&tContext,pSymbol->layerId,&myLayer);
	// получаю номер страницы
	pListCur->sheet = myLayer.layerPosition;
	// получаю коородиныты символа
	if(bDirection)
	{	// для нумерации слева-направо
		pListCur->coord2 = 0x7FFFFFFF - pSymbol->refPoint.y;	// координата Y, вычитание - для правильной сортировки
		pListCur->coord1 = pSymbol->refPoint.x;	// координата X
//		pListCur->coord2 = 32767 - (pSymbol->refPoint.y / 100000);	// координата Y - в мм, вычитание - для правильной сортировки
//		pListCur->coord1 = pSymbol->refPoint.x / 100000;	// координата X - в мм
	}
	else
	{	// для нумерации сверху-вниз
		pListCur->coord1 = 0x7FFFFFFF - pSymbol->refPoint.y;	// координата Y, вычитание - для правильной сортировки
		pListCur->coord2 = pSymbol->refPoint.x;	// координата X
//		pListCur->coord1 = 32767 - (pSymbol->refPoint.y / 100000);	// координата Y - в мм, вычитание - для правильной сортировки
//		pListCur->coord2 = pSymbol->refPoint.x / 100000;	// координата X - в мм
	}
	return true;
}

// получаю символы 
static long getSymbolsList(char *pRefDes, COMPONENT_LIST_STRUCT *pListCur,bool bDirection)
{
	TSymbol mySymbol;
	long num_symbols = 0;
	// получаю первый символ
	tStatus = TGetFirstCompSymbol(&tContext,pRefDes,&mySymbol);
	while(tStatus == DBX_OK)
	{
		if(getSymbol(pListCur,&mySymbol,bDirection))
		{
			num_symbols++;
			pListCur++;
		}
		// получаю слудующий символ
		tStatus = TGetNextCompSymbol(&tContext,&mySymbol);
	}
	return num_symbols;
}

// получаю компонент 
static bool getComponent(COMPONENT_LIST_STRUCT *pListCur,TComponent * pComponent, bool bDirection)
{
	TAttribute myAttr;		// текуший атрибут компонента
	char *tmp;
	// инициализирую строки
	pListCur->refdes_old[0] = 0;
	pListCur->refdes_new[0] = 0;
	pListCur->refdes_txt[0] = 0;
	// номера группы
	pListCur->group = 0;
	// номера канала в группе
	pListCur->channel = 0;
	// получаю первый атрибут
	tStatus = TGetFirstCompAttribute(&tContext,pComponent->refDes,&myAttr);
	while (tStatus == DBX_OK)
	{
		// атрибут с номером канала в группе
		if(strcmp(myAttr.type,attrNoChannelInGroupType) == 0)
			sscanf_s(myAttr.value,"%d",&pListCur->channel);
		// атрибут с номером гуппы каналов
		else if(strcmp(myAttr.type,attrNoChannelGroupType) == 0)
			sscanf_s(myAttr.value,"%d",&pListCur->group);
		// линк
		else if(strcmp(myAttr.type,"Link") == 0)
			strcpy_s(pListCur->link,DBX_MAX_NAME_LEN,myAttr.value);
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	// обрабатываю refDes
	strcpy_s(pListCur->refdes_old, DBX_MAX_NAME_LEN, pComponent->refDes); // копирую refDes
	strcpy_s(pListCur->refdes_txt, DBX_MAX_NAME_LEN, pComponent->refDes); // копирую refDes
	//ищу в pListCur->refdes_txt начало цифровой части и обрубаю строку в этом месте
	tmp = strpbrk(pListCur->refdes_txt, acceptNumber); 
	if(tmp != NULL) *tmp = 0;
	// ищу положение первого символа компонента
	if(pComponent->numberParts > 0)
	{
		COMPONENT_LIST_STRUCT * pSymbolsList = NULL;
		long * pIndexSymbols = NULL;
		while(true)
		{
			long numSymbols;
			// выделяю память
			pSymbolsList = new COMPONENT_LIST_STRUCT[pComponent->numberParts];
			pIndexSymbols = new long [pComponent->numberParts];
			if(pSymbolsList == NULL) break;
			if(pIndexSymbols == NULL) break;
			// инициализация индексов
			initIndex(pIndexSymbols,pComponent->numberParts);
			// получаю список символов
			numSymbols	= getSymbolsList(pListCur->refdes_old,pSymbolsList,bDirection);
			if(numSymbols < 1) break;
			// сортировка списка символов по Id
			sortComponentList(pSymbolsList,pIndexSymbols,numSymbols,
				&compareComponentListElementsByPlacement);
			// положение самого первого символа из символов компонента
			pListCur->coord1 = pSymbolsList[pIndexSymbols[0]].coord1;
			pListCur->coord2 = pSymbolsList[pIndexSymbols[0]].coord2;
			pListCur->sheet = pSymbolsList[pIndexSymbols[0]].sheet;
			break;
		}		
		delete pIndexSymbols;
		delete pSymbolsList;
		return true;
	}
	// возврат
	return false;
}		

// получаю список компонентов
static long getComponentsList(long connectionType,COMPONENT_LIST_STRUCT *pListCur, bool bDirection)
{
	TComponent myComponent;	// комонент
	long num_components = 0;
	if(pListCur == NULL) return 0;
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while(tStatus == DBX_OK)
	{
		if(isProcessComponent(connectionType,&myComponent))
		{	// компонент соответствует заданному типу
			if(getComponent(pListCur,&myComponent,bDirection))
			{	// переход к следующей записи
				pListCur++;
				num_components++;
			}
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext,&myComponent);
	}
	return num_components;
}

// получаю общее число групп каналов в списке
static long getNumGroups(COMPONENT_LIST_STRUCT *pList, long num_components)
{
	long num_groups = 0;
	if(pList == NULL) return 1;
	for(long i = 0; i < num_components; i++)
	{
		if( pList[i].group > num_groups )
			num_groups = pList[i].group;
	}
	num_groups++;
	return num_groups;
}

// формирую в сортированном списке новый RefDes
// - элементы нумеруются с 1 с инкрементом 1 в порядке сортировки
// - элементы первого канала группы продолжают общую нумерацию в порядке нумерации групп
// - у элементов последующих каналов к индексу элемента первого канала 
//   через '_' добавляется номер канала в группе
static bool makeNewRefDesComponents(long connectionType, COMPONENT_LIST_STRUCT *pList, long *pIndexComponents, long num_components)
{
	long index;	// индекс элемента
	long current_group; // предыдущая группа каналов
	long current_channel; // предыдущий канал в гуппе каналов
	char current_refdes_txt[DBX_MAX_NAME_LEN] = {0}; // предыдущая текстовая часть RefDes
	// массив индексов первого элемента в первом канале группы
	long *index_channel = new long [getNumGroups(pList, num_components)];
	if(index_channel == NULL)
		return false;
	// собственно формирование сортированного списка
	for(long i = 0; i < num_components; i++)
	{
		COMPONENT_LIST_STRUCT *pListCur = pList + pIndexComponents[i];
		if(strcmp(pListCur->refdes_txt, current_refdes_txt) != 0)
		{	// новая текстовая часть RefDes
			strcpy_s(current_refdes_txt, pListCur->refdes_txt);
			index = 1;
			index_channel[0] = 1;
			current_channel = 0;
			current_group = 0;
		}
		if(connectionType == DBX_COMPONENT_CONNECTION_NORMAL)
		{	// для нормальных компонентов учитываем разбиение на каналы
			if(pListCur->group != current_group)
			{	// новая группа каналов
				current_group = pListCur->group;
				if(current_group > 0)
				{	// не основная часть схемы (группа 0)
					current_channel = pListCur->channel;
					if(current_channel <= 1)
					{	// первый канал в группе каналов
						current_channel = 1;
						// сохраняю индекс первого элемента в первом канале группы
						index_channel[current_group] = index;
					}
					else
					{	// последующие каналы в группе каналов
						// извлекаю индекс первого элемента в первом канале группы
						index = index_channel[current_group];
					}
				}
				else
				{
					current_channel = 0;
				}

			}
			else if(pListCur->channel != current_channel)
			{	// новый канал в группе каналов
				current_channel = pListCur->channel;
				if(current_group > 0) 
					index = index_channel[current_group];
			}
			// заношу новое значение refdes
			if(current_channel <= 1)
				// первый канал группы каналов
				sprintf_s(pListCur->refdes_new,DBX_MAX_NAME_LEN,"%s%d",pListCur->refdes_txt,index);
			else
				// последующий канал групп каналов
				sprintf_s(pListCur->refdes_new,DBX_MAX_NAME_LEN,"%s%d_%d",pListCur->refdes_txt,index,current_channel);
		}
		else
			// для остальных комонентов - сплошная перенумерация
			sprintf_s(pListCur->refdes_new,DBX_MAX_NAME_LEN,"%s%d",pListCur->refdes_txt,index);
		// если refdes не изменился, ничего не делаем
		if(strcmp(pListCur->refdes_new,pListCur->refdes_old) == 0)
			pListCur->refdes_new[0] = 0;
		index++;
	}
	delete index_channel;
	return true;
}

/**
 * @brief Функция изменяет значения RefDes на новые
 * @param connectionType  Тип соединиения.
 * @param pList           Указатель на массив компонентов.
 * @param flag            Флаг удаления '@' из RefDes компонента.
 * @param hEcoFile_p      Heandle ECO файла.
 */
static void
saveNewRefDesComponents(long connectionType, COMPONENT_LIST_STRUCT *pList,
	bool flag, FILE * hEcoFile_p)
{
	TComponent myComponent;	// комонент
	TSymbol mySymbol;		// символ
	bool bSaveEco = (hEcoFile_p != NULL);
	char refdes_prev[DBX_MAX_NAME_LEN];

	refdes_prev[0] = 0;
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while(tStatus == DBX_OK)
	{
		if(isProcessComponent(connectionType,&myComponent)) {
			// компонент соответствует заданному типу
			// получаю первый символ компонента
			tStatus = TGetFirstCompSymbol(&tContext, myComponent.refDes, &mySymbol);
			while(tStatus == DBX_OK) {
				if(flag) {
					// удаление "@"
					char *pStr = strchr(mySymbol.refDes, '@');
					if(pStr != NULL) {
						if (*(pStr+1) == ':') {
							if (bSaveEco) {
								*(pStr+1) = 0;
								if (strcmp(refdes_prev, mySymbol.refDes) != 0) {
									strcpy_s(refdes_prev, DBX_MAX_NAME_LEN, mySymbol.refDes);
									writeEcoFile(hEcoFile_p, mySymbol.refDes, 0);
									*pStr = 0;
									writeEcoFile(hEcoFile_p, mySymbol.refDes, 1);
								}
								*(pStr+1) = ':';
							}
							strcpy_s(pStr, DBX_MAX_NAME_LEN, pStr+1);
						}
						else {
							if (bSaveEco) {
								writeEcoFile(hEcoFile_p, mySymbol.refDes, 0);
								*pStr = 0;
								writeEcoFile(hEcoFile_p, mySymbol.refDes, 1);
							}
							else
								*pStr = 0;
						}
						// модифицирую символ
						tStatus = TModifySymbol(&tContext, &mySymbol);
					}
				}
				else if(pList->refdes_new[0] != 0) {
					// занесение нового refDes
					// есть новый refdes
					char refdes_new[DBX_MAX_NAME_LEN];
					bool bNewComp = true;
					char *pStr;

					if (bSaveEco) {
						bNewComp = (strcmp(refdes_prev, pList->refdes_old) != 0);
						if (bNewComp) {
							strcpy_s(refdes_prev, DBX_MAX_NAME_LEN, pList->refdes_old);
							writeEcoFile(hEcoFile_p, refdes_prev, 0);
						}
					}
					strcpy_s(refdes_new, DBX_MAX_NAME_LEN, pList->refdes_new);
					// добавление "@"
					strcat_s(refdes_new, DBX_MAX_NAME_LEN, "@");
					if (bSaveEco && bNewComp)
						writeEcoFile(hEcoFile_p, refdes_new, 1);
					// ищу начало номера cекции
					pStr = strchr(mySymbol.refDes,':');
					if(pStr != NULL)
						strcat_s(refdes_new, DBX_MAX_NAME_LEN, pStr);
					// вношу новый refDes
					strcpy_s(mySymbol.refDes, DBX_MAX_NAME_LEN, refdes_new);
					// модифицирую символ
					tStatus = TModifySymbol(&tContext, &mySymbol);
				}
				// получаю следующий символ компонента
				tStatus = TGetNextCompSymbol(&tContext, &mySymbol);
			}
			// переход к следующей записи
			pList++;
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext, &myComponent);
	}
}

// перенумерация 
bool processRenumber(long connectionType, bool bDirection, bool bSaveEco_p)
{
	COMPONENT_LIST_STRUCT *pListComponents = NULL;
	long *pIndexComponents = NULL;
	FILE * hEcoFile = NULL;

	while(openDesign())
	{
		if (bSaveEco_p) {
			hEcoFile = openEcoFile();
			if (hEcoFile == NULL)
				bSaveEco_p = false;
		}
		// получаю число компонентов
		long numComponents = getNumberComponents(connectionType);
		if(numComponents < 1) break;
		// выделяю память
		pListComponents = new COMPONENT_LIST_STRUCT [numComponents];
		pIndexComponents = new long [numComponents];
		if(pListComponents == NULL) break;
		if(pIndexComponents == NULL) break;
		// инициализация индексов
		initIndex(pIndexComponents,numComponents);
		// получаю компоненты
		numComponents = getComponentsList(connectionType,pListComponents, bDirection);
		if(numComponents < 1) break;
		// сортировка списка компонентов по Id
		sortComponentList(pListComponents,pIndexComponents,numComponents, 
			&compareComponentListElementsByChannels);
		// получение новых значений RefDes
		makeNewRefDesComponents(connectionType,pListComponents,pIndexComponents,numComponents);
		// обновляю значения RefDes
		saveNewRefDesComponents(connectionType,pListComponents, false, hEcoFile);
		// сохраняю значения RefDes
		saveNewRefDesComponents(connectionType,pListComponents, true, hEcoFile);
		break;
	}
	closeEcoFile(hEcoFile);
	closeDesign();
	delete pListComponents;
	delete pIndexComponents;
	return true;
}

// добавляем RefDes2
bool processAddRefDes2(void)
{
	while(openDesign())
	{
		TComponent myComponent;	// комонент
		//получаю первый компонент
		tStatus = TGetFirstComponent(&tContext,&myComponent);
		while(tStatus == DBX_OK)
		{
			if(isProcessComponent(DBX_COMPONENT_CONNECTION_NORMAL,&myComponent))
			{	// компонент соответствует заданному типу
				TAttribute myAttr; // атрибут
				bool flag = false;
				// получаю первый атрибут компонента
				tStatus = TGetFirstCompAttribute(&tContext,myComponent.refDes,&myAttr);
				while(tStatus == DBX_OK)
				{
					// атрибут с номером канала в группе
					if(strcmp(myAttr.type,attrRefDes2) == 0)
					{
						strcpy_s(myAttr.value,DBX_MAX_NAME_LEN,myComponent.refDes);
						myAttr.valueLength = strlen(myAttr.value);
						TModifyCompAttribute(&tContext,myComponent.refDes,&myAttr);
						flag = true;
						break;
					}
					//получаю следующий атрибут
					tStatus = TGetNextCompAttribute(&tContext,&myAttr);
				}
				if(!flag)
				{
					strcpy_s(myAttr.type,DBX_MAX_NAME_LEN,attrRefDes2);
					myAttr.typeLength = strlen(myAttr.value);
					strcpy_s(myAttr.value,DBX_MAX_NAME_LEN,myComponent.refDes);
					myAttr.valueLength = strlen(myAttr.value);
					myAttr.isVisible = false;
					TAddCompAttribute(&tContext,myComponent.refDes,&myAttr);
				}
			}
			//получаю следующий компонент
			tStatus = TGetNextComponent(&tContext,&myComponent);
		}
		break;
	}
	closeDesign();
	return true;
}

// каналирование компонента 
bool makechanComponent(char * pRefDes, long no_group, long no_channel)
{
	TAttribute myAttr; // атрибут
	bool flag_no_group = false;
	bool flag_no_channel = false;
	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		// атрибут с номером группы
		if(strcmp(myAttr.type,attrNoChannelGroupType) == 0)
		{
			if(no_group == 0)
				TDeleteCompAttribute(&tContext,pRefDes,&myAttr);
			else
			{
				flag_no_group = true;
				sprintf_s(myAttr.value,DBX_MAX_NAME_LEN,"%d",no_group);
				myAttr.valueLength = strlen(myAttr.value);
				TModifyCompAttribute(&tContext,pRefDes,&myAttr);
			}
		}
		// атрибут с номером канала в группе
		else if(strcmp(myAttr.type,attrNoChannelInGroupType) == 0)
		{
			if(no_group == 0)
				TDeleteCompAttribute(&tContext,pRefDes,&myAttr);
			else
			{
				flag_no_channel = true;
				sprintf_s(myAttr.value,DBX_MAX_NAME_LEN,"%d",no_channel);
				myAttr.valueLength = strlen(myAttr.value);
				TModifyCompAttribute(&tContext,pRefDes,&myAttr);
			}
		}
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	if(no_group > 0)
	{
		if(!flag_no_group)
		{
			myAttr.isVisible = false;
			strcpy_s(myAttr.type,DBX_MAX_NAME_LEN,attrNoChannelGroupType);
			myAttr.typeLength = strlen(myAttr.value);
			sprintf_s(myAttr.value,DBX_MAX_NAME_LEN,"%d",no_group);
			myAttr.valueLength = strlen(myAttr.value);
			TAddCompAttribute(&tContext,pRefDes,&myAttr);
		}
		if(!flag_no_channel)
		{
			myAttr.isVisible = false;
			strcpy_s(myAttr.type,DBX_MAX_NAME_LEN,attrNoChannelInGroupType);
			myAttr.typeLength = strlen(myAttr.value);
			sprintf_s(myAttr.value,DBX_MAX_NAME_LEN,"%d",no_channel);
			myAttr.valueLength = strlen(myAttr.value );
			TAddCompAttribute(&tContext,pRefDes,&myAttr);
		}
	}
	return true;
}

// ручное каналирование предварительно выделенным компонентов
bool processMakeChanManual(long no_group, long no_channel)
{
	while(openDesign())
	{
		TItem myItem;
		//получаю первый компонент
		tStatus = TGetFirstSelectedItem(&tContext,&myItem);
		while(tStatus == DBX_OK)
		{
			if(myItem.itemType == DBX_SYMBOL)
			{	// компонент выделен
				// получаю RefDes выделенного компонента
				char myRefDes[DBX_MAX_NAME_LEN], *pStr;
				strcpy_s(myRefDes,DBX_MAX_NAME_LEN,myItem.symbol.refDes);
				pStr = strchr(myRefDes,':');
				if(pStr != NULL) *pStr = 0;
				// каналирование компонена
				makechanComponent(myRefDes, no_group, no_channel);
			}
			//получаю следующий компонент
			tStatus = TGetNextSelectedItem(&tContext,&myItem);
		}
		break;
	}
	closeDesign();
	return true;
}

// автоматическое каналирование
bool processMakeChanAuto(void)
{
	COMPONENT_LIST_STRUCT *pListChannels = NULL;
	COMPONENT_LIST_STRUCT *pListLinks = NULL;
	COMPONENT_LIST_STRUCT *pListComponents = NULL;
	while(openDesign())
	{
		// получаю число компонентов
		long numChannels = getNumberComponents(DBX_COMPONENT_CONNECTION_MODULE);
		long numLinks = getNumberComponents(DBX_COMPONENT_CONNECTION_LINK);
		long numComponents = getNumberComponents(DBX_COMPONENT_CONNECTION_NORMAL);
		// выделяю память для компонентов
		if(numComponents < 1) break;
		pListComponents = new COMPONENT_LIST_STRUCT [numComponents];
		if(pListComponents == NULL) break;
		if(numChannels > 0)
		{
			// выделяю память для каналов
			pListChannels = new COMPONENT_LIST_STRUCT [numChannels];
			if(numLinks > 0)
				// выделяю память для линков
				pListLinks = new COMPONENT_LIST_STRUCT [numLinks];
		}
		// получаю каналы
		numChannels = getComponentsList(DBX_COMPONENT_CONNECTION_MODULE,pListChannels,false);
		// получаю линки
		numLinks = getComponentsList(DBX_COMPONENT_CONNECTION_LINK,pListLinks,false);
		// получаю компоненты
		numComponents = getComponentsList(DBX_COMPONENT_CONNECTION_NORMAL,pListComponents,false);
		// присваиваю линкам номера группы и канала группы
		for(long i = 0; i < numLinks; i++)
		{
			for(long j = 0; j < numChannels; j++)
			{
				if(strcmp(pListLinks[i].refdes_old,pListChannels[j].link) == 0)
				{	// имя линка совпадает с атрибутом канала
					pListLinks[i].group = pListChannels[j].group;
					pListLinks[i].channel = pListChannels[j].channel;
					break;
				}
			}
		}
		// очищаю у компонента номера группы и канала группы
		for(long i = 0; i < numComponents; i++)
		{	// имя линка совпадает с атрибутом канала
			pListComponents[i].group = 0;
			pListComponents[i].channel = 0;
		}
		// присваиваю компонентами номера группы и канала группы, как у линка находящегося на этой страницые
		for(long i = 0; i < numLinks; i++)
		{
			long sheet = pListLinks[i].sheet;
			long group = pListLinks[i].group;
			long channel = pListLinks[i].channel;
			for(long j = 0; j < numComponents; j++)
			{
				if(pListComponents[j].sheet == sheet)
				{
					pListComponents[j].group = group;
					pListComponents[j].channel = channel;
				}
			}
		}
		// каналирование компонентов
		for(long i = 0; i < numComponents; i++)
			makechanComponent(pListComponents[i].refdes_old, pListComponents[i].group, pListComponents[i].channel);
		break;
	}
	closeDesign();
	delete pListChannels;
	delete pListLinks;
	delete pListComponents;
	return true;
}

void CRenumberDlg::OnBnClickedOk()
{
	// гашу кнопку
	OkButton.EnableWindow(false);
	// Определяю направление 
	bool bDirection = (GetCheckedRadioButton(IDC_RADIO_DIRECTION1,IDC_RADIO_DIRECTION2) == IDC_RADIO_DIRECTION2);
	// Флаг записи ECO
	bool bSaveEco = (IsDlgButtonChecked(IDC_CHECK_ECO) == BST_CHECKED);

	// запускаем задачу
	switch(GetCheckedRadioButton(IDC_RADIO_NORMAL,IDC_RADIO_ADDREFDES))
	{
	case IDC_RADIO_NORMAL:
		processRenumber(DBX_COMPONENT_CONNECTION_NORMAL, bDirection, bSaveEco);
		break;
	case IDC_RADIO_MODULE:
		processRenumber(DBX_COMPONENT_CONNECTION_MODULE, bDirection, false);
		break;
	case IDC_RADIO_MAKECHANMANUAL:
		{
			CString str2,str4;
			Edit2.GetWindowTextW(str2);
			Edit4.GetWindowTextW(str4);
			processMakeChanManual((long)StrToIntW(str2),(long)StrToIntW(str4));
		}
		break;
	case IDC_RADIO_MAKECHAN:
		processMakeChanAuto();
		break;
	case IDC_RADIO_ADDREFDES:
		processAddRefDes2();
		break;
	default:
		break;
	}
	CDialogEx::OnOK();
}

void CRenumberDlg::OnBnClickedRadioNormal()
{
	// TODO: Add your control notification handler code here
	Edit1.ShowWindow(0);
	Edit2.ShowWindow(0);
	Edit3.ShowWindow(0);
	Edit4.ShowWindow(0);

	CheckEco.ShowWindow(1);
}

void CRenumberDlg::OnBnClickedRadioModule()
{
	// TODO: Add your control notification handler code here
	Edit1.ShowWindow(0);
	Edit2.ShowWindow(0);
	Edit3.ShowWindow(0);
	Edit4.ShowWindow(0);

	CheckEco.ShowWindow(0);
}

void CRenumberDlg::OnBnClickedRadioMakechanmanual()
{
	// TODO: Add your control notification handler code here
	CString str;
	str = "Группа";
	Edit1.ShowWindow(1);
	Edit1.SetWindowTextW(str);
	Edit1.EnableWindow(false);
	str = "Канал";
	Edit3.ShowWindow(1);
	Edit3.SetWindowTextW(str);
	Edit3.EnableWindow(false);
	str = "";
	Edit2.ShowWindow(1);
	Edit2.SetWindowTextW(str);
	Edit2.EnableWindow(true);
	Edit4.ShowWindow(1);
	Edit4.SetWindowTextW(str);
	Edit4.EnableWindow(true);
	
	CheckEco.ShowWindow(0);
}

void CRenumberDlg::OnBnClickedRadioMakechan()
{
	// TODO: Add your control notification handler code here
	Edit1.ShowWindow(0);
	Edit2.ShowWindow(0);
	Edit3.ShowWindow(0);
	Edit4.ShowWindow(0);

	CheckEco.ShowWindow(0);
}

void CRenumberDlg::OnBnClickedRadioAddrefdes()
{
	// TODO: Add your control notification handler code here
	Edit1.ShowWindow(0);
	Edit2.ShowWindow(0);
	Edit3.ShowWindow(0);
	Edit4.ShowWindow(0);

	CheckEco.ShowWindow(0);
}

void CRenumberDlg::OnBnClickedCheckEco()
{
	// TODO: Add your control notification handler code here
}
