@echo off
mkdir build
xcopy /Y src\*.dll build
pushd build
g++ -Wall -g -Wpedantic -Wall -Werror -static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive -std=c++17 ..\src\main.cpp  ..\src\libraylib.dll ../src/monkey.cpp ..\src\timer.cpp ../src/snake.cpp ../src/Fruits.cpp ../src/Nukes.cpp ../src/Explosion.cpp ../src/FrostNuke.cpp ../src/FrostExplosion.cpp ../src/pig.cpp -o snake_plus_plus.exe
popd
build\snake_plus_plus.exe
rmdir /Q /S build