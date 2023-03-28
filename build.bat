@echo off

set batchDir=%~dp0
set config=%1
set runPremake=1
set runProg=%2

if "%1"=="clean" (
   if exist %batchDir%\bin (
       rmdir /s /q  %batchDir%\bin
       echo deleted .\bin\
   )
   if exist %batchDir%\build (
       rmdir /s /q %batchDir%\build
       echo deleted .\build\
   )
   
   goto :eof
)

if "%1"=="help" (
   echo Usage: build.bat ^<Build^|Release^> [subcommand]
   echo.
   echo Subcommands:
   echo        help       Prints the usage.
   echo        run        Runs the the first .exe file found in .\bin\^<Debug^|Release^>.
   echo        clean      Removes .\bin\ and .\build\ if they exist.
   echo.
   echo NOTE:if only `run` subcommand is provided with no config the program will run without building.
   goto :eof
)


if "%1"=="run" (
    set runProg=run
    set config=Debug
    goto :run
)


rem run premake5
if "%runPremake%"=="1" (
   echo.
   echo ^<=== Running Premake5 ===^>
   echo.
   premake5 --file=%batchDir%\premake5.lua vs2022
)

rem default condig is Debug
if "%config%"=="" (
    set config=Debug
)

echo.
echo ^<=== Building %config% ===^>
echo.

msbuild -p:configuration=%config% -warnAsMessage:LNK4217,LNK4286 -verbosity:m -m %batchDir%build\hash-table.sln
if not "%errorlevel%"=="0" ( exit %errorlevel% )

:run
if "%runProg%"=="run" (
    if not exist %batchDir%bin (
        echo ERROR: executable not found!
	echo HINT: try to build once before running!
        exit 1
    )
    for %%F in (%batchDir%bin\%config%\*) do (
        if "%%~xF"==".exe" (
            echo.
            echo ^<=== RUNNING %%~nxF ===^>
            echo.

	    %%F
	)
    )
)
