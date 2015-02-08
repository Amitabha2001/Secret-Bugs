#include "Display.h"

MEMORY_MANAGER mem_manager;

void Screen::print(String pstr,int8_t char_color)
{
	int16_t len = pstr.strlen(pstr.str);
	int16_t cntr = 0;

	for(cntr = 0;cntr < len;cntr++)
	{
		char pchar = pstr.str[cntr];
		
		if (cur_vm == GRAPHICS_MODE)
		{
			int8_t _cl = char_color;

			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				mov bl , _cl ;
				int 0x10 ;
			};
		}
		else
		{
			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				int 0x10 ;
			};
		}
	}
}

void Screen::print(const char far * str,int8_t char_color)
{ 
	String str_handle;
	int16_t len = str_handle.strlen(str);
	int16_t cntr = 0;

	for(cntr = 0;cntr < len;cntr++)
	{
		char pchar = str[cntr];
		
		if (cur_vm == GRAPHICS_MODE)
		{
			int8_t _cl = char_color;

			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				mov bl , _cl ;
				int 0x10 ;
			};
		}
		else
		{
			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				int 0x10 ;
			};
		}
	}
}

void Screen::printf(String pstr,int8_t char_color)
{
	int16_t len = pstr.strlen(pstr.str);
	int16_t cntr = 0;

	for(cntr = 0;cntr < len;cntr++)
	{
		char pchar = pstr.str[cntr];
		
		if (cur_vm == GRAPHICS_MODE)
		{
			int8_t _cl = char_color;

			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				mov bl , _cl ;
				int 0x10 ;
			};
		}
		else
		{
			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				int 0x10 ;
			};
		}
	}

	__asm
	{
		mov ah , 0x0e ;
		mov al , 10 ;
		int 0x10 ;
		mov al , 13 ;
		int 0x10 ;
	};
}

void Screen::printf(const char far * str,int8_t char_color)
{ 
	String str_handle;
	int16_t len = str_handle.strlen(str);
	int16_t cntr = 0;

	for(cntr = 0;cntr < len;cntr++)
	{
		char pchar = str[cntr];
		
		if (cur_vm == GRAPHICS_MODE)
		{
			int8_t _cl = char_color;

			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				mov bl , _cl ;
				int 0x10 ;
			};
		}
		else
		{
			__asm
			{
				mov ah , 0x0e ;
				mov al , pchar;
				int 0x10 ;
			};
		}
	}

	__asm
	{
		mov ah , 0x0e ;
		mov al , 10 ;
		int 0x10 ;
		mov al , 13 ;
		int 0x10 ;
	};
}

void Screen::setCursor(COORD pos)
{
	int8_t px = pos.x;
	int8_t py = pos.y;

	__asm
	{
		mov ah , 0x3 ;
		mov dh , px ;
		mov dl , py ;
		int 0x10 ;
	};
}

COORD Screen::getCursor()
{
	COORD crd;

	int8_t px = 0,py = 0;

	__asm
	{ 
		mov ah , 0x2 ;
		int 0x10 ;
		mov px , dh ;
		mov py , dl ;
	}

	crd.x = px;
	crd.y = py;

	return crd;
}

void Screen::enableMouse()
{
	__asm
	{
		mov ax , 1 ;
		int 0x33 ;
	};	
}

void Screen::disableMouse( )
{
	__asm
	{
		mov ax , 2 ;
		int 0x33 ;
	};
}

void Screen::drawPixel(COORD pos,int8_t pix_color)
{
	int32_t px = pos.x;
	int32_t py = pos.y;

	__asm
	{
		mov ah , 0x0c ;
		mov al , pix_color ;
		mov cx , px ;
		mov dx , py ;
		int 0x10 ;
	};
}

int8_t Screen::getPixel(COORD pos)
{
	int32_t px = pos.x;
	int32_t py = pos.y;
    int8_t col = 0;

	__asm
	{
		mov ah , 0x0d ;
		mov cx , px ;
		mov dx , py ;
		int 0x10 ;
		mov col , al ;
	};

	return col;
}

void Screen::clearScreen(byte MODE)
{
	cur_vm = MODE;

	byte cur_md = MODE;

	__asm
	{
		mov ah , 0x0 ;
		mov al , cur_md ;
		int 0x10 ;
	};
}