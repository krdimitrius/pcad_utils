# Microsoft Developer Studio Generated NMAKE File, Based on Renumber.dsp
!IF "$(CFG)" == ""
CFG=RENUMBER - Win32 Release
!MESSAGE No configuration specified. Defaulting to RENUMBER - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "RENUMBER - Win32 Release" && "$(CFG)" !=\
 "RENUMBER - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Renumber.mak" CFG="RENUMBER - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RENUMBER - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RENUMBER - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Renumber.exe"

!ELSE 

ALL : "$(OUTDIR)\Renumber.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CMPLSTDL.OBJ"
	-@erase "$(INTDIR)\COMPITEM.OBJ"
	-@erase "$(INTDIR)\COMPLIST.OBJ"
	-@erase "$(INTDIR)\DBXUTILS.OBJ"
	-@erase "$(INTDIR)\RENUMBER.OBJ"
	-@erase "$(INTDIR)\RENUMBER.res"
	-@erase "$(INTDIR)\RENUMDLG.OBJ"
	-@erase "$(INTDIR)\RFDESITM.OBJ"
	-@erase "$(INTDIR)\RFDESLST.OBJ"
	-@erase "$(INTDIR)\STAT_DLG.OBJ"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\UTILITY.OBJ"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Renumber.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)\Renumber.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RENUMBER.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Renumber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oldnames.lib dbx32.lib /nologo /stack:0x2ee0 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\Renumber.pdb" /machine:IX86\
 /def:".\RENUMBER.DEF" /out:"$(OUTDIR)\Renumber.exe" 
DEF_FILE= \
	".\RENUMBER.DEF"
LINK32_OBJS= \
	"$(INTDIR)\CMPLSTDL.OBJ" \
	"$(INTDIR)\COMPITEM.OBJ" \
	"$(INTDIR)\COMPLIST.OBJ" \
	"$(INTDIR)\DBXUTILS.OBJ" \
	"$(INTDIR)\RENUMBER.OBJ" \
	"$(INTDIR)\RENUMBER.res" \
	"$(INTDIR)\RENUMDLG.OBJ" \
	"$(INTDIR)\RFDESITM.OBJ" \
	"$(INTDIR)\RFDESLST.OBJ" \
	"$(INTDIR)\STAT_DLG.OBJ" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\UTILITY.OBJ"

"$(OUTDIR)\Renumber.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Renumber.exe"

!ELSE 

ALL : "$(OUTDIR)\Renumber.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CMPLSTDL.OBJ"
	-@erase "$(INTDIR)\COMPITEM.OBJ"
	-@erase "$(INTDIR)\COMPLIST.OBJ"
	-@erase "$(INTDIR)\DBXUTILS.OBJ"
	-@erase "$(INTDIR)\RENUMBER.OBJ"
	-@erase "$(INTDIR)\RENUMBER.res"
	-@erase "$(INTDIR)\RENUMDLG.OBJ"
	-@erase "$(INTDIR)\RFDESITM.OBJ"
	-@erase "$(INTDIR)\RFDESLST.OBJ"
	-@erase "$(INTDIR)\STAT_DLG.OBJ"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\UTILITY.OBJ"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Renumber.exe"
	-@erase "$(OUTDIR)\Renumber.ilk"
	-@erase "$(OUTDIR)\Renumber.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Renumber.pch" /YX /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RENUMBER.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Renumber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oldnames.lib dbx32.lib /nologo /stack:0x2ee0 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\Renumber.pdb" /debug /machine:IX86\
 /def:".\RENUMBER.DEF" /out:"$(OUTDIR)\Renumber.exe" 
DEF_FILE= \
	".\RENUMBER.DEF"
LINK32_OBJS= \
	"$(INTDIR)\CMPLSTDL.OBJ" \
	"$(INTDIR)\COMPITEM.OBJ" \
	"$(INTDIR)\COMPLIST.OBJ" \
	"$(INTDIR)\DBXUTILS.OBJ" \
	"$(INTDIR)\RENUMBER.OBJ" \
	"$(INTDIR)\RENUMBER.res" \
	"$(INTDIR)\RENUMDLG.OBJ" \
	"$(INTDIR)\RFDESITM.OBJ" \
	"$(INTDIR)\RFDESLST.OBJ" \
	"$(INTDIR)\STAT_DLG.OBJ" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\UTILITY.OBJ"

"$(OUTDIR)\Renumber.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "RENUMBER - Win32 Release" || "$(CFG)" ==\
 "RENUMBER - Win32 Debug"
SOURCE=.\CMPLSTDL.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_CMPLS=\
	".\CMPLSTDL.H"\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\RENUMBER.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\CMPLSTDL.OBJ" : $(SOURCE) $(DEP_CPP_CMPLS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_CMPLS=\
	".\CMPLSTDL.H"\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\RENUMBER.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\CMPLSTDL.OBJ" : $(SOURCE) $(DEP_CPP_CMPLS) "$(INTDIR)"


!ENDIF 

SOURCE=.\COMPITEM.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_COMPI=\
	".\COMPITEM.H"\
	".\dbx32.h"\
	".\STDAFX.H"\
	

"$(INTDIR)\COMPITEM.OBJ" : $(SOURCE) $(DEP_CPP_COMPI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_COMPI=\
	".\COMPITEM.H"\
	".\dbx32.h"\
	".\STDAFX.H"\
	

"$(INTDIR)\COMPITEM.OBJ" : $(SOURCE) $(DEP_CPP_COMPI) "$(INTDIR)"


!ENDIF 

SOURCE=.\COMPLIST.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_COMPL=\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\STDAFX.H"\
	

"$(INTDIR)\COMPLIST.OBJ" : $(SOURCE) $(DEP_CPP_COMPL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_COMPL=\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\STDAFX.H"\
	

"$(INTDIR)\COMPLIST.OBJ" : $(SOURCE) $(DEP_CPP_COMPL) "$(INTDIR)"


!ENDIF 

SOURCE=.\DBXUTILS.CPP
DEP_CPP_DBXUT=\
	".\dbx32.h"\
	".\STDAFX.H"\
	

"$(INTDIR)\DBXUTILS.OBJ" : $(SOURCE) $(DEP_CPP_DBXUT) "$(INTDIR)"


SOURCE=.\RENUMBER.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_RENUM=\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\RENUMBER.H"\
	".\RENUMDLG.H"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STDAFX.H"\
	".\UTILITY.H"\
	

"$(INTDIR)\RENUMBER.OBJ" : $(SOURCE) $(DEP_CPP_RENUM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_RENUM=\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\RENUMBER.H"\
	".\RENUMDLG.H"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STDAFX.H"\
	".\UTILITY.H"\
	

"$(INTDIR)\RENUMBER.OBJ" : $(SOURCE) $(DEP_CPP_RENUM) "$(INTDIR)"


!ENDIF 

SOURCE=.\RENUMBER.RC
DEP_RSC_RENUMB=\
	".\RENUMBER.ICO"\
	".\RENUMBR2.RC"\
	

"$(INTDIR)\RENUMBER.res" : $(SOURCE) $(DEP_RSC_RENUMB) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\RENUMDLG.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_RENUMD=\
	".\CMPLSTDL.H"\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\DBXUTILS.H"\
	".\RENUMBER.H"\
	".\RENUMDLG.H"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STAT_DLG.H"\
	".\STDAFX.H"\
	".\UTILITY.H"\
	

"$(INTDIR)\RENUMDLG.OBJ" : $(SOURCE) $(DEP_CPP_RENUMD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_RENUMD=\
	".\CMPLSTDL.H"\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\DBXUTILS.H"\
	".\RENUMBER.H"\
	".\RENUMDLG.H"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STAT_DLG.H"\
	".\STDAFX.H"\
	".\UTILITY.H"\
	

"$(INTDIR)\RENUMDLG.OBJ" : $(SOURCE) $(DEP_CPP_RENUMD) "$(INTDIR)"


!ENDIF 

SOURCE=.\RFDESITM.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_RFDES=\
	".\dbx32.h"\
	".\RFDESITM.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\RFDESITM.OBJ" : $(SOURCE) $(DEP_CPP_RFDES) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_RFDES=\
	".\dbx32.h"\
	".\RFDESITM.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\RFDESITM.OBJ" : $(SOURCE) $(DEP_CPP_RFDES) "$(INTDIR)"


!ENDIF 

SOURCE=.\RFDESLST.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_RFDESL=\
	".\dbx32.h"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\RFDESLST.OBJ" : $(SOURCE) $(DEP_CPP_RFDESL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_RFDESL=\
	".\dbx32.h"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\RFDESLST.OBJ" : $(SOURCE) $(DEP_CPP_RFDESL) "$(INTDIR)"


!ENDIF 

SOURCE=.\STAT_DLG.CPP

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

DEP_CPP_STAT_=\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\RENUMDLG.H"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STAT_DLG.H"\
	".\STDAFX.H"\
	".\UTILITY.H"\
	

"$(INTDIR)\STAT_DLG.OBJ" : $(SOURCE) $(DEP_CPP_STAT_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

DEP_CPP_STAT_=\
	".\COMPITEM.H"\
	".\COMPLIST.H"\
	".\dbx32.h"\
	".\RENUMDLG.H"\
	".\RFDESITM.H"\
	".\RFDESLST.H"\
	".\STAT_DLG.H"\
	".\STDAFX.H"\
	".\UTILITY.H"\
	

"$(INTDIR)\STAT_DLG.OBJ" : $(SOURCE) $(DEP_CPP_STAT_) "$(INTDIR)"


!ENDIF 

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\STDAFX.H"\
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


SOURCE=.\UTILITY.CPP
DEP_CPP_UTILI=\
	".\STDAFX.H"\
	".\UTILITY.H"\
	

"$(INTDIR)\UTILITY.OBJ" : $(SOURCE) $(DEP_CPP_UTILI) "$(INTDIR)"


SOURCE=.\RENUMBR2.RC

!ENDIF 

