#include "include/clib.h"

int	main(int argc, char **argv)
{
	struct s_allocator *heap;
	struct s_allocator *logging;
	t_file	*file;
	t_striter *iter;
	uint8_t	*ptr;

	if (argc == 2)
	{
		heap = heap_init();
		logging = dbg_allocator_init(heap, false);
		file = file_create(logging, (uint8_t*)argv[1], (uint8_t*)"r");
		iter = file_iterator(file, (uint8_t*)":");
		while ((ptr = iter->next(iter)) != 0)
			printf("%s\n",ptr);

		file_destroy(file);
		string_iter_destroy(iter);
		dbg_allocator_deinit(logging);
		heap_deinit(heap);
		
	}
	return (0);
}
