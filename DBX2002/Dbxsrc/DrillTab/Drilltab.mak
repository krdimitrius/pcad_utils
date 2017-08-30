# Microsoft Developer Studio Generated NMAKE File, Based on Drilltab.dsp
!IF "$(CFG)" == ""
CFG=Drilltab - Win32 Release
!MESSAGE No configuration specified. Defaulting to Drilltab - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Drilltab - Win32 Release" && "$(CFG)" !=\
 "Drilltab - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Drilltab.mak" CFG="Drilltab - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Drilltab - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Drilltab - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Drilltab - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Drilltab.exe"

!ELSE 

ALL : "$(OUTDIR)\Drilltab.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Aboutdlg.obj"
	-@erase "$(INTDIR)\Dbxutils.obj"
	-@erase "$(INTDIR)\Drilldlg.obj"
	-@erase "$(INTDIR)\Drilltab.obj"
	-@erase "$(INTDIR)\Drilltab.res"
	-@erase "$(INTDIR)\Dtutils.obj"
	-@erase "$(INTDIR)\Statdlg.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Drilltab.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)\Drilltab.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Drilltab.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Drilltab.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dbx32.lib widge32.lib /nologo /stack:0x5000 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\Drilltab.pdb" /machine:IX86\
 /def:".\Drilltab.def" /out:"$(OUTDIR)\Drilltab.exe" 
DEF_FILE= \
	".\Drilltab.def"
LINK32_OBJS= \
	"$(INTDIR)\Aboutdlg.obj" \
	"$(INTDIR)\Dbxutils.obj" \
	"$(INTDIR)\Drilldlg.obj" \
	"$(INTDIR)\Drilltab.obj" \
	"$(INTDIR)\Drilltab.res" \
	"$(INTDIR)\Dtutils.obj" \
	"$(INTDIR)\Statdlg.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\Drilltab.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Drilltab.exe"

!ELSE 

ALL : "$(OUTDIR)\Drilltab.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Aboutdlg.obj"
	-@erase "$(INTDIR)\Dbxutils.obj"
	-@erase "$(INTDIR)\Drilldlg.obj"
	-@erase "$(INTDIR)\Drilltab.obj"
	-@erase "$(INTDIR)\Drilltab.res"
	-@erase "$(INTDIR)\Dtutils.obj"
	-@erase "$(INTDIR)\Statdlg.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Drilltab.exe"
	-@erase "$(OUTDIR)\Drilltab.ilk"
	-@erase "$(OUTDIR)\Drilltab.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Drilltab.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Drilltab.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Drilltab.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dbx32.lib widge32.lib /nologo /stack:0x5000 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\Drilltab.pdb" /debug /machine:IX86\
 /def:".\Drilltab.def" /out:"$(OUTDIR)\Drilltab.exe" 
DEF_FILE= \
	".\Drilltab.def"
LINK32_OBJS= \
	"$(INTDIR)\Aboutdlg.obj" \
	"$(INTDIR)\Dbxutils.obj" \
	"$(INTDIR)\Drilldlg.obj" \
	"$(INTDIR)\Drilltab.obj" \
	"$(INTDIR)\Drilltab.res" \
	"$(INTDIR)\Dtutils.obj" \
	"$(INTDIR)\Statdlg.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\Drilltab.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Drilltab - Win32 Release" || "$(CFG)" ==\
 "Drilltab - Win32 Debug"
SOURCE=.\Aboutdlg.cpp

!IF  "$(CFG)" == "Drilltab - Win32 Release"

DEP_CPP_ABOUT=\
	".\Aboutdlg.h"\
	".\Drilltab.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Aboutdlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

DEP_CPP_ABOUT=\
	".\Aboutdlg.h"\
	".\Drilltab.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Aboutdlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"


!ENDIF 

SOURCE=.\Dbxutils.cpp

!IF  "$(CFG)" == "Drilltab - Win32 Release"

DEP_CPP_DBXUT=\
	".\Dbx32.h"\
	".\Dbxutils.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Dbxutils.obj" : $(SOURCE) $(DEP_CPP_DBXUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

DEP_CPP_DBXUT=\
	".\Dbx32.h"\
	".\Dbxutils.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Dbxutils.obj" : $(SOURCE) $(DEP_CPP_DBXUT) "$(INTDIR)"


!ENDIF 

SOURCE=.\Drilldlg.cpp

!IF  "$(CFG)" == "Drilltab - Win32 Release"

DEP_CPP_DRILL=\
	".\Aboutdlg.h"\
	".\Dbx32.h"\
	".\Dbxutils.h"\
	".\Drilldlg.h"\
	".\Drilltab.h"\
	".\Dtutils.h"\
	".\Statdlg.h"\
	".\stdafx.h"\
	".\Widgets.h"\
	

"$(INTDIR)\Drilldlg.obj" : $(SOURCE) $(DEP_CPP_DRILL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

DEP_CPP_DRILL=\
	".\Aboutdlg.h"\
	".\Dbx32.h"\
	".\Dbxutils.h"\
	".\Drilldlg.h"\
	".\Drilltab.h"\
	".\Dtutils.h"\
	".\Statdlg.h"\
	".\stdafx.h"\
	".\Widgets.h"\
	

"$(INTDIR)\Drilldlg.obj" : $(SOURCE) $(DEP_CPP_DRILL) "$(INTDIR)"


!ENDIF 

SOURCE=.\Drilltab.cpp

!IF  "$(CFG)" == "Drilltab - Win32 Release"

DEP_CPP_DRILLT=\
	".\Dbx32.h"\
	".\Drilldlg.h"\
	".\Drilltab.h"\
	".\stdafx.h"\
	".\Widgets.h"\
	

"$(INTDIR)\Drilltab.obj" : $(SOURCE) $(DEP_CPP_DRILLT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

DEP_CPP_DRILLT=\
	".\Dbx32.h"\
	".\Drilldlg.h"\
	".\Drilltab.h"\
	".\stdafx.h"\
	".\Widgets.h"\
	

"$(INTDIR)\Drilltab.obj" : $(SOURCE) $(DEP_CPP_DRILLT) "$(INTDIR)"


!ENDIF 

SOURCE=.\Drilltab.rc
DEP_RSC_DRILLTA=\
	".\DRILLTAB.GRS"\
	".\res\Drilltab.rc2"\
	".\res\Drtab1.ico"\
	".\res\Drtab2.ico"\
	".\res\Drtab3.ico"\
	

"$(INTDIR)\Drilltab.res" : $(SOURCE) $(DEP_RSC_DRILLTA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Dtutils.cpp

!IF  "$(CFG)" == "Drilltab - Win32 Release"

DEP_CPP_DTUTI=\
	".\Dbxutils.h"\
	".\Dtutils.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Dtutils.obj" : $(SOURCE) $(DEP_CPP_DTUTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

DEP_CPP_DTUTI=\
	".\Dbxutils.h"\
	".\Dtutils.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Dtutils.obj" : $(SOURCE) $(DEP_CPP_DTUTI) "$(INTDIR)"


!ENDIF 

SOURCE=.\Statdlg.cpp

!IF  "$(CFG)" == "Drilltab - Win32 Release"

DEP_CPP_STATD=\
	".\Drilltab.h"\
	".\Statdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Statdlg.obj" : $(SOURCE) $(DEP_CPP_STATD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

DEP_CPP_STATD=\
	".\Drilltab.h"\
	".\Statdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Statdlg.obj" : $(SOURCE) $(DEP_CPP_STATD) "$(INTDIR)"


!ENDIF 

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"



!ENDIF 

