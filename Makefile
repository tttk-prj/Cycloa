.PHONY: all sdl noio

all: sdl

sdl:
	g++ -o cycloa_sdl `sdl2-config --cflags` `find src/emulator -name "*.cpp"` `find src/fairy -name "*.cpp"` `sdl2-config --libs`

noio:
	g++ -o cycloa_noio -std=c++11 `find src/emulator -name "*.cpp"` `find src/noio_fairy -name "*.cpp"`

clean:
	rm -f cycloa_sdl cycloa_noio

