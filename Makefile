all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp game.cpp -Lmingw32 -LSDL2main -LSDL2