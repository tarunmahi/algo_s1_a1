#include "time_measurement.h"
#include <time.h>
#include<stdlib.h>
#include<stdio.h>

double measure_time(void (*sort_func)(int[], int), int arr[], int size) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);  // Start the clock
    sort_func(arr, size);  // Call the sorting function with the array and its size
    clock_gettime(CLOCK_MONOTONIC, &end);    // End the clock

    // Calculate time in seconds with nanosecond precision
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return time_taken;
}

// double measure_time(void (*sort_func)(int[], int), int arr[], int size) {
//     clock_t start, end;
//     start = clock();
//     sort_func(arr, size);
//     end = clock();
//     return ((double)(end - start)) / CLOCKS_PER_SEC;
// }

// double measure_time_merge(void (*sort_func)(int[], int, int), int arr[], int l, int r) {
//     clock_t start, end;
//     start = clock();
//     sort_func(arr, l, r);
//     end = clock();
//     return ((double)(end - start)) / CLOCKS_PER_SEC;
// }
double measure_time_merge(void (*sort_func)(int[], int, int), int arr[], int l, int r) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    sort_func(arr, l, r);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return time_taken;
}