#include "Display.h"
#include "Disk.h"
#include "Memory.h"
#include "System.h"
#include "Process.h"

extern "C" void kmain()
{
	int8_t boot_drive = 0;

	__asm
	{
		mov boot_drive , dl ;
	};

	String string_handle;
	Screen vdu_handle;
	System sys_handle;
	FileSystem file_sys;
	MEMORY_MANAGER mem_manager;
	
	mem_manager.kmem_init( );

	string_handle.str = " $$$$$$$$$ Welcome to AmiOS Kernel $$$$$$$$$ ";
	
	vdu_handle.clearScreen(TEXT_MODE); // Kernel Text MODE.

	vdu_handle.printf(string_handle,0);

	sys_handle.sys_delay( );

	string_handle.str = "    $$$$$$$$$ Version : 1.0.0 $$$$$$$$$ ";

	vdu_handle.printf(string_handle,0);

	sys_handle.sys_delay( );

	string_handle.str = "";

	vdu_handle.printf(string_handle,0);

	string_handle.str = "PC Configure";

	vdu_handle.printf(string_handle,0);

	string_handle.str = "============";

	vdu_handle.printf(string_handle,0 );

	string_handle.str = "File System Check             [...]";

	vdu_handle.printf(string_handle,0);

	sys_handle.sys_delay( );

	if (SUCCES(file_sys.loadTable(boot_drive)) == TRUE)
	{
		string_handle.str = "File System Ok                [T]";
		vdu_handle.printf(string_handle,0);
	}
	else
	{
		string_handle.str = "File System Failure           [F]";
		vdu_handle.printf(string_handle,0);
	}

	string_handle.str = "APM Services Check            [...]";

	vdu_handle.printf(string_handle,0);

	sys_handle.sys_delay( );

	if (SUCCES(sys_handle.sys_checkAPM( )) == TRUE)
	{
		string_handle.str = "APM Services Ok               [T]";
		vdu_handle.printf(string_handle,0);
	}
	else
	{
		string_handle.str = "APM Services Failed           [F]";
		vdu_handle.printf(string_handle,0);
	}

	vdu_handle.clearScreen(TEXT_MODE);

	// Load our first process .

	string_handle.str = "Shellii";

	Process newProcess = process_create(string_handle,PROCESS_PRIVILAGE_HIGH);

	if (newProcess.isReady == TRUE)
	{
		if (SUCCES(process_start(newProcess)) == FALSE)
		{
			string_handle.str = "Cannot start Shell!";
			vdu_handle.printf(string_handle,0);
		}
	}
	else
	{
		string_handle.str = "Cannot find Shell!";

		vdu_handle.printf(string_handle,0);
	}

	// Shut down PC.
wait_forever:
		
	goto wait_forever;
}