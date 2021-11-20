CC = g++

INCLUDE_PATHS = -I${CURDIR}\SDL2\include\SDL2

LIBRARY_PATHS = -L${CURDIR}\SDL2\lib

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

COMPILER_FLAGS = -w -Wl,-subsystem,windows

OBJS = main.cpp SDLManager.cpp Game.cpp

EXECUTABLE = puyo

puyo : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE)

clean:
	rm -rf *o puyo.exe