#ifndef MEMORY_H
#define MEMORY_H

#include "Types.h"

struct MEMORY_BLOCK
{
	void * block_ptr;
	int32_t block_address;
	int32_t tot_bytes;
};

struct MEMORY_MANAGER
{
	void kmem_init();
	MEMORY_BLOCK kmalloc(int32_t tot_size);
	MEMORY_BLOCK krealloc(MEMORY_BLOCK mem_block,int32_t tot_size);
	RESULT kfree(MEMORY_BLOCK mem_block);
	MEMORY_BLOCK findBlock(int32_t block_address);
};


#endif // MEMORY_H
