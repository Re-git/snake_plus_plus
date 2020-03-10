@echo off
mkdir build
xcopy /Y src\*.dll build
pushd build
g++ -Wall -g -Wpedantic -Wall -Werror -pedantic-errors -std=c++17 ../src/main.cpp ../src/libraylib.dll -o snake_plus_plus.exe
popd
build\snake_plus_plus.exe
rmdir /Q /S build