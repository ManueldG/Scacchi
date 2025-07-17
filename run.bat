
@echo off

gcc src/*.c -o bin/%1.exe

SET c = Hello

@echo %c%

FOR %%A IN (%*) DO (
      
    SET c =%c% %%A.c
    @echo %c%
)

cd bin
%1
cd..
