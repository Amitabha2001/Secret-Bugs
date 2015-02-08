#include "String.h"

static MEMORY_MANAGER mem_manager;

int16_t String::strlen(const char far * str)
{
	// For Dynamic Allocated Strings.
	MEMORY_BLOCK mem_block = mem_manager.findBlock((int32_t) str);

	if (mem_block.block_address == (int32_t) str)
	{
		return mem_block.tot_bytes;
	}

	int16_t len = 0;

	while(str[len] != 0)
	{
		len++;
	}

	return len;
}

bool String::strcmp(const char far * str1,const char far * str2)
{ 
	int16_t len_f = strlen(str1);
	int16_t len_s = strlen(str2);

	if (len_f < len_s || len_f > len_s)
	{
		return FALSE;
	}

	int16_t cnt = 0;

	for(cnt = 0;cnt < len_f;cnt++)
	{
		if (str1[cnt] != str2[cnt])
		{
			return FALSE;
		}
	}

	return TRUE;
}

char far * String::strcpy(const char far * dest,const char far * src)
{
	MEMORY_BLOCK mem_block = mem_manager.kmalloc(sizeof(char) * (strlen(dest) + strlen(src)));
	char far * ret_str = (char far *) mem_block.block_ptr;
	int16_t cnt = 0;
	
	for(cnt = 0;cnt < strlen(dest);cnt++)
	{
		ret_str[cnt] = dest[cnt];
	}
	
	int16_t cntr = 0;
	
	for(cntr = 0;cntr < strlen(src);cnt++,cntr++)
	{ 
		ret_str[cnt] = src[cntr];
	}
	
	return ret_str;
}

char far * String::str_substr(const char far * src,int16_t start_pos,int16_t end_pos)
{
	if (start_pos > 0 && start_pos < strlen(src) && end_pos > 0 && end_pos < strlen(src) && start_pos <= end_pos)
	{ 
		MEMORY_BLOCK mem_block = mem_manager.kmalloc(sizeof(char) * (end_pos - start_pos));
		char far * ret_str = (char far *) mem_block.block_ptr;	
		int16_t cnt = 0;
		int16_t cntr = 0;
		
		for(cnt = start_pos;cnt <= end_pos;cnt++,cntr++)
		{ 
		   ret_str[cntr] = src[cnt];
		}
		
		return ret_str;
	}
	
	return 0;
}

int16_t String::str_getchar_pos(const char far * src,char ch)
{
	int16_t len = strlen(src);
	int16_t cnt = 0;
	
	for(cnt = 0;cnt < len;cnt++)
	{ 
	   if (src[cnt] == ch)
	   { 
		return (cnt + 1);
	   }
	}
	
	return -1;
}

bool String::str_setchar(char far  * src,int16_t pos,char ch)
{
	if (pos < strlen(src) && pos > 0)
	{ 
	     src[pos - 1] = ch;
	     
	     return TRUE;
	}
	
	return FALSE;
}
