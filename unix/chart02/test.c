#include <stdio.h>
#include <stdlib.h>
#define SIZE 3
int main() {
    int arr[SIZE] = {1, 2, 3};
    int arr2[SIZE];
    int n;
    FILE* fp;
    if ((fp = fopen("./arr", "wr")) == NULL) {
        puts("error to open file");
        exit(1);
    }

    printf("before write\n");
    fwrite(arr, sizeof(int), SIZE, fp);
    printf("after write\n");
    while(fread(arr2, sizeof(int), SIZE, fp)) {
        printf("list num");
        printf("%d\n", arr2[0]);
    }

    return 0;
}