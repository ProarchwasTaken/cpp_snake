all: main.o tile_grid.o snake.o apple.o
	g++ main.o tile_grid.o snake.o apple.o -lraylib -lopengl32 -lgdi32 -lwinmm -o game.exe

final: main.o tile_grid.o snake.o apple.o
	g++ main.o tile_grid.o snake.o apple.o -O3 -lraylib -lopengl32 -lgdi32 -lwinmm -o game.exe

main.o: main.cpp
	g++ -c main.cpp

tile_grid.o: scripts\tile_grid.cpp
	g++ -c scripts\tile_grid.cpp

snake.o: scripts\snake.cpp
	g++ -c scripts\snake.cpp

apple.o: scripts\apple.cpp
	g++ -c scripts\apple.cpp

clean:
	del *.o

