#include "time_measurement.h"
#include <time.h>

double measure_time(void (*sort_func)(int[], int), int arr[], int size) {
    clock_t start, end;
    start = clock();
    sort_func(arr, size);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double measure_time_merge(void (*sort_func)(int[], int, int), int arr[], int l, int r) {
    clock_t start, end;
    start = clock();
    sort_func(arr, l, r);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}
