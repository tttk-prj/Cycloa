.PHONY: all sdl noio

all: sdl

sdl:
	g++ -o cycloa_sdl `sdl2-config --cflags` `find src/emulator -name "*.cpp"` `find src/fairy/sdl -name "*.cpp"` `sdl2-config --libs`

noio:
	g++ -o cycloa_noio -DNOIO_CASE `find src/emulator -name "*.cpp"` `find src/fairy/noio -name "*.cpp"`

clean:
	rm -f cycloa_sdl cycloa_noio

