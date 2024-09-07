#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALGORITHMS 10
#define MAX_LINE_LENGTH 256
#define MAX_INPUTS 100

// Function prototypes
void process_data(const char* input_file, const char* output_file);

int main() {
    const char* input_filename = "time_results.txt";
    const char* output_filename = "time_results_transformed.txt";
    
    process_data(input_filename, output_filename);
    
    return 0;
}

void process_data(const char* input_file, const char* output_file) {
    FILE *infile = fopen(input_file, "r");
    if (!infile) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *outfile = fopen(output_file, "w");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    char algorithms[MAX_ALGORITHMS][MAX_LINE_LENGTH];
    int algorithm_count = 0;
    char inputs[MAX_INPUTS][MAX_LINE_LENGTH];
    int input_count = 0;
    char data[MAX_INPUTS][MAX_ALGORITHMS][MAX_LINE_LENGTH] = {0};
    
    while (fgets(line, sizeof(line), infile)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character

        if (strncmp(line, "# Algorithm:", 12) == 0) {
            if (algorithm_count < MAX_ALGORITHMS) {
                // Extract algorithm name
                strcpy(algorithms[algorithm_count], line + 13);
                algorithm_count++;
            }
        } else if (line[0] != '#' && strlen(line) > 0) {
            // Process data lines
            int i;
            char input_size[MAX_LINE_LENGTH], time[MAX_LINE_LENGTH];
            sscanf(line, "%s %s", input_size, time);
            
            // Store input size if not already present
            for (i = 0; i < input_count; i++) {
                if (strcmp(inputs[i], input_size) == 0) break;
            }
            if (i == input_count) {
                if (input_count < MAX_INPUTS) {
                    strcpy(inputs[input_count], input_size);
                    input_count++;
                }
            }

            // Store time data
            int algorithm_index = algorithm_count - 1;
            for (i = 0; i < input_count; i++) {
                if (strcmp(inputs[i], input_size) == 0) {
                    strcpy(data[i][algorithm_index], time);
                    break;
                }
            }
        }
    }
    
    // Write output file
    fprintf(outfile, "# Inputs");
    for (int i = 0; i < algorithm_count; i++) {
        fprintf(outfile, " %s", algorithms[i]);
    }
    fprintf(outfile, "\n");
    
    for (int i = 0; i < input_count; i++) {
        fprintf(outfile, "%s", inputs[i]);
        for (int j = 0; j < algorithm_count; j++) {
            fprintf(outfile, " %s", data[i][j]);
        }
        fprintf(outfile, "\n");
    }
    
    fclose(infile);
    fclose(outfile);
}
