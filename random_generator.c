#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_unique_random_numbers(int *arr, int size, int max_value) {
    int count = 0;
    while (count < size) {
        int num = rand() % max_value;
        int is_unique = 1;

        for (int i = 0; i < count; i++) {
            if (arr[i] == num) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique) {
            arr[count++] = num;
        }
    }
}

void save_to_csv(int *arr, int size, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }

    fclose(fp);
}
