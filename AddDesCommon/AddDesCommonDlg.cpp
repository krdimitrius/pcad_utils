
// AddDesCommonDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "AddDesCommon.h"
#include "AddDesCommonDlg.h"
#include "afxdialogex.h"
#include "dbx32.h"
#include "myDbxUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const char sVersion[] = "1.0.2.0";
static const char sName[] = "AddDesCommon Utility";

// диалоговое окно CAddDesCommonDlg
CAddDesCommonDlg::CAddDesCommonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddDesCommonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddDesCommonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, myCombo1);
	DDX_Control(pDX, IDC_COMBO2, myCombo2);
	DDX_Control(pDX, IDC_EDIT_LIST, EditList);
}

BEGIN_MESSAGE_MAP(CAddDesCommonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAddDesCommonDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_SELECT, &CAddDesCommonDlg::OnBnClickedRadioSelect)
	ON_BN_CLICKED(IDC_RADIO_LIST, &CAddDesCommonDlg::OnBnClickedRadioList)
	ON_BN_CLICKED(IDGET, &CAddDesCommonDlg::OnBnClickedGet)
	ON_BN_CLICKED(IDSAVE2LIST, &CAddDesCommonDlg::OnBnClickedSave2list)
	ON_BN_CLICKED(IDGET2, &CAddDesCommonDlg::OnBnClickedGet2)
	ON_BN_CLICKED(IDOK2, &CAddDesCommonDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDDEL2LIST, &CAddDesCommonDlg::OnBnClickedDel2list)
	ON_BN_CLICKED(IDCANCEL, &CAddDesCommonDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// обработчики сообщений CAddDesCommonDlg

BOOL CAddDesCommonDlg::OnInitDialog()
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

	CheckDlgButton(IDC_RADIO_SELECT, BST_CHECKED);
	EditList.ShowWindow(0);
	// получаю данные из ini-файла
	GetCurrentDirectoryW(1024,IniFilename);
	wcscat_s(IniFilename,1024,_T("\\AddDesCommon.ini"));
	myCombo1.AddString(_T("@"));

	for (int i = 1; i < 1000; i++)
	{
		WCHAR keyName[6];
		WCHAR keyValue[DBX_MAX_ATTRIBUTE_LEN];
		swprintf(keyName, 5, _T("%d"), i);
		if( GetPrivateProfileString(_T("DesCommon"), keyName, NULL, keyValue, DBX_MAX_ATTRIBUTE_LEN, IniFilename) )
		{
			myCombo1.AddString(keyValue);
		}
	}
	myCombo1.SetCurSel(0);

	myCombo2.AddString(_T(" "));
	myCombo2.SetCurSel(0);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CAddDesCommonDlg::OnPaint()
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
HCURSOR CAddDesCommonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//========================================================================================

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

// получаю субстроки c RefDes
// строки деляться по пробелам
// src != NULL - первая субстрока
// src == NULL - последующие субстроки
// возвращает true, если есть субстрока
static bool getRefDesFromString(char *dest, char *src)
{
	char *pPrvDig, *pPrvDiv, *pCurTxt, *pCurDig;
	long sizePrvTxt,sizeCurTxt;
	static char *substr = NULL;	// указатель субстроки
	static long prvCnt, curCnt; // счетчики номера элемента
	if(dest == NULL)
		return false;
	*dest = 0;
	if(src != NULL)
	{
		substr = src;
		prvCnt = 0;
		curCnt = 0;
	}
	// субстроки не существует
	if(substr == NULL)
		return false;
	// получаю начало обозначения элемента
	substr = myStrpbrkLatin(substr);
	if(substr == NULL)
		return false;
	// получаю начало номера элемента
	pPrvDig = myStrpbrkDigit(substr);
	if(pPrvDig == NULL)
		return false;
	// получаю длину текстовой части
	sizePrvTxt = pPrvDig - substr;
	if(++prvCnt < curCnt)
	{	// выдаем элемент из перечисления типа "C1...C3"
		// копирую текстовую часть
		strncpy_s(dest,DBX_MAX_ATTRIBUTE_LEN,substr,sizePrvTxt);
		// формирую цифровую часть
		sprintf_s(dest+sizePrvTxt,DBX_MAX_ATTRIBUTE_LEN-sizePrvTxt,"%d",prvCnt);
		return true;
	}
	// получаю разделитель
	pPrvDiv = strpbrk(pPrvDig,".-, ");
	// копирую обозначение элемента
	strncpy_s(dest,DBX_MAX_ATTRIBUTE_LEN,substr,(pPrvDiv == NULL)?(DBX_MAX_ATTRIBUTE_LEN):(pPrvDiv - substr));
	// получаю начало тесктовой части следующего элемента
	pCurTxt = myStrpbrkLatin(pPrvDig);
	// а вдруг это последний элемент ?
	if((pPrvDiv == NULL) || (pCurTxt == NULL))
	{
		substr = NULL;
		return true;
	}
	// получаю начало цифровой части следующего элемента
	pCurDig = myStrpbrkDigit(pCurTxt);
	// а вдруг это последний элемент ?
	if(pCurDig == NULL)
	{
		substr = NULL;
		return true;
	}
	// получаю номер следующего элемента
	sscanf_s(pCurDig,"%d",&curCnt);
	prvCnt = curCnt;
	// получаю длину тексовой части следующего элемента
	sizeCurTxt = pCurDig - pCurTxt;
	// проверяю возможность начала перечисления типа "C1...C3" или "C1-C3" 
	if((*pPrvDiv == '.') || (*pPrvDiv == '-'))
	{
		if(sizePrvTxt == sizeCurTxt)
		{
			if(strncmp(substr, pCurTxt, sizeCurTxt ) == 0)
			{	// есть перечисление - получаю номер предыдущего элемента
				sscanf_s(pPrvDig,"%d",&prvCnt);
				if(prvCnt > curCnt) 
					prvCnt = curCnt;
			}
		}
	}
	// сохраняю указатель текущей субстроки
	substr = pCurTxt;
	return true;
}

// добавляю атрибут к компоненту
bool addAttribute(char * pRefDes, const char * typeAttr, char * valueAttr)
{
	TAttribute myAttr; // атрибут
	bool isAttr = false;
	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		if(strcmp(myAttr.type,typeAttr) == 0)
		{	// есть требуемый атрибут
			isAttr = true;
			break;
		}
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	myAttr.isVisible = false;
	strcpy_s(myAttr.value,DBX_MAX_NAME_LEN,valueAttr);
	myAttr.valueLength = strlen(myAttr.value);
	if(isAttr)
	{
		TModifyCompAttribute(&tContext,pRefDes,&myAttr);
	}
	else
	{
		strcpy_s(myAttr.type,DBX_MAX_NAME_LEN,typeAttr);
		myAttr.typeLength = strlen(myAttr.type);
		TAddCompAttribute(&tContext,pRefDes,&myAttr);
	}
	return true;
}

// считывают атрибут компонента
bool getAttribute(char * pRefDes, const char * typeAttr, char * valueAttr)
{
	TAttribute myAttr; // атрибут

	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		if(strcmp(myAttr.type,typeAttr) == 0)
		{	// есть требуемый атрибут
			strcpy_s(valueAttr, DBX_MAX_NAME_LEN, myAttr.value);
			break;
		}
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	return true;
}

// удаление атрибута компонента
bool deleteAttribute(char * pRefDes, const char * typeAttr)
{
	TAttribute myAttr; // атрибут
	bool isAttr = false;
	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		if(strcmp(myAttr.type,typeAttr) == 0)
		{	// есть требуемый атрибут
			TDeleteCompAttribute(&tContext,pRefDes,&myAttr);
			break;
		}
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	return true;
}

// добавление атрибутов в выделенный компонент
bool addAttributesSelect(const char * typeAttr, char * valueAttr)
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
			// добавляю атрибут компонена
			addAttribute(myRefDes,typeAttr,valueAttr);
		}
		//получаю следующий компонент
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	return true;
}

// чтение атрибута из первого выделенного компонента
static bool
getAttributeSelect(const char * typeAttr, char * valueAttr)
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
			// добавляю атрибут компонена
			getAttribute(myRefDes, typeAttr, valueAttr);
			break;
		}
		//получаю следующий компонент
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	return true;
}

// добавление атрибутов в компоненты из списка
bool addAttributesList(const char * typeAttr, char * valueAttr, char * listRefDesComp)
{
	char myRefDes[DBX_MAX_ATTRIBUTE_LEN];
	// получаю первый RefDes
	bool flag = getRefDesFromString(myRefDes,listRefDesComp);
	while(flag)
	{
		// добавляю атрибут компонена
		addAttribute(myRefDes,typeAttr,valueAttr);
		// получаю последующий RefDes
		flag = getRefDesFromString(myRefDes,NULL);
	}
	return true;
}

// получение атрибута из первого компонента списка
bool getAttributeList(const char * typeAttr, char * valueAttr, char * listRefDesComp)
{
	char myRefDes[DBX_MAX_ATTRIBUTE_LEN];
	// получаю первый RefDes
	bool flag = getRefDesFromString(myRefDes,listRefDesComp);
	if(flag)
	{
		// получение атрибута компонена
		getAttribute(myRefDes, typeAttr, valueAttr);
	}
	return true;
}

// удаление атрибутов из выделенных компонентов
bool deleteAttributesSelect(const char * typeAttr)
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
			// добавляю атрибут компонена
			deleteAttribute(myRefDes,typeAttr);
		}
		//получаю следующий компонент
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	return true;
}

// удаление атрибутов компонентов из списка
bool deleteAttributesList(const char * typeAttr, char * listRefDesComp)
{
	char myRefDes[DBX_MAX_ATTRIBUTE_LEN];
	// получаю первый RefDes
	bool flag = getRefDesFromString(myRefDes,listRefDesComp);
	while(flag)
	{
		// добавляю атрибут компонена
		deleteAttribute(myRefDes,typeAttr);
		// получаю последующий RefDes
		flag = getRefDesFromString(myRefDes,NULL);
	}
	return true;
}

// добавление атрибутов в выделенный компонент
bool processAddAttributes(const char * typeAttr, char * valueAttr, char * listRefDesComp)
{
	bool flag = false;
	if( (strlen(typeAttr) == 0) ||
		(strlen(valueAttr) == 0) )
		return flag;
	if(openDesign())
	{
		if(listRefDesComp == NULL)
			flag = addAttributesSelect(typeAttr, valueAttr);
		else
			flag = addAttributesList(typeAttr, valueAttr, listRefDesComp);
	}
	closeDesign();
	return flag;
}

// получение атрибута из компонента
bool
processGetAttribute(const char * typeAttr, char * valueAttr, char * listRefDesComp)
{
	bool flag = false;
	if (strlen(typeAttr) == 0)
		return flag;
	if(openDesign())
	{
		if(listRefDesComp == NULL)
			flag = getAttributeSelect(typeAttr, valueAttr);
		else
			flag = getAttributeList(typeAttr, valueAttr, listRefDesComp);
	}
	closeDesign();
	return flag;
}

// добавление атрибутов в выделенный компонент
bool processDeleteAttributes(const char * typeAttr, char * listRefDesComp)
{
	bool flag = false;
	if(strlen(typeAttr) == 0)
		return flag;
	if(openDesign())
	{
		if(listRefDesComp == NULL)
			flag = deleteAttributesSelect(typeAttr);
		else
			flag = deleteAttributesList(typeAttr, listRefDesComp);
	}
	closeDesign();
	return flag;
}

//========================================================================================
void CAddDesCommonDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	long length = myCombo1.GetWindowTextLengthW()+1;
	LPWSTR pStrW = new WCHAR [length];
	LPSTR pValueA = new CHAR [length * 2];
	LPSTR pListA = NULL;
	// получаю значение атрибута
	myCombo1.GetWindowTextW(pStrW,length);
	// строку конвертирую в ANSI
	while (0 != WideCharToMultiByte(CP_ACP, 0, pStrW, length, pValueA,
                  length*2, NULL, NULL))
	{
		if(GetCheckedRadioButton(IDC_RADIO_SELECT,IDC_RADIO_LIST) == IDC_RADIO_LIST)
		{
			// получаю список
			length = EditList.GetWindowTextLengthW()+1;
			delete pStrW;
			pStrW = new WCHAR [length];
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// конвертирую список в ANSI
			if (0 == WideCharToMultiByte(CP_ACP, 0, pStrW, length, pListA, length*2, NULL, NULL))
				break;
		}
		if(IsDlgButtonChecked(IDC_CHECK_CHANNEL) == BST_CHECKED)
		{
			processAddAttributes(attrDesChannel,pValueA,pListA);
			processDeleteAttributes(attrDesCommonType,pListA);
		}	
		else
		{
			processAddAttributes(attrDesCommonType,pValueA,pListA);
			processDeleteAttributes(attrDesChannel,pListA);
		}
		break;
	}
	delete pStrW;
	delete pValueA;
	delete pListA;
}

void CAddDesCommonDlg::OnBnClickedRadioSelect()
{
	// TODO: Add your control notification handler code here
	EditList.ShowWindow(0);
}

void CAddDesCommonDlg::OnBnClickedRadioList()
{
	// TODO: Add your control notification handler code here
	EditList.ShowWindow(1);
}

void CAddDesCommonDlg::OnBnClickedGet()
{
	// TODO: Add your control notification handler code here
	const long sizeBuffer = 255;
	long length;
	LPWSTR pStrW = new WCHAR [sizeBuffer];
	LPSTR pValueA = new CHAR [sizeBuffer * 2];
	LPSTR pListA = NULL;

	pValueA[0] = 0;

	while (1) {
		if(GetCheckedRadioButton(IDC_RADIO_SELECT,IDC_RADIO_LIST) == IDC_RADIO_LIST)
		{
			// получаю список
			length = EditList.GetWindowTextLengthW() + 1;
			if (length > sizeBuffer) {
				delete pStrW;
				pStrW = new WCHAR [length];
			}
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// конвертирую список в ANSI
			if (!WideCharToMultiByte(CP_ACP, 0, pStrW, length, pListA, length*2, NULL, NULL))
				break;
		}
		processGetAttribute(attrDesCommonType, pValueA, pListA);
		break;
	}

	if (pValueA[0]) {
		// строку конвертирую из ANSI
		MultiByteToWideChar(CP_ACP, 0, pValueA, -1, pStrW, sizeBuffer);
		// устанавливаю значение атрибута
		myCombo1.SetWindowTextW(pStrW);
	}

	delete pStrW;
	delete pValueA;
	delete pListA;
}

void CAddDesCommonDlg::OnBnClickedSave2list()
{
	// TODO: Add your control notification handler code here
	long length = myCombo1.GetWindowTextLengthW()+1;
	LPWSTR pStrW = new WCHAR [length];
	WCHAR attrName[DBX_MAX_ATTRIBUTE_LEN];

	// получаю значение атрибута
	myCombo1.GetWindowTextW(pStrW, length);
	myCombo1.AddString(pStrW);
	for (int i = 1; i < 1000; i++)
	{
		WCHAR keyName[6];
		WCHAR keyValue[DBX_MAX_ATTRIBUTE_LEN];
		swprintf(keyName, 5, _T("%d"), i);
		if( !GetPrivateProfileString(_T("DesCommon"), keyName, NULL, keyValue, DBX_MAX_ATTRIBUTE_LEN, IniFilename) )
		{
			WritePrivateProfileStringW(_T("DesCommon"), keyName, pStrW, IniFilename);
			break;
		}
	}

	delete pStrW;
}

void CAddDesCommonDlg::OnBnClickedDel2list()
{
	// TODO: Add your control notification handler code here
	long length = myCombo1.GetWindowTextLengthW() + 1;
	LPWSTR pStrW = new WCHAR [length];

	myCombo1.GetWindowTextW(pStrW, length);
	int index = myCombo1.FindString(0, pStrW);
	if (index > 0)
		myCombo1.DeleteString(index);

	for (int i = 1; i < 1000; i++)
	{
		WCHAR keyName[6];
		WCHAR keyValue[DBX_MAX_ATTRIBUTE_LEN];
		swprintf(keyName, 5, _T("%d"), i);
		if( GetPrivateProfileString(_T("DesCommon"), keyName, NULL, keyValue, DBX_MAX_ATTRIBUTE_LEN, IniFilename) )
		{
			if (StrCmpW(pStrW, keyValue) == 0) {
				WritePrivateProfileStringW(_T("DesCommon"), keyName, NULL, IniFilename);
				break;
			}
		}
	}

	delete pStrW;
}

void CAddDesCommonDlg::OnBnClickedGet2()
{
	// TODO: Add your control notification handler code here
	const long sizeBuffer = 255;
	long length;
	LPWSTR pStrW = new WCHAR [sizeBuffer];
	LPSTR pValueA = new CHAR [sizeBuffer * 2];
	LPSTR pListA = NULL;

	pValueA[0] = 0;

	while (1) {
		if(GetCheckedRadioButton(IDC_RADIO_SELECT,IDC_RADIO_LIST) == IDC_RADIO_LIST)
		{
			// получаю список
			length = EditList.GetWindowTextLengthW() + 1;
			if (length > sizeBuffer) {
				delete pStrW;
				pStrW = new WCHAR [length];
			}
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// конвертирую список в ANSI
			if (!WideCharToMultiByte(CP_ACP, 0, pStrW, length, pListA, length*2, NULL, NULL))
				break;
		}
		processGetAttribute(attrValue, pValueA, pListA);
		break;
	}

	if (pValueA[0]) {
		// строку конвертирую из ANSI
		MultiByteToWideChar(CP_ACP, 0, pValueA, -1, pStrW, sizeBuffer);
		// устанавливаю значение атрибута
		myCombo2.SetWindowTextW(pStrW);
	}

	delete pStrW;
	delete pValueA;
	delete pListA;
}

void CAddDesCommonDlg::OnBnClickedOk2()
{
	// TODO: Add your control notification handler code here
	long length = myCombo2.GetWindowTextLengthW()+1;
	LPWSTR pStrW = new WCHAR [length];
	LPSTR pValueA = new CHAR [length * 2];
	LPSTR pListA = NULL;
	// получаю значение атрибута
	myCombo2.GetWindowTextW(pStrW,length);
	// строку конвертирую в ANSI
	while (0 != WideCharToMultiByte(CP_ACP, 0, pStrW, length, pValueA,
                  length*2, NULL, NULL))
	{
		if(GetCheckedRadioButton(IDC_RADIO_SELECT,IDC_RADIO_LIST) == IDC_RADIO_LIST)
		{
			// получаю список
			length = EditList.GetWindowTextLengthW()+1;
			delete pStrW;
			pStrW = new WCHAR [length];
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// конвертирую список в ANSI
			if (0 == WideCharToMultiByte(CP_ACP, 0, pStrW, length, pListA, length*2, NULL, NULL))
				break;
		}

		processAddAttributes(attrValue,pValueA,pListA);
		break;
	}
	delete pStrW;
	delete pValueA;
	delete pListA;
}


void CAddDesCommonDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
