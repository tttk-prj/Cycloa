
EMULATOR_CORE_SRCS = $(shell find src/emulator   -name "*.cxx")
SDL_FAIRY_SRCS     = $(shell find src/fairy/sdl  -name "*.cpp")
NOIO_FAIRY_SRCS    = $(shell find src/fairy/noio -name "*.cpp")

EMULATOR_CORE_OBJS = $(subst .cxx,.o,$(EMULATOR_CORE_SRCS))
SDL_FAIRY_OBJS     = $(subst .cpp,.o,$(SDL_FAIRY_SRCS))
NOIO_FAIRY_OBJS    = $(subst .cpp,.o,$(NOIO_FAIRY_SRCS))

SDL_CXXFLAGS = -DORIGINAL_CYCLOA $(shell sdl2-config --cflags)
SDL_LDFLAGS  = $(shell sdl2-config --libs)

NOIO_CXXFLAGS = -DORIGINAL_CYCLOA -DNOIO_CASE
NOIO_LDFLAGS  = 

SDL_OBJS = $(EMULATOR_CORE_OBJS) $(SDL_FAIRY_OBJS)
NOIO_OBJS = $(EMULATOR_CORE_OBJS) $(NOIO_FAIRY_OBJS)

.PHONY: all cycloa_sdl cycloa_noio

all: cycloa_sdl

check:
	@echo $(SDL_OBJS)
	@echo $(SDL_CFLAGS)

cycloa_sdl:: CXXFLAGS = $(SDL_CXXFLAGS)

cycloa_noio:: CXXFLAGS = $(NOIO_CXXFLAGS)

cycloa_sdl:: $(SDL_OBJS)
	@echo Link $@
	@g++ -o $@ $^ $(SDL_LDFLAGS)

cycloa_noio:: $(NOIO_OBJS)
	@echo Link $@
	@g++ -o $@ $^ $(MONI_LDFLAGS)

%.o:: %.cxx
	@echo Compile cxx file $@
	@g++ -o $@ -c $(CXXFLAGS) $<

%.o:: %.cpp
	@echo Compile cpp file $@
	@g++ -o $@ -c $(CXXFLAGS) $<

clean:
	@rm -f $(SDL_OBJS) $(NOIO_OBJS) cycloa_sdl cycloa_noio

