set VIEWER="C:\Program Files (x86)\Microsoft Office\Office14\ois.exe"

set OUTPUT=%TMP%\mytempfile-%RANDOM%-%TIME:~6,5%.png
set ERRORS=%TMP%\mytempfile-%RANDOM%-%TIME:~6,5%.txt

REM -query
call "%~dp0\..\..\tests\autotester\indigo-depict\x86\indigo-depict.exe" "%1" "%OUTPUT%"  2>"%ERRORS%"

for %%R in ("%ERRORS%") do if %%~zR equ 0 goto showpict

call "notepad.exe" "%ERRORS%"
goto errors

:showpict

call %VIEWER% "%OUTPUT%"

:errors

del "%OUTPUT%"
del "%ERRORS%"

