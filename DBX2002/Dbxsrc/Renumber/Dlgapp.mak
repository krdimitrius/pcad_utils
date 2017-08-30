# Microsoft Visual C++ generated build script - Do not modify

PROJ = DLGAPP
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\TANGO3\UTIL\DBXAPPS\RENUMBER\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /Zp1 /W3 /Zi /AL /YX /Od /D "_DEBUG" /GA /Fd"DLGAPP.PDB"   /Fp"DLGAPP.PCH"
CFLAGS_R_WEXE = /nologo /Gs /G2 /Zp1 /W3 /AL /YX /O1 /D "NDEBUG" /GA /Fp"DLGAPP.PCH"
LFLAGS_D_WEXE = /NOLOGO /NOD /NOE /PACKC:61440 /STACK:12000 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /NOE /PACKC:61440 /STACK:12000 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = lafxcwd oldnames libw llibcew acceldbx ctl3dv2 commdlg.lib shell.lib 
LIBS_R_WEXE = lafxcw oldnames libw llibcew acceldbx commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = DLGAPP.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		DLGAPP.SBR \
		DLGDLG.SBR \
		COMPITEM.SBR \
		DBXUTILS.SBR \
		STAT_DLG.SBR \
		COMPLIST.SBR \
		UTILITY.SBR \
		CMPLSTDL.SBR \
		RFDESITM.SBR \
		RFDESLST.SBR


DLGAPP_RCDEP = c:\tango3\util\dbxapps\renumber\res\renumber.ico \
	c:\tango3\util\dbxapps\renumber\res\dlgapp.rc2


STDAFX_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h


DLGAPP_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\dlgapp.h \
	c:\tango3\util\dbxapps\renumber\dlgdlg.h \
	c:\tango3\util\dbxapps\renumber\complist.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h \
	c:\tango3\util\dbxapps\renumber\compitem.h \
	c:\tango3\util\dbxapps\renumber\rfdeslst.h \
	c:\tango3\util\dbxapps\renumber\rfdesitm.h \
	c:\tango3\util\dbxapps\renumber\utility.h


DLGDLG_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\compitem.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h \
	c:\tango3\util\dbxapps\renumber\complist.h \
	c:\tango3\util\dbxapps\renumber\rfdesitm.h \
	c:\tango3\util\dbxapps\renumber\dbxutils.h \
	c:\tango3\util\dbxapps\renumber\dlgapp.h \
	c:\tango3\util\dbxapps\renumber\dlgdlg.h \
	c:\tango3\util\dbxapps\renumber\rfdeslst.h \
	c:\tango3\util\dbxapps\renumber\utility.h \
	c:\tango3\util\dbxapps\renumber\stat_dlg.h \
	c:\tango3\util\dbxapps\renumber\cmplstdl.h


COMPITEM_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\compitem.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h


DBXUTILS_DEP = c:\tango3\util\dbxapps\renumber\acceldbx.h


STAT_DLG_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\dlgdlg.h \
	c:\tango3\util\dbxapps\renumber\complist.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h \
	c:\tango3\util\dbxapps\renumber\compitem.h \
	c:\tango3\util\dbxapps\renumber\rfdeslst.h \
	c:\tango3\util\dbxapps\renumber\rfdesitm.h \
	c:\tango3\util\dbxapps\renumber\utility.h \
	c:\tango3\util\dbxapps\renumber\stat_dlg.h


COMPLIST_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\compitem.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h \
	c:\tango3\util\dbxapps\renumber\complist.h


UTILITY_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\utility.h


CMPLSTDL_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\dlgapp.h \
	c:\tango3\util\dbxapps\renumber\cmplstdl.h \
	c:\tango3\util\dbxapps\renumber\complist.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h \
	c:\tango3\util\dbxapps\renumber\compitem.h


RFDESITM_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\rfdesitm.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h


RFDESLST_DEP = c:\tango3\util\dbxapps\renumber\stdafx.h \
	c:\tango3\util\dbxapps\renumber\rfdeslst.h \
	c:\tango3\util\dbxapps\renumber\acceldbx.h \
	c:\tango3\util\dbxapps\renumber\rfdesitm.h


all:	$(PROJ).EXE

DLGAPP.RES:	DLGAPP.RC $(DLGAPP_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DLGAPP.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

DLGAPP.OBJ:	DLGAPP.CPP $(DLGAPP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLGAPP.CPP

DLGDLG.OBJ:	DLGDLG.CPP $(DLGDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLGDLG.CPP

COMPITEM.OBJ:	COMPITEM.CPP $(COMPITEM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMPITEM.CPP

DBXUTILS.OBJ:	DBXUTILS.CPP $(DBXUTILS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DBXUTILS.CPP

STAT_DLG.OBJ:	STAT_DLG.CPP $(STAT_DLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STAT_DLG.CPP

COMPLIST.OBJ:	COMPLIST.CPP $(COMPLIST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMPLIST.CPP

UTILITY.OBJ:	UTILITY.CPP $(UTILITY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c UTILITY.CPP

CMPLSTDL.OBJ:	CMPLSTDL.CPP $(CMPLSTDL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CMPLSTDL.CPP

RFDESITM.OBJ:	RFDESITM.CPP $(RFDESITM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RFDESITM.CPP

RFDESLST.OBJ:	RFDESLST.CPP $(RFDESLST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RFDESLST.CPP


$(PROJ).EXE::	DLGAPP.RES

$(PROJ).EXE::	STDAFX.OBJ DLGAPP.OBJ DLGDLG.OBJ COMPITEM.OBJ DBXUTILS.OBJ STAT_DLG.OBJ \
	COMPLIST.OBJ UTILITY.OBJ CMPLSTDL.OBJ RFDESITM.OBJ RFDESLST.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
DLGAPP.OBJ +
DLGDLG.OBJ +
COMPITEM.OBJ +
DBXUTILS.OBJ +
STAT_DLG.OBJ +
COMPLIST.OBJ +
UTILITY.OBJ +
CMPLSTDL.OBJ +
RFDESITM.OBJ +
RFDESLST.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc15\lib\+
c:\msvc15\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DLGAPP.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	DLGAPP.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DLGAPP.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
