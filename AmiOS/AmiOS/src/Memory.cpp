#include "Memory.h"

// Protected Data.
static char mem_array[1024];
static MEMORY_BLOCK mem_blocks[1024];
static int32_t block_cntr = 0;

void MEMORY_MANAGER::kmem_init()
{
	int32_t cnt = 0;
	
	for(cnt = 0;cnt < 1024;cnt++)
	{
		mem_array[cnt] = 0;
	}

	block_cntr = 0;
}

MEMORY_BLOCK MEMORY_MANAGER::kmalloc(int32_t tot_size)
{
	int32_t cnt = 0;
	MEMORY_BLOCK mem_block;

	if (block_cntr > 1023)
	{
		return mem_block;
	}

	for(cnt = 0;cnt < 1024;cnt++)
	{
		if (mem_array[cnt] == 0)
		{
			int32_t _cnt = 0;
			bool fail = FALSE;
			
			for(_cnt = 1;_cnt <= tot_size;_cnt++)
			{
				if (mem_array[cnt + _cnt] != 0)
				{
					fail = TRUE;
					break;
				}
			}
			
			if (fail == TRUE)
			{
				cnt += _cnt; 
			}
			else
			{
				mem_block.block_address = (int32_t ) &mem_array[cnt] ;
				mem_block.block_ptr = &mem_array[cnt];
				mem_block.tot_bytes = tot_size;

				mem_blocks[block_cntr] = mem_block;

				block_cntr++;

				break;
			}
		}
	}
	
	return mem_block;
}

MEMORY_BLOCK MEMORY_MANAGER::krealloc(MEMORY_BLOCK mem_block,int32_t tot_size)
{
	if (SUCCES(kfree(mem_block)) == TRUE)
	{
		return kmalloc(tot_size);
	}
	else
	{
		MEMORY_BLOCK nullBlock;

		return nullBlock;
	}
}

RESULT MEMORY_MANAGER::kfree(MEMORY_BLOCK mem_block)
{
	RESULT res;

	MEMORY_BLOCK _mem_block = findBlock(mem_block.block_address);

	if (_mem_block.tot_bytes != 0)
	{
		res.__val = FALSE;
		return res;
	}
	
	int32_t _cnt = 0;
			
	for(_cnt = 0;_cnt < mem_block.tot_bytes;_cnt++	)	
	{
		mem_array[mem_block.block_address + _cnt] = 0;		
	}
	
	int32_t i = 0;

	for(_cnt = 0;_cnt < block_cntr;_cnt++)
	{
		if (mem_block.block_address == mem_blocks[_cnt].block_address)
		{
			if (_cnt == 1023)
			{
				MEMORY_BLOCK nullBlock;

				mem_blocks[_cnt] = nullBlock;
			}
			else
			{
				mem_blocks[_cnt] = mem_blocks[_cnt + 1];
			}

			i = 1;
		}
		else
		{
			mem_blocks[_cnt] = mem_blocks[_cnt + i];
		}
	}

	block_cntr--;

	res.__val = TRUE;		
	return res;		
}

MEMORY_BLOCK MEMORY_MANAGER::findBlock(int32_t block_address)
{
	MEMORY_BLOCK nullBlock;
	int32_t cntr = 0;

	for(cntr = 0;cntr < 1024;cntr++)
	{
		if (block_address == mem_blocks[cntr].block_address)
		{
			return mem_blocks[cntr];
		}
	}

	return nullBlock;
}