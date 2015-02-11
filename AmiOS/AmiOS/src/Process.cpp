#include "Process.h"
#include "Display.h"

int jmp_val = 0;

Process process_create(String file_nm)
{
	FileSystem file_sys_handle;
	Process newProcess;
	
	FAT_File file_handle = file_sys_handle.getFile(file_nm);
	int32_t cur_adr = 0x001;
	int32_t _seg = 0x2000;
	
	if (file_handle.file_name[0] != 0)
	{
		int8_t clus_num = file_handle.clustor_start;
		FAT_Clustor fat_clus = file_sys_handle.getClustor(clus_num);

		while(fat_clus.clustor_record.free == FALSE)
		{
			int16_t dat_cnt = 0;

			for(dat_cnt = 0;dat_cnt < 510;dat_cnt++)
			{
				byte cur_dat = fat_clus.data_bytes[dat_cnt];

				__asm
				{
					push es;

					mov ax , _seg ;
					mov es , ax ;

					mov bx , cur_adr ;
					mov al , cur_dat ;
					mov byte ptr es:[bx] , al ;

					pop es;
				};

				cur_adr++;
			}

			if (fat_clus.clustor_record.end == TRUE)
			{
				break;
			}
			else
			{
				fat_clus = file_sys_handle.getClustor(fat_clus.clustor_record.ptr);
			}
		}

		int16_t cnt = 0;

		for(cnt = 0;cnt < 7;cnt++)
		{
			if (file_nm.strlen(file_nm.str) < (cnt + 1))
			{
				newProcess.pname[cnt] = 'i';
			}
			else
			{
				newProcess.pname[cnt] = file_nm.str[cnt];
			}
		}

		newProcess.isReady = TRUE;
		newProcess.pstack.cs = _seg;
		newProcess.pstack.ds = _seg;
		newProcess.pstack.ss = _seg;
		newProcess.pstack.es = _seg;
		
		return newProcess;
	}
	else
	{
		newProcess.isReady = FALSE;
		return newProcess;
	}
}

extern "C" bool process_handler(Process process_obj)
{
	if (process_obj.isReady == TRUE)
	{
		int32_t code_seg = process_obj.pstack.cs;
	
		__asm
		{ 
			cli ;

			mov word ptr [jmp_val] , 0x1 ;
			mov ax , code_seg ;
			mov word ptr [jmp_val + 2] , ax ;

			sti ;

			push cs ;
			mov ax , offset kcall ;
			push ax ;

			jmp dword ptr [jmp_val] ;
kcall:
			cli ;
			mov ax , cs ;
			mov ds , ax ;
			mov es , ax ;
			sti ;
		};

		return TRUE;
	}

	return FALSE;
}
