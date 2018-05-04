#include <stdio.h>
#include <stdlib.h>
#define SIZE 3
int main() {
    int arr[3];
    FILE * fp;
    int j = 6;

    if((fp = fopen("./arr", "r+")) == NULL) {
        puts("error to open file");
        exit(1);
    }

    if (fread(arr, sizeof(int), SIZE, fp)) {
        long i;
        for (i = 0; i < SIZE; i++) {
            if (arr[i] == 2) {
                printf("start to modify\n");
                fseek(fp, i * sizeof(int), SEEK_SET);
                int r = fwrite(&j, sizeof(int), 1, fp);
                printf("after printf %d\n", r);
            }
        }
    }

    fclose(fp);
    return 0;
}