
// AddDesCommonDlg.cpp : ���� ����������
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

// ���������� ���� CAddDesCommonDlg
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


// ����������� ��������� CAddDesCommonDlg

BOOL CAddDesCommonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
	CString name;
	name = sName;
	name += _T(" v.");
	name += sVersion;
	CDialogEx::SetWindowTextW(name);

	CheckDlgButton(IDC_RADIO_SELECT, BST_CHECKED);
	EditList.ShowWindow(0);
	// ������� ������ �� ini-�����
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

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CAddDesCommonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CAddDesCommonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//========================================================================================

// �������� ����
static bool openDesign(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "sch",&tContext) == DBX_OK)
		return true;
	MessageBox(NULL,_T("������ �������� ���� !"),_T("������"),MB_OK);
	return false;
}

// �������� ����
static bool closeDesign(void)
{
	TCloseDesign(&tContext,"");
	return true;
}

// ������� ��������� c RefDes
// ������ �������� �� ��������
// src != NULL - ������ ���������
// src == NULL - ����������� ���������
// ���������� true, ���� ���� ���������
static bool getRefDesFromString(char *dest, char *src)
{
	char *pPrvDig, *pPrvDiv, *pCurTxt, *pCurDig;
	long sizePrvTxt,sizeCurTxt;
	static char *substr = NULL;	// ��������� ���������
	static long prvCnt, curCnt; // �������� ������ ��������
	if(dest == NULL)
		return false;
	*dest = 0;
	if(src != NULL)
	{
		substr = src;
		prvCnt = 0;
		curCnt = 0;
	}
	// ��������� �� ����������
	if(substr == NULL)
		return false;
	// ������� ������ ����������� ��������
	substr = myStrpbrkLatin(substr);
	if(substr == NULL)
		return false;
	// ������� ������ ������ ��������
	pPrvDig = myStrpbrkDigit(substr);
	if(pPrvDig == NULL)
		return false;
	// ������� ����� ��������� �����
	sizePrvTxt = pPrvDig - substr;
	if(++prvCnt < curCnt)
	{	// ������ ������� �� ������������ ���� "C1...C3"
		// ������� ��������� �����
		strncpy_s(dest,DBX_MAX_ATTRIBUTE_LEN,substr,sizePrvTxt);
		// �������� �������� �����
		sprintf_s(dest+sizePrvTxt,DBX_MAX_ATTRIBUTE_LEN-sizePrvTxt,"%d",prvCnt);
		return true;
	}
	// ������� �����������
	pPrvDiv = strpbrk(pPrvDig,".-, ");
	// ������� ����������� ��������
	strncpy_s(dest,DBX_MAX_ATTRIBUTE_LEN,substr,(pPrvDiv == NULL)?(DBX_MAX_ATTRIBUTE_LEN):(pPrvDiv - substr));
	// ������� ������ ��������� ����� ���������� ��������
	pCurTxt = myStrpbrkLatin(pPrvDig);
	// � ����� ��� ��������� ������� ?
	if((pPrvDiv == NULL) || (pCurTxt == NULL))
	{
		substr = NULL;
		return true;
	}
	// ������� ������ �������� ����� ���������� ��������
	pCurDig = myStrpbrkDigit(pCurTxt);
	// � ����� ��� ��������� ������� ?
	if(pCurDig == NULL)
	{
		substr = NULL;
		return true;
	}
	// ������� ����� ���������� ��������
	sscanf_s(pCurDig,"%d",&curCnt);
	prvCnt = curCnt;
	// ������� ����� �������� ����� ���������� ��������
	sizeCurTxt = pCurDig - pCurTxt;
	// �������� ����������� ������ ������������ ���� "C1...C3" ��� "C1-C3" 
	if((*pPrvDiv == '.') || (*pPrvDiv == '-'))
	{
		if(sizePrvTxt == sizeCurTxt)
		{
			if(strncmp(substr, pCurTxt, sizeCurTxt ) == 0)
			{	// ���� ������������ - ������� ����� ����������� ��������
				sscanf_s(pPrvDig,"%d",&prvCnt);
				if(prvCnt > curCnt) 
					prvCnt = curCnt;
			}
		}
	}
	// �������� ��������� ������� ���������
	substr = pCurTxt;
	return true;
}

// �������� ������� � ����������
bool addAttribute(char * pRefDes, const char * typeAttr, char * valueAttr)
{
	TAttribute myAttr; // �������
	bool isAttr = false;
	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		if(strcmp(myAttr.type,typeAttr) == 0)
		{	// ���� ��������� �������
			isAttr = true;
			break;
		}
		//������� ��������� �������
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

// ��������� ������� ����������
bool getAttribute(char * pRefDes, const char * typeAttr, char * valueAttr)
{
	TAttribute myAttr; // �������

	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		if(strcmp(myAttr.type,typeAttr) == 0)
		{	// ���� ��������� �������
			strcpy_s(valueAttr, DBX_MAX_NAME_LEN, myAttr.value);
			break;
		}
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	return true;
}

// �������� �������� ����������
bool deleteAttribute(char * pRefDes, const char * typeAttr)
{
	TAttribute myAttr; // �������
	bool isAttr = false;
	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		if(strcmp(myAttr.type,typeAttr) == 0)
		{	// ���� ��������� �������
			TDeleteCompAttribute(&tContext,pRefDes,&myAttr);
			break;
		}
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	return true;
}

// ���������� ��������� � ���������� ���������
bool addAttributesSelect(const char * typeAttr, char * valueAttr)
{
	TItem myItem;
	//������� ������ ���������
	tStatus = TGetFirstSelectedItem(&tContext,&myItem);
	while(tStatus == DBX_OK)
	{
		if(myItem.itemType == DBX_SYMBOL)
		{	// ��������� �������
			// ������� RefDes ����������� ����������
			char myRefDes[DBX_MAX_NAME_LEN], *pStr;
			strcpy_s(myRefDes,DBX_MAX_NAME_LEN,myItem.symbol.refDes);
			pStr = strchr(myRefDes,':');
			if(pStr != NULL) *pStr = 0;
			// �������� ������� ���������
			addAttribute(myRefDes,typeAttr,valueAttr);
		}
		//������� ��������� ���������
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	return true;
}

// ������ �������� �� ������� ����������� ����������
static bool
getAttributeSelect(const char * typeAttr, char * valueAttr)
{
	TItem myItem;
	//������� ������ ���������
	tStatus = TGetFirstSelectedItem(&tContext,&myItem);
	while(tStatus == DBX_OK)
	{
		if(myItem.itemType == DBX_SYMBOL)
		{	// ��������� �������
			// ������� RefDes ����������� ����������
			char myRefDes[DBX_MAX_NAME_LEN], *pStr;
			strcpy_s(myRefDes,DBX_MAX_NAME_LEN,myItem.symbol.refDes);
			pStr = strchr(myRefDes,':');
			if(pStr != NULL) *pStr = 0;
			// �������� ������� ���������
			getAttribute(myRefDes, typeAttr, valueAttr);
			break;
		}
		//������� ��������� ���������
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	return true;
}

// ���������� ��������� � ���������� �� ������
bool addAttributesList(const char * typeAttr, char * valueAttr, char * listRefDesComp)
{
	char myRefDes[DBX_MAX_ATTRIBUTE_LEN];
	// ������� ������ RefDes
	bool flag = getRefDesFromString(myRefDes,listRefDesComp);
	while(flag)
	{
		// �������� ������� ���������
		addAttribute(myRefDes,typeAttr,valueAttr);
		// ������� ����������� RefDes
		flag = getRefDesFromString(myRefDes,NULL);
	}
	return true;
}

// ��������� �������� �� ������� ���������� ������
bool getAttributeList(const char * typeAttr, char * valueAttr, char * listRefDesComp)
{
	char myRefDes[DBX_MAX_ATTRIBUTE_LEN];
	// ������� ������ RefDes
	bool flag = getRefDesFromString(myRefDes,listRefDesComp);
	if(flag)
	{
		// ��������� �������� ���������
		getAttribute(myRefDes, typeAttr, valueAttr);
	}
	return true;
}

// �������� ��������� �� ���������� �����������
bool deleteAttributesSelect(const char * typeAttr)
{
	TItem myItem;
	//������� ������ ���������
	tStatus = TGetFirstSelectedItem(&tContext,&myItem);
	while(tStatus == DBX_OK)
	{
		if(myItem.itemType == DBX_SYMBOL)
		{	// ��������� �������
			// ������� RefDes ����������� ����������
			char myRefDes[DBX_MAX_NAME_LEN], *pStr;
			strcpy_s(myRefDes,DBX_MAX_NAME_LEN,myItem.symbol.refDes);
			pStr = strchr(myRefDes,':');
			if(pStr != NULL) *pStr = 0;
			// �������� ������� ���������
			deleteAttribute(myRefDes,typeAttr);
		}
		//������� ��������� ���������
		tStatus = TGetNextSelectedItem(&tContext,&myItem);
	}
	return true;
}

// �������� ��������� ����������� �� ������
bool deleteAttributesList(const char * typeAttr, char * listRefDesComp)
{
	char myRefDes[DBX_MAX_ATTRIBUTE_LEN];
	// ������� ������ RefDes
	bool flag = getRefDesFromString(myRefDes,listRefDesComp);
	while(flag)
	{
		// �������� ������� ���������
		deleteAttribute(myRefDes,typeAttr);
		// ������� ����������� RefDes
		flag = getRefDesFromString(myRefDes,NULL);
	}
	return true;
}

// ���������� ��������� � ���������� ���������
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

// ��������� �������� �� ����������
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

// ���������� ��������� � ���������� ���������
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
	// ������� �������� ��������
	myCombo1.GetWindowTextW(pStrW,length);
	// ������ ����������� � ANSI
	while (0 != WideCharToMultiByte(CP_ACP, 0, pStrW, length, pValueA,
                  length*2, NULL, NULL))
	{
		if(GetCheckedRadioButton(IDC_RADIO_SELECT,IDC_RADIO_LIST) == IDC_RADIO_LIST)
		{
			// ������� ������
			length = EditList.GetWindowTextLengthW()+1;
			delete pStrW;
			pStrW = new WCHAR [length];
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// ����������� ������ � ANSI
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
			// ������� ������
			length = EditList.GetWindowTextLengthW() + 1;
			if (length > sizeBuffer) {
				delete pStrW;
				pStrW = new WCHAR [length];
			}
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// ����������� ������ � ANSI
			if (!WideCharToMultiByte(CP_ACP, 0, pStrW, length, pListA, length*2, NULL, NULL))
				break;
		}
		processGetAttribute(attrDesCommonType, pValueA, pListA);
		break;
	}

	if (pValueA[0]) {
		// ������ ����������� �� ANSI
		MultiByteToWideChar(CP_ACP, 0, pValueA, -1, pStrW, sizeBuffer);
		// ������������ �������� ��������
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

	// ������� �������� ��������
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
			// ������� ������
			length = EditList.GetWindowTextLengthW() + 1;
			if (length > sizeBuffer) {
				delete pStrW;
				pStrW = new WCHAR [length];
			}
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// ����������� ������ � ANSI
			if (!WideCharToMultiByte(CP_ACP, 0, pStrW, length, pListA, length*2, NULL, NULL))
				break;
		}
		processGetAttribute(attrValue, pValueA, pListA);
		break;
	}

	if (pValueA[0]) {
		// ������ ����������� �� ANSI
		MultiByteToWideChar(CP_ACP, 0, pValueA, -1, pStrW, sizeBuffer);
		// ������������ �������� ��������
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
	// ������� �������� ��������
	myCombo2.GetWindowTextW(pStrW,length);
	// ������ ����������� � ANSI
	while (0 != WideCharToMultiByte(CP_ACP, 0, pStrW, length, pValueA,
                  length*2, NULL, NULL))
	{
		if(GetCheckedRadioButton(IDC_RADIO_SELECT,IDC_RADIO_LIST) == IDC_RADIO_LIST)
		{
			// ������� ������
			length = EditList.GetWindowTextLengthW()+1;
			delete pStrW;
			pStrW = new WCHAR [length];
			pListA = new CHAR [length * 2];
			EditList.GetWindowTextW(pStrW,length);
			// ����������� ������ � ANSI
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
