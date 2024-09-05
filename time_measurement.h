#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

double measure_time(void (*sort_func)(int[], int), int arr[], int size);
double measure_time_merge(void (*sort_func)(int[], int, int), int arr[], int l, int r);

#endif
