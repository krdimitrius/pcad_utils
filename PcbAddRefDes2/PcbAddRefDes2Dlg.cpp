
// PcbAddRefDes2Dlg.cpp : файл реализации
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

// диалоговое окно CPcbAddRefDes2Dlg
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


// обработчики сообщений CPcbAddRefDes2Dlg

BOOL CPcbAddRefDes2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	CheckDlgButton(IDC_CHECK_ADDREFDES2, BST_CHECKED);
	CheckDlgButton(IDC_CHECK_VISIBLEREFDES2, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_MOVEREFDES2, BST_UNCHECKED);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CPcbAddRefDes2Dlg::OnPaint()
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
HCURSOR CPcbAddRefDes2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// открываю базу
static bool openDesign(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "pcb",&tContext) == DBX_OK)
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

// добавляем RefDes2
void processComponent(
	TComponent * pMyComponent,
	bool addRefDes2, 
	bool visibleRefDes2,
	bool moveRefDes2)
{
	TAttribute refdesAttr,refdes2Attr; // атрибут
	bool isRefDes2 = false;
	// обрабатываю RefDes
	// получаю первый атрибут компонента
	tStatus = TGetFirstCompAttribute(&tContext,pMyComponent->refDes,&refdesAttr);
	while(tStatus == DBX_OK)
	{
		// атрибут с номером канала в группе
		if( (strcmp(refdesAttr.type, attrRefDes) == 0)
			|| (strcmp(refdesAttr.type, attrRefDes_1) == 0) )
			break;
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext,&refdesAttr);
	}
	// обрабатываю RefDes2
	// получаю первый атрибут компонента
	tStatus = TGetFirstCompAttribute(&tContext,pMyComponent->refDes,&refdes2Attr);
	while(tStatus == DBX_OK)
	{
		// атрибут с номером канала в группе
		if( (strcmp(refdes2Attr.type, attrRefDes2) == 0)
			|| (strcmp(refdes2Attr.type, attrRefDes2_1) == 0) )
		{
			isRefDes2 = true;
			break;
		}
		//получаю следующий атрибут
		tStatus = TGetNextCompAttribute(&tContext,&refdes2Attr);
	}
	if( isRefDes2 )
	{
		// Перемещение RefDes2 на место RefDes 
		if( moveRefDes2 )
		{
			int isFlipped = pMyComponent->isFlipped;
			// поворот
			refdes2Attr.rotationAng = refdesAttr.rotationAng;
			// выравнивание текста
			refdes2Attr.justPoint = refdesAttr.justPoint;
			// стиль текста
			refdes2Attr.textStyleId = refdesAttr.textStyleId;
			// слой
			if( isFlipped )
				refdes2Attr.layerId = DBX_LAYER_BOTTOM_SILK;
			else
				refdes2Attr.layerId = DBX_LAYER_TOP_SILK;
			// точка привязки текста
			refdes2Attr.refPoint.x = refdesAttr.refPoint.x;
			refdes2Attr.refPoint.y = refdesAttr.refPoint.y; 
			// видимость
			refdes2Attr.isVisible = 1;
			TModifyCompAttribute(&tContext,pMyComponent->refDes,&refdes2Attr);
		}
		// Видимость RefDes2
		refdes2Attr.isVisible = (visibleRefDes2)? 1 : 0;
		TModifyCompAttribute(&tContext, pMyComponent->refDes, &refdes2Attr);
	}
	else if( addRefDes2 )
	{	
		// Добавляем RefDes2 если его нет и требуется добавление
		int isFlipped = pMyComponent->isFlipped;
		// имя
		strcpy_s(refdes2Attr.type,DBX_MAX_NAME_LEN,attrRefDes2);
		refdes2Attr.typeLength = strlen(refdes2Attr.value);
		// значение (текст)
		strcpy_s(refdes2Attr.value,DBX_MAX_NAME_LEN, pMyComponent->refDes);
		refdes2Attr.valueLength = strlen(refdes2Attr.value);
		// выравнивание текста
		refdes2Attr.justPoint = refdesAttr.justPoint;
		// стиль текста
		refdes2Attr.textStyleId = refdesAttr.textStyleId;
		// слой
		if( isFlipped )
			refdes2Attr.layerId = DBX_LAYER_BOTTOM_SILK;
		else
			refdes2Attr.layerId = DBX_LAYER_TOP_SILK;
		// точка привязки текста
		refdes2Attr.refPoint.x = refdesAttr.refPoint.x;
		refdes2Attr.refPoint.y = refdesAttr.refPoint.y; 
		// угол поворота текста
		refdes2Attr.rotationAng = refdesAttr.rotationAng;
		// видимость
		refdes2Attr.isVisible = 1;
		// добавляю
		TAddCompAttribute(&tContext, pMyComponent->refDes,&refdes2Attr);
		// Видимость RefDes2
		refdes2Attr.isVisible = (visibleRefDes2)? 1 : 0;
		TModifyCompAttribute(&tContext, pMyComponent->refDes, &refdes2Attr);
	}
}

// добавляем RefDes2
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
			// получаю первый выделенный элемент
			tStatus = TGetFirstSelectedItem(&tContext, &myItem);
			while(tStatus == DBX_OK)
			{
				if( myItem.itemType == DBX_COMPONENT )
					processComponent(&myItem.component, addRefDes2, visibleRefDes2, moveRefDes2);
				// получаю следующий выделенный элемент
				tStatus = TGetNextSelectedItem(&tContext, &myItem);
			}
		}
		else
		{
			TComponent myComponent;	// комонент
			//получаю первый компонент
			tStatus = TGetFirstComponent(&tContext, &myComponent);
			while(tStatus == DBX_OK)
			{	
				processComponent(&myComponent, addRefDes2, visibleRefDes2, moveRefDes2);
				//получаю следующий компонент
				tStatus = TGetNextComponent(&tContext,&myComponent);
			}
		}
	}
	closeDesign();
	return true;
}

void CPcbAddRefDes2Dlg::OnBnClickedOk()
{
	// гашу кнопку
	OkButton.EnableWindow(false);
	// запускаем задачу
	processAddRefDes2((IsDlgButtonChecked(IDC_CHECK_ADDREFDES2) == BST_CHECKED),
		(IsDlgButtonChecked(IDC_CHECK_VISIBLEREFDES2) == BST_CHECKED),
		(IsDlgButtonChecked(IDC_CHECK_MOVEREFDES2) == BST_CHECKED),
		(IsDlgButtonChecked(IDC_CHECK_SELECTED) == BST_CHECKED)
		);
	//
	CDialogEx::OnOK();
}

