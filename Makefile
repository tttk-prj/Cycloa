all:
	g++ -o cycloa -std=c++11 `sdl2-config --cflags` `find src/ -name "*.cpp"` `sdl2-config --libs`

