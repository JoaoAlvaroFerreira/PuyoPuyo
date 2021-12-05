# PuyoPuyo
A small version of Puyo Puyo created with C++

Due to a lack of available MacOS and Linux computers, this project was only compiled and executed on Windows machines.

The compiler used was the MSYS2 version of MinGW (64 bit), and although the source files may compile as intended with other compilers, some of the SDL libraries used
(in the SDL2 folder) are specific for MinGW. Due to this, I can't ensure that compilation will work as expected outside of this specific environment.
With MinGW installed, simply running "make puyo" inside the src file should generate "puyo.exe" in the base folder.

There is an intended delay and event flush after each scene change in the game, so that players don't accidentally skip scenes (skipping the How to Play instructions, 
for example).
