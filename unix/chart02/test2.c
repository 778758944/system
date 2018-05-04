#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

int main() {
    int arr[SIZE];
    FILE * fp;
    if((fp = fopen("./arr", "r")) == NULL) {
        puts("err to open file");
        exit(1);
    }

    if (fread(arr, sizeof(int), SIZE, fp)) {
        printf("show data\n");
        printf("%d\n", arr[0]);
        printf("%d\n", arr[1]);
        printf("%d\n", arr[2]);
    }

    fclose(fp);

    return 0;
}