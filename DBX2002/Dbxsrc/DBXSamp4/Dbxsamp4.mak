# Microsoft Developer Studio Generated NMAKE File, Based on Dbxsamp4.dsp
!IF "$(CFG)" == ""
CFG=DBXSAMP4 - Win32 Release
!MESSAGE No configuration specified. Defaulting to DBXSAMP4 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DBXSAMP4 - Win32 Release" && "$(CFG)" !=\
 "DBXSAMP4 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dbxsamp4.mak" CFG="DBXSAMP4 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DBXSAMP4 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DBXSAMP4 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DBXSAMP4 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Dbxsamp4.exe"

!ELSE 

ALL : "$(OUTDIR)\Dbxsamp4.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DBXSAMP4.OBJ"
	-@erase "$(INTDIR)\DBXSAMP4.res"
	-@erase "$(INTDIR)\DBXsamp4Doc.obj"
	-@erase "$(INTDIR)\DBXSAVW.OBJ"
	-@erase "$(INTDIR)\DBXUTILS.OBJ"
	-@erase "$(INTDIR)\MAINFRM.OBJ"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Dbxsamp4.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MT /W3 /Gi /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)\Dbxsamp4.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DBXSAMP4.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Dbxsamp4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dbx32.lib /nologo /stack:0x2800 /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\Dbxsamp4.pdb" /machine:IX86 /out:"$(OUTDIR)\Dbxsamp4.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DBXSAMP4.OBJ" \
	"$(INTDIR)\DBXSAMP4.res" \
	"$(INTDIR)\DBXsamp4Doc.obj" \
	"$(INTDIR)\DBXSAVW.OBJ" \
	"$(INTDIR)\DBXUTILS.OBJ" \
	"$(INTDIR)\MAINFRM.OBJ" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\Dbxsamp4.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DBXSAMP4 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Dbxsamp4.exe"

!ELSE 

ALL : "$(OUTDIR)\Dbxsamp4.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DBXSAMP4.OBJ"
	-@erase "$(INTDIR)\DBXSAMP4.res"
	-@erase "$(INTDIR)\DBXsamp4Doc.obj"
	-@erase "$(INTDIR)\DBXSAVW.OBJ"
	-@erase "$(INTDIR)\DBXUTILS.OBJ"
	-@erase "$(INTDIR)\MAINFRM.OBJ"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Dbxsamp4.exe"
	-@erase "$(OUTDIR)\Dbxsamp4.ilk"
	-@erase "$(OUTDIR)\Dbxsamp4.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MTd /W3 /Gm /Gi /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Dbxsamp4.pch" /YX /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DBXSAMP4.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Dbxsamp4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dbx32.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\Dbxsamp4.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)\Dbxsamp4.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DBXSAMP4.OBJ" \
	"$(INTDIR)\DBXSAMP4.res" \
	"$(INTDIR)\DBXsamp4Doc.obj" \
	"$(INTDIR)\DBXSAVW.OBJ" \
	"$(INTDIR)\DBXUTILS.OBJ" \
	"$(INTDIR)\MAINFRM.OBJ" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\Dbxsamp4.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "DBXSAMP4 - Win32 Release" || "$(CFG)" ==\
 "DBXSAMP4 - Win32 Debug"
SOURCE=.\DBXSAMP4.CPP

!IF  "$(CFG)" == "DBXSAMP4 - Win32 Release"

DEP_CPP_DBXSA=\
	".\dbx32.h"\
	".\dbxsamp4.h"\
	".\dbxsamp4doc.h"\
	".\dbxsavw.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXSAMP4.OBJ" : $(SOURCE) $(DEP_CPP_DBXSA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DBXSAMP4 - Win32 Debug"

DEP_CPP_DBXSA=\
	".\dbx32.h"\
	".\dbxsamp4.h"\
	".\dbxsamp4doc.h"\
	".\dbxsavw.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXSAMP4.OBJ" : $(SOURCE) $(DEP_CPP_DBXSA) "$(INTDIR)"


!ENDIF 

SOURCE=.\DBXSAMP4.RC

"$(INTDIR)\DBXSAMP4.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DBXsamp4Doc.cpp

!IF  "$(CFG)" == "DBXSAMP4 - Win32 Release"

DEP_CPP_DBXSAM=\
	".\dbxsamp4.h"\
	".\dbxsamp4doc.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXsamp4Doc.obj" : $(SOURCE) $(DEP_CPP_DBXSAM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DBXSAMP4 - Win32 Debug"

DEP_CPP_DBXSAM=\
	".\dbxsamp4.h"\
	".\dbxsamp4doc.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXsamp4Doc.obj" : $(SOURCE) $(DEP_CPP_DBXSAM) "$(INTDIR)"


!ENDIF 

SOURCE=.\DBXSAVW.CPP

!IF  "$(CFG)" == "DBXSAMP4 - Win32 Release"

DEP_CPP_DBXSAV=\
	".\dbx32.h"\
	".\dbxsamp4.h"\
	".\dbxsavw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXSAVW.OBJ" : $(SOURCE) $(DEP_CPP_DBXSAV) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DBXSAMP4 - Win32 Debug"

DEP_CPP_DBXSAV=\
	".\dbx32.h"\
	".\dbxsamp4.h"\
	".\dbxsavw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXSAVW.OBJ" : $(SOURCE) $(DEP_CPP_DBXSAV) "$(INTDIR)"


!ENDIF 

SOURCE=.\DBXUTILS.CPP

!IF  "$(CFG)" == "DBXSAMP4 - Win32 Release"

DEP_CPP_DBXUT=\
	".\dbx32.h"\
	".\dbxutils.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXUTILS.OBJ" : $(SOURCE) $(DEP_CPP_DBXUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DBXSAMP4 - Win32 Debug"

DEP_CPP_DBXUT=\
	".\dbx32.h"\
	".\dbxutils.h"\
	".\stdafx.h"\
	

"$(INTDIR)\DBXUTILS.OBJ" : $(SOURCE) $(DEP_CPP_DBXUT) "$(INTDIR)"


!ENDIF 

SOURCE=.\MAINFRM.CPP

!IF  "$(CFG)" == "DBXSAMP4 - Win32 Release"

DEP_CPP_MAINF=\
	".\dbxsamp4.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	

"$(INTDIR)\MAINFRM.OBJ" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DBXSAMP4 - Win32 Debug"

DEP_CPP_MAINF=\
	".\dbxsamp4.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	

"$(INTDIR)\MAINFRM.OBJ" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ENDIF 

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"



!ENDIF 

