#ifndef DISPLAY_H
#define DISPLAY_H


#include "Types.h"
#include "String.h"

#define GRAPHICS_MODE 0x12
#define TEXT_MODE 0x2

struct COORD
{ 
	int32_t x;
	int32_t y;
};

// Prototypes of some basic functions.
struct Screen
{
	byte cur_vm;
	COORD screen_size;
	void (*onDraw)(Screen & ); // 18 call a second.

	void print(String pstr,int8_t char_color);
	void print(const char far * str,int8_t char_col);
	void printf(String pstr,int8_t char_color);
	void printf(const char far * str,int8_t char_color);
	void setCursor(COORD pos);
	COORD getCursor();
	void enableMouse();
	void disableMouse( );
	void drawPixel(COORD pos,int8_t pix_color);
	int8_t getPixel(COORD pos);
	void clearScreen(byte MODE);
};

#endif // DISPLAY_H
