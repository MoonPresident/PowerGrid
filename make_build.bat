cd C:/dev-builds

if not exist PowerGrid\ (
	mkdir PowerGrid
)

cd PowerGrid

cmake C:/dev/PowerGrid .
cmake --build .