
// RenumberDlg.cpp : ���� ����������
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

// ���������� ���� CRenumberDlg
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


// ����������� ��������� CRenumberDlg

BOOL CRenumberDlg::OnInitDialog()
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

	CheckDlgButton(IDC_RADIO_NORMAL, BST_CHECKED);
	CheckDlgButton(IDC_RADIO_DIRECTION1, BST_CHECKED);

	Edit1.ShowWindow(0);
	Edit2.ShowWindow(0);
	Edit3.ShowWindow(0);
	Edit4.ShowWindow(0);
	CheckEco.ShowWindow(1);

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CRenumberDlg::OnPaint()
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
HCURSOR CRenumberDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//========================================================================================
// ������� ���������
typedef struct COMPONENT_LIST_STRUCT {
	long coord1;						// ���������� �������� 1
	long coord2;						// ���������� �������� 1
	long sheet;							// ����� �����
	long channel;						// ����� �����a � ������ 
	long group;							// ����� ������ �������
	char refdes_txt[DBX_MAX_NAME_LEN];	// ��������� ����� �����������
	char refdes_old[DBX_MAX_NAME_LEN];	// ������ �����������
	union {
		char refdes_new[DBX_MAX_NAME_LEN];	// ����� �����������
		char link[DBX_MAX_NAME_LEN];	//link
	};
} COMPONENT_LIST_STRUCT;
//========================================================================================

/**
 * @brief ��������� ����� �����
 * @param pFilename_p  ��������� �� ��� �����.
 * @return true, ���� ��� ��������.
 */
static bool
getDesignFilename(char * pFilename_p)
{
	TDesign tDesignInfo;
	//������� ���������� � ����
	tStatus = TGetDesignInfo(&tContext, &tDesignInfo);
	if(tStatus == DBX_OK)
		strncpy_s(pFilename_p, DBX_MAX_NAME_LEN, tDesignInfo.designName, DBX_MAX_NAME_LEN);
	else
		strcpy_s(pFilename_p, DBX_MAX_NAME_LEN, "design");
	return true;
}

/**
 * @brief ��������� ����� ECO-����� �� ����� �����
 * @param pFilename_p  ��������� �� ��� �����.
 * @return true, ���� ��� ��������.
 */
static bool
getEcoFilename(char * pFilename_p)
{
	bool result = true;
	TDesign tDesignInfo;
	//������� ���������� � ����
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

	// �������� ����������
	strcat_s(pFilename_p, DBX_MAX_NAME_LEN, ".ECO");

	return result;
}

/**
 * @brief ������� �������� ECO-�����
 * @return true, ���� ���� ������
 */
static FILE *
openEcoFile(void)
{
	bool result = true;
	char sFilename[DBX_MAX_NAME_LEN*5];
	char sEcoFilename[DBX_MAX_NAME_LEN*5];
	FILE * hEcoFile = NULL;

	// ������� ��� ����
	if (result)
		result = getDesignFilename(sFilename);

	// ������� ��� ECO
	if (result)
		result = getEcoFilename(sEcoFilename);

	// �������� ECO
	if (result)
		result = (fopen_s(&hEcoFile, sEcoFilename, "a") == 0);

	// ���� ���������
	if (result) 
		fprintf(hEcoFile, "; %s Version %s [%s]\n", sName, sVersion, sFilename);

	return (result) ? (hEcoFile) : (NULL);
}

/**
 * @brief ������ ������ � ECO-����
 * @param pStr_p  ��������� �� ������.
 * @param idx_p   ������ ������:
 *   0 - ������ �����;
 *   1 - ������ �����.
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
 * @brief �������� ECO-�����
 */
static void
closeEcoFile(FILE * hEcoFile_p)
{
	if (hEcoFile_p != NULL)
		fclose(hEcoFile_p);
}

/*
// ��������� ���� ��������� �� Id (��� ���������� �� ����������)
static long compareComponentListElementsByIdDecrease(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	if( pComp1->id > pComp2->id ) return -1;
	if( pComp1->id < pComp2->id ) return 1;
	return 0;
}

// ��������� ���� ��������� �� Id (��� ���������� �� ����������)
static long compareComponentListElementsByIdIncrease(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	if( pComp1->id > pComp2->id ) return 1;
	if( pComp1->id < pComp2->id ) return -1;
	return 0;
}
*/
// ��������� ���� ��������� �� ��������� � �����
static long compareComponentListElementsByPlacement(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	long result;
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	// ��������� �� ��������
	result = pComp1->sheet - pComp2->sheet;
	if(result != 0) return result;
	// ��������� �� ���������� 2
	result = pComp1->coord2 - pComp2->coord2;
	if(result != 0) return result;
	// ��������� �� ���������� 1
	result = pComp1->coord1 - pComp2->coord1;
	return result;
}

// ��������� ���� ��������� ��:
//	- ��������� ����� RefDes
//	- ������ �������
//	- ������ ������ ������ ������ �������
//	- ��������� � �����
static long compareComponentListElementsByChannels(COMPONENT_LIST_STRUCT *listComp, long *indexComponents, long index1, long index2)
{
	long result;
	COMPONENT_LIST_STRUCT *pComp1 = listComp + indexComponents[index1];
	COMPONENT_LIST_STRUCT *pComp2 = listComp + indexComponents[index2];
	// ��������� �� RefDes
	result = strcmp(pComp1->refdes_txt,pComp2->refdes_txt);
	if(result != 0) return result;
	// ��������� �� ������� �������
	result = pComp1->group - pComp2->group;
	if(result != 0) return result;
	// ��������� �� ������ ������ ������
	result = pComp1->channel - pComp2->channel;
	if(result != 0) return result;
	// ��������� �� ��������� � �����
	return compareComponentListElementsByPlacement(listComp,indexComponents,index1,index2);
}

// ���������� ����������
static void sortComponentList(COMPONENT_LIST_STRUCT *pListComp, long *indexComponents, long num_components, 
	long(* pFunc)(COMPONENT_LIST_STRUCT *,long *, long, long))
{
	long i,j;
	// ������ ����������
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

// ���������� true ���� ��������� - ����������� �����
static bool isChannelNormalComponent(TComponent *pComponent)
{
	if(pComponent->connectionType == DBX_COMPONENT_CONNECTION_NORMAL)
	{	
		TAttribute myAttr;	// ������� ������� ����������
		// ������� ������ �������
		tStatus = TGetFirstCompAttribute(&tContext,pComponent->refDes,&myAttr);
		while (tStatus == DBX_OK)
		{
			// ������� � ������� ������ � ������
			if(strcmp(myAttr.type, attrDesChannel) == 0)
				return true;
			//������� ��������� �������
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
	}
	return false;
}

// ���������� true ���� ��������� ������������� ��������� ����
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

// ������� ����� ����������� � ����
static long getNumberComponents(long connectionType)
{
	TComponent myComponent;
	long num_components = 0;
	//������� ������ ���������
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while (tStatus == DBX_OK)
	{
		// ��������� ������������� ��������� ���� ?
		if(isProcessComponent(connectionType,&myComponent))
			num_components++;
		//������� ��������� ���������
		tStatus = TGetNextComponent(&tContext,&myComponent);
	}
	//��������� ����� �����������
	return num_components;
}

// ������������� ��������	
static void initIndex(long *pIndexComponents, long num_components) 
{	
	for(long i = 0; i < num_components; i++)
		pIndexComponents[i] = i;
}

// ������� ������
static bool getSymbol(COMPONENT_LIST_STRUCT *pListCur,TSymbol *pSymbol,bool bDirection)
{
	// ������� ��������, ��� ��������� ������
	TLayer myLayer;
	TGetLayerById(&tContext,pSymbol->layerId,&myLayer);
	// ������� ����� ��������
	pListCur->sheet = myLayer.layerPosition;
	// ������� ����������� �������
	if(bDirection)
	{	// ��� ��������� �����-�������
		pListCur->coord2 = 0x7FFFFFFF - pSymbol->refPoint.y;	// ���������� Y, ��������� - ��� ���������� ����������
		pListCur->coord1 = pSymbol->refPoint.x;	// ���������� X
//		pListCur->coord2 = 32767 - (pSymbol->refPoint.y / 100000);	// ���������� Y - � ��, ��������� - ��� ���������� ����������
//		pListCur->coord1 = pSymbol->refPoint.x / 100000;	// ���������� X - � ��
	}
	else
	{	// ��� ��������� ������-����
		pListCur->coord1 = 0x7FFFFFFF - pSymbol->refPoint.y;	// ���������� Y, ��������� - ��� ���������� ����������
		pListCur->coord2 = pSymbol->refPoint.x;	// ���������� X
//		pListCur->coord1 = 32767 - (pSymbol->refPoint.y / 100000);	// ���������� Y - � ��, ��������� - ��� ���������� ����������
//		pListCur->coord2 = pSymbol->refPoint.x / 100000;	// ���������� X - � ��
	}
	return true;
}

// ������� ������� 
static long getSymbolsList(char *pRefDes, COMPONENT_LIST_STRUCT *pListCur,bool bDirection)
{
	TSymbol mySymbol;
	long num_symbols = 0;
	// ������� ������ ������
	tStatus = TGetFirstCompSymbol(&tContext,pRefDes,&mySymbol);
	while(tStatus == DBX_OK)
	{
		if(getSymbol(pListCur,&mySymbol,bDirection))
		{
			num_symbols++;
			pListCur++;
		}
		// ������� ��������� ������
		tStatus = TGetNextCompSymbol(&tContext,&mySymbol);
	}
	return num_symbols;
}

// ������� ��������� 
static bool getComponent(COMPONENT_LIST_STRUCT *pListCur,TComponent * pComponent, bool bDirection)
{
	TAttribute myAttr;		// ������� ������� ����������
	char *tmp;
	// ������������� ������
	pListCur->refdes_old[0] = 0;
	pListCur->refdes_new[0] = 0;
	pListCur->refdes_txt[0] = 0;
	// ������ ������
	pListCur->group = 0;
	// ������ ������ � ������
	pListCur->channel = 0;
	// ������� ������ �������
	tStatus = TGetFirstCompAttribute(&tContext,pComponent->refDes,&myAttr);
	while (tStatus == DBX_OK)
	{
		// ������� � ������� ������ � ������
		if(strcmp(myAttr.type,attrNoChannelInGroupType) == 0)
			sscanf_s(myAttr.value,"%d",&pListCur->channel);
		// ������� � ������� ����� �������
		else if(strcmp(myAttr.type,attrNoChannelGroupType) == 0)
			sscanf_s(myAttr.value,"%d",&pListCur->group);
		// ����
		else if(strcmp(myAttr.type,"Link") == 0)
			strcpy_s(pListCur->link,DBX_MAX_NAME_LEN,myAttr.value);
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext,&myAttr);
	}
	// ����������� refDes
	strcpy_s(pListCur->refdes_old, DBX_MAX_NAME_LEN, pComponent->refDes); // ������� refDes
	strcpy_s(pListCur->refdes_txt, DBX_MAX_NAME_LEN, pComponent->refDes); // ������� refDes
	//��� � pListCur->refdes_txt ������ �������� ����� � ������� ������ � ���� �����
	tmp = strpbrk(pListCur->refdes_txt, acceptNumber); 
	if(tmp != NULL) *tmp = 0;
	// ��� ��������� ������� ������� ����������
	if(pComponent->numberParts > 0)
	{
		COMPONENT_LIST_STRUCT * pSymbolsList = NULL;
		long * pIndexSymbols = NULL;
		while(true)
		{
			long numSymbols;
			// ������� ������
			pSymbolsList = new COMPONENT_LIST_STRUCT[pComponent->numberParts];
			pIndexSymbols = new long [pComponent->numberParts];
			if(pSymbolsList == NULL) break;
			if(pIndexSymbols == NULL) break;
			// ������������� ��������
			initIndex(pIndexSymbols,pComponent->numberParts);
			// ������� ������ ��������
			numSymbols	= getSymbolsList(pListCur->refdes_old,pSymbolsList,bDirection);
			if(numSymbols < 1) break;
			// ���������� ������ �������� �� Id
			sortComponentList(pSymbolsList,pIndexSymbols,numSymbols,
				&compareComponentListElementsByPlacement);
			// ��������� ������ ������� ������� �� �������� ����������
			pListCur->coord1 = pSymbolsList[pIndexSymbols[0]].coord1;
			pListCur->coord2 = pSymbolsList[pIndexSymbols[0]].coord2;
			pListCur->sheet = pSymbolsList[pIndexSymbols[0]].sheet;
			break;
		}		
		delete pIndexSymbols;
		delete pSymbolsList;
		return true;
	}
	// �������
	return false;
}		

// ������� ������ �����������
static long getComponentsList(long connectionType,COMPONENT_LIST_STRUCT *pListCur, bool bDirection)
{
	TComponent myComponent;	// ��������
	long num_components = 0;
	if(pListCur == NULL) return 0;
	//������� ������ ���������
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while(tStatus == DBX_OK)
	{
		if(isProcessComponent(connectionType,&myComponent))
		{	// ��������� ������������� ��������� ����
			if(getComponent(pListCur,&myComponent,bDirection))
			{	// ������� � ��������� ������
				pListCur++;
				num_components++;
			}
		}
		//������� ��������� ���������
		tStatus = TGetNextComponent(&tContext,&myComponent);
	}
	return num_components;
}

// ������� ����� ����� ����� ������� � ������
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

// �������� � ������������� ������ ����� RefDes
// - �������� ���������� � 1 � ����������� 1 � ������� ����������
// - �������� ������� ������ ������ ���������� ����� ��������� � ������� ��������� �����
// - � ��������� ����������� ������� � ������� �������� ������� ������ 
//   ����� '_' ����������� ����� ������ � ������
static bool makeNewRefDesComponents(long connectionType, COMPONENT_LIST_STRUCT *pList, long *pIndexComponents, long num_components)
{
	long index;	// ������ ��������
	long current_group; // ���������� ������ �������
	long current_channel; // ���������� ����� � ����� �������
	char current_refdes_txt[DBX_MAX_NAME_LEN] = {0}; // ���������� ��������� ����� RefDes
	// ������ �������� ������� �������� � ������ ������ ������
	long *index_channel = new long [getNumGroups(pList, num_components)];
	if(index_channel == NULL)
		return false;
	// ���������� ������������ �������������� ������
	for(long i = 0; i < num_components; i++)
	{
		COMPONENT_LIST_STRUCT *pListCur = pList + pIndexComponents[i];
		if(strcmp(pListCur->refdes_txt, current_refdes_txt) != 0)
		{	// ����� ��������� ����� RefDes
			strcpy_s(current_refdes_txt, pListCur->refdes_txt);
			index = 1;
			index_channel[0] = 1;
			current_channel = 0;
			current_group = 0;
		}
		if(connectionType == DBX_COMPONENT_CONNECTION_NORMAL)
		{	// ��� ���������� ����������� ��������� ��������� �� ������
			if(pListCur->group != current_group)
			{	// ����� ������ �������
				current_group = pListCur->group;
				if(current_group > 0)
				{	// �� �������� ����� ����� (������ 0)
					current_channel = pListCur->channel;
					if(current_channel <= 1)
					{	// ������ ����� � ������ �������
						current_channel = 1;
						// �������� ������ ������� �������� � ������ ������ ������
						index_channel[current_group] = index;
					}
					else
					{	// ����������� ������ � ������ �������
						// �������� ������ ������� �������� � ������ ������ ������
						index = index_channel[current_group];
					}
				}
				else
				{
					current_channel = 0;
				}

			}
			else if(pListCur->channel != current_channel)
			{	// ����� ����� � ������ �������
				current_channel = pListCur->channel;
				if(current_group > 0) 
					index = index_channel[current_group];
			}
			// ������ ����� �������� refdes
			if(current_channel <= 1)
				// ������ ����� ������ �������
				sprintf_s(pListCur->refdes_new,DBX_MAX_NAME_LEN,"%s%d",pListCur->refdes_txt,index);
			else
				// ����������� ����� ����� �������
				sprintf_s(pListCur->refdes_new,DBX_MAX_NAME_LEN,"%s%d_%d",pListCur->refdes_txt,index,current_channel);
		}
		else
			// ��� ��������� ���������� - �������� �������������
			sprintf_s(pListCur->refdes_new,DBX_MAX_NAME_LEN,"%s%d",pListCur->refdes_txt,index);
		// ���� refdes �� ���������, ������ �� ������
		if(strcmp(pListCur->refdes_new,pListCur->refdes_old) == 0)
			pListCur->refdes_new[0] = 0;
		index++;
	}
	delete index_channel;
	return true;
}

/**
 * @brief ������� �������� �������� RefDes �� �����
 * @param connectionType  ��� �����������.
 * @param pList           ��������� �� ������ �����������.
 * @param flag            ���� �������� '@' �� RefDes ����������.
 * @param hEcoFile_p      Heandle ECO �����.
 */
static void
saveNewRefDesComponents(long connectionType, COMPONENT_LIST_STRUCT *pList,
	bool flag, FILE * hEcoFile_p)
{
	TComponent myComponent;	// ��������
	TSymbol mySymbol;		// ������
	bool bSaveEco = (hEcoFile_p != NULL);
	char refdes_prev[DBX_MAX_NAME_LEN];

	refdes_prev[0] = 0;
	//������� ������ ���������
	tStatus = TGetFirstComponent(&tContext,&myComponent);
	while(tStatus == DBX_OK)
	{
		if(isProcessComponent(connectionType,&myComponent)) {
			// ��������� ������������� ��������� ����
			// ������� ������ ������ ����������
			tStatus = TGetFirstCompSymbol(&tContext, myComponent.refDes, &mySymbol);
			while(tStatus == DBX_OK) {
				if(flag) {
					// �������� "@"
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
						// ����������� ������
						tStatus = TModifySymbol(&tContext, &mySymbol);
					}
				}
				else if(pList->refdes_new[0] != 0) {
					// ��������� ������ refDes
					// ���� ����� refdes
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
					// ���������� "@"
					strcat_s(refdes_new, DBX_MAX_NAME_LEN, "@");
					if (bSaveEco && bNewComp)
						writeEcoFile(hEcoFile_p, refdes_new, 1);
					// ��� ������ ������ c�����
					pStr = strchr(mySymbol.refDes,':');
					if(pStr != NULL)
						strcat_s(refdes_new, DBX_MAX_NAME_LEN, pStr);
					// ����� ����� refDes
					strcpy_s(mySymbol.refDes, DBX_MAX_NAME_LEN, refdes_new);
					// ����������� ������
					tStatus = TModifySymbol(&tContext, &mySymbol);
				}
				// ������� ��������� ������ ����������
				tStatus = TGetNextCompSymbol(&tContext, &mySymbol);
			}
			// ������� � ��������� ������
			pList++;
		}
		//������� ��������� ���������
		tStatus = TGetNextComponent(&tContext, &myComponent);
	}
}

// ������������� 
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
		// ������� ����� �����������
		long numComponents = getNumberComponents(connectionType);
		if(numComponents < 1) break;
		// ������� ������
		pListComponents = new COMPONENT_LIST_STRUCT [numComponents];
		pIndexComponents = new long [numComponents];
		if(pListComponents == NULL) break;
		if(pIndexComponents == NULL) break;
		// ������������� ��������
		initIndex(pIndexComponents,numComponents);
		// ������� ����������
		numComponents = getComponentsList(connectionType,pListComponents, bDirection);
		if(numComponents < 1) break;
		// ���������� ������ ����������� �� Id
		sortComponentList(pListComponents,pIndexComponents,numComponents, 
			&compareComponentListElementsByChannels);
		// ��������� ����� �������� RefDes
		makeNewRefDesComponents(connectionType,pListComponents,pIndexComponents,numComponents);
		// �������� �������� RefDes
		saveNewRefDesComponents(connectionType,pListComponents, false, hEcoFile);
		// �������� �������� RefDes
		saveNewRefDesComponents(connectionType,pListComponents, true, hEcoFile);
		break;
	}
	closeEcoFile(hEcoFile);
	closeDesign();
	delete pListComponents;
	delete pIndexComponents;
	return true;
}

// ��������� RefDes2
bool processAddRefDes2(void)
{
	while(openDesign())
	{
		TComponent myComponent;	// ��������
		//������� ������ ���������
		tStatus = TGetFirstComponent(&tContext,&myComponent);
		while(tStatus == DBX_OK)
		{
			if(isProcessComponent(DBX_COMPONENT_CONNECTION_NORMAL,&myComponent))
			{	// ��������� ������������� ��������� ����
				TAttribute myAttr; // �������
				bool flag = false;
				// ������� ������ ������� ����������
				tStatus = TGetFirstCompAttribute(&tContext,myComponent.refDes,&myAttr);
				while(tStatus == DBX_OK)
				{
					// ������� � ������� ������ � ������
					if(strcmp(myAttr.type,attrRefDes2) == 0)
					{
						strcpy_s(myAttr.value,DBX_MAX_NAME_LEN,myComponent.refDes);
						myAttr.valueLength = strlen(myAttr.value);
						TModifyCompAttribute(&tContext,myComponent.refDes,&myAttr);
						flag = true;
						break;
					}
					//������� ��������� �������
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
			//������� ��������� ���������
			tStatus = TGetNextComponent(&tContext,&myComponent);
		}
		break;
	}
	closeDesign();
	return true;
}

// ������������� ���������� 
bool makechanComponent(char * pRefDes, long no_group, long no_channel)
{
	TAttribute myAttr; // �������
	bool flag_no_group = false;
	bool flag_no_channel = false;
	if(pRefDes == NULL) return false;
	if(strlen(pRefDes) == 0) return false;
	//
	tStatus = TGetFirstCompAttribute(&tContext,pRefDes,&myAttr);
	while(tStatus == DBX_OK)
	{
		// ������� � ������� ������
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
		// ������� � ������� ������ � ������
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
		//������� ��������� �������
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

// ������ ������������� �������������� ���������� �����������
bool processMakeChanManual(long no_group, long no_channel)
{
	while(openDesign())
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
				// ������������� ���������
				makechanComponent(myRefDes, no_group, no_channel);
			}
			//������� ��������� ���������
			tStatus = TGetNextSelectedItem(&tContext,&myItem);
		}
		break;
	}
	closeDesign();
	return true;
}

// �������������� �������������
bool processMakeChanAuto(void)
{
	COMPONENT_LIST_STRUCT *pListChannels = NULL;
	COMPONENT_LIST_STRUCT *pListLinks = NULL;
	COMPONENT_LIST_STRUCT *pListComponents = NULL;
	while(openDesign())
	{
		// ������� ����� �����������
		long numChannels = getNumberComponents(DBX_COMPONENT_CONNECTION_MODULE);
		long numLinks = getNumberComponents(DBX_COMPONENT_CONNECTION_LINK);
		long numComponents = getNumberComponents(DBX_COMPONENT_CONNECTION_NORMAL);
		// ������� ������ ��� �����������
		if(numComponents < 1) break;
		pListComponents = new COMPONENT_LIST_STRUCT [numComponents];
		if(pListComponents == NULL) break;
		if(numChannels > 0)
		{
			// ������� ������ ��� �������
			pListChannels = new COMPONENT_LIST_STRUCT [numChannels];
			if(numLinks > 0)
				// ������� ������ ��� ������
				pListLinks = new COMPONENT_LIST_STRUCT [numLinks];
		}
		// ������� ������
		numChannels = getComponentsList(DBX_COMPONENT_CONNECTION_MODULE,pListChannels,false);
		// ������� �����
		numLinks = getComponentsList(DBX_COMPONENT_CONNECTION_LINK,pListLinks,false);
		// ������� ����������
		numComponents = getComponentsList(DBX_COMPONENT_CONNECTION_NORMAL,pListComponents,false);
		// ���������� ������ ������ ������ � ������ ������
		for(long i = 0; i < numLinks; i++)
		{
			for(long j = 0; j < numChannels; j++)
			{
				if(strcmp(pListLinks[i].refdes_old,pListChannels[j].link) == 0)
				{	// ��� ����� ��������� � ��������� ������
					pListLinks[i].group = pListChannels[j].group;
					pListLinks[i].channel = pListChannels[j].channel;
					break;
				}
			}
		}
		// ������ � ���������� ������ ������ � ������ ������
		for(long i = 0; i < numComponents; i++)
		{	// ��� ����� ��������� � ��������� ������
			pListComponents[i].group = 0;
			pListComponents[i].channel = 0;
		}
		// ���������� ������������ ������ ������ � ������ ������, ��� � ����� ������������ �� ���� ���������
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
		// ������������� �����������
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
	// ���� ������
	OkButton.EnableWindow(false);
	// ��������� ����������� 
	bool bDirection = (GetCheckedRadioButton(IDC_RADIO_DIRECTION1,IDC_RADIO_DIRECTION2) == IDC_RADIO_DIRECTION2);
	// ���� ������ ECO
	bool bSaveEco = (IsDlgButtonChecked(IDC_CHECK_ECO) == BST_CHECKED);

	// ��������� ������
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
	str = "������";
	Edit1.ShowWindow(1);
	Edit1.SetWindowTextW(str);
	Edit1.EnableWindow(false);
	str = "�����";
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
