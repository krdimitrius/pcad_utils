@echo off
REM ==============================================================
REM ���ન ��� PCAD-2006
REM ==============================================================
SET COPYTO="\\teconpc.local\teconsystems\�⤥� ����\PCAD_LIB\UTILS_2006"
copy *.exe %COPYTO%
copy *.readme %COPYTO%
copy *.dll %COPYTO%
REM copy *.ini %COPYTO%
SET COPYTO="\\teconpc.local\teconsystems\�⤥� ����\PCAD_LIB\static"
copy ..\ReleaseStatic\*.exe %COPYTO%
copy *.readme %COPYTO%
copy *.dll %COPYTO%
REM copy *.ini %COPYTO%
REM ==============================================================
REM ���ન ��� PCAD-2002
REM ==============================================================
SET COPYTO="\\teconpc.local\teconsystems\�⤥� ����\PCAD_LIB\UTILS_2002"
copy ..\Release2002\*.exe %COPYTO%
copy *.readme %COPYTO%
REM copy *.ini %COPYTO%
REM ==============================================================
pause