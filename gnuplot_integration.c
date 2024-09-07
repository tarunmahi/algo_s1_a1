// #include "gnuplot_integration.h"
// #include <stdio.h>

// void plot_results() {
//     FILE *gnuplot = popen("gnuplot -persistent", "w");
//     fprintf(gnuplot, "set terminal png\n");
//     fprintf(gnuplot, "set output 'comparison_graph.png'\n");
//     fprintf(gnuplot, "set title 'Sorting Algorithm Comparison'\n");
//     fprintf(gnuplot, "set xlabel 'Input Size'\n");
//     fprintf(gnuplot, "set ylabel 'Time Taken (seconds)'\n");
//     fprintf(gnuplot, "set key outside\n");
//     fprintf(gnuplot, "plot 'time_results.txt' using 1:2 with linespoints title columnheader(3)\n");
//     pclose(gnuplot);
// // // // }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gnuplot_integration.h"

#define MAX_ALGO_COUNT 10
#define MAX_ALGO_NAME_LENGTH 50

void plot_results() {
    FILE *fp = fopen("time_results_transformed.txt", "r");
    if (fp == NULL) {
        perror("Failed to open time_results_transformed.txt");
        exit(EXIT_FAILURE);
    }

    // Read the first line (header) to get the algorithm names
    char header_line[1024];
    if (fgets(header_line, sizeof(header_line), fp) == NULL) {
        perror("Error reading header from time_results_transformed.txt");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fclose(fp);

    // Tokenize the header to get algorithm names (ignoring the first token, which is "Inputs")
    char *token = strtok(header_line, " \t\n");
    char algorithms[MAX_ALGO_COUNT][MAX_ALGO_NAME_LENGTH];
    int algo_count = 0;

    // Skip the first token ("Inputs") and then extract algorithm names
    token = strtok(NULL, " \t\n");
    while (token != NULL && algo_count < MAX_ALGO_COUNT) {
        strncpy(algorithms[algo_count], token, MAX_ALGO_NAME_LENGTH - 1);
        algorithms[algo_count][MAX_ALGO_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
        algo_count++;
        token = strtok(NULL, " \t\n");
    }

    // Open gnuplot and write the plotting commands
    FILE *gnuplot = popen("gnuplot", "w");
    if (gnuplot == NULL) {
        perror("Failed to open gnuplot");
        exit(EXIT_FAILURE);
    }

    // Write gnuplot script
    fprintf(gnuplot, "set terminal pngcairo size 800,600\n");
    fprintf(gnuplot, "set output 'sorting_algorithms_comparison.png'\n");
    fprintf(gnuplot, "set title 'Sorting Algorithms Comparison'\n");
    fprintf(gnuplot, "set xlabel 'Number of Inputs'\n");
    fprintf(gnuplot, "set ylabel 'Time (seconds)'\n");
    fprintf(gnuplot, "set grid\n");

    // Define line styles for different algorithms
    const char *line_colors[] = {"red", "blue", "green", "purple", "orange", "cyan", "magenta", "yellow", "brown", "grey"};
    for (int i = 0; i < algo_count; i++) {
        fprintf(gnuplot, "set style line %d lc rgb '%s' lt 1 lw 2\n", i + 1, line_colors[i % 10]);
    }

    // Start plotting using the dynamically retrieved algorithm names
    fprintf(gnuplot, "plot ");
    for (int i = 0; i < algo_count; i++) {
        fprintf(gnuplot, "'time_results_transformed.txt' using 1:%d title '%s' with lines linestyle %d", i + 2, algorithms[i], i + 1);
        if (i < algo_count - 1) {
            fprintf(gnuplot, ", \\\n");
        } else {
            fprintf(gnuplot, "\n");
        }
    }

    pclose(gnuplot);
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_ALGO_COUNT 10
// #define MAX_ALGO_NAME_LENGTH 50

// void plot_results() {
//     FILE *fp = fopen("time_results_transformed.txt", "r");
//     if (fp == NULL) {
//         perror("Failed to open time_results_transformed.txt");
//         exit(EXIT_FAILURE);
//     }

//     // Read the first line (header) to get the algorithm names
//     char header_line[1024];
//     if (fgets(header_line, sizeof(header_line), fp) == NULL) {
//         perror("Error reading header from time_results_transformed.txt");
//         fclose(fp);
//         exit(EXIT_FAILURE);
//     }

//     fclose(fp);

//     // Tokenize the header to get algorithm names (ignoring the first token, which is "Inputs")
//     char *token = strtok(header_line, " \t\n");
//     char algorithms[MAX_ALGO_COUNT][MAX_ALGO_NAME_LENGTH];
//     int algo_count = 0;

//     // Skip the first token ("Inputs") and then extract algorithm names
//     token = strtok(NULL, " \t\n");
//     while (token != NULL && algo_count < MAX_ALGO_COUNT) {
//         strncpy(algorithms[algo_count], token, MAX_ALGO_NAME_LENGTH - 1);
//         algorithms[algo_count][MAX_ALGO_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
//         algo_count++;
//         token = strtok(NULL, " \t\n");
//     }

//     // Debug: Print the algorithm names
//     // printf("Algorithms:\n");
//     // for (int i = 0; i < algo_count; i++) {
//     //     printf("%d: %s\n", i + 1, algorithms[i]);
//     // }

//     // Open gnuplot and write the plotting commands
//     FILE *gnuplot = popen("gnuplot", "w");
//     if (gnuplot == NULL) {
//         perror("Failed to open gnuplot");
//         exit(EXIT_FAILURE);
//     }

//     // Write gnuplot script
//     fprintf(gnuplot, "set terminal pngcairo size 800,600\n");
//     fprintf(gnuplot, "set output 'sorting_algorithms_comparison.png'\n");
//     fprintf(gnuplot, "set title 'Sorting Algorithms Comparison'\n");
//     fprintf(gnuplot, "set xlabel 'Number of Inputs'\n");
//     fprintf(gnuplot, "set ylabel 'Time (seconds)'\n");
//     fprintf(gnuplot, "set grid\n");

//     // Define line styles for different algorithms
//     const char *line_colors[] = {"red", "blue", "green", "purple", "orange", "cyan", "magenta", "yellow", "brown", "grey"};
//     for (int i = 0; i < algo_count; i++) {
//         fprintf(gnuplot, "set style line %d lc rgb '%s' lt 1 lw 2\n", i + 1, line_colors[i % 10]);
//     }

//     // Start plotting using the dynamically retrieved algorithm names
//     fprintf(gnuplot, "plot ");
//     for (int i = 0; i < algo_count; i++) {
//         fprintf(gnuplot, "'time_results_transformed.txt' using 1:%d title '%s' with lines linestyle %d", i + 2, algorithms[i], i + 1);
//         if (i < algo_count - 1) {
//             fprintf(gnuplot, ", \\\n");
//         } else {
//             fprintf(gnuplot, "\n");
//         }
//     }

//     pclose(gnuplot);
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_ALGO_COUNT 50 // Increase the count to handle more algorithms
// #define MAX_ALGO_NAME_LENGTH 50
// #define MAX_LINE_LENGTH 1024

// void plot_results() {
//     FILE *fp = fopen("time_results_transformed.txt", "r");
//     if (fp == NULL) {
//         perror("Failed to open time_results_transformed.txt");
//         exit(EXIT_FAILURE);
//     }

//     // Read the first line (header) to get the algorithm names
//     char header_line[MAX_LINE_LENGTH];
//     if (fgets(header_line, sizeof(header_line), fp) == NULL) {
//         perror("Error reading header from time_results_transformed.txt");
//         fclose(fp);
//         exit(EXIT_FAILURE);
//     }

//     // Tokenize the header to get algorithm names (ignoring the first token, which is "Inputs")
//     char *token = strtok(header_line, " \t\n");
//     char algorithms[MAX_ALGO_COUNT][MAX_ALGO_NAME_LENGTH];
//     int algo_count = 0;

//     // Skip the first token ("Inputs") and then extract algorithm names
//     token = strtok(NULL, " \t\n");
//     while (token != NULL && algo_count < MAX_ALGO_COUNT) {
//         strncpy(algorithms[algo_count], token, MAX_ALGO_NAME_LENGTH - 1);
//         algorithms[algo_count][MAX_ALGO_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
//         algo_count++;
//         token = strtok(NULL, " \t\n");
//     }

//     fclose(fp);

//     // // Debug: Print the algorithm names
//     // printf("Algorithms:\n");
//     // for (int i = 0; i < algo_count; i++) {
//     //     printf("%d: %s\n", i + 1, algorithms[i]);
//     // }

//     // Open gnuplot and write the plotting commands
//     FILE *gnuplot = popen("gnuplot", "w");
//     if (gnuplot == NULL) {
//         perror("Failed to open gnuplot");
//         exit(EXIT_FAILURE);
//     }

//     // Write gnuplot script
//     fprintf(gnuplot, "set terminal pngcairo size 800,600\n");
//     fprintf(gnuplot, "set output 'sorting_algorithms_comparison.png'\n");
//     fprintf(gnuplot, "set title 'Sorting Algorithms Comparison'\n");
//     fprintf(gnuplot, "set xlabel 'Number of Inputs'\n");
//     fprintf(gnuplot, "set ylabel 'Time (seconds)'\n");
//     fprintf(gnuplot, "set grid\n");

//     // Define line styles for different algorithms
//     const char *line_colors[] = {"red", "blue", "green", "purple", "orange", "cyan", "magenta", "yellow", "brown", "grey"};
//     for (int i = 0; i < algo_count; i++) {
//         fprintf(gnuplot, "set style line %d lc rgb '%s' lt 1 lw 2\n", i + 1, line_colors[i % 10]);
//     }

//     // Start plotting using the dynamically retrieved algorithm names
//     fprintf(gnuplot, "plot ");
//     for (int i = 0; i < algo_count; i++) {
//         fprintf(gnuplot, "'time_results_transformed.txt' using 1:%d title '%s' with lines linestyle %d", i + 2, algorithms[i], i + 1);
//         if (i < algo_count - 1) {
//             fprintf(gnuplot, ", \\\n");
//         } else {
//             fprintf(gnuplot, "\n");
//         }
//     }

//     pclose(gnuplot);
// }

// int main() {
//     plot_results();
//     return 0;
// }
