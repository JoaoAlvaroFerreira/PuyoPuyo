/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings

#include "SDLManager.h"


int main( int argc, char* args[] )
{
    SDLManager * sdl = new SDLManager();
	//Start up SDL and create window
	if( !sdl->init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !sdl->loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			sdl->screenLoop();
		}
	}

	//Free resources and close SDL
	sdl->close();

	return 0;
}