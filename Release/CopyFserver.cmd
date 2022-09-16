@echo off
REM ==============================================================
REM Сборки для PCAD-2006
REM ==============================================================
SET COPYTO="\\teconpc.local\teconsystems\Отдел РРЭА\PCAD_LIB\UTILS_2006"
copy *.exe %COPYTO%
copy *.readme %COPYTO%
copy *.dll %COPYTO%
REM copy *.ini %COPYTO%
SET COPYTO="\\teconpc.local\teconsystems\Отдел РРЭА\PCAD_LIB\static"
copy ..\ReleaseStatic\*.exe %COPYTO%
copy *.readme %COPYTO%
copy *.dll %COPYTO%
REM copy *.ini %COPYTO%
REM ==============================================================
REM Сборки для PCAD-2002
REM ==============================================================
SET COPYTO="\\teconpc.local\teconsystems\Отдел РРЭА\PCAD_LIB\UTILS_2002"
copy ..\Release2002\*.exe %COPYTO%
copy *.readme %COPYTO%
REM copy *.ini %COPYTO%
REM ==============================================================
pause