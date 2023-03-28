@echo off
set config=%1

rem default condig is Debug
if "%config%"=="" (
    set config=Debug
)

echo Building %config%....
echo.

msbuild -p:configuration=%config% -warnAsMessage:LNK4217,LNK4286 -verbosity:m -m D:\programming\C++\hash-table\build\hash-table.sln
