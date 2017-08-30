# Microsoft Developer Studio Project File - Name="Drilltab" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Drilltab - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Drilltab.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Drilltab - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib dbx32.lib widge32.lib mfcwdgl.lib /nologo /stack:0x5000 /subsystem:windows /machine:IX86
# ADD LINK32 ..\Common\Dbx32.lib ..\Common\Widge32.lib /nologo /stack:0x5000 /subsystem:windows /machine:IX86

!ELSEIF  "$(CFG)" == "Drilltab - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
# ADD CPP /nologo /Zp1 /MTd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib dbx32.lib widge32.lib mfcwdgl.lib /nologo /stack:0x5000 /subsystem:windows /debug /machine:IX86
# ADD LINK32 ..\Common\Dbx32.lib ..\Common\Widge32.lib /nologo /stack:0x5000 /subsystem:windows /debug /machine:IX86

!ENDIF 

# Begin Target

# Name "Drilltab - Win32 Release"
# Name "Drilltab - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Aboutdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\DbxUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\Drilldlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Drilltab.cpp
# End Source File
# Begin Source File

SOURCE=.\Drilltab.def
# End Source File
# Begin Source File

SOURCE=.\Drilltab.rc
# End Source File
# Begin Source File

SOURCE=.\Dtutils.cpp
# End Source File
# Begin Source File

SOURCE=.\Statdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Stdafx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Aboutdlg.h
# End Source File
# Begin Source File

SOURCE=..\Common\Dbx32.h
# End Source File
# Begin Source File

SOURCE=..\Common\DbxUtils.h
# End Source File
# Begin Source File

SOURCE=.\Drilldlg.h
# End Source File
# Begin Source File

SOURCE=.\Drilltab.h
# End Source File
# Begin Source File

SOURCE=.\Dtutils.h
# End Source File
# Begin Source File

SOURCE=.\Statdlg.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=..\Common\Widgets.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Drilltab.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Drtab1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Drtab2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Drtab3.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\DRILLTAB.GRS
# End Source File
# End Target
# End Project
