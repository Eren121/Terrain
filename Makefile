all: a.out
CXX=i686-w64-mingw32-g++

a.out: Heightmap.cpp main.cpp
	$(CXX) -m32 -L. -Iinclude  glew.c main.cpp Heightmap.cpp module.cpp modules/*.cpp -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -lopengl32

run: all
	./a.out

debug: all
	echo -e "run\nbacktrace"| gdb --quiet a.out | grep --color -E 'SIGSEGV|'

	
#Windows
#g++ -g main.cpp Heightmap.cpp -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lglew32 -lopengl32 -I C:\MinGW\mingw64\include -m64 -g
#bug si c'est pas en debug (?)