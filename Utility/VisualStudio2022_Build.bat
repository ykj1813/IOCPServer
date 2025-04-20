@echo off
:: Check if the correct number of arguments is provided
if "%~3"=="" (
    echo Usage: build.bat [Configuration] [Platform] [Action]
    echo Example: build.bat Release x86 Rebuild
    exit /b 1
)
 
set CONFIG=%1
set PLATFORM=%2
set ACTION=%3
set TIMESTAMP=%4
set _CALLVSDEVCMD=%5
set _SLN_NAME=%6

:: Set the Visual Studio environment variables
if "%_CALLVSDEVCMD%"=="" call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

:: Define the project or solution file and output directory
set LOG_DIR=".\buildlog"

:: Check if fourth argument is provided
if "%~4"=="" (
    :: Extract current date and time in desired format
    for /f "tokens=2 delims==" %%a in ('wmic os get localdatetime /value') do set datetime=%%a

    :: Format the timestamp without milliseconds and timezone
    set TIMESTAMP=%datetime:~0,8%_%datetime:~8,6%
)

set LOG_FILE_NAME=buildlog_%TIMESTAMP%_%CONFIG%_%PLATFORM%.log

mkdir %LOG_DIR%
set LOG_FILE_PATH=%LOG_DIR%\%LOG_FILE_NAME%

:: Display a message indicating information will be provided before the build
echo [Starting build with] [Configuration : %CONFIG%] [Platform : %PLATFORM%] [Action : %ACTION%]
echo [LogFilePath : %LOG_FILE_PATH%]
echo [Start Build : %_SLN_NAME%]

:: Run MSBuild to build the solution
msbuild %_SLN_NAME% /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /T:%ACTION%  /fileLogger /flp:logfile=%LOG_FILE_PATH%;verbosity=diagnostic

:: Check the exit code of MSBuild and handle errors
if %ERRORLEVEL% neq 0 (
    echo MSBuild failed with exit code %ERRORLEVEL%. Please check the log file %LOG_FILE_DIR% for details. [%CONFIG% %PLATFORM% %ACTION%]
    echo Showing errors from the log:%LOG_FILE_PATH%
    findstr /i "error" %LOG_FILE_PATH% | findstr /i /v "succeeded" | findstr /i /v "0 error" | findstr /v "done" | more +0
    
    exit /b %ERRORLEVEL%
)

echo Build completed successfully!