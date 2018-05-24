
// ComponentListDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "ComponentList.h"
#include "ComponentListDlg.h"
#include "afxdialogex.h"
#include "dbx32.h"
#include "myDbxUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CComponentListDlg
CComponentListDlg::CComponentListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComponentListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComponentListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CComponentListDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CComponentListDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CComponentListDlg

BOOL CComponentListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	CheckDlgButton(IDC_RADIO_TYPE_PE, BST_CHECKED);
	CheckDlgButton(IDC_RADIO_FILE_TXTSEP, BST_CHECKED);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CComponentListDlg::OnPaint()
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
HCURSOR CComponentListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//========================================================================================
// типы списка
enum TYPE_OUT_LIST
{
	OUT_LIST_PE = 0,	// перечень
	OUT_LIST,			// просто список
	OUT_LIST_SP,		// спецификация
	OUT_LIST_VP,		// ведомость покупных 
	OUT_LIST_MAX
};

static const char sOutFileNameEnd[OUT_LIST_MAX][10] = {
	"_ПЭ3",
	"_СПИСОК",
	"_СП",
	"_ВП",
};

// типы выходных фалов
enum TYPE_OUT_FILE
{
	OUT_FILE_TXTDLM = 0,	// текстовый с разделителем
	OUT_FILE_TXT,			// текстовый
	OUT_FILE_HTML,			// html-файл
	OUT_FILE_RTF,			// html-файл
	OUT_FILE_MAX
};

static const char sOutFileExtension[OUT_FILE_MAX][10] = {
	".txt",
	".txt",
	".html",
	".rtf",
};

typedef struct COMPONENT_ACCEPT_TEXT
{
	const char accept[20];
	const char text[20];
} COMPONENT_ACCEPT_TEXT;

typedef struct COMPONENT_ACCEPT
{
	COMPONENT_ACCEPT_TEXT * pComponentAcceptText;
	long number;
	char ch;
} COMPONENT_ACCEPT;

// Конденсаторы
#define C_NUMBER_ACCEPTS 6
static COMPONENT_ACCEPT_TEXT _c_accepts[C_NUMBER_ACCEPTS] =  {
	" мМmMпПpPнНnNuU", " п",
	"пПpP",	" п",	// пФ
	"нНnN",	" н",	// нФ
	",кКkKuU", " мк",	// мкФ
	"мМmM",	" м",	// мФ
	"фФfF",	" ",	// Ф
};

COMPONENT_ACCEPT Caccept = {
	_c_accepts,
	C_NUMBER_ACCEPTS,
	'Ф',
};

// Индуктивности	
#define L_NUMBER_ACCEPTS 3
static COMPONENT_ACCEPT_TEXT _l_accepts[L_NUMBER_ACCEPTS] =  {
	" кКkKмМmMuU", " ", //Гн
	"кКkKuU",	" мк",	// мкГн
	"мМmM",	" м",	// мГн
};

COMPONENT_ACCEPT Laccept = {
	_l_accepts,
	L_NUMBER_ACCEPTS,
	'Г',
};

// Резисторы
#define R_NUMBER_ACCEPTS 5
static COMPONENT_ACCEPT_TEXT _r_accepts[R_NUMBER_ACCEPTS] =  {
	" мmМMкКkKГгgG", " ", //Ом
	"мm",	" м",	//мОм
	"кКkK", " к",	//кОм
	"МM",	" М",	//МОм
	"ГгgG", " Г",	// ГОм
};

COMPONENT_ACCEPT Raccept = {
	_r_accepts,
	R_NUMBER_ACCEPTS,
	'О',
};

typedef struct COMPONENT_ACCEPT_NAME
{
	const char refdes[3];
	const char name[DBX_MAX_NAME_LEN];
	const char nameSingle[DBX_MAX_NAME_LEN];
	long group;
} COMPONENT_ACCEPT_NAME;

// ассоциация буквенной части RefDes c групповым наименованием
// Групп сортировать по алфавиту c 1 !
static COMPONENT_ACCEPT_NAME CompNameAccept[] = {
	"--", "\0\0", "\0\0", 0,
	"A" , "\0\0", "\0\0", 1,
	"RU", "Варисторы", "Варистор ", 2,
	"VD", "Диоды", "Диод ", 3, 
	"HL", "Индикаторы", "Индикатор ", 4,
	"HG", "Индикаторы", "Индикатор ", 4,
	"L" , "Индуктивности", "Индуктивность ", 5,
	"SB", "Кнопки", "Кнопка ", 6,
	"C" , "Конденсаторы", "Конденсатор ", 7,
	"D" , "Микросхемы", "Микросхема ", 8,
	"DA", "Микросхемы", "Микросхема ", 8,
	"DD", "Микросхемы", "Микросхема ", 8,
	"SA", "Переключатели", "Переключатель ", 9,
	"F" , "Предохранители", "Предохранитель ", 10,
	"FU", "Предохранители", "Предохранитель ", 10,
	"R" , "Резисторы", "Резистор ", 11,
	"K" , "Реле", "Реле ", 12,
	"T" , "Трансформаторы", "Трансформатор ", 13,
	"TV", "Трансформаторы", "Трансформатор ", 13,
	"X" , "Соединители", "Соединитель ", 14,
	"XP", "Соединители", "Соединитель ", 14,
	"XS", "Соединители", "Соединитель ", 14,
	"XT", "Соединители", "Соединитель ", 14,
	"VT", "Транзисторы", "Транзистор ", 15,
};
#define COMP_NAME_NUMBER_ACCEPTS (sizeof(CompNameAccept)/sizeof(COMPONENT_ACCEPT_NAME))

// маскимальная длина тесктовой строки атрибута VALUE
#define VALUE_MAX_STRING_LEN		(DBX_MAX_ATTRIBUTE_LEN*2)
// маскимальная длина тесктовой строки атрибута VALUE
#define REFDES_MAX_STRING_LEN		(DBX_MAX_ATTRIBUTE_LEN*16)

// рабочая структура
typedef struct COMPONENT_LIST_STRUCT {
	union {
		unsigned _int64 id;							// индекс
		struct {
			unsigned _int64 num_refdes	:16;		// цифровая часть обозначения
			unsigned _int64 lyt2_refdes	:8;			// 2-ой символ обозначения (для компонента) и 1-ый - для канала
			unsigned _int64 lyt1_refdes	:8;			// 1-ый символ обозначения (для компонениа) и '@' - для канаоа
			unsigned _int64 channel		:8;			// номер канала в группе
			unsigned _int64 group		:8;			// номер группы каналов
		} ids;
		char idstr[8];
	};
	long quantity;							// количество
	long channel;							// номер каналa в группе 
	long group;								// номер группы каналов
	long indexGroupName;					// индекс группового имени компонента
	char notList[DBX_MAX_ATTRIBUTE_LEN];	// в какие списки не заносится
	char refdes[REFDES_MAX_STRING_LEN];		// текстовая часть обозначения
	char value[VALUE_MAX_STRING_LEN];		// наименование
} COMPONENT_LIST_STRUCT;
//========================================================================================

// возвращает true, если компонент - канал
static bool isChannel(TComponent * pComponent)
{
	TAttribute myAttr;		// текуший атрибут компонента
	// получаю первый атрибут
	tStatus = TGetFirstCompAttribute(&tContext, pComponent->refDes, &myAttr);
	while (tStatus == DBX_OK)
	{
		// атрибут DesChannel
		if( strcmp(attrDesChannel, myAttr.type) == 0) 
			return true;
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext, &myAttr);
	}
	return false;
}

// получаю групповое имя компонентов (больше одного)
static const char * getComponentGroupName(long indexGroupName,bool flagSingle)
{
	long i;
	for(i = 0; i < COMP_NAME_NUMBER_ACCEPTS; i++)
		if( (long)CompNameAccept[i].group == indexGroupName ) break;
	if( i >= COMP_NAME_NUMBER_ACCEPTS) i = 0; 
	return (flagSingle)?(CompNameAccept[i].nameSingle):(CompNameAccept[i].name);
}

// получаю индекс группового имени комонента
static long getComponentGroupNameIndex(char ch1, char ch2)
{
	char str[3];
	long i;
	// копирую RefDes в буфер
	str[0] = ch1;
	str[1] = ch2;
	str[2] = 0;
	// ищу буквенное обохначение компонента в таблице
	for(i = 0; i < COMP_NAME_NUMBER_ACCEPTS; i++)
		if(strcmp(str,CompNameAccept[i].refdes) == 0) break;
	//  номер в соответсвии с групповым именем компонента
	if( i >= COMP_NAME_NUMBER_ACCEPTS ) i = 0;
	return CompNameAccept[i].group;
}

// получаю число компонентов в базе
static long getNumberComponents(void)
{
	TComponent myComponent;
	long num_components = 0;
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext, &myComponent);
	while (tStatus == DBX_OK)
	{
		switch(myComponent.connectionType)
		{
		case DBX_COMPONENT_CONNECTION_NORMAL:	// нормальный компонент
			if( strpbrk(myComponent.refDes,acceptLastChannelComponets)==NULL )
				num_components++;
			break;
		case DBX_COMPONENT_CONNECTION_MODULE: // модуль
			num_components++;
			break;
		case DBX_COMPONENT_CONNECTION_POWER: // питание
			if( isChannel(&myComponent) )
				num_components++;
		default:
			break;
		}
		tStatus = TGetNextComponent(&tContext, &myComponent);
	}
	//возвращаю число компонентов
	return num_components;
}

// корректирую строку
static void correctString(char *pString, long max_length)
{
	char str[VALUE_MAX_STRING_LEN];
	long len = strlen(pString);
	if((len > 1) && (pString != NULL))
	{
		// посторонние символы заменяю пробелами
		while(len > 0)
		{
			len--;
			switch(pString[len])
			{
			case 0xD:
			case 0xA:
				pString[len] = ' ';
			default:
				break;
			}
		}
		//убиваю повторные пробелы
		while(true)
		{
			char *pstr = strstr(pString, "  ");
			if(pstr == NULL) break;
			strcpy_s(str,max_length,pstr+1);
			*pstr = 0;
			strcat_s(pString,max_length,str);
		}
		//убиваю пробел в конце строки
		len = strlen(pString);
		if((len > 1) && (pString[len-1] == ' ')) 
			pString[len-1] = 0;
	}
}

// модифицирует в pComponent->value текстовую часть
static void getComponentValueUnits(TComponent * pComponent, char * pDesCommon,
	COMPONENT_ACCEPT * pCompAccept, char *value_str)
{
	// вторым символом в RefDes должна быть цифра, 
	// в DesCommon должна быть прописана единица измерения - Ом
	// DesCommon может не быть
	if( ((unsigned char)pComponent->refDes[1] <= (unsigned char)'9') &&
		(*pDesCommon == pCompAccept->ch) )
	{
		long i = 0;
		// ищу начало текстовой части Value 
		char * pStr = strpbrk(value_str, pCompAccept->pComponentAcceptText[0].accept);
		if(pStr != NULL)
		{	// ищу вхождение
			for(i=1; i < pCompAccept->number; i++)
				if(strpbrk(value_str, pCompAccept->pComponentAcceptText[i].accept) != NULL)
					break;
			if(i >= pCompAccept->number) 
				// значение текстовой части по умолчанию
				i = 0; 
			// обрубаю Value на конце цифровой части
			*pStr = 0;	
		}
		else
			// значение текстовой части по умолчанию
			i = 0; 
		// текстовая часть
		strcat_s(value_str, DBX_MAX_ATTRIBUTE_LEN, pCompAccept->pComponentAcceptText[i].text);
	}
}

//------------------------------------------------------------------------------
/**
 *  \brief Получение значениz Value компонента по атрибутам RefDes и Value
 *	\param pCompCur - указатель на текущий компонент в таблице компонентов
 *	\param pComponent - указатель на компонент
 *	\param pDesCommon - указатель на значение атрибута DesCommon
 *	\param isInsertPattern - TRUE, если требуется дополнить Value значением Pattern
 */
//------------------------------------------------------------------------------
static void getComponentListValue(COMPONENT_LIST_STRUCT * pCompCur, TComponent * pComponent,
	char * pDesCommon, bool isInsertPattern)
{
	char value_str[VALUE_MAX_STRING_LEN];
	char *pStr;
	const char *pStr1;
	int fValueParsing = 1;

	*(pCompCur->value) = 0;
	// получаю и ищу в DesCommon групповое имя
	pStr1= getComponentGroupName(pCompCur->indexGroupName,true);
	pStr = strstr(pDesCommon,pStr1);
	if(pStr != NULL) {
		// удаляю из DesCommon групповое имя
		pDesCommon = pStr + strlen(pStr1);
	}

	// разбираю DesCommon
	if(strlen(pDesCommon) > 0)
	{	// есть DesCommon
		// ищу место вставки Value в DesCommon начиная с начала строки
		pStr = strchr(pDesCommon, '@');

		if(pStr != NULL)
		{	// есть место для вставки Value
			*pStr = 0;
			pStr++;
			fValueParsing = 1;
		}
		else {
			fValueParsing = 0;
		}
		//заношу первую часть DesCommon в pValue
		strcpy_s(pCompCur->value, VALUE_MAX_STRING_LEN, pDesCommon);
		if (fValueParsing) {
			// есть место для вставки Value
			pDesCommon = pStr;
		}
	}

	if (fValueParsing) {
		// разбираю Value
		if(strlen(pComponent->value) > 0)
		{	// есть Value
			// копирую Value в буфер, убирая при этом из начала строки символ '~'
			strcpy_s(value_str, VALUE_MAX_STRING_LEN,
				(pComponent->value + ((pComponent->value[0]=='~')?(1):(0))));
			// заменяю точку на запятую в Value
			pStr = strchr(value_str, '.');
			if(pStr != NULL) *pStr = ',';
			// корректирую Value по текстовой части RefDes
			switch(pComponent->refDes[0])
			{
			case 'R':
				getComponentValueUnits(pComponent, pDesCommon, &Raccept, value_str);
				break;
			case 'C':
				getComponentValueUnits(pComponent, pDesCommon, &Caccept, value_str);
				break;
			case 'L':
				getComponentValueUnits(pComponent, pDesCommon, &Laccept, value_str);
				break;
			default:
				break;
			}
			// вставляю Value
			strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, value_str);
		}
		// вставляю окончание pDesCommon
		strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, pDesCommon);
	}

	// добавляю тип корпуса
	if( isInsertPattern )
	{
		if ( (pComponent->patternName != NULL) 
			&& ( strlen(pComponent->patternName) > 0 ) ) {
				strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, " (корпус ");
				strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, pComponent->patternName);
				strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, ")");
			}
		else {
			strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, " (корпус не определен)"); 
		}
	}
}

// получаю модуль (канал)
static bool getChannel(COMPONENT_LIST_STRUCT *listChan,TComponent * pComponent)
{
	TAttribute myAttr;		// текуший атрибут компонента
	char *tmp;
	char attrDesChannelValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesTUValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesFirmValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	listChan->id = 1;				// цифровая часть обозначения + два первых символа обозначения
	listChan->quantity = 1;			// количество
	listChan->channel = 1;			// номер канала в группе
	listChan->group = 1;			// номер группы каналов
	listChan->indexGroupName = 0;	// индекс группового имени
	listChan->notList[0] = 0;		// куда элемент не вносить
	listChan->refdes[0] = 0;		// текстовая часть  обозначения
	listChan->value[0] = 0;			// наименование
	// получаю первый атрибут
	tStatus = TGetFirstCompAttribute(&tContext, pComponent->refDes, &myAttr);
	while (tStatus == DBX_OK)
	{
		// атрибут с DesCommon или DesChannel
		if( (strcmp(attrDesCommonType, myAttr.type) == 0) ||
			(strcmp(attrDesChannel, myAttr.type) == 0) )
			strcpy_s(attrDesChannelValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// атрибут с DesTU (ТУ)
		else if(strcmp(attrDesTUType, myAttr.type) == 0)
			strcpy_s(attrDesTUValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// атрибут с DesFirm (производителем)
		else if(strcmp(attrDesFirmType, myAttr.type) == 0)
			strcpy_s(attrDesFirmValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// атрибут с номером гуппы каналов
		else if(strcmp(attrNoChannelGroupType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listChan->group);
		// атрибут с признаком не внесения в списки
		else if(strcmp(attrNotList, myAttr.type) == 0)
		{
			if( strstr(myAttr.value, "ALL") != NULL)
				// элемент в списки не заносится
				return false;
			strcpy_s(listChan->notList, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		}
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext, &myAttr);
	}
	// получили все атрибуты
	//-------------------------------------------------------------------
	// ищу номер элемента
	tmp = strpbrk(pComponent->refDes, acceptNumber);
	if(tmp != NULL)
	{	// заношу в id номер элемента
		long i=0;
		sscanf_s(tmp, "%d", &i);
		listChan->ids.num_refdes = i;
	}
	// заношу в id признак канала
	listChan->ids.lyt1_refdes = '@';
	// заношу в id первый символ
	if((unsigned char)pComponent->refDes[1] >= (unsigned char)'A')
		listChan->ids.lyt2_refdes = pComponent->refDes[0];
	// заношу в id номер канала
	listChan->ids.group = listChan->group;
	listChan->ids.channel = listChan->channel;
	// формирую результирующий listChan->refdes
	strcpy_s(listChan->refdes, DBX_MAX_ATTRIBUTE_LEN, pComponent->refDes);
	//-------------------------------------------------------------------
	// формирую результирующий listChan->value
	if(strlen(attrDesChannelValue) != 0)
	{
		// ищу место вставки Value начиная с начала строки
		char *pStr = strchr(attrDesChannelValue, '@');
		if(pStr != NULL)
		{	// есть место для вставки Value
			*pStr = 0;
			pStr++;
			strcpy_s(listChan->value, VALUE_MAX_STRING_LEN, attrDesChannelValue);
			strcat_s(listChan->value, VALUE_MAX_STRING_LEN, pComponent->value);
			strcat_s(listChan->value, VALUE_MAX_STRING_LEN, pStr);
		}
		else
			strcpy_s(listChan->value, VALUE_MAX_STRING_LEN, attrDesChannelValue);
	}
	else
		strcpy_s(listChan->value, VALUE_MAX_STRING_LEN, pComponent->value);
	// дописываю производителя
	if(strlen(attrDesFirmValue) > 0)
	{
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, attrDesFirmValue);
	}
	// дописываю ТУ
	if(strlen(attrDesTUValue) > 0)
	{
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, attrDesTUValue);
	}
	//------------------------------------------------------------------
	// корректирую Value
	correctString(listChan->value, VALUE_MAX_STRING_LEN);
	//------------------------------------------------------------------
	return true;
}

//------------------------------------------------------------------------------
/*! \brief Получение компонента
 *	\param listComp - указатель на таблицу компонентов
 *	\param pComponent - указатель на компонент
 *	\param isInsertPattern - TRUE, если требуется дополнить Value значением Pattern
 */
//------------------------------------------------------------------------------
static bool getComponent(COMPONENT_LIST_STRUCT *listComp, TComponent * pComponent, bool isInsertPattern)
{
	TAttribute myAttr;		// текуший атрибут компонента
	char *tmp;
	char attrDesTUValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesFirmValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesCommonValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	listComp->id = 1;				// цифровая часть обозначения + два первых символа обозначения
	listComp->quantity = 1;			// количество
	listComp->channel = 0;			// номер канала
	listComp->group = 0;			// номер группы каналов
	listComp->indexGroupName = 0;	// индекс группового имени
	listComp->notList[0] = 0;		// куда элемент не вносить
	listComp->refdes[0] = 0;		// текстовая часть  обозначения
	listComp->value[0] = 0;			// наименование
	// получаю первый атрибут
	tStatus = TGetFirstCompAttribute(&tContext, pComponent->refDes, &myAttr);
	while (tStatus == DBX_OK)
	{
		// это канал !
		if(strcmp(attrDesChannel, myAttr.type) == 0)
			return getChannel(listComp, pComponent);
		// атрибут с DesCommon
		else if(strcmp(attrDesCommonType, myAttr.type) == 0)
			strcpy_s(attrDesCommonValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// атрибут с DesTU (ТУ)
		else if(strcmp(attrDesTUType, myAttr.type) == 0)
			strcpy_s(attrDesTUValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// атрибут с DesFirm (производителем)
		else if(strcmp(attrDesFirmType, myAttr.type) == 0)
			strcpy_s(attrDesFirmValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// атрибут с признаком не внесения в списки
		else if(strcmp(attrNotList, myAttr.type) == 0)
		// в какие списки элемент не заносится
		{
			if( strstr(myAttr.value, "ALL") != NULL)
				// элемент в списки не заносится
				return false;
			strcpy_s(listComp->notList, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		}
		// атрибут с номером канала
		else if(strcmp(attrNoChannelType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listComp->channel);
		// атрибут с номером канала в группе
		else if(strcmp(attrNoChannelInGroupType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listComp->channel);
		// атрибут с номером гуппы каналов
		else if(strcmp(attrNoChannelGroupType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listComp->group);
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext, &myAttr);
	}
	// получили все атрибуты
	//-------------------------------------------------------------------
	// ищу число в RefDes
	tmp = strpbrk(pComponent->refDes, acceptNumber);
	if(tmp != NULL)
	{	// заношу в id номер элемента
		long i=0;
		sscanf_s(tmp, "%d", &i);
		listComp->ids.num_refdes = i;
	}
	// заношу в id первый символ
	listComp->ids.lyt1_refdes = 
		((unsigned char)pComponent->refDes[0] >= (unsigned char)'A')?(pComponent->refDes[0]):(0);
	// заношу в id второй символ
	listComp->ids.lyt2_refdes = 
		((unsigned char)pComponent->refDes[1] >= (unsigned char)'A')?(pComponent->refDes[1]):(0);
	// получаю индекс группового имени компонента
	if(pComponent->refDes[0] >= 'A')
		listComp->indexGroupName = getComponentGroupNameIndex(listComp->ids.lyt1_refdes,listComp->ids.lyt2_refdes);
	// корректирую для старых схем
	if( (listComp->channel > 0) && (listComp->group == 0) )
		listComp->group = 1;
	// заношу в id номер канала
	listComp->ids.group = listComp->group;
	listComp->ids.channel = listComp->channel;
	// формирую результирующий listComp->refdes
	strcpy_s(listComp->refdes, REFDES_MAX_STRING_LEN, pComponent->refDes);
	// формирую listComp->value;
	getComponentListValue(listComp, pComponent, attrDesCommonValue, isInsertPattern);
	// дописываю производителя
	if(strlen(attrDesFirmValue) > 0)
	{
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, attrDesFirmValue);
	}
	// дописываю ТУ
	if(strlen(attrDesTUValue) > 0)
	{
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, attrDesTUValue);
	}
	// корректирую Value
	correctString(listComp->value, VALUE_MAX_STRING_LEN);
	return true;
}

//------------------------------------------------------------------------------
/*! \brief Получение перечня компонентов
 *	\param listComp - указатель на таблицу компонентов
 *	\param isInsertPattern - TRUE, если требуется дополнить Value значением Pattern
 */
//------------------------------------------------------------------------------
static long getComponentsList(COMPONENT_LIST_STRUCT *listComp, bool isInsertPattern)
{
	TComponent myComponent;	// комонент
	long num_components = 0;
	//получаю первый компонент
	tStatus = TGetFirstComponent(&tContext, &myComponent);
	while(tStatus == DBX_OK)
	{
		switch(myComponent.connectionType)
		{
		case DBX_COMPONENT_CONNECTION_NORMAL:
			if( strpbrk(myComponent.refDes,acceptLastChannelComponets)==NULL)
			{	// настоящий компонент
				if(getComponent(listComp, &myComponent, isInsertPattern))
				{	// переход к следующей записи
					listComp++;
					num_components++;
				}
			}
			break;
		case DBX_COMPONENT_CONNECTION_MODULE:
			//канал
			if( getChannel(listComp, &myComponent) )
			{	// переход к следующей записи
				listComp++;
				num_components++;
			}
			break;
		case DBX_COMPONENT_CONNECTION_POWER:
			// порт питания
			if( isChannel(&myComponent) )
			{	// это канал!
				if( getChannel(listComp, &myComponent) )
				{	// переход к следующей записи
					listComp++;
					num_components++;
				}
			}
			break;
		default:
			break;
		}
		//получаю следующий компонент
		tStatus = TGetNextComponent(&tContext, &myComponent);
	}
	return num_components;
}

/**
 * @brief Функция сравнениния двух компонентов по Id
 * @param listComp         Список компонентов.
 * @param indexComponents  Таблица индексов компонентов в списке компонентов.
 * @param index1           Индекс компонента 1.
 * @param index1           Индекс компонента 1.
 * @return Функция возвращает результат сравнения.
 * @retval 0 - компоненты  идентичны.
 * @retval 1 - компоненты  1 больше компонента 2.
 * @retval 0 - компоненты  1 менььше компонента 2.
 */
static long 
compareComponentListElementsById(COMPONENT_LIST_STRUCT *listComp,
	long *indexComponents, long index1, long index2)
{
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	if( pComp1->id > pComp2->id ) return 1;
	if( pComp1->id < pComp2->id ) return -1;
	return 0;
}

/**
 * @brief Функция сравнениния двух компонентов по Id и Value
 * @param listComp         Список компонентов.
 * @param indexComponents  Таблица индексов компонентов в списке компонентов.
 * @param index1           Индекс компонента 1.
 * @param index1           Индекс компонента 1.
 * @return Функция возвращает результат сравнения.
 * @retval 0 - компоненты  идентичны.
 * @retval 1 - компоненты  1 больше компонента 2.
 * @retval 0 - компоненты  1 менььше компонента 2.
 */
static long 
compareComponentListElementsByIdAndValue(COMPONENT_LIST_STRUCT *listComp,
	long *indexComponents, long index1, long index2)
{
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	if( (pComp1->ids.group == 0) || (pComp2->ids.group == 0) )
	{
		long i = (long)pComp1->ids.lyt1_refdes - (long)pComp2->ids.lyt1_refdes;
		if(i != 0) return i;
		i = (long)pComp1->ids.lyt2_refdes - (long)pComp2->ids.lyt2_refdes;
		if(i != 0) return i;
	}
	else
	{
		if( pComp1->id > pComp2->id ) return 1;
		if( pComp1->id < pComp2->id ) return -1;
	}
	return strcmp(pComp1->value,pComp2->value);
}

/**
 * @brief Функция сортировки компонентов
 * @param listComp         Список компонентов.
 * @param indexComponents  Таблица индексов компонентов в списке компонентов.
 * @param num_components   Число компонентов.
 * @param pFunc            Указатель на функцию сравнения компонетов.
 */
static void
sortComponentList(COMPONENT_LIST_STRUCT *listComp,
	long *indexComponents, long num_components, 
	long(* pFunc)(COMPONENT_LIST_STRUCT *,long *, long, long))
{
	long i,j;
	// Гномья сортировка
	i = 1;
	j = 2;
	while(i < num_components)
	{
		if(pFunc(listComp,indexComponents,i-1,i) < 0)
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

// Id присваиваю номер функциональной группы
static void setIdComponentsByGroupName(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long num_components)
{
	for(long i=0; i < num_components; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComponents[i];
		// сбрасываю Id
		pListCur->id = 0;
		//  добавляю номер в соответсвии с групповым именем компонента
		if( pListCur->indexGroupName == 0 )
		{
			pListCur->ids.group = 0;
			pListCur->ids.lyt1_refdes = CompNameAccept[pListCur->indexGroupName].name[0];
			pListCur->ids.lyt2_refdes = pListCur->value[1];
		}
		else
		{
			pListCur->ids.group = pListCur->indexGroupName;
			pListCur->ids.lyt1_refdes = CompNameAccept[pListCur->indexGroupName].name[0];
			pListCur->ids.lyt2_refdes = CompNameAccept[pListCur->indexGroupName].name[1];
		}
	}
}

// формирую id по Value
static void makeIdFromValue(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long indexStart, long indexEnd, long index)
{
	// получаю смещение, с которого формируется Id
	index *= 8;
	for(long i= indexStart; i < indexEnd; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComponents[i];
		// обнуляю индекс
		pListCur->id = 0;			
		// длина строки
		long length = strlen(pListCur->value);
		if(index < length)
		{	// после index есть символы
			// начало части Value (от index)
			char *str = pListCur->value + index;
			// длина части Value
			length = strlen(str);
			// должны копировать не более 8 символов
			if(length > 8) length = 8;
			// копирую часть Value
			for(long j = 0; j < length; j++)
				pListCur->idstr[7-j] = str[j];
		}
	}
}

// обединение комонентов с одинаковым Value и соседними RefDes (для перечня)
// в сортированном (по RefDes и номеру канала) списке
static long mergeComponentListPE(COMPONENT_LIST_STRUCT *listComp, long *indexComp, long numComp)
{
	long i=0, j=0, k=0, n=0;
	while((++k) < numComp)
	{
		if( strstr(listComp[indexComp[k]].notList, "PE") != NULL )
			// компонент исключается из списка
			continue;
		//сравниваю Value
		if(	(strcmp(listComp[indexComp[j]].value, listComp[indexComp[k]].value) == 0) &&	// совпали Value
			(listComp[indexComp[j]].ids.group == listComp[indexComp[k]].ids.group) &&		// совпали номера групп
			(listComp[indexComp[j]].ids.channel == listComp[indexComp[k]].ids.channel) &&	// совпали номера каналов
			(strcmp(listComp[indexComp[j]].notList,listComp[indexComp[k]].notList) == 0) &&	// совпали маркеры не включения в списки
			(strstr(listComp[indexComp[k]].notList, "SP") == NULL) )							// компонет не будет исключаться из СП
		{	// Value и Channel одинаковые - увеличиваю количество
			listComp[indexComp[j]].quantity++;	// увеличиваю позицию количество
			// сравниваю RefDes
			if((listComp[indexComp[j]].ids.num_refdes+1) < listComp[indexComp[k]].ids.num_refdes)
			{	// RefDes отличаются более чем на 1 (ситуация: С1,С2,C3,С5,С6,С7 -> C1...C3,С5...С7)
				// добавляю к RefDes разделитель ", " или "..."
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, (n<2)?textMerge1Component:textMergeManyComponents);
				if(n > 0)
				{
					n = 0;
					// сливаю RefDes-ы
					strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k-1]].refdes);
					// добавляю к RefDes разделитель ", "
					strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, textMerge1Component);
				}
				// сливаю RefDes-ы
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k]].refdes);
			}
			else
				n++;
			// копирую номер RefDes-а
			listComp[indexComp[j]].ids.num_refdes = listComp[indexComp[k]].ids.num_refdes;
		}
		else 
		{	// записи разняться или список закончился
			if(n > 0)
			{	// если несколько компонентов, изменяю RefDes
				// добавляю к RefDes разделитель ", " или "..."
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, (n==1)?textMerge1Component:textMergeManyComponents);
				// сливаю RefDes-ы
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k-1]].refdes);
				n = 0;
			}
			indexComp[i] = indexComp[j];
			j = k;
			i++;
		}
	}
	if(n > 0)
	{	// если несколько компонентов, изменяю RefDes
		// добавляю к RefDes разделитель ", " или "..."
		strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, (n==1)?textMerge1Component:textMergeManyComponents);
		// сливаю RefDes-ы
		strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k-1]].refdes);
	}
	//дописываю последний элемент из списка
	indexComp[i] = indexComp[j];
	i++;
	return i;
}

//------------------------------------------------------------------------------
/* \brief Объединение комонентов с одинаковым Value (для спецификации)
 * в сортированном (по RefDes и номеру канала) списке
 * объединение происходит через ', ', по этому для корректного результата
 * предварительно необходим вызов mergeComponentListPE
 * \param listComp - указатель на таблицу компонентов
 * \param indexComp - указатель на таблицу индексов компонентов
 * \param numComp - число компонентов
 */
//------------------------------------------------------------------------------
static long mergeComponentListSP(COMPONENT_LIST_STRUCT *listComp, long *indexComp, long numComp)
{
	char refdes[REFDES_MAX_STRING_LEN];
	long i, j, k;

	// ищу группы каналов и бъединяю записи с одинаковым Value в списке
	k = 0;
	for(i = 0; i < numComp; i++)
	{	//получаю текущий компонент
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		// 
		if(strstr(pListCur->notList, "SP")) 	
			//компонент исключается из СП
			pListCur->ids.lyt1_refdes = '.';
		// попалась ненужная запись
		if(pListCur->ids.lyt1_refdes == '.') continue;
		// попалась группа каналов
		if(pListCur->ids.lyt1_refdes == '@') 
			k = pListCur->group;
		else if(k > 0)
		{
			for(j = i+1; j < numComp; j++)
			{
				COMPONENT_LIST_STRUCT * pListNext = listComp + indexComp[j];
				// попалась ненужная запись
				if(pListNext->ids.lyt1_refdes == '.') continue;
				// попалась следующий канал
				if(pListNext->ids.lyt1_refdes == '@') break;
				if( strcmp(pListCur->value, pListNext->value) == 0 )
				{	// Value одниковы
					// сливаю RefDes
					strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, ", ");
					strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, pListNext->refdes);
					// сливаю колчичество
					pListCur->quantity += pListNext->quantity;
					// помечаю запись как ненудную
					pListNext->ids.lyt1_refdes = '.';
				}
			}
		}
	}
	// ищу группы каналов и модифицирую значение RefDes до вида '5 групп: C1...C3'
	k = 0;
	refdes[0] = 0;
	for(i=0; i < numComp; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		if(pListCur->ids.lyt1_refdes == '@')
		{	// попалось описание канала
			refdes[0] = 0;
			k = pListCur->quantity;
			switch(k)
			{
			case 0:
			case 1:
				strcpy_s(refdes, REFDES_MAX_STRING_LEN, "1 группа: ");
				break;
			case 2:
			case 3:
			case 4:
				sprintf_s(refdes, REFDES_MAX_STRING_LEN, "%d группы: ",k);
				break;
			default:
				sprintf_s(refdes, REFDES_MAX_STRING_LEN, "%d групп: ",k);
				break;
			}
			// помечаю запись как ненужную
			pListCur->ids.lyt1_refdes = '.';
		}
		else if( refdes[0] != 0 )
		{	// после записи о канала должны следовать записи об элементах канала
			char tmp[REFDES_MAX_STRING_LEN];
			strcpy_s(tmp, REFDES_MAX_STRING_LEN, refdes);
			strcat_s(tmp, REFDES_MAX_STRING_LEN, pListCur->refdes);
			strcpy_s(pListCur->refdes, REFDES_MAX_STRING_LEN, tmp);
			// количество элементов в канале умножается на число каналов
			pListCur->quantity *= k;
		}
	}
	// объединяю записи с одинаковым Value в списке
	for(i = 0; i < numComp; i++)
	{	//получаю текущий компонент
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		// пропускаю ненужные записи
		if(pListCur->ids.lyt1_refdes == '.') continue;
		for(j = i+1; j < numComp; j++)
		{
			COMPONENT_LIST_STRUCT * pListNext = listComp + indexComp[j];
			// пропускаю ненужные записи
			if(pListNext->ids.lyt1_refdes == '.') continue;
			if( strcmp(pListCur->value, pListNext->value) == 0 )
			{	// Value одниковы
				// сливаю RefDes
				strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, ", ");
				strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, pListNext->refdes);
				// сливаю колчичество
				pListCur->quantity += pListNext->quantity;
				// помечаю запись как ненужную
				pListNext->ids.lyt1_refdes = '.';
			}
		}
	}
	// удаляю каналы и лишние элементы из списка
	j = 0;
	for(i = 0; i < numComp; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		if(pListCur->ids.lyt1_refdes != '.')
			indexComp[j++] = indexComp[i];
	}	
	// возвращаю число записей
	return j;
}

// открываю базу
static bool openDesign(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "sch", &tContext) == DBX_OK)
		return true;
	MessageBox(NULL,_T("Ошибка открытия базы !"),_T("Ошибка"),MB_OK);
	return false;
}

// закрываю базу
static bool closeDesign(void)
{
	TCloseDesign(&tContext, "");
	return true;
}
	
// получаю имя файла
static bool getDesignFilename(long typeFile, long typeList, char *pFilename)
{
	TDesign tDesignInfo;
	//получаю информацию о базе
	tStatus = TGetDesignInfo(&tContext, &tDesignInfo);
	if(tStatus == DBX_OK)
	{
		strncpy_s(pFilename,DBX_MAX_NAME_LEN,tDesignInfo.designName,DBX_MAX_NAME_LEN);
		char *pStr = strrchr(pFilename, '.');
		if(pStr != NULL) *pStr = 0;			
		pStr = strstr(pFilename, "Э3");
		if(pStr != NULL) *pStr = 0;			
	}
	else
	{
		strcpy_s(pFilename,DBX_MAX_NAME_LEN, "design");
	}
	// добавляю расширение
	strcat_s(pFilename,DBX_MAX_NAME_LEN,sOutFileNameEnd[typeList]);
	strcat_s(pFilename,DBX_MAX_NAME_LEN,sOutFileExtension[typeFile]);
	return true;
}

// получаю название
static bool getDesignName(char *pName)
{
	TDesign tDesignInfo;
	//получаю информацию о базе
	tStatus = TGetDesignInfo(&tContext, &tDesignInfo);
	if(tStatus == DBX_OK)
	{
		char *pStr = strstr(tDesignInfo.designName, "Э3");
		if(pStr != NULL) *pStr = 0;
		strcpy_s(pName,DBX_MAX_NAME_LEN,strrchr(tDesignInfo.designName, '\\')+1);
		if(strlen(tDesignInfo.drawingNumber) > 0)
		{
			strcat_s(pName,DBX_MAX_NAME_LEN, " ");
			strcat_s(pName,DBX_MAX_NAME_LEN,tDesignInfo.drawingNumber);
		}
	}
	return true;
}

// получаю субстроки длиной не более length
// строки деляться по пробелам
// src != NULL - первая субстрока
// src == NULL - последующие субстроки
static char * getSubstring(char *src, long length)
{
	static char *substr;	// указатель субстроки
	static long str_cnt = 0;
	if(src == NULL)
	{
		if(substr != NULL)
		{
			if(str_cnt == 0)
				substr = NULL;
			else
			{
				while(*(++substr) != 0);
				substr++;
				str_cnt--;
			}
		}
	}
	else
	{
		long size = strlen(src);
		if(size > 0)
		{	// не нулевая строка
			str_cnt = 1;
			for(long pos_end = length; pos_end < size; pos_end += length, str_cnt++)
			{
				// ищу место разрыва от конца строки
				for(long i = pos_end; i > 0; --i)
				{
					if(src[i] == ' ') 
					{	// место разрыва найдено
						src[i] = 0;
						// получаю начало новой субстроки
						pos_end = i+1;
						break;
					}
				}
			}			
			str_cnt--;
			substr = src;
		}
		else
		{	// нулевая строка
			substr = NULL;
		}
	}
	return substr;
}

/*
// получаю разделяю строк на субстроки строки src с индексом index
// маркер конца субстроки - @
static void getSubstring(char *src, long index, char *buffer, long length)
{
	for(long i = 0; i < index; i++)
	{
		if(src == NULL) break;
		// ищу начало строки
		src = strchr(src, '@');
	}
	if(src == NULL)
		strcpy_s(buffer,length, " ");
	else
	{
		if(index > 0) src++;
		strcpy_s(buffer,length,src);
		src = strchr(buffer, '@');
		if(src != NULL) *src = 0;
	}
}
// разделяю строк на субстроки с целыми словами и длиной, не превышающей length
// маркер конца субстроки - @
// возвращает число субстрок
static long makeSubstring(char *src, long length)
{
	// длина текущей субстроки
	long cur_length = 0;
	// счетчик субстрок
	long number = 1;
	while(true)
	{
		// получаю слово
		char *str = strchr(src, ' ');
		if(str == NULL) break;
		if((cur_length + str + 1 - src)<= length)
		{	// есть место для добавления слова
			// добавляю к строке еще слово
			if(cur_length > 0) cur_length++;
			str++;
			cur_length += (str-src);
			src = str;
		}
		else
		{	// нет места для добавления нового слова
			if(cur_length > 0)
			{	// начинаю новую субстроку
				*str = '@';
				cur_length = 0;
				number++;
			}
		}
	}			
	return number;
}
*/
// запись перечня в файл
static bool putToFileComponentList(long typeFile, long typeList, COMPONENT_LIST_STRUCT *pListComp, long *pIndexComp, long numComp, bool isFeedLine)
{
	FILE * hFile;
	char sFilename[DBX_MAX_NAME_LEN*5];
	// получаю имя файла
	if(!getDesignFilename(typeFile, typeList, sFilename))
		return false;
	// открываю файл
	if(fopen_s(&hFile,sFilename, "w") != 0)
		return false;
	// формирую заголовок
	getDesignName(sFilename);
	switch( typeFile )
	{
	case OUT_FILE_HTML:
		switch( typeList )
		{
		case OUT_LIST_VP:
			fprintf(hFile, "<!DOCTYPE HTML>\n<html>\n<body>\n<head>\n<title>Ведомость покупных %s</title>\n</head>\n",sFilename);
			fprintf(hFile, "<kbd><table>\n<table border=\"1\">\n");
			fprintf(hFile, "<caption>Ведомость покупных %s</caption>\n",sFilename);
			fprintf(hFile, "<tr><th>Наименование</th><th>Кол.</th></tr>\n");
			break;
		case OUT_LIST_SP:
			fprintf(hFile, "<!DOCTYPE HTML>\n<html>\n<body>\n<head>\n<title>Спецификация %s</title>\n</head>\n",sFilename);
			fprintf(hFile, "<kbd><table>\n<table border=\"1\">\n");
			fprintf(hFile, "<caption>Спецификация %s</caption>\n",sFilename);
			fprintf(hFile, "<tr><th>Наименование</th><th>Кол.</th><th>Примечание</th></tr>\n");
			break;
		default:
			fprintf(hFile, "<!DOCTYPE HTML>\n<html>\n<body>\n<head>\n<title>Перечень элементов %s</title>\n</head>\n",sFilename);
			fprintf(hFile, "<kbd><table>\n<table border=\"1\">\n");
			fprintf(hFile, "<caption>Перечень элементов %s</caption>\n",sFilename);
			fprintf(hFile, "<tr><th>Поз. обозначение</th><th>Наименование</th><th>Кол.</th><th>Примечание</th></tr>\n");
			break;
		}
		break;
	case OUT_FILE_RTF:
		fprintf(hFile, "{\\rtf1\\ansi\\ansicpg1251\n");
		switch( typeList )
		{
		case OUT_LIST_VP:
			fprintf(hFile, "Ведомость покупных %s\n\\par\n",sFilename);
			fprintf(hFile, "\\trowd\\trgaph50\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
			fprintf(hFile, "\\pard\\intbl\n");
			fprintf(hFile, "Наименование\\cell\nКол.\\cell\n\\row\n");
			break;
		case OUT_LIST_SP:
			fprintf(hFile, "Спецификация %s\n\\par\n",sFilename);
			fprintf(hFile, "\\trowd\\trgaph50\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
			fprintf(hFile, "\\pard\\intbl\n");
			fprintf(hFile, "Наименование\\cell\nКол.\\cell\nПримечание\\cell\n\\row\n");
			break;
		default:
			fprintf(hFile, "Перечень элементов %s\n\\par\n",sFilename);
			fprintf(hFile, "\\trowd\\trgaph50\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
			fprintf(hFile, "\\pard\\intbl\n");
			fprintf(hFile, "Поз. обозначение\\cell\nНаименование\\cell\nКол.\\cell\nПримечание\\cell\n\\row\n");
			break;
		}
		break;
	default:
		break;
	}
	// формирую список			
	// индекс группы элементов
	long indexGroupName = 0;
	bool fSingle = false;
	for(long i = 0; i < numComp; i++)
	{
		char strValue[VALUE_MAX_STRING_LEN];
		const char *pGroupName = NULL;
		COMPONENT_LIST_STRUCT * pList = pListComp + pIndexComp[i];
		COMPONENT_LIST_STRUCT * pListNext = pListComp + pIndexComp[i+1];
		if( indexGroupName != pList->indexGroupName)
		{	// группа элементов изменилась
			indexGroupName = pList->indexGroupName;
			if( (i+1) < numComp )
				// следующий элемент относится к другой группе
				fSingle = (indexGroupName != pListNext->indexGroupName);
			else
				// последний элемент - точно один
				fSingle = true;				
			pGroupName = getComponentGroupName(indexGroupName,fSingle);
		}
		// получаю полное имя компонента
		if( (!fSingle) ||						//элемент не одинок
			(pGroupName == NULL) ||				//нет группового имени
			(pList->ids.lyt1_refdes == '@') )	// это канал
		{
			strcpy_s(strValue, VALUE_MAX_STRING_LEN, pList->value);
		}
		else
		{	// для одинокого элемента к Value добавляется групповое имя
			strcpy_s(strValue, VALUE_MAX_STRING_LEN, pGroupName);
			strcat_s(strValue, VALUE_MAX_STRING_LEN, pList->value);
		}

		switch( typeList )
		{
		case OUT_LIST_VP:
			switch( typeFile )
			{
			case OUT_FILE_TXT:
				if(pGroupName != NULL)
				{
					fprintf(hFile, "%s",pGroupName);
					if( !fSingle ) fprintf(hFile, "\n");
				}
				fprintf(hFile, "%s %d шт\n",pList->value,pList->quantity);
				break;
			case OUT_FILE_HTML:
				if(fSingle)
				{
					fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td></tr>\n");
					fprintf(hFile, "<tr><td>%s%s</td><td align=\"center\">%d</td></tr>\n",pGroupName,pList->value,pList->quantity);
				}
				else 
				{
					if(pGroupName != NULL)
					{
						fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td></tr>\n");
						fprintf(hFile, "<tr><th>%s</th><td>&nbsp</td></tr>\n",pGroupName);
						fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td></tr>\n");
					}
					fprintf(hFile, "<tr><td>%s</td><td align=\"center\">%d</td></tr>\n",pList->value,pList->quantity);
				}
				break;
			case OUT_FILE_RTF:
				if(fSingle)
				{
					fprintf(hFile, "\\trowd\\trgaph50\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
					fprintf(hFile, "\\pard\\intbl\n");
					fprintf(hFile, " \\cell\n \\cell\n\\row\n");
					fprintf(hFile, "\\trowd\\trgaph50\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
					fprintf(hFile, "\\pard\\intbl\n");
					fprintf(hFile, "%s%s\\cell\n%d\\cell\n\\row\n",pGroupName,pList->value,pList->quantity);
				}
				else 
				{
					if(pGroupName != NULL)
					{
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, " \\cell\n \\cell\n\\row\n");
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, "%s\\cell\n \\cell\n\\row\n",pGroupName);
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, " \\cell\n \\cell\n\\row\n");
					}
					fprintf(hFile, "\\trowd\\trgaph50\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
					fprintf(hFile, "\\pard\\intbl\n");
					fprintf(hFile, "%s\\cell\n%d\\cell\n\\row\n",pList->value,pList->quantity);
				}
				break;
			default:
				if(pGroupName != NULL)
				{
					fprintf(hFile, "%s",pGroupName);
					if( !fSingle ) fprintf(hFile, ";;\n");
				}
				fprintf(hFile, "%s;%d;\n",pList->value,pList->quantity);
				break;
			}
			break;
		case OUT_LIST_SP:
			switch( typeFile )
			{
			case OUT_FILE_TXT:
				if(pGroupName != NULL)
				{
					fprintf(hFile, "%s",pGroupName);
					if( !fSingle ) fprintf(hFile, "\n");
				}
				fprintf(hFile, "%s %d шт %s\n",pList->value,pList->quantity,pList->refdes);
				break;
			case OUT_FILE_HTML:
				if(fSingle)
				{
					fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td></tr>\n");
					fprintf(hFile, "<tr><td>%s%s</td><td align=\"center\">%d</td><td>%s</td></tr>\n",pGroupName,pList->value,pList->quantity,pList->refdes);
				}
				else
				{
					if(pGroupName != NULL)
					{
						fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td></tr>\n");
						fprintf(hFile, "<tr><th>%s</th><td>&nbsp</td><td>&nbsp</td></tr>\n",pGroupName);
						fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td></tr>\n");
					}
					fprintf(hFile, "<tr><td>%s</td><td align=\"center\">%d</td><td>%s</td></tr>\n",pList->value,pList->quantity,pList->refdes);
				}
				break;
			case OUT_FILE_RTF:
				if(fSingle)
				{
					fprintf(hFile, "\\trowd\\trgaph50\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
					fprintf(hFile, "\\pard\\intbl\n");
					fprintf(hFile, " \\cell\n \\cell\n \\cell\n\\row\n");
					fprintf(hFile, "\\trowd\\trgaph50\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
					fprintf(hFile, "\\pard\\intbl\n");
					fprintf(hFile, "%s%s\\cell\n%d\\cell\n%s\\cell\n\\row\n",pGroupName,pList->value,pList->quantity,pList->refdes);
				}
				else
				{
					if(pGroupName != NULL)
					{
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, " \\cell\n \\cell\n \\cell\n\\row\n");
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, "%s\\cell\n \\cell\n \\cell\n\\row\n",pGroupName);
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, " \\cell\n \\cell\n \\cell\n\\row\n");
					}
					fprintf(hFile, "\\trowd\\trgaph50\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
					fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
					fprintf(hFile, "\\pard\\intbl\n");
					fprintf(hFile, "%s\\cell\n%d\\cell\n%s\\cell\n\\row\n",pList->value,pList->quantity,pList->refdes);
				}
				break;
			default:
				if(pGroupName != NULL)
				{
					fprintf(hFile, ";;;\n%s",pGroupName);
					if( !fSingle ) fprintf(hFile, ";;;\n;;;\n");
				}
				fprintf(hFile, "%s;%d;%s;\n",pList->value,pList->quantity,pList->refdes);
				break;
			}
			break;
		default:
			// перечень элементов
			{
				const char *pRemark = (strstr(pList->notList, "SP") != NULL)?("Не устанавливается"):("");
				switch( typeFile )
				{
				case OUT_FILE_TXT:
					if(pGroupName != NULL)
					{
						if( fSingle ) fprintf(hFile, "%s ",pList->refdes);
						fprintf(hFile, "%s",pGroupName);
						if( !fSingle ) fprintf(hFile, "\n");
					}
					if( !fSingle ) fprintf(hFile, "%s ",pList->refdes);
					fprintf(hFile, "%s %d шт %s\n",pList->value,pList->quantity,pRemark);
					break;
				case OUT_FILE_HTML:
					if(pList->ids.lyt1_refdes == '@')
					{
						fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td></tr>\n");
						fprintf(hFile, "<tr><th>%s</th><th>%s</th><th>%d</th><th>&nbsp</th></tr>\n",pList->refdes,pList->value,pList->quantity);
					}
					else
					{
						if(fSingle)
						{
							fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td></tr>\n");
							fprintf(hFile, "<tr><td>%s</td><td>%s%s</td><td align=\"center\">%d</td><td>%s&nbsp</td></tr>\n",pList->refdes,pGroupName,pList->value,pList->quantity,pRemark);
						}
						else
						{
							if(pGroupName != NULL)
							{
								fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td></tr>\n");
								fprintf(hFile, "<tr><td>&nbsp</td><th>%s&nbsp</th><td>&nbsp</td><td>&nbsp</td></tr>\n",pGroupName);
								fprintf(hFile, "<tr><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td></tr>\n");
							}
							fprintf(hFile, "<tr><td>%s</td><td>%s</td><td align=\"center\">%d</td><td>%s&nbsp</td></tr>\n",pList->refdes,pList->value,pList->quantity,pRemark);
						}
					}
					break;
				case OUT_FILE_RTF:
					if(pList->ids.lyt1_refdes == '@')
					{	// канал
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, " \\cell\n \\cell\n \\cell\n \\cell\n\\row\n");
						fprintf(hFile, "\\trowd\\trgaph50\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
						fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
						fprintf(hFile, "\\pard\\intbl\n");
						fprintf(hFile, "%s\\cell\n%s\\cell\n%d\\cell\n \\cell\n\\row\n",pList->refdes,pList->value,pList->quantity);
					}
					else
					{
						if(pGroupName != NULL)
						{	//началась новая группа
							fprintf(hFile, "\\trowd\\trgaph50\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
							fprintf(hFile, "\\pard\\intbl\n");
							fprintf(hFile, " \\cell\n \\cell\n \\cell\n \\cell\n\\row\n");
							if(!fSingle)
							{	// элемент в гурппе не один
								fprintf(hFile, "\\trowd\\trgaph50\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
								fprintf(hFile, "\\pard\\intbl\n");
								fprintf(hFile, " \\cell\n%s\\cell\n \\cell\n \\cell\n\\row\n",pGroupName);
								fprintf(hFile, "\\trowd\\trgaph50\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
								fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
								fprintf(hFile, "\\pard\\intbl\n");
								fprintf(hFile, " \\cell\n \\cell\n \\cell\n \\cell\n\\row\n");
							}
						}
						if(isFeedLine)
						{
							const char nullStr[3] = {" "};
							char *pStr1[DBX_MAX_ATTRIBUTE_LEN/11] = {NULL};
							char *pStr2[DBX_MAX_ATTRIBUTE_LEN/11] = {NULL};
							// получаю разбиение на субстроки
							long i1 = 0;
							pStr1[i1] = getSubstring(pList->refdes,11);
							while(pStr1[i1] != NULL)
							{
								if((++i1) >= DBX_MAX_ATTRIBUTE_LEN/11)
									break;
								pStr1[i1] = getSubstring(NULL,11);
							}
							// получаю разбиение на субстроки
							long i2 = 0;
							pStr2[i2] = getSubstring(strValue,45);
							while(pStr2[i2] != NULL)
							{
								if((++i2) >= DBX_MAX_ATTRIBUTE_LEN/45)
									break;
								pStr2[i2] = getSubstring(NULL,45);
							}
							fprintf(hFile, "\\trowd\\trgaph50\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
							fprintf(hFile, "\\pard\\intbl\n");
							if(i1 > i2) i2 = i1;
							for(i1 = 0; i1 < i2; i1++)
							{
								// замена нулевых указателей
								if(pStr1[i1] == NULL) pStr1[i1] = (char *)nullStr;
								if(pStr2[i1] == NULL) pStr2[i1] = (char *)nullStr;
								if(i1 == 0)
									fprintf(hFile, "%s\\cell\n%s\\cell\n%d\\cell\n%s\\cell\n\\row\n",pStr1[i1],pStr2[i1],pList->quantity,pRemark);
								else
									fprintf(hFile, "%s\\cell\n%s\\cell\n\\cell\n\\cell\n\\row\n",pStr1[i1],pStr2[i1]);
							}
						}
						else
						{
							fprintf(hFile, "\\trowd\\trgaph50\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
							fprintf(hFile, "\\pard\\intbl\n");
							fprintf(hFile, "%s\\cell\n%s\\cell\n%d\\cell\n%s\\cell\n\\row\n",pList->refdes,strValue,pList->quantity,pRemark);
						}					
					}
					break;
				default:
					if(pGroupName != NULL)
					{
						if( fSingle ) fprintf(hFile, "%s;",pList->refdes);
						fprintf(hFile, "%s",pGroupName);
						if( !fSingle ) fprintf(hFile, ";;;\n;;;;\n");
					}
					if( !fSingle ) fprintf(hFile, "%s;",pList->refdes);
					fprintf(hFile, "%s;%d;%s;\n",pList->value,pList->quantity,pRemark);
				}
				break;
			}
		}
	}
	// формирую заключение
	switch( typeFile )
	{
	case OUT_FILE_HTML:
		fprintf(hFile, "</table>\n</kbd>\n</body>\n</html>\n");
		break;
	case OUT_FILE_RTF:
		fprintf(hFile, "}\n");
		break;
	default:
		break;
	}
	// закрываю файл
	fclose(hFile);
	return true;
}

// запись перечня в файл
bool makeComponentList(long typeFile, long typeList, bool isFeedLine, 
	bool isInsertPattern, bool isSortingRefdes)
{
	COMPONENT_LIST_STRUCT *pListComponents;
	long *pIndexComponents;
	pListComponents = NULL;
	pIndexComponents = NULL;
	while(openDesign())
	{
		// получаю число компонентов
		long numComponents = getNumberComponents();
		if(numComponents < 1) break;
		// выделяю память
		pListComponents = new COMPONENT_LIST_STRUCT [numComponents];
		pIndexComponents = new long [numComponents];
		if(pListComponents == NULL) break;
		if(pIndexComponents == NULL) break;
		// получаю компоненты
		numComponents = getComponentsList(pListComponents, isInsertPattern);
		if(numComponents < 1) break;
		// инициализация индексов	
		for(long i = 0; i < numComponents; i++)
			pIndexComponents[i] = i;
		// сортировка списка компонентов по RefDes
		sortComponentList(pListComponents,pIndexComponents,numComponents, 
			&compareComponentListElementsById);
		switch(typeList)
		{
		// пспецификация
		case OUT_LIST_VP:
		case OUT_LIST_SP:	// для спецификации
			// слияние соседних позиций в списке компонентов
			numComponents = mergeComponentListPE(pListComponents,pIndexComponents,numComponents);
			// слияние соседних позиций в списке компонентов
			numComponents = mergeComponentListSP(pListComponents,pIndexComponents,numComponents);
			if (!isSortingRefdes) {
				// вставляю в Id групповой порядковый номер компонента
				setIdComponentsByGroupName(pListComponents,pIndexComponents,numComponents);
				// сортировка списка компонентов по Id и Value
				sortComponentList(pListComponents,pIndexComponents,numComponents,
					&compareComponentListElementsByIdAndValue);
			}
			break;
		// перечень
		case OUT_LIST_PE:	// для перечня
			// слияние соседних позиций в списке компонентов
			numComponents = mergeComponentListPE(pListComponents,pIndexComponents,numComponents);
			break;
		// простой спикок
		default:
			break;
		}
		// формирую список в файле
		if(!putToFileComponentList(typeFile, typeList, pListComponents,pIndexComponents,numComponents, isFeedLine))
			MessageBox(NULL,_T("Ошибка записи в выходной файл !"),_T("Ошибка"),MB_OK);
		// выхожу
		break;
	}
	closeDesign();
	delete pListComponents;
	delete pIndexComponents;
	return true;
}

void CComponentListDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// тип файла
	long fileType = OUT_FILE_TXTDLM;
	switch(GetCheckedRadioButton(IDC_RADIO_FILE_TXTSEP,IDC_RADIO_FILE_RTF))
	{
	case IDC_RADIO_FILE_TXTSEP:
		fileType = OUT_FILE_TXTDLM;
		break;
	case IDC_RADIO_FILE_TXT:
		fileType = OUT_FILE_TXT;
		break;
	case IDC_RADIO_FILE_HTML:
		fileType = OUT_FILE_HTML;
		break;
	case IDC_RADIO_FILE_RTF:
		fileType = OUT_FILE_RTF;
		break;
	}
	// тип списка
	switch(GetCheckedRadioButton(IDC_RADIO_TYPE_PE,IDC_RADIO_TYPE_LST))
	{
	case IDC_RADIO_TYPE_PE:
		makeComponentList(fileType, OUT_LIST_PE, 
			(IsDlgButtonChecked(IDC_CHECK_FEED) == BST_CHECKED),
			(IsDlgButtonChecked(IDC_CHECK_INSERT_PATTERN) == BST_CHECKED),
			false);
		break;
	case IDC_RADIO_TYPE_SP:
		makeComponentList(fileType, OUT_LIST_SP,
			(IsDlgButtonChecked(IDC_CHECK_FEED) == BST_CHECKED),
			(IsDlgButtonChecked(IDC_CHECK_INSERT_PATTERN) == BST_CHECKED),
			(IsDlgButtonChecked(IDC_CHECK_SORTING_REFDES) == BST_CHECKED) );
		break;
	case IDC_RADIO_TYPE_VP:
		makeComponentList(fileType, OUT_LIST_VP,
			(IsDlgButtonChecked(IDC_CHECK_FEED) == BST_CHECKED),
			(IsDlgButtonChecked(IDC_CHECK_INSERT_PATTERN) == BST_CHECKED),
			(IsDlgButtonChecked(IDC_CHECK_SORTING_REFDES) == BST_CHECKED) );
		break;
	case IDC_RADIO_TYPE_LST:
		makeComponentList(fileType, OUT_LIST,
			(IsDlgButtonChecked(IDC_CHECK_FEED) == BST_CHECKED),
			(IsDlgButtonChecked(IDC_CHECK_INSERT_PATTERN) == BST_CHECKED),
			false );
		break;
	}

	CDialogEx::OnOK();
}
