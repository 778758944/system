#include <stdio.h>
void swap();

int buf[2] = {1, 2};
int main() {
	swap();
	printf("%d\n", buf[1]);
	return 0;
}