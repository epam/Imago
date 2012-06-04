@echo -------------------Updating variables-------------------

set FUZZ_LEVEL_FILTERS=0.01
set FUZZ_LEVEL_OTHER=0.1
set PYTHON_DIR=C:\Python27
set CPP_COMPILER="C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\devenv.exe"
set SRC_IMAGES_PATH="K:\Projects\OpenSource\flamingo-dev\progress\test-tools-dev\images"

@SET PATH=%PATH%;%PYTHON_DIR%
@SET PYTHON_EXE="%PYTHON_DIR%\python.exe"
@SET TIMELIMIT="%~dp0\tools\timelimit\Release\timelimit.exe"
@SET CONSTFUZZ="%~dp0\tools\constfuzzer\Release\constfuzzer.exe"
@SET IMAGO_EXE="%~dp0\tests\rc\Release\test.rc.exe"
@SET CONSTS_SRC1="%~dp0\imago\src\settings_filters.inc"
@SET CONSTS_SRC2="%~dp0\imago\src\settings_handwritten.inc"
@SET CONSTS_SRC3="%~dp0\imago\src\settings_highres.inc"
@SET CONSTS_SRC4="%~dp0\imago\src\settings_scanned.inc"
@SET TESTTOOLS="%~dp0\tools\testing\"
@SET TESTTOOLS_IMAGES="%~dp0\tools\testing\images\"
@SET TESTTOOLS_CONSTS1="%~dp0\tools\testing\settings_filters.inc"
@SET TESTTOOLS_CONSTS2="%~dp0\tools\testing\settings_handwritten.inc"
@SET TESTTOOLS_CONSTS3="%~dp0\tools\testing\settings_highres.inc"
@SET TESTTOOLS_CONSTS4="%~dp0\tools\testing\settings_scanned.inc"
@SET IMAGO_SLN="%~dp0\Imago.sln"

@echo -------------------Updating projects/solutions-------------------

CMake .
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@echo -------------------Compiling solution-------------------

@mkdir _fuzzing-logs 2>NUL

%CPP_COMPILER% %IMAGO_SLN% /Build Release /Out "_fuzzing-logs\log-cpp.txt"
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@echo -------------------Copying testset-------------------

XCOPY %SRC_IMAGES_PATH%  %TESTTOOLS_IMAGES% /s /c /y >>_fuzzing-logs\log-copy.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@echo -------------------Checking built files-------------------

@mkdir _fuzzing-results 2>NUL

cd %TESTTOOLS%
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

%TIMELIMIT% 1>NUL
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

%CONSTFUZZ% 1>NUL
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

%IMAGO_EXE% 1>NUL
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@echo -------------------Entering the loop-------------------

copy %CONSTS_SRC1% %TESTTOOLS_CONSTS1% >>..\..\_fuzzing-logs\log-copy.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

copy %CONSTS_SRC2% %TESTTOOLS_CONSTS2% >>..\..\_fuzzing-logs\log-copy.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

copy %CONSTS_SRC3% %TESTTOOLS_CONSTS3% >>..\..\_fuzzing-logs\log-copy.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

copy %CONSTS_SRC4% %TESTTOOLS_CONSTS4% >>..\..\_fuzzing-logs\log-copy.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

copy %TIMELIMIT% ".\TimeLimit.exe" >>..\..\_fuzzing-logs\log-copy.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@set /a ITER=0

@mkdir results 2>NUL
@mkdir tmp 2>NUL
@mkdir versions 2>NUL

:loop

@set /a ITER=ITER+1

@echo -------------------Iteration %ITER%-------------------

@echo Iteration %ITER% >>..\..\_fuzzing-logs\log-fuzz.txt

@%CONSTFUZZ% %TESTTOOLS_CONSTS1% %CONSTS_SRC1% %FUZZ_LEVEL_FILTERS% -strict >>..\..\_fuzzing-logs\log-fuzz.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@%CONSTFUZZ% %TESTTOOLS_CONSTS2% %CONSTS_SRC2% %FUZZ_LEVEL_OTHER% -strict >>..\..\_fuzzing-logs\log-fuzz.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@%CONSTFUZZ% %TESTTOOLS_CONSTS3% %CONSTS_SRC3% %FUZZ_LEVEL_OTHER% -strict >>..\..\_fuzzing-logs\log-fuzz.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@%CONSTFUZZ% %TESTTOOLS_CONSTS4% %CONSTS_SRC4% %FUZZ_LEVEL_OTHER% -strict >>..\..\_fuzzing-logs\log-fuzz.txt
@IF %ERRORLEVEL% NEQ 0 GOTO EXIT

@DEL %IMAGO_EXE% >>..\..\_fuzzing-logs\log-del.txt
%TIMELIMIT% 600 %CPP_COMPILER% %IMAGO_SLN% /Build Release /Out ..\..\_fuzzing-logs\log-cpp.txt
@IF %ERRORLEVEL% NEQ 0 GOTO FAIL

@RD /S /Q .\results\v777 >>..\..\_fuzzing-logs\log-del.txt 2>NUL
@del .\versions\v777.exe >>..\..\_fuzzing-logs\log-del.txt 2>NUL
@copy %IMAGO_EXE% .\versions\v777.exe >>..\..\_fuzzing-logs\log-copy.txt
@IF %ERRORLEVEL% NEQ 0 GOTO FAIL
@del score.txt >>..\..\_fuzzing-logs\log-del.txt 2>NUL

@echo Iteration %ITER% >>..\..\_fuzzing-logs\log-py.txt
%TIMELIMIT% 1800 %PYTHON_EXE% run.py >>..\..\_fuzzing-logs\log-py.txt
@IF %ERRORLEVEL% NEQ 0 GOTO FAIL

@set SCORE=0
@set /p SCORE=<score.txt
copy %CONSTS_SRC1% "..\..\_fuzzing-results\score%SCORE%_iter%ITER%_settings_filters.inc" >>..\..\_fuzzing-logs\log-copy.txt
copy %CONSTS_SRC2% "..\..\_fuzzing-results\score%SCORE%_iter%ITER%_settings_handwritten.inc" >>..\..\_fuzzing-logs\log-copy.txt
copy %CONSTS_SRC3% "..\..\_fuzzing-results\score%SCORE%_iter%ITER%_settings_highres.inc" >>..\..\_fuzzing-logs\log-copy.txt
copy %CONSTS_SRC4% "..\..\_fuzzing-results\score%SCORE%_iter%ITER%_settings_scanned.inc" >>..\..\_fuzzing-logs\log-copy.txt
copy report.html   "..\..\_fuzzing-results\score%SCORE%_iter%ITER%_report.html" >>..\..\_fuzzing-logs\log-copy.txt

@goto loop

:FAIL

@echo Some failure occured. Restart the loop
goto loop

:EXIT

@echo Unrecoverable error occured. Check the logs.
pause
