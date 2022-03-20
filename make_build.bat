@echo off
cd C:/dev-builds

if not exist PowerGrid\ (
	mkdir PowerGrid
)

cd PowerGrid

if not exist dep-builds\ (
	mkdir dep-builds\glfw\src\
	cd dep-builds/glfw
	cmake C:/dev/Powergrid/Dependencies/glfw-3.3
	cmake --build .
	cd ../..
)

cmake C:/dev/PowerGrid .
cmake --build .	

C:\dev-builds\PowerGrid\Debug\PowerGrid.exe 