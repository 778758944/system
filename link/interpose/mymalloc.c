#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

void* mymalloc(size_t size) {
	void* p = malloc(size);
	printf("malloc(%d) = %p\n", (int) size, p);
	return p;
}

void free(void* p) {
	free(p);
	printf("free(%p)\n", p);
}
#endif