
// ComponentListDlg.cpp : ���� ����������
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


// ���������� ���� CComponentListDlg
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


// ����������� ��������� CComponentListDlg

BOOL CComponentListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
	CheckDlgButton(IDC_RADIO_TYPE_PE, BST_CHECKED);
	CheckDlgButton(IDC_RADIO_FILE_TXTSEP, BST_CHECKED);

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CComponentListDlg::OnPaint()
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
HCURSOR CComponentListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//========================================================================================
// ���� ������
enum TYPE_OUT_LIST
{
	OUT_LIST_PE = 0,	// ��������
	OUT_LIST,			// ������ ������
	OUT_LIST_SP,		// ������������
	OUT_LIST_VP,		// ��������� �������� 
	OUT_LIST_MAX
};

static const char sOutFileNameEnd[OUT_LIST_MAX][10] = {
	"_��3",
	"_������",
	"_��",
	"_��",
};

// ���� �������� �����
enum TYPE_OUT_FILE
{
	OUT_FILE_TXTDLM = 0,	// ��������� � ������������
	OUT_FILE_TXT,			// ���������
	OUT_FILE_HTML,			// html-����
	OUT_FILE_RTF,			// html-����
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

// ������������
#define C_NUMBER_ACCEPTS 6
static COMPONENT_ACCEPT_TEXT _c_accepts[C_NUMBER_ACCEPTS] =  {
	" ��mM��pP��nNuU", " �",
	"��pP",	" �",	// ��
	"��nN",	" �",	// ��
	",��kKuU", " ��",	// ���
	"��mM",	" �",	// ��
	"��fF",	" ",	// �
};

COMPONENT_ACCEPT Caccept = {
	_c_accepts,
	C_NUMBER_ACCEPTS,
	'�',
};

// �������������	
#define L_NUMBER_ACCEPTS 3
static COMPONENT_ACCEPT_TEXT _l_accepts[L_NUMBER_ACCEPTS] =  {
	" ��kK��mMuU", " ", //��
	"��kKuU",	" ��",	// ����
	"��mM",	" �",	// ���
};

COMPONENT_ACCEPT Laccept = {
	_l_accepts,
	L_NUMBER_ACCEPTS,
	'�',
};

// ���������
#define R_NUMBER_ACCEPTS 5
static COMPONENT_ACCEPT_TEXT _r_accepts[R_NUMBER_ACCEPTS] =  {
	" �m�M��kK��gG", " ", //��
	"�m",	" �",	//���
	"��kK", " �",	//���
	"�M",	" �",	//���
	"��gG", " �",	// ���
};

COMPONENT_ACCEPT Raccept = {
	_r_accepts,
	R_NUMBER_ACCEPTS,
	'�',
};

typedef struct COMPONENT_ACCEPT_NAME
{
	const char refdes[3];
	const char name[DBX_MAX_NAME_LEN];
	const char nameSingle[DBX_MAX_NAME_LEN];
	long group;
} COMPONENT_ACCEPT_NAME;

// ���������� ��������� ����� RefDes c ��������� �������������
// ����� ����������� �� �������� c 1 !
static COMPONENT_ACCEPT_NAME CompNameAccept[] = {
	"--", "\0\0", "\0\0", 0,
	"A" , "\0\0", "\0\0", 1,
	"RU", "���������", "�������� ", 2,
	"VD", "�����", "���� ", 3, 
	"HL", "����������", "��������� ", 4,
	"HG", "����������", "��������� ", 4,
	"L" , "�������������", "������������� ", 5,
	"SB", "������", "������ ", 6,
	"C" , "������������", "����������� ", 7,
	"D" , "����������", "���������� ", 8,
	"DA", "����������", "���������� ", 8,
	"DD", "����������", "���������� ", 8,
	"SA", "�������������", "������������� ", 9,
	"F" , "��������������", "�������������� ", 10,
	"FU", "��������������", "�������������� ", 10,
	"R" , "���������", "�������� ", 11,
	"K" , "����", "���� ", 12,
	"T" , "��������������", "������������� ", 13,
	"TV", "��������������", "������������� ", 13,
	"X" , "�����������", "����������� ", 14,
	"XP", "�����������", "����������� ", 14,
	"XS", "�����������", "����������� ", 14,
	"XT", "�����������", "����������� ", 14,
	"VT", "�����������", "���������� ", 15,
};
#define COMP_NAME_NUMBER_ACCEPTS (sizeof(CompNameAccept)/sizeof(COMPONENT_ACCEPT_NAME))

// ������������ ����� ��������� ������ �������� VALUE
#define VALUE_MAX_STRING_LEN		(DBX_MAX_ATTRIBUTE_LEN*2)
// ������������ ����� ��������� ������ �������� VALUE
#define REFDES_MAX_STRING_LEN		(DBX_MAX_ATTRIBUTE_LEN*16)

// ������� ���������
typedef struct COMPONENT_LIST_STRUCT {
	union {
		unsigned _int64 id;							// ������
		struct {
			unsigned _int64 num_refdes	:16;		// �������� ����� �����������
			unsigned _int64 lyt2_refdes	:8;			// 2-�� ������ ����������� (��� ����������) � 1-�� - ��� ������
			unsigned _int64 lyt1_refdes	:8;			// 1-�� ������ ����������� (��� ����������) � '@' - ��� ������
			unsigned _int64 channel		:8;			// ����� ������ � ������
			unsigned _int64 group		:8;			// ����� ������ �������
		} ids;
		char idstr[8];
	};
	long quantity;							// ����������
	long channel;							// ����� �����a � ������ 
	long group;								// ����� ������ �������
	long indexGroupName;					// ������ ���������� ����� ����������
	char notList[DBX_MAX_ATTRIBUTE_LEN];	// � ����� ������ �� ���������
	char refdes[REFDES_MAX_STRING_LEN];		// ��������� ����� �����������
	char value[VALUE_MAX_STRING_LEN];		// ������������
} COMPONENT_LIST_STRUCT;
//========================================================================================

// ���������� true, ���� ��������� - �����
static bool isChannel(TComponent * pComponent)
{
	TAttribute myAttr;		// ������� ������� ����������
	// ������� ������ �������
	tStatus = TGetFirstCompAttribute(&tContext, pComponent->refDes, &myAttr);
	while (tStatus == DBX_OK)
	{
		// ������� DesChannel
		if( strcmp(attrDesChannel, myAttr.type) == 0) 
			return true;
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext, &myAttr);
	}
	return false;
}

// ������� ��������� ��� ����������� (������ ������)
static const char * getComponentGroupName(long indexGroupName,bool flagSingle)
{
	long i;
	for(i = 0; i < COMP_NAME_NUMBER_ACCEPTS; i++)
		if( (long)CompNameAccept[i].group == indexGroupName ) break;
	if( i >= COMP_NAME_NUMBER_ACCEPTS) i = 0; 
	return (flagSingle)?(CompNameAccept[i].nameSingle):(CompNameAccept[i].name);
}

// ������� ������ ���������� ����� ���������
static long getComponentGroupNameIndex(char ch1, char ch2)
{
	char str[3];
	long i;
	// ������� RefDes � �����
	str[0] = ch1;
	str[1] = ch2;
	str[2] = 0;
	// ��� ��������� ����������� ���������� � �������
	for(i = 0; i < COMP_NAME_NUMBER_ACCEPTS; i++)
		if(strcmp(str,CompNameAccept[i].refdes) == 0) break;
	//  ����� � ����������� � ��������� ������ ����������
	if( i >= COMP_NAME_NUMBER_ACCEPTS ) i = 0;
	return CompNameAccept[i].group;
}

// ������� ����� ����������� � ����
static long getNumberComponents(void)
{
	TComponent myComponent;
	long num_components = 0;
	//������� ������ ���������
	tStatus = TGetFirstComponent(&tContext, &myComponent);
	while (tStatus == DBX_OK)
	{
		switch(myComponent.connectionType)
		{
		case DBX_COMPONENT_CONNECTION_NORMAL:	// ���������� ���������
			if( strpbrk(myComponent.refDes,acceptLastChannelComponets)==NULL )
				num_components++;
			break;
		case DBX_COMPONENT_CONNECTION_MODULE: // ������
			num_components++;
			break;
		case DBX_COMPONENT_CONNECTION_POWER: // �������
			if( isChannel(&myComponent) )
				num_components++;
		default:
			break;
		}
		tStatus = TGetNextComponent(&tContext, &myComponent);
	}
	//��������� ����� �����������
	return num_components;
}

// ����������� ������
static void correctString(char *pString, long max_length)
{
	char str[VALUE_MAX_STRING_LEN];
	long len = strlen(pString);
	if((len > 1) && (pString != NULL))
	{
		// ����������� ������� ������� ���������
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
		//������ ��������� �������
		while(true)
		{
			char *pstr = strstr(pString, "  ");
			if(pstr == NULL) break;
			strcpy_s(str,max_length,pstr+1);
			*pstr = 0;
			strcat_s(pString,max_length,str);
		}
		//������ ������ � ����� ������
		len = strlen(pString);
		if((len > 1) && (pString[len-1] == ' ')) 
			pString[len-1] = 0;
	}
}

// ������������ � pComponent->value ��������� �����
static void getComponentValueUnits(TComponent * pComponent, char * pDesCommon,
	COMPONENT_ACCEPT * pCompAccept, char *value_str)
{
	// ������ �������� � RefDes ������ ���� �����, 
	// � DesCommon ������ ���� ��������� ������� ��������� - ��
	// DesCommon ����� �� ����
	if( ((unsigned char)pComponent->refDes[1] <= (unsigned char)'9') &&
		(*pDesCommon == pCompAccept->ch) )
	{
		long i = 0;
		// ��� ������ ��������� ����� Value 
		char * pStr = strpbrk(value_str, pCompAccept->pComponentAcceptText[0].accept);
		if(pStr != NULL)
		{	// ��� ���������
			for(i=1; i < pCompAccept->number; i++)
				if(strpbrk(value_str, pCompAccept->pComponentAcceptText[i].accept) != NULL)
					break;
			if(i >= pCompAccept->number) 
				// �������� ��������� ����� �� ���������
				i = 0; 
			// ������� Value �� ����� �������� �����
			*pStr = 0;	
		}
		else
			// �������� ��������� ����� �� ���������
			i = 0; 
		// ��������� �����
		strcat_s(value_str, DBX_MAX_ATTRIBUTE_LEN, pCompAccept->pComponentAcceptText[i].text);
	}
}

//------------------------------------------------------------------------------
/**
 *  \brief ��������� �������z Value ���������� �� ��������� RefDes � Value
 *	\param pCompCur - ��������� �� ������� ��������� � ������� �����������
 *	\param pComponent - ��������� �� ���������
 *	\param pDesCommon - ��������� �� �������� �������� DesCommon
 *	\param isInsertPattern - TRUE, ���� ��������� ��������� Value ��������� Pattern
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
	// ������� � ��� � DesCommon ��������� ���
	pStr1= getComponentGroupName(pCompCur->indexGroupName,true);
	pStr = strstr(pDesCommon,pStr1);
	if(pStr != NULL) {
		// ������ �� DesCommon ��������� ���
		pDesCommon = pStr + strlen(pStr1);
	}

	// �������� DesCommon
	if(strlen(pDesCommon) > 0)
	{	// ���� DesCommon
		// ��� ����� ������� Value � DesCommon ������� � ������ ������
		pStr = strchr(pDesCommon, '@');

		if(pStr != NULL)
		{	// ���� ����� ��� ������� Value
			*pStr = 0;
			pStr++;
			fValueParsing = 1;
		}
		else {
			fValueParsing = 0;
		}
		//������ ������ ����� DesCommon � pValue
		strcpy_s(pCompCur->value, VALUE_MAX_STRING_LEN, pDesCommon);
		if (fValueParsing) {
			// ���� ����� ��� ������� Value
			pDesCommon = pStr;
		}
	}

	if (fValueParsing) {
		// �������� Value
		if(strlen(pComponent->value) > 0)
		{	// ���� Value
			// ������� Value � �����, ������ ��� ���� �� ������ ������ ������ '~'
			strcpy_s(value_str, VALUE_MAX_STRING_LEN,
				(pComponent->value + ((pComponent->value[0]=='~')?(1):(0))));
			// ������� ����� �� ������� � Value
			pStr = strchr(value_str, '.');
			if(pStr != NULL) *pStr = ',';
			// ����������� Value �� ��������� ����� RefDes
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
			// �������� Value
			strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, value_str);
		}
		// �������� ��������� pDesCommon
		strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, pDesCommon);
	}

	// �������� ��� �������
	if( isInsertPattern )
	{
		if ( (pComponent->patternName != NULL) 
			&& ( strlen(pComponent->patternName) > 0 ) ) {
				strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, " (������ ");
				strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, pComponent->patternName);
				strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, ")");
			}
		else {
			strcat_s(pCompCur->value, VALUE_MAX_STRING_LEN, " (������ �� ���������)"); 
		}
	}
}

// ������� ������ (�����)
static bool getChannel(COMPONENT_LIST_STRUCT *listChan,TComponent * pComponent)
{
	TAttribute myAttr;		// ������� ������� ����������
	char *tmp;
	char attrDesChannelValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesTUValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesFirmValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	listChan->id = 1;				// �������� ����� ����������� + ��� ������ ������� �����������
	listChan->quantity = 1;			// ����������
	listChan->channel = 1;			// ����� ������ � ������
	listChan->group = 1;			// ����� ������ �������
	listChan->indexGroupName = 0;	// ������ ���������� �����
	listChan->notList[0] = 0;		// ���� ������� �� �������
	listChan->refdes[0] = 0;		// ��������� �����  �����������
	listChan->value[0] = 0;			// ������������
	// ������� ������ �������
	tStatus = TGetFirstCompAttribute(&tContext, pComponent->refDes, &myAttr);
	while (tStatus == DBX_OK)
	{
		// ������� � DesCommon ��� DesChannel
		if( (strcmp(attrDesCommonType, myAttr.type) == 0) ||
			(strcmp(attrDesChannel, myAttr.type) == 0) )
			strcpy_s(attrDesChannelValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// ������� � DesTU (��)
		else if(strcmp(attrDesTUType, myAttr.type) == 0)
			strcpy_s(attrDesTUValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// ������� � DesFirm (��������������)
		else if(strcmp(attrDesFirmType, myAttr.type) == 0)
			strcpy_s(attrDesFirmValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// ������� � ������� ����� �������
		else if(strcmp(attrNoChannelGroupType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listChan->group);
		// ������� � ��������� �� �������� � ������
		else if(strcmp(attrNotList, myAttr.type) == 0)
		{
			if( strstr(myAttr.value, "ALL") != NULL)
				// ������� � ������ �� ���������
				return false;
			strcpy_s(listChan->notList, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		}
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext, &myAttr);
	}
	// �������� ��� ��������
	//-------------------------------------------------------------------
	// ��� ����� ��������
	tmp = strpbrk(pComponent->refDes, acceptNumber);
	if(tmp != NULL)
	{	// ������ � id ����� ��������
		long i=0;
		sscanf_s(tmp, "%d", &i);
		listChan->ids.num_refdes = i;
	}
	// ������ � id ������� ������
	listChan->ids.lyt1_refdes = '@';
	// ������ � id ������ ������
	if((unsigned char)pComponent->refDes[1] >= (unsigned char)'A')
		listChan->ids.lyt2_refdes = pComponent->refDes[0];
	// ������ � id ����� ������
	listChan->ids.group = listChan->group;
	listChan->ids.channel = listChan->channel;
	// �������� �������������� listChan->refdes
	strcpy_s(listChan->refdes, DBX_MAX_ATTRIBUTE_LEN, pComponent->refDes);
	//-------------------------------------------------------------------
	// �������� �������������� listChan->value
	if(strlen(attrDesChannelValue) != 0)
	{
		// ��� ����� ������� Value ������� � ������ ������
		char *pStr = strchr(attrDesChannelValue, '@');
		if(pStr != NULL)
		{	// ���� ����� ��� ������� Value
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
	// ��������� �������������
	if(strlen(attrDesFirmValue) > 0)
	{
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, attrDesFirmValue);
	}
	// ��������� ��
	if(strlen(attrDesTUValue) > 0)
	{
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listChan->value, VALUE_MAX_STRING_LEN, attrDesTUValue);
	}
	//------------------------------------------------------------------
	// ����������� Value
	correctString(listChan->value, VALUE_MAX_STRING_LEN);
	//------------------------------------------------------------------
	return true;
}

//------------------------------------------------------------------------------
/*! \brief ��������� ����������
 *	\param listComp - ��������� �� ������� �����������
 *	\param pComponent - ��������� �� ���������
 *	\param isInsertPattern - TRUE, ���� ��������� ��������� Value ��������� Pattern
 */
//------------------------------------------------------------------------------
static bool getComponent(COMPONENT_LIST_STRUCT *listComp, TComponent * pComponent, bool isInsertPattern)
{
	TAttribute myAttr;		// ������� ������� ����������
	char *tmp;
	char attrDesTUValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesFirmValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	char attrDesCommonValue[DBX_MAX_ATTRIBUTE_LEN] = {0};
	listComp->id = 1;				// �������� ����� ����������� + ��� ������ ������� �����������
	listComp->quantity = 1;			// ����������
	listComp->channel = 0;			// ����� ������
	listComp->group = 0;			// ����� ������ �������
	listComp->indexGroupName = 0;	// ������ ���������� �����
	listComp->notList[0] = 0;		// ���� ������� �� �������
	listComp->refdes[0] = 0;		// ��������� �����  �����������
	listComp->value[0] = 0;			// ������������
	// ������� ������ �������
	tStatus = TGetFirstCompAttribute(&tContext, pComponent->refDes, &myAttr);
	while (tStatus == DBX_OK)
	{
		// ��� ����� !
		if(strcmp(attrDesChannel, myAttr.type) == 0)
			return getChannel(listComp, pComponent);
		// ������� � DesCommon
		else if(strcmp(attrDesCommonType, myAttr.type) == 0)
			strcpy_s(attrDesCommonValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// ������� � DesTU (��)
		else if(strcmp(attrDesTUType, myAttr.type) == 0)
			strcpy_s(attrDesTUValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// ������� � DesFirm (��������������)
		else if(strcmp(attrDesFirmType, myAttr.type) == 0)
			strcpy_s(attrDesFirmValue, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		// ������� � ��������� �� �������� � ������
		else if(strcmp(attrNotList, myAttr.type) == 0)
		// � ����� ������ ������� �� ���������
		{
			if( strstr(myAttr.value, "ALL") != NULL)
				// ������� � ������ �� ���������
				return false;
			strcpy_s(listComp->notList, DBX_MAX_ATTRIBUTE_LEN, myAttr.value);
		}
		// ������� � ������� ������
		else if(strcmp(attrNoChannelType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listComp->channel);
		// ������� � ������� ������ � ������
		else if(strcmp(attrNoChannelInGroupType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listComp->channel);
		// ������� � ������� ����� �������
		else if(strcmp(attrNoChannelGroupType, myAttr.type) == 0)
			sscanf_s(myAttr.value, "%d", &listComp->group);
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext, &myAttr);
	}
	// �������� ��� ��������
	//-------------------------------------------------------------------
	// ��� ����� � RefDes
	tmp = strpbrk(pComponent->refDes, acceptNumber);
	if(tmp != NULL)
	{	// ������ � id ����� ��������
		long i=0;
		sscanf_s(tmp, "%d", &i);
		listComp->ids.num_refdes = i;
	}
	// ������ � id ������ ������
	listComp->ids.lyt1_refdes = 
		((unsigned char)pComponent->refDes[0] >= (unsigned char)'A')?(pComponent->refDes[0]):(0);
	// ������ � id ������ ������
	listComp->ids.lyt2_refdes = 
		((unsigned char)pComponent->refDes[1] >= (unsigned char)'A')?(pComponent->refDes[1]):(0);
	// ������� ������ ���������� ����� ����������
	if(pComponent->refDes[0] >= 'A')
		listComp->indexGroupName = getComponentGroupNameIndex(listComp->ids.lyt1_refdes,listComp->ids.lyt2_refdes);
	// ����������� ��� ������ ����
	if( (listComp->channel > 0) && (listComp->group == 0) )
		listComp->group = 1;
	// ������ � id ����� ������
	listComp->ids.group = listComp->group;
	listComp->ids.channel = listComp->channel;
	// �������� �������������� listComp->refdes
	strcpy_s(listComp->refdes, REFDES_MAX_STRING_LEN, pComponent->refDes);
	// �������� listComp->value;
	getComponentListValue(listComp, pComponent, attrDesCommonValue, isInsertPattern);
	// ��������� �������������
	if(strlen(attrDesFirmValue) > 0)
	{
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, attrDesFirmValue);
	}
	// ��������� ��
	if(strlen(attrDesTUValue) > 0)
	{
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, " ");
		strcat_s(listComp->value, VALUE_MAX_STRING_LEN, attrDesTUValue);
	}
	// ����������� Value
	correctString(listComp->value, VALUE_MAX_STRING_LEN);
	return true;
}

//------------------------------------------------------------------------------
/*! \brief ��������� ������� �����������
 *	\param listComp - ��������� �� ������� �����������
 *	\param isInsertPattern - TRUE, ���� ��������� ��������� Value ��������� Pattern
 */
//------------------------------------------------------------------------------
static long getComponentsList(COMPONENT_LIST_STRUCT *listComp, bool isInsertPattern)
{
	TComponent myComponent;	// ��������
	long num_components = 0;
	//������� ������ ���������
	tStatus = TGetFirstComponent(&tContext, &myComponent);
	while(tStatus == DBX_OK)
	{
		switch(myComponent.connectionType)
		{
		case DBX_COMPONENT_CONNECTION_NORMAL:
			if( strpbrk(myComponent.refDes,acceptLastChannelComponets)==NULL)
			{	// ��������� ���������
				if(getComponent(listComp, &myComponent, isInsertPattern))
				{	// ������� � ��������� ������
					listComp++;
					num_components++;
				}
			}
			break;
		case DBX_COMPONENT_CONNECTION_MODULE:
			//�����
			if( getChannel(listComp, &myComponent) )
			{	// ������� � ��������� ������
				listComp++;
				num_components++;
			}
			break;
		case DBX_COMPONENT_CONNECTION_POWER:
			// ���� �������
			if( isChannel(&myComponent) )
			{	// ��� �����!
				if( getChannel(listComp, &myComponent) )
				{	// ������� � ��������� ������
					listComp++;
					num_components++;
				}
			}
			break;
		default:
			break;
		}
		//������� ��������� ���������
		tStatus = TGetNextComponent(&tContext, &myComponent);
	}
	return num_components;
}

/**
 * @brief ������� ����������� ���� ����������� �� Id
 * @param listComp         ������ �����������.
 * @param indexComponents  ������� �������� ����������� � ������ �����������.
 * @param index1           ������ ���������� 1.
 * @param index1           ������ ���������� 1.
 * @return ������� ���������� ��������� ���������.
 * @retval 0 - ����������  ���������.
 * @retval 1 - ����������  1 ������ ���������� 2.
 * @retval 0 - ����������  1 ������� ���������� 2.
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
 * @brief ������� ����������� ���� ����������� �� Id � Value
 * @param listComp         ������ �����������.
 * @param indexComponents  ������� �������� ����������� � ������ �����������.
 * @param index1           ������ ���������� 1.
 * @param index1           ������ ���������� 1.
 * @return ������� ���������� ��������� ���������.
 * @retval 0 - ����������  ���������.
 * @retval 1 - ����������  1 ������ ���������� 2.
 * @retval 0 - ����������  1 ������� ���������� 2.
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
 * @brief ������� ���������� �����������
 * @param listComp         ������ �����������.
 * @param indexComponents  ������� �������� ����������� � ������ �����������.
 * @param num_components   ����� �����������.
 * @param pFunc            ��������� �� ������� ��������� ����������.
 */
static void
sortComponentList(COMPONENT_LIST_STRUCT *listComp,
	long *indexComponents, long num_components, 
	long(* pFunc)(COMPONENT_LIST_STRUCT *,long *, long, long))
{
	long i,j;
	// ������ ����������
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

// Id ���������� ����� �������������� ������
static void setIdComponentsByGroupName(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long num_components)
{
	for(long i=0; i < num_components; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComponents[i];
		// ��������� Id
		pListCur->id = 0;
		//  �������� ����� � ����������� � ��������� ������ ����������
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

// �������� id �� Value
static void makeIdFromValue(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long indexStart, long indexEnd, long index)
{
	// ������� ��������, � �������� ����������� Id
	index *= 8;
	for(long i= indexStart; i < indexEnd; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComponents[i];
		// ������� ������
		pListCur->id = 0;			
		// ����� ������
		long length = strlen(pListCur->value);
		if(index < length)
		{	// ����� index ���� �������
			// ������ ����� Value (�� index)
			char *str = pListCur->value + index;
			// ����� ����� Value
			length = strlen(str);
			// ������ ���������� �� ����� 8 ��������
			if(length > 8) length = 8;
			// ������� ����� Value
			for(long j = 0; j < length; j++)
				pListCur->idstr[7-j] = str[j];
		}
	}
}

// ���������� ���������� � ���������� Value � ��������� RefDes (��� �������)
// � ������������� (�� RefDes � ������ ������) ������
static long mergeComponentListPE(COMPONENT_LIST_STRUCT *listComp, long *indexComp, long numComp)
{
	long i=0, j=0, k=0, n=0;
	while((++k) < numComp)
	{
		if( strstr(listComp[indexComp[k]].notList, "PE") != NULL )
			// ��������� ����������� �� ������
			continue;
		//��������� Value
		if(	(strcmp(listComp[indexComp[j]].value, listComp[indexComp[k]].value) == 0) &&	// ������� Value
			(listComp[indexComp[j]].ids.group == listComp[indexComp[k]].ids.group) &&		// ������� ������ �����
			(listComp[indexComp[j]].ids.channel == listComp[indexComp[k]].ids.channel) &&	// ������� ������ �������
			(strcmp(listComp[indexComp[j]].notList,listComp[indexComp[k]].notList) == 0) &&	// ������� ������� �� ��������� � ������
			(strstr(listComp[indexComp[k]].notList, "SP") == NULL) )							// �������� �� ����� ����������� �� ��
		{	// Value � Channel ���������� - ���������� ����������
			listComp[indexComp[j]].quantity++;	// ���������� ������� ����������
			// ��������� RefDes
			if((listComp[indexComp[j]].ids.num_refdes+1) < listComp[indexComp[k]].ids.num_refdes)
			{	// RefDes ���������� ����� ��� �� 1 (��������: �1,�2,C3,�5,�6,�7 -> C1...C3,�5...�7)
				// �������� � RefDes ����������� ", " ��� "..."
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, (n<2)?textMerge1Component:textMergeManyComponents);
				if(n > 0)
				{
					n = 0;
					// ������ RefDes-�
					strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k-1]].refdes);
					// �������� � RefDes ����������� ", "
					strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, textMerge1Component);
				}
				// ������ RefDes-�
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k]].refdes);
			}
			else
				n++;
			// ������� ����� RefDes-�
			listComp[indexComp[j]].ids.num_refdes = listComp[indexComp[k]].ids.num_refdes;
		}
		else 
		{	// ������ ��������� ��� ������ ����������
			if(n > 0)
			{	// ���� ��������� �����������, ������� RefDes
				// �������� � RefDes ����������� ", " ��� "..."
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, (n==1)?textMerge1Component:textMergeManyComponents);
				// ������ RefDes-�
				strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k-1]].refdes);
				n = 0;
			}
			indexComp[i] = indexComp[j];
			j = k;
			i++;
		}
	}
	if(n > 0)
	{	// ���� ��������� �����������, ������� RefDes
		// �������� � RefDes ����������� ", " ��� "..."
		strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, (n==1)?textMerge1Component:textMergeManyComponents);
		// ������ RefDes-�
		strcat_s(listComp[indexComp[j]].refdes, REFDES_MAX_STRING_LEN, listComp[indexComp[k-1]].refdes);
	}
	//��������� ��������� ������� �� ������
	indexComp[i] = indexComp[j];
	i++;
	return i;
}

//------------------------------------------------------------------------------
/* \brief ����������� ���������� � ���������� Value (��� ������������)
 * � ������������� (�� RefDes � ������ ������) ������
 * ����������� ���������� ����� ', ', �� ����� ��� ����������� ����������
 * �������������� ��������� ����� mergeComponentListPE
 * \param listComp - ��������� �� ������� �����������
 * \param indexComp - ��������� �� ������� �������� �����������
 * \param numComp - ����� �����������
 */
//------------------------------------------------------------------------------
static long mergeComponentListSP(COMPONENT_LIST_STRUCT *listComp, long *indexComp, long numComp)
{
	char refdes[REFDES_MAX_STRING_LEN];
	long i, j, k;

	// ��� ������ ������� � �������� ������ � ���������� Value � ������
	k = 0;
	for(i = 0; i < numComp; i++)
	{	//������� ������� ���������
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		// 
		if(strstr(pListCur->notList, "SP")) 	
			//��������� ����������� �� ��
			pListCur->ids.lyt1_refdes = '.';
		// �������� �������� ������
		if(pListCur->ids.lyt1_refdes == '.') continue;
		// �������� ������ �������
		if(pListCur->ids.lyt1_refdes == '@') 
			k = pListCur->group;
		else if(k > 0)
		{
			for(j = i+1; j < numComp; j++)
			{
				COMPONENT_LIST_STRUCT * pListNext = listComp + indexComp[j];
				// �������� �������� ������
				if(pListNext->ids.lyt1_refdes == '.') continue;
				// �������� ��������� �����
				if(pListNext->ids.lyt1_refdes == '@') break;
				if( strcmp(pListCur->value, pListNext->value) == 0 )
				{	// Value ��������
					// ������ RefDes
					strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, ", ");
					strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, pListNext->refdes);
					// ������ �����������
					pListCur->quantity += pListNext->quantity;
					// ������� ������ ��� ��������
					pListNext->ids.lyt1_refdes = '.';
				}
			}
		}
	}
	// ��� ������ ������� � ����������� �������� RefDes �� ���� '5 �����: C1...C3'
	k = 0;
	refdes[0] = 0;
	for(i=0; i < numComp; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		if(pListCur->ids.lyt1_refdes == '@')
		{	// �������� �������� ������
			refdes[0] = 0;
			k = pListCur->quantity;
			switch(k)
			{
			case 0:
			case 1:
				strcpy_s(refdes, REFDES_MAX_STRING_LEN, "1 ������: ");
				break;
			case 2:
			case 3:
			case 4:
				sprintf_s(refdes, REFDES_MAX_STRING_LEN, "%d ������: ",k);
				break;
			default:
				sprintf_s(refdes, REFDES_MAX_STRING_LEN, "%d �����: ",k);
				break;
			}
			// ������� ������ ��� ��������
			pListCur->ids.lyt1_refdes = '.';
		}
		else if( refdes[0] != 0 )
		{	// ����� ������ � ������ ������ ��������� ������ �� ��������� ������
			char tmp[REFDES_MAX_STRING_LEN];
			strcpy_s(tmp, REFDES_MAX_STRING_LEN, refdes);
			strcat_s(tmp, REFDES_MAX_STRING_LEN, pListCur->refdes);
			strcpy_s(pListCur->refdes, REFDES_MAX_STRING_LEN, tmp);
			// ���������� ��������� � ������ ���������� �� ����� �������
			pListCur->quantity *= k;
		}
	}
	// ��������� ������ � ���������� Value � ������
	for(i = 0; i < numComp; i++)
	{	//������� ������� ���������
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		// ��������� �������� ������
		if(pListCur->ids.lyt1_refdes == '.') continue;
		for(j = i+1; j < numComp; j++)
		{
			COMPONENT_LIST_STRUCT * pListNext = listComp + indexComp[j];
			// ��������� �������� ������
			if(pListNext->ids.lyt1_refdes == '.') continue;
			if( strcmp(pListCur->value, pListNext->value) == 0 )
			{	// Value ��������
				// ������ RefDes
				strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, ", ");
				strcat_s(pListCur->refdes, REFDES_MAX_STRING_LEN, pListNext->refdes);
				// ������ �����������
				pListCur->quantity += pListNext->quantity;
				// ������� ������ ��� ��������
				pListNext->ids.lyt1_refdes = '.';
			}
		}
	}
	// ������ ������ � ������ �������� �� ������
	j = 0;
	for(i = 0; i < numComp; i++)
	{
		COMPONENT_LIST_STRUCT * pListCur = listComp + indexComp[i];
		if(pListCur->ids.lyt1_refdes != '.')
			indexComp[j++] = indexComp[i];
	}	
	// ��������� ����� �������
	return j;
}

// �������� ����
static bool openDesign(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "sch", &tContext) == DBX_OK)
		return true;
	MessageBox(NULL,_T("������ �������� ���� !"),_T("������"),MB_OK);
	return false;
}

// �������� ����
static bool closeDesign(void)
{
	TCloseDesign(&tContext, "");
	return true;
}
	
// ������� ��� �����
static bool getDesignFilename(long typeFile, long typeList, char *pFilename)
{
	TDesign tDesignInfo;
	//������� ���������� � ����
	tStatus = TGetDesignInfo(&tContext, &tDesignInfo);
	if(tStatus == DBX_OK)
	{
		strncpy_s(pFilename,DBX_MAX_NAME_LEN,tDesignInfo.designName,DBX_MAX_NAME_LEN);
		char *pStr = strrchr(pFilename, '.');
		if(pStr != NULL) *pStr = 0;			
		pStr = strstr(pFilename, "�3");
		if(pStr != NULL) *pStr = 0;			
	}
	else
	{
		strcpy_s(pFilename,DBX_MAX_NAME_LEN, "design");
	}
	// �������� ����������
	strcat_s(pFilename,DBX_MAX_NAME_LEN,sOutFileNameEnd[typeList]);
	strcat_s(pFilename,DBX_MAX_NAME_LEN,sOutFileExtension[typeFile]);
	return true;
}

// ������� ��������
static bool getDesignName(char *pName)
{
	TDesign tDesignInfo;
	//������� ���������� � ����
	tStatus = TGetDesignInfo(&tContext, &tDesignInfo);
	if(tStatus == DBX_OK)
	{
		char *pStr = strstr(tDesignInfo.designName, "�3");
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

// ������� ��������� ������ �� ����� length
// ������ �������� �� ��������
// src != NULL - ������ ���������
// src == NULL - ����������� ���������
static char * getSubstring(char *src, long length)
{
	static char *substr;	// ��������� ���������
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
		{	// �� ������� ������
			str_cnt = 1;
			for(long pos_end = length; pos_end < size; pos_end += length, str_cnt++)
			{
				// ��� ����� ������� �� ����� ������
				for(long i = pos_end; i > 0; --i)
				{
					if(src[i] == ' ') 
					{	// ����� ������� �������
						src[i] = 0;
						// ������� ������ ����� ���������
						pos_end = i+1;
						break;
					}
				}
			}			
			str_cnt--;
			substr = src;
		}
		else
		{	// ������� ������
			substr = NULL;
		}
	}
	return substr;
}

/*
// ������� �������� ����� �� ��������� ������ src � �������� index
// ������ ����� ��������� - @
static void getSubstring(char *src, long index, char *buffer, long length)
{
	for(long i = 0; i < index; i++)
	{
		if(src == NULL) break;
		// ��� ������ ������
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
// �������� ����� �� ��������� � ������ ������� � ������, �� ����������� length
// ������ ����� ��������� - @
// ���������� ����� ��������
static long makeSubstring(char *src, long length)
{
	// ����� ������� ���������
	long cur_length = 0;
	// ������� ��������
	long number = 1;
	while(true)
	{
		// ������� �����
		char *str = strchr(src, ' ');
		if(str == NULL) break;
		if((cur_length + str + 1 - src)<= length)
		{	// ���� ����� ��� ���������� �����
			// �������� � ������ ��� �����
			if(cur_length > 0) cur_length++;
			str++;
			cur_length += (str-src);
			src = str;
		}
		else
		{	// ��� ����� ��� ���������� ������ �����
			if(cur_length > 0)
			{	// ������� ����� ���������
				*str = '@';
				cur_length = 0;
				number++;
			}
		}
	}			
	return number;
}
*/
// ������ ������� � ����
static bool putToFileComponentList(long typeFile, long typeList, COMPONENT_LIST_STRUCT *pListComp, long *pIndexComp, long numComp, bool isFeedLine)
{
	FILE * hFile;
	char sFilename[DBX_MAX_NAME_LEN*5];
	// ������� ��� �����
	if(!getDesignFilename(typeFile, typeList, sFilename))
		return false;
	// �������� ����
	if(fopen_s(&hFile,sFilename, "w") != 0)
		return false;
	// �������� ���������
	getDesignName(sFilename);
	switch( typeFile )
	{
	case OUT_FILE_HTML:
		switch( typeList )
		{
		case OUT_LIST_VP:
			fprintf(hFile, "<!DOCTYPE HTML>\n<html>\n<body>\n<head>\n<title>��������� �������� %s</title>\n</head>\n",sFilename);
			fprintf(hFile, "<kbd><table>\n<table border=\"1\">\n");
			fprintf(hFile, "<caption>��������� �������� %s</caption>\n",sFilename);
			fprintf(hFile, "<tr><th>������������</th><th>���.</th></tr>\n");
			break;
		case OUT_LIST_SP:
			fprintf(hFile, "<!DOCTYPE HTML>\n<html>\n<body>\n<head>\n<title>������������ %s</title>\n</head>\n",sFilename);
			fprintf(hFile, "<kbd><table>\n<table border=\"1\">\n");
			fprintf(hFile, "<caption>������������ %s</caption>\n",sFilename);
			fprintf(hFile, "<tr><th>������������</th><th>���.</th><th>����������</th></tr>\n");
			break;
		default:
			fprintf(hFile, "<!DOCTYPE HTML>\n<html>\n<body>\n<head>\n<title>�������� ��������� %s</title>\n</head>\n",sFilename);
			fprintf(hFile, "<kbd><table>\n<table border=\"1\">\n");
			fprintf(hFile, "<caption>�������� ��������� %s</caption>\n",sFilename);
			fprintf(hFile, "<tr><th>���. �����������</th><th>������������</th><th>���.</th><th>����������</th></tr>\n");
			break;
		}
		break;
	case OUT_FILE_RTF:
		fprintf(hFile, "{\\rtf1\\ansi\\ansicpg1251\n");
		switch( typeList )
		{
		case OUT_LIST_VP:
			fprintf(hFile, "��������� �������� %s\n\\par\n",sFilename);
			fprintf(hFile, "\\trowd\\trgaph50\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx9000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
			fprintf(hFile, "\\pard\\intbl\n");
			fprintf(hFile, "������������\\cell\n���.\\cell\n\\row\n");
			break;
		case OUT_LIST_SP:
			fprintf(hFile, "������������ %s\n\\par\n",sFilename);
			fprintf(hFile, "\\trowd\\trgaph50\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx6000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
			fprintf(hFile, "\\pard\\intbl\n");
			fprintf(hFile, "������������\\cell\n���.\\cell\n����������\\cell\n\\row\n");
			break;
		default:
			fprintf(hFile, "�������� ��������� %s\n\\par\n",sFilename);
			fprintf(hFile, "\\trowd\\trgaph50\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
			fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
			fprintf(hFile, "\\pard\\intbl\n");
			fprintf(hFile, "���. �����������\\cell\n������������\\cell\n���.\\cell\n����������\\cell\n\\row\n");
			break;
		}
		break;
	default:
		break;
	}
	// �������� ������			
	// ������ ������ ���������
	long indexGroupName = 0;
	bool fSingle = false;
	for(long i = 0; i < numComp; i++)
	{
		char strValue[VALUE_MAX_STRING_LEN];
		const char *pGroupName = NULL;
		COMPONENT_LIST_STRUCT * pList = pListComp + pIndexComp[i];
		COMPONENT_LIST_STRUCT * pListNext = pListComp + pIndexComp[i+1];
		if( indexGroupName != pList->indexGroupName)
		{	// ������ ��������� ����������
			indexGroupName = pList->indexGroupName;
			if( (i+1) < numComp )
				// ��������� ������� ��������� � ������ ������
				fSingle = (indexGroupName != pListNext->indexGroupName);
			else
				// ��������� ������� - ����� ����
				fSingle = true;				
			pGroupName = getComponentGroupName(indexGroupName,fSingle);
		}
		// ������� ������ ��� ����������
		if( (!fSingle) ||						//������� �� ������
			(pGroupName == NULL) ||				//��� ���������� �����
			(pList->ids.lyt1_refdes == '@') )	// ��� �����
		{
			strcpy_s(strValue, VALUE_MAX_STRING_LEN, pList->value);
		}
		else
		{	// ��� ��������� �������� � Value ����������� ��������� ���
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
				fprintf(hFile, "%s %d ��\n",pList->value,pList->quantity);
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
				fprintf(hFile, "%s %d �� %s\n",pList->value,pList->quantity,pList->refdes);
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
			// �������� ���������
			{
				const char *pRemark = (strstr(pList->notList, "SP") != NULL)?("�� ���������������"):("");
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
					fprintf(hFile, "%s %d �� %s\n",pList->value,pList->quantity,pRemark);
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
					{	// �����
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
						{	//�������� ����� ������
							fprintf(hFile, "\\trowd\\trgaph50\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx1500\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx7000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx8000\n");
							fprintf(hFile, "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx10000\n");
							fprintf(hFile, "\\pard\\intbl\n");
							fprintf(hFile, " \\cell\n \\cell\n \\cell\n \\cell\n\\row\n");
							if(!fSingle)
							{	// ������� � ������ �� ����
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
							// ������� ��������� �� ���������
							long i1 = 0;
							pStr1[i1] = getSubstring(pList->refdes,11);
							while(pStr1[i1] != NULL)
							{
								if((++i1) >= DBX_MAX_ATTRIBUTE_LEN/11)
									break;
								pStr1[i1] = getSubstring(NULL,11);
							}
							// ������� ��������� �� ���������
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
								// ������ ������� ����������
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
	// �������� ����������
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
	// �������� ����
	fclose(hFile);
	return true;
}

// ������ ������� � ����
bool makeComponentList(long typeFile, long typeList, bool isFeedLine, 
	bool isInsertPattern, bool isSortingRefdes)
{
	COMPONENT_LIST_STRUCT *pListComponents;
	long *pIndexComponents;
	pListComponents = NULL;
	pIndexComponents = NULL;
	while(openDesign())
	{
		// ������� ����� �����������
		long numComponents = getNumberComponents();
		if(numComponents < 1) break;
		// ������� ������
		pListComponents = new COMPONENT_LIST_STRUCT [numComponents];
		pIndexComponents = new long [numComponents];
		if(pListComponents == NULL) break;
		if(pIndexComponents == NULL) break;
		// ������� ����������
		numComponents = getComponentsList(pListComponents, isInsertPattern);
		if(numComponents < 1) break;
		// ������������� ��������	
		for(long i = 0; i < numComponents; i++)
			pIndexComponents[i] = i;
		// ���������� ������ ����������� �� RefDes
		sortComponentList(pListComponents,pIndexComponents,numComponents, 
			&compareComponentListElementsById);
		switch(typeList)
		{
		// �������������
		case OUT_LIST_VP:
		case OUT_LIST_SP:	// ��� ������������
			// ������� �������� ������� � ������ �����������
			numComponents = mergeComponentListPE(pListComponents,pIndexComponents,numComponents);
			// ������� �������� ������� � ������ �����������
			numComponents = mergeComponentListSP(pListComponents,pIndexComponents,numComponents);
			if (!isSortingRefdes) {
				// �������� � Id ��������� ���������� ����� ����������
				setIdComponentsByGroupName(pListComponents,pIndexComponents,numComponents);
				// ���������� ������ ����������� �� Id � Value
				sortComponentList(pListComponents,pIndexComponents,numComponents,
					&compareComponentListElementsByIdAndValue);
			}
			break;
		// ��������
		case OUT_LIST_PE:	// ��� �������
			// ������� �������� ������� � ������ �����������
			numComponents = mergeComponentListPE(pListComponents,pIndexComponents,numComponents);
			break;
		// ������� ������
		default:
			break;
		}
		// �������� ������ � �����
		if(!putToFileComponentList(typeFile, typeList, pListComponents,pIndexComponents,numComponents, isFeedLine))
			MessageBox(NULL,_T("������ ������ � �������� ���� !"),_T("������"),MB_OK);
		// ������
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
	// ��� �����
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
	// ��� ������
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
