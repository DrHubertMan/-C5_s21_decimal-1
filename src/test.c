#include<stdio.h>
#include<stdlib.h>

void translate_to_bin(int * value_bin, int x);

int main() {
    int x;
    scanf("%d", &x);
    int* value_bin;
    value_bin = malloc(2 * sizeof(int));
    translate_to_bin(value_bin, x);
    free(value_bin);
    return 0;
} 

void translate_to_bin(int *value_bin, int x) {
    int i = 0;
    value_bin[i] = x % 2;
    i++;
    while(x > 0) {
        value_bin[i] = x % 2;
        x = x / 2;
        i++;
        value_bin = realloc(value_bin, i * sizeof(int));
    }

    for (int j = 1; j < i; j ++) {
        printf("%d", value_bin[j]);
    }
}
