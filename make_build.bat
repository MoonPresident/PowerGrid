@echo off
cmake -S C:/dev/PowerGrid -B C:/dev-builds/PowerGrid/ -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build C:/dev-builds/PowerGrid/

C:\dev-builds\PowerGrid\PowerGrid.exe 