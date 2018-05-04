#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main() {
	void* handle;
	void (*addvec) (int *, int *, int *, int);
	char* error;
	int i;

	handle = dlopen("./libvector.so", RTLD_LAZY);

	if (handle == NULL) {
		printf("err occured: %s\n", dlerror());
		exit(1);
	}

	addvec = dlsym(handle, "addvec");

	if ((error = dlerror()) != NULL) {
		printf("%s\n", error);
		exit(1);
	}

	puts("enter");
	scanf("%d", &i);

	while(i != 1) {
		if (i != 2) {		
			addvec(x, y, z, 2);
			printf("z = {%d, %d}\n", z[0], z[1]);
		} else {
			if (dlclose(handle) == 0) {
				handle = dlopen("./libvector.so", RTLD_LAZY);
				if (handle == NULL) {
					exit(1);
				}
				addvec = dlsym(handle, "addvec");
			}
		}
		puts("enter again");
		scanf("%d", &i);
	}


	if(dlclose(handle) < 0) {
		printf("failed to close: %s\n", dlerror());
		exit(1);
	}
	return 0;
}






























