@ECHO OFF
ECHO Hello World!
gcc .\hello.c -I.\SDL64\include\SDL2 -L.\SDL64\lib -lSDL2main -lSDL2
.\a.exe
PAUSE
