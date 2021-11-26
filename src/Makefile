CC = g++

INCLUDE_PATHS = -I..\SDL2\include\SDL2

LIBRARY_PATHS = -L..\SDL2\lib
 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread -static-libgcc -static-libstdc++

COMPILER_FLAGS = -Wl,-subsystem,windows 

OBJS = main.cpp SDLManager.cpp Game.cpp my1.res

EXECUTABLE = ..\puyo

puyo : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o  $(EXECUTABLE)

clean:
	rm -rf *o ..\puyo.exe