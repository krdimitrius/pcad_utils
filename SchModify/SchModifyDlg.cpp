
// SchModifyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SchModify.h"
#include "SchModifyDlg.h"
#include "afxdialogex.h"
#include "dbx32.h"
#include "myDbxUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const char sVersion[] = "0.1";
static const char sName[] = "SCH Modify Utility";

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSchModifyDlg dialog
CSchModifyDlg::CSchModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSchModifyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSchModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSchModifyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSchModifyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSchModifyDlg message handlers

BOOL CSchModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	{
		CString name;
		name = sName;
		name += _T(" v.");
		name += sVersion;

		CDialogEx::SetWindowTextW(name);

		CheckDlgButton(IDC_RADIO_VALUE, BST_CHECKED);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSchModifyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSchModifyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSchModifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
 * ���������� true ���� ��������� - ����������� �����
 * @param pComponent - ��������� �� ���������
 */
static bool check_channel_component(TComponent *pComponent)
{
	if (pComponent->connectionType == DBX_COMPONENT_CONNECTION_NORMAL) {	
		TAttribute myAttr;	// ������� ������� ����������
		// ������� ������ �������
		tStatus = TGetFirstCompAttribute(&tContext,pComponent->refDes,&myAttr);

		while (tStatus == DBX_OK) {
			// ������� � ������� ������ � ������
			if (strcmp(myAttr.type, attrDesChannel) == 0)
				return true;
			//������� ��������� �������
			tStatus = TGetNextCompAttribute(&tContext,&myAttr);
		}
	}
	return false;
}

/**
 * ���������� true ���� ��������� ������������� ��������� ����
 * @param pComponent - ��������� �� ���������
 * @param connectionType - ��� ����������
 */
static bool check_type_component(TComponent *pComponent, long connectionType)
{
	if (connectionType == DBX_COMPONENT_CONNECTION_NORMAL) {
		return ((pComponent->connectionType == DBX_COMPONENT_CONNECTION_NORMAL) &&
			(check_channel_component(pComponent) == false));
	}
	else if (connectionType == DBX_COMPONENT_CONNECTION_MODULE) {
		return ((pComponent->connectionType == DBX_COMPONENT_CONNECTION_MODULE) ||
			(check_channel_component(pComponent) == true));
	}
	else {
		return (pComponent->connectionType == DBX_COMPONENT_CONNECTION_LINK);
	}

	return false;
}

/**
 * ���������� ����������� VALUE:
 * - ����� ��������� � ������� ���������� ������, ���� ����������
 * - "." ���������� �� ","
 * - ��������� ����� ���������� �� ���������
 */
static bool modify_value(char * pRefDes, TAttribute * pAttr)
{
	bool flag = FALSE;

	if ((pRefDes[0] == 'R') || (pRefDes[0] == 'L') || (pRefDes[0] == 'C')) {
		if ((pRefDes[1] >= '0') && (pRefDes[1] <= '9')) {
			char * src = pAttr->value;
			char * psrc = src;

			if (psrc[0] == '~')
				psrc++;

			if ((psrc[0] >= '0') && (psrc[0] <= '9')) {
				char dst[DBX_MAX_ATTRIBUTE_LEN] = {0};
				char * pdst = dst;
				size_t size;

				// ������ '.' �� ','
				psrc = strchr(src, '.');
				if (psrc != NULL)
					*psrc = ',';

				// ������ �������� �����
				size = strspn(src, "~0123456789,");

				// ������� �������� �����
				strncpy_s(pdst, DBX_MAX_ATTRIBUTE_LEN, src, size);
				pdst += size;

				// ��������� �� ���������� �����
				psrc = src + size;
				psrc += strspn(psrc, " ");

				if ((*psrc == '�') || (*psrc == 'm')) {
					*pdst++ = ' ';
					*pdst++ = '�';
					if ((*(psrc + 1) == '�') || (*(psrc + 1) == '�') || (*(psrc + 1) == 'k') || (*(psrc + 1) == 'K')) {
						*pdst++ = '�';
					}
				}
				else if ((*psrc == '�') || (*psrc == '�') || (*psrc == 'k') || (*psrc == 'K')) {
					*pdst++ = ' ';
					*pdst++ = '�';
				}
				else if ((*psrc == '�') || (*psrc == 'M')) {
					*pdst++ = ' ';
					*pdst++ = '�';
				}
				else if ((*psrc == '�') || (*psrc == '�') || (*psrc == 'g') || (*psrc == 'G')) {
					*pdst++ = ' ';
					*pdst++ = '�';
				}

				strncpy_s(src, DBX_MAX_ATTRIBUTE_LEN, dst, DBX_MAX_ATTRIBUTE_LEN);

				flag = TRUE;
			}
		}
	}

	return flag;
}

/**
 * ��������� ����������� ����
 */
static bool process_modify_value(void)
{
	if (openDesignSch()) {
		TComponent myComponent;	// ��������
		//������� ������ ���������
		tStatus = TGetFirstComponent(&tContext, &myComponent);
		while (tStatus == DBX_OK) {
			if (check_type_component(&myComponent, DBX_COMPONENT_CONNECTION_NORMAL)) {
				// ��������� ������������� ��������� ����
				TAttribute myAttr; // �������
				
				// ������� ������ ������� ����������
				tStatus = TGetFirstCompAttribute(&tContext, myComponent.refDes, &myAttr);
				while (tStatus == DBX_OK) {
					// ������� ������� VALUE
					if (strcmp(myAttr.type, attrValue) == 0) {
						if (modify_value(myComponent.refDes, &myAttr)) {
							TModifyCompAttribute(&tContext, myComponent.refDes, &myAttr);
						}
						break;
					}
					//������� ��������� �������
					tStatus = TGetNextCompAttribute(&tContext, &myAttr);
				}
			}
			//������� ��������� ���������
			tStatus = TGetNextComponent(&tContext,&myComponent);
		}
		closeDesignSch();
	}
	else {
		MessageBox(NULL,_T("������ �������� ���� !"),_T("������"),MB_OK);
	}

	return true;
}

void CSchModifyDlg::OnBnClickedOk()
{
//	TODO: ������������� ��� ���������� ��������
//	switch(GetCheckedRadioButton(IDC_RADIO_VALUE, IDC_RADIO_VALUE)) {
//	case IDC_RADIO_VALUE:
		process_modify_value();
//		break;
//	default:
//		break;
//	}

	CDialogEx::OnOK();
}
