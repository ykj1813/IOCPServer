

@set PATCH_DATE=29991231
@set PATH_BASE=.
@set NAME_DATA=Data
@set PATH_DATA_DIR=%PATH_BASE%\%NAME_DATA%

mkdir %PATH_DATA_DIR%

setlocal enabledelayedexpansion

:: 현재 디렉터리의 모든 폴더 검색
for /d %%d in (*) do (
    :: 폴더 이름을 사용하여 날짜를 비교
    set "folderName=%%~nxd"

    if "!folderName!" leq "!PATCH_DATE!" (
        if not "%%~nxd"=="!NAME_DATA!" (
			echo xcopy "!PATH_BASE!\%%~nxd\*.*" "!PATH_DATA_DIR!\" /e /h /k /i /y
            xcopy "!PATH_BASE!\%%~nxd\*.*" "!PATH_DATA_DIR!\" /e /h /k /i /y
        )
    )
)

endlocal
