all:
all:
	g++ -Isrc/include -Lsrc/lib -o main main.cpp game.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image