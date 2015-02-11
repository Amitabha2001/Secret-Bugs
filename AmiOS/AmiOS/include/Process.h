#ifndef PROCESS_H
#define PROCESS_H

#include "Types.h"
#include "String.h"
#include "Disk.h"

struct ProcessStack
{
	int32_t	ds;
	int32_t	es;
	int32_t	ss;
	int32_t	cs;
};

struct Process
{
	char pname[10];
	bool isReady;
	ProcessStack pstack;	
};

Process process_create(String file_nm);
extern "C" bool process_start(Process process_obj);

#endif // PROCESS_H
