# Microsoft Developer Studio Project File - Name="RENUMBER" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RENUMBER - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Renumber.mak".
!MESSAGE 
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

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
# ADD CPP /nologo /Zp1 /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib acceldbx.lib /nologo /stack:0x2ee0 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib dbx32.lib /nologo /stack:0x2ee0 /subsystem:windows /machine:IX86

!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
# ADD CPP /nologo /Zp1 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib acceldbx.lib /nologo /stack:0x2ee0 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib dbx32.lib /nologo /stack:0x2ee0 /subsystem:windows /debug /machine:IX86

!ENDIF 

# Begin Target

# Name "RENUMBER - Win32 Release"
# Name "RENUMBER - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CMPLSTDL.CPP
# End Source File
# Begin Source File

SOURCE=.\COMPITEM.CPP
# End Source File
# Begin Source File

SOURCE=.\COMPLIST.CPP
# End Source File
# Begin Source File

SOURCE=.\DBXUTILS.CPP
# End Source File
# Begin Source File

SOURCE=.\RENUMBER.CPP
# End Source File
# Begin Source File

SOURCE=.\RENUMBER.DEF
# End Source File
# Begin Source File

SOURCE=.\RENUMBER.RC

!IF  "$(CFG)" == "RENUMBER - Win32 Release"

!ELSEIF  "$(CFG)" == "RENUMBER - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RENUMDLG.CPP
# End Source File
# Begin Source File

SOURCE=.\RFDESITM.CPP
# End Source File
# Begin Source File

SOURCE=.\RFDESLST.CPP
# End Source File
# Begin Source File

SOURCE=.\STAT_DLG.CPP
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# End Source File
# Begin Source File

SOURCE=.\UTILITY.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CMPLSTDL.H
# End Source File
# Begin Source File

SOURCE=.\COMPITEM.H
# End Source File
# Begin Source File

SOURCE=.\COMPLIST.H
# End Source File
# Begin Source File

SOURCE=.\DBXUTILS.H
# End Source File
# Begin Source File

SOURCE=.\RENUMBER.H
# End Source File
# Begin Source File

SOURCE=.\RENUMDLG.H
# End Source File
# Begin Source File

SOURCE=.\RFDESITM.H
# End Source File
# Begin Source File

SOURCE=.\RFDESLST.H
# End Source File
# Begin Source File

SOURCE=.\STAT_DLG.H
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\UTILITY.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RENUMBER.ICO
# End Source File
# End Group
# Begin Source File

SOURCE=.\RENUMBR2.RC
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Target
# End Project
