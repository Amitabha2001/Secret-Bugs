#include "Display.h"

Screen screen_handle;
const char far * str = "Welcome";

extern "C" void onTimer( )
{
	__asm
	{ 
		cli ;

		mov ax , cs ;
		mov ds , ax ;
		mov ss , ax ;

		sti ;
	};
}

extern "C" void desktopMain( )
{
	screen_handle.clearScreen(TEXT_MODE);
	screen_handle.printf(str,0);
//	screen_handle.printf("[Desktop 1.0.0]",0);
	
wait:

	goto wait;
}