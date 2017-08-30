; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCmpLstDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "renumber.h"
LastPage=0

ClassCount=8
Class1=CDlgappApp
Class2=CAboutDlg
Class3=CDlgappDlg

ResourceCount=6
Resource1=IDD_DIALOG_STATUS_BOX
Resource2=IDD_ABOUTBOX
Resource3=IDR_MENU1
Resource4="IDD_DIALOG_STATUS_BOX"
Resource5=IDD_RENUMBER_DLG
Class4=StatusDlg
Class5=RenumberDlg
Class6=SetStartIndexDlg
Class7=CCmpLstDlg
Class8=CEditNumber
Resource6=IDD_COMPLIST

[CLS:CDlgappApp]
Type=0
HeaderFile=renumber.h
ImplementationFile=renumber.cpp
Filter=N
LastObject=IDM_FILE_EXIT

[CLS:CAboutDlg]
Type=0
HeaderFile=dlgdlg.h
ImplementationFile=dlgdlg.cpp
LastObject=IDOK
Filter=D

[CLS:CDlgappDlg]
Type=0
HeaderFile=dlgdlg.h
ImplementationFile=dlgdlg.cpp
Filter=D
LastObject=CDlgappDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MENU1]
Type=1
Command1=IDM_FILE_EXIT
Command2=IDM_HELP_ABOUT
CommandCount=2

[DLG:"IDD_DIALOG_STATUS_BOX"]
Type=1
ControlCount=2
Control1=IDC_TEXT_STATUS,static,1342308353
Control2=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_STATUS_BOX]
Type=1
Class=StatusDlg
ControlCount=2
Control1=IDC_TEXT_STATUS,static,1342308353
Control2=IDPB_CANCEL,button,1342242816

[CLS:StatusDlg]
Type=0
HeaderFile=stat_dlg.h
ImplementationFile=stat_dlg.cpp
Filter=D
LastObject=IDPB_CANCEL

[DLG:IDD_RENUMBER_DLG]
Type=1
Class=RenumberDlg
ControlCount=26
Control1=IDPB_RENUMBER,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDLB_PREFIX_INDEX,listbox,1352730755
Control4=IDEB_START_INDEX,edit,1350631424
Control5=IDPB_SET_INDEX,button,1342242816
Control6=IDPB_SELECT_ALL,button,1342242816
Control7=IDPB_CLEAR_ALL,button,1342242816
Control8=IDPB_REFRESH,button,1342242816
Control9=IDEB_PASS_WIDTH,edit,1350631424
Control10=IDRB_FLIPPEDOPTS_ALL,button,1342308356
Control11=IDRB_FLIPPEDOPTS_TOPBOT,button,1342308356
Control12=IDRB_FLIPPEDOPTS_TOPONLY,button,1342308356
Control13=IDRB_FLIPPEDOPTS_BOTONLY,button,1342308356
Control14=IDRB_LFT_RGT_TOP_BOT,button,1342308356
Control15=IDRB_TOP_BOT_LFT_RGT,button,1342373892
Control16=IDRB_LFT_RGT_BOT_TOP,button,1342373892
Control17=IDRB_BOT_TOP_LFT_RGT,button,1342373892
Control18=IDC_STATIC,static,1342308352
Control19=IDGB_RENUM_DIR,button,1342177287
Control20=IDC_STATIC,static,1342308352
Control21=IDST_DESIGN_NAME,static,1342177408
Control22=IDC_STATIC,static,1342308352
Control23=IDGB_FLIPPED_OPTNS,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342177283
Control26=IDST_NUMCOMPS,static,1342177280

[CLS:RenumberDlg]
Type=0
HeaderFile=dlgdlg.h
ImplementationFile=dlgdlg.cpp
Filter=D
LastObject=IDCANCEL

[CLS:SetStartIndexDlg]
Type=0
HeaderFile=setstart.h
ImplementationFile=setstart.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_COMPLIST]
Type=1
Class=CCmpLstDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDLB_COMPLIST,listbox,1353777536
Control3=IDST_LBHDR_REFDES,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDST_LBHDR_TYPE,static,1342308352
Control6=IDST_LBHDR_LOC,static,1342308352

[CLS:CCmpLstDlg]
Type=0
HeaderFile=cmplstdl.h
ImplementationFile=cmplstdl.cpp
Filter=D
LastObject=IDST_LBHDR_TYPE

[CLS:CEditNumber]
Type=0
HeaderFile=editnumb.h
ImplementationFile=editnumb.cpp
Filter=W

