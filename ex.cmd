@echo off

set str="cmd politic"
echo.%str%
for /f "useback tokens=*" %%a in ('%str%') do set str=%%~a
echo.%str%