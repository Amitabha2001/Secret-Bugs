#ifndef SYSTEM_H
#define SYSTEM_H

#include "Types.h"
#include "String.h"

struct PrinterSTATUS
{
	bool print_error;
};

struct System
{
	void sys_delay();
	void sys_shutdown();
	RESULT sys_checkAPM( );
	RESULT sys_ready_printer();
	RESULT sys_write_printer(String str);
	PrinterSTATUS sys_getstatus_printer();
};

#endif // SYSTEM_H
