#ifndef STRING_H
#define STRING_H

#include "Types.h"
#include "Memory.h"

#define EXP_STRING(exp) # exp

struct String
{
	char far * str;

	int16_t strlen(const char far * str);
	bool strcmp(const char far * str1,const char far  * str2);
	char far * strcpy(const char far * dest,const char far * src);
	bool str_substr(const char far * src,int16_t start_pos,int16_t end_pos);
	int16_t str_getchar_pos(const char far * src,char ch);
	bool str_setchar(char far  * src,int16_t pos,char ch);
};

#endif // STRING_H
