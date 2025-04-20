@echo off


echo The main build will be executed for x64 architecture.

:: Extract current date and time in desired format
for /f "tokens=2 delims==" %%a in ('wmic os get localdatetime /value') do set _datetime=%%a
:: Format the timestamp without milliseconds and timezone
set _TIMESTAMP=%_datetime:~0,8%_%_datetime:~8,6%
set ACTIVE_CALL_VSDEVCMD=%2%

:: Set the Visual Studio environment variables
if ""=="%ACTIVE_CALL_VSDEVCMD%" call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

set _CONFIG=Debug
set _PLATFORM=x64
set _ACTION=Rebuild

:: Call the other batch file with arguments
echo %_ACTION% %_CONFIG% %_PLATFORM%...

call DDServerMain_Build.bat %_CONFIG% %_PLATFORM% %_ACTION% %_TIMESTAMP% False
if %ERRORLEVEL% neq 0 (
    powershell -Command "Write-Host 'Error : Build script failed with exit code %ERRORLEVEL% : [%_CONFIG%] [%_PLATFORM%] [%_ACTION%] [%_TIMESTAMP%]' -ForegroundColor Red"
    :: Handle the error (e.g., exit with the same error level)
    if "%~1"=="" pause
    exit /b %ERRORLEVEL%
)

set _CONFIG=Release
set _PLATFORM=x64
set _ACTION=Rebuild

:: Call the other batch file with arguments
echo %_ACTION% %_CONFIG% %_PLATFORM%...
call DDServerMain_Build.bat %_CONFIG% %_PLATFORM% %_ACTION% %_TIMESTAMP% False
if %ERRORLEVEL% neq 0 (
    powershell -Command "Write-Host 'Error : Build script failed with exit code %ERRORLEVEL% : [%_CONFIG%] [%_PLATFORM%] [%_ACTION%] [%_TIMESTAMP%]' -ForegroundColor Red"
    :: Handle the error (e.g., exit with the same error level)
    if "%~1"=="" pause
    exit /b %ERRORLEVEL%
)


echo Main build script completed!
if "%~1"=="" pause