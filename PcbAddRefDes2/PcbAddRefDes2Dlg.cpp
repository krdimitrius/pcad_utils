
// PcbAddRefDes2Dlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "PcbAddRefDes2.h"
#include "PcbAddRefDes2Dlg.h"
#include "afxdialogex.h"
#include "dbx32.h"
#include "myDbxUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���������� ���� CPcbAddRefDes2Dlg
CPcbAddRefDes2Dlg::CPcbAddRefDes2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPcbAddRefDes2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPcbAddRefDes2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, OkButton);
}

BEGIN_MESSAGE_MAP(CPcbAddRefDes2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPcbAddRefDes2Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� CPcbAddRefDes2Dlg

BOOL CPcbAddRefDes2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
	CheckDlgButton(IDC_CHECK_ADDREFDES2, BST_CHECKED);
	CheckDlgButton(IDC_CHECK_VISIBLEREFDES2, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_MOVEREFDES2, BST_UNCHECKED);
	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CPcbAddRefDes2Dlg::OnPaint()
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
HCURSOR CPcbAddRefDes2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �������� ����
static bool openDesign(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "pcb",&tContext) == DBX_OK)
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

// ��������� RefDes2
void processComponent(
	TComponent * pMyComponent,
	bool addRefDes2, 
	bool visibleRefDes2,
	bool moveRefDes2)
{
	TAttribute refdesAttr,refdes2Attr; // �������
	bool isRefDes2 = false;
	// ����������� RefDes
	// ������� ������ ������� ����������
	tStatus = TGetFirstCompAttribute(&tContext,pMyComponent->refDes,&refdesAttr);
	while(tStatus == DBX_OK)
	{
		// ������� � ������� ������ � ������
		if( (strcmp(refdesAttr.type, attrRefDes) == 0)
			|| (strcmp(refdesAttr.type, attrRefDes_1) == 0) )
			break;
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext,&refdesAttr);
	}
	// ����������� RefDes2
	// ������� ������ ������� ����������
	tStatus = TGetFirstCompAttribute(&tContext,pMyComponent->refDes,&refdes2Attr);
	while(tStatus == DBX_OK)
	{
		// ������� � ������� ������ � ������
		if( (strcmp(refdes2Attr.type, attrRefDes2) == 0)
			|| (strcmp(refdes2Attr.type, attrRefDes2_1) == 0) )
		{
			isRefDes2 = true;
			break;
		}
		//������� ��������� �������
		tStatus = TGetNextCompAttribute(&tContext,&refdes2Attr);
	}
	if( isRefDes2 )
	{
		// ����������� RefDes2 �� ����� RefDes 
		if( moveRefDes2 )
		{
			int isFlipped = pMyComponent->isFlipped;
			// �������
			refdes2Attr.rotationAng = refdesAttr.rotationAng;
			// ������������ ������
			refdes2Attr.justPoint = refdesAttr.justPoint;
			// ����� ������
			refdes2Attr.textStyleId = refdesAttr.textStyleId;
			// ����
			if( isFlipped )
				refdes2Attr.layerId = DBX_LAYER_BOTTOM_SILK;
			else
				refdes2Attr.layerId = DBX_LAYER_TOP_SILK;
			// ����� �������� ������
			refdes2Attr.refPoint.x = refdesAttr.refPoint.x;
			refdes2Attr.refPoint.y = refdesAttr.refPoint.y; 
			// ���������
			refdes2Attr.isVisible = 1;
			TModifyCompAttribute(&tContext,pMyComponent->refDes,&refdes2Attr);
		}
		// ��������� RefDes2
		refdes2Attr.isVisible = (visibleRefDes2)? 1 : 0;
		TModifyCompAttribute(&tContext, pMyComponent->refDes, &refdes2Attr);
	}
	else if( addRefDes2 )
	{	
		// ��������� RefDes2 ���� ��� ��� � ��������� ����������
		int isFlipped = pMyComponent->isFlipped;
		// ���
		strcpy_s(refdes2Attr.type,DBX_MAX_NAME_LEN,attrRefDes2);
		refdes2Attr.typeLength = strlen(refdes2Attr.value);
		// �������� (�����)
		strcpy_s(refdes2Attr.value,DBX_MAX_NAME_LEN, pMyComponent->refDes);
		refdes2Attr.valueLength = strlen(refdes2Attr.value);
		// ������������ ������
		refdes2Attr.justPoint = refdesAttr.justPoint;
		// ����� ������
		refdes2Attr.textStyleId = refdesAttr.textStyleId;
		// ����
		if( isFlipped )
			refdes2Attr.layerId = DBX_LAYER_BOTTOM_SILK;
		else
			refdes2Attr.layerId = DBX_LAYER_TOP_SILK;
		// ����� �������� ������
		refdes2Attr.refPoint.x = refdesAttr.refPoint.x;
		refdes2Attr.refPoint.y = refdesAttr.refPoint.y; 
		// ���� �������� ������
		refdes2Attr.rotationAng = refdesAttr.rotationAng;
		// ���������
		refdes2Attr.isVisible = 1;
		// ��������
		TAddCompAttribute(&tContext, pMyComponent->refDes,&refdes2Attr);
		// ��������� RefDes2
		refdes2Attr.isVisible = (visibleRefDes2)? 1 : 0;
		TModifyCompAttribute(&tContext, pMyComponent->refDes, &refdes2Attr);
	}
}

// ��������� RefDes2
bool processAddRefDes2(
	bool addRefDes2, 
	bool visibleRefDes2,
	bool moveRefDes2,
	bool selCmp)
{
	if(openDesign())
	{
		if( selCmp )
		{
			TItem myItem;
			// ������� ������ ���������� �������
			tStatus = TGetFirstSelectedItem(&tContext, &myItem);
			while(tStatus == DBX_OK)
			{
				if( myItem.itemType == DBX_COMPONENT )
					processComponent(&myItem.component, addRefDes2, visibleRefDes2, moveRefDes2);
				// ������� ��������� ���������� �������
				tStatus = TGetNextSelectedItem(&tContext, &myItem);
			}
		}
		else
		{
			TComponent myComponent;	// ��������
			//������� ������ ���������
			tStatus = TGetFirstComponent(&tContext, &myComponent);
			while(tStatus == DBX_OK)
			{	
				processComponent(&myComponent, addRefDes2, visibleRefDes2, moveRefDes2);
				//������� ��������� ���������
				tStatus = TGetNextComponent(&tContext,&myComponent);
			}
		}
	}
	closeDesign();
	return true;
}

void CPcbAddRefDes2Dlg::OnBnClickedOk()
{
	// ���� ������
	OkButton.EnableWindow(false);
	// ��������� ������
	processAddRefDes2((IsDlgButtonChecked(IDC_CHECK_ADDREFDES2) == BST_CHECKED),
		(IsDlgButtonChecked(IDC_CHECK_VISIBLEREFDES2) == BST_CHECKED),
		(IsDlgButtonChecked(IDC_CHECK_MOVEREFDES2) == BST_CHECKED),
		(IsDlgButtonChecked(IDC_CHECK_SELECTED) == BST_CHECKED)
		);
	//
	CDialogEx::OnOK();
}

