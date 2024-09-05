#include "gnuplot_integration.h"
#include <stdio.h>

void plot_results() {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "set terminal png\n");
    fprintf(gnuplot, "set output 'comparison_graph.png'\n");
    fprintf(gnuplot, "set title 'Sorting Algorithm Comparison'\n");
    fprintf(gnuplot, "set xlabel 'Input Size'\n");
    fprintf(gnuplot, "set ylabel 'Time Taken (seconds)'\n");
    fprintf(gnuplot, "set key outside\n");
    fprintf(gnuplot, "plot 'time_results.txt' using 1:2 with linespoints title columnheader(3)\n");
    pclose(gnuplot);
}
