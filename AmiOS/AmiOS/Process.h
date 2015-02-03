#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_PRIVILAGE_HIGH 0x0001
#define PROCESS_PRIVILAGE_LOW  0x0000

#include "Types.h"
#include "String.h"
#include "Disk.h"

struct ProcessStack
{
	int32_t	ds;
	int32_t	es;
	int32_t	sp;
	int32_t	bp;
	int32_t	ss;
	int32_t	cs;
};

struct Process
{
	char pname[10];
	byte privilage;
	bool isReady;
	ProcessStack pstack;	
};

Process process_create(String file_nm,byte privilage);
RESULT  process_start(Process process_obj);

#endif // PROCESS_H
