#include "System.h"
#include "Display.h"

void System::sys_delay()
{
	int64_t cnt = 0;
	
	for(cnt = 0;cnt < 10000000;cnt++); // Delayed Loop.
}

void System::sys_shutdown()
{
	if (SUCCES(sys_checkAPM( )) == TRUE)
	{

	}
	else
	{
		Screen screen_handle;

		screen_handle.printf("Shut down requires direct power off . You data is saved properly.",0);

		__asm
		{
			cli ;
			hlt ;
		}
	}
}

RESULT System::sys_checkAPM( )
{
	RESULT res;

	__asm
	{ 
		mov ah , 0x53 ;
		mov al , 0 ;
		xor bx , bx ;

		int 0x15 ;

		jc on_error;

	};

	res.__val = TRUE;

	return res;

on_error:

	res.__val = FALSE;

	return res;
}

RESULT System::sys_ready_printer()
{
	RESULT res;

	return res;
}

RESULT System::sys_write_printer(String str)
{
	RESULT res;

	return res;
}

PrinterSTATUS System::sys_getstatus_printer()
{
	PrinterSTATUS pstat;

	return pstat;
}