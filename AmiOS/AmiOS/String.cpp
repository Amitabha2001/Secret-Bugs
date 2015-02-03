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
	return 0;
}

bool String::str_substr(const char far * src,int16_t start_pos,int16_t end_pos)
{
	return FALSE;
}

int16_t String::str_getchar_pos(const char far * src,char ch)
{
	return 0;
}

bool String::str_setchar(char far  * src,int16_t pos,char ch)
{
	return FALSE;
}