#include "include/clib.h"
#include <stddef.h>
#include <string.h>

int	main(void)
{
	t_allocator	*allocator;
	char		*source;
	char		*result;
	uint64_t	count;

	allocator = arena_init(NULL, 65536);
	source = " ";
	count = 0;
	do
	{
		result = memalloc(allocator, 32);
		count += 1;
	} while (result != NULL);
	printf("count : %lu\n", count);
	allocator->deinit(allocator);
}
