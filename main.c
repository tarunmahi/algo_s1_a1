#include "num_gen.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int *arr=NULL;
    int size=1000;
    arr = (int *)malloc(size * sizeof(int));
                generate_unique_random_numbers(arr, size, 10000);
                save_to_csv(arr, size, "dataset.csv");
                printf("Dataset generated and saved to dataset.csv\n");
}