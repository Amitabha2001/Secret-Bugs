#ifndef TYPES_H
#define TYPES_H

/*
	Some good defination of basic types.
*/

typedef char byte;
typedef char bool;
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;


#define TRUE 0x001 
#define FALSE 0x000

struct RESULT
{
	bool __val;
};

/* 
	Note : The two macro below uses structure RESULT for proper working.
*/
#define SUCCES(obj) (obj.__val == 1) ? TRUE : FALSE
#define FAIL(obj) (obj.__val == 0) ? TRUE : FALSE


#define SIZE(x) sizeof(x) // Returns the total bytes allocated.


#endif // TYPES_H
