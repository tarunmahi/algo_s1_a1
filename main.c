// 






// #include <windows.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include "random_generator.h"
// #include "sorting_algorithms.h"
// #include "time_measurement.h"
// #include "gnuplot_integration.h"

// #define IDC_COMBOBOX 1001
// #define IDC_BUTTON_GENERATE 1002
// #define IDC_BUTTON_SORT 1003
// #define IDC_BUTTON_COMPARE 1004
// #define IDC_LABEL 1005

// #define MAX_HISTORY 5

// typedef struct {
//     char name[50];
//     double time_taken[5]; // Time for each input size
//     int input_size[5];    // Input sizes
// } SortHistory;

// // Various values
// SortHistory history[MAX_HISTORY];
// int history_index = 0;
// int *current_dataset = NULL;
// int dataset_size = 5000; // Generate dataset of 5000 elements

// void add_to_history(const char *name, double times[], int sizes[], int count) {
//     if (history_index < MAX_HISTORY) {
//         strcpy(history[history_index].name, name);
//         for (int i = 0; i < count; i++) {
//             history[history_index].time_taken[i] = times[i];
//             history[history_index].input_size[i] = sizes[i];
//         }
//         history_index++;
//     } else {
//         // Shift the history array to make room for the new entry
//         for (int i = 0; i < MAX_HISTORY - 1; i++) {
//             history[i] = history[i + 1];
//         }
//         // Add the new entry to the last position
//         strcpy(history[MAX_HISTORY - 1].name, name);
//         for (int i = 0; i < count; i++) {
//             history[MAX_HISTORY - 1].time_taken[i] = times[i];
//             history[MAX_HISTORY - 1].input_size[i] = sizes[i];
//         }
//     }
// }

// void update_label(HWND hwnd, const char *message) {
//     SetWindowText(GetDlgItem(hwnd, IDC_LABEL), message);
// }

// LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//     switch (uMsg) {
//         case WM_CREATE: {
//             HWND hComboBox = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
//                                           20, 20, 200, 200, hwnd, (HMENU)IDC_COMBOBOX, NULL, NULL);
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Quick Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Bubble Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Merge Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Heap Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Shell Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Odd-Even Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Tree Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Cycle Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Selection Sort");

//             CreateWindow("BUTTON", "Generate Dataset", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//                          240, 20, 150, 30, hwnd, (HMENU)IDC_BUTTON_GENERATE, NULL, NULL);
//             CreateWindow("BUTTON", "Sort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//                          240, 60, 150, 30, hwnd, (HMENU)IDC_BUTTON_SORT, NULL, NULL);
//             CreateWindow("BUTTON", "Compare", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//                          240, 100, 150, 30, hwnd, (HMENU)IDC_BUTTON_COMPARE, NULL, NULL);

//             CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE, 20, 140, 370, 30, hwnd, (HMENU)IDC_LABEL, NULL, NULL);
//             break;
//         }
//         case WM_COMMAND: {
//             int wmId = LOWORD(wParam);
//             switch (wmId) {
//                 case IDC_BUTTON_GENERATE: {
//                     if (current_dataset != NULL) {
//                         free(current_dataset);
//                     }
//                     current_dataset = (int *)malloc(dataset_size * sizeof(int));
//                     generate_unique_random_numbers(current_dataset, dataset_size, 10000);
//                     save_to_csv(current_dataset, dataset_size, "dataset.csv");
//                     update_label(hwnd, "Dataset generated and saved to dataset.csv");
//                     break;
//                 }
//                 case IDC_BUTTON_SORT: {
//                     HWND hComboBox = GetDlgItem(hwnd, IDC_COMBOBOX);
//                     int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
//                     if (selectedIndex == CB_ERR) {
//                         update_label(hwnd, "Please select a sorting algorithm.");
//                         return 0;
//                     }

//                     const char *selected_sort;
//                     void (*sort_function)(int[], int);
//                     void (*sort_function_merge)(int[], int, int);
//                     double times[5];
//                     int sizes[] = {1000, 2000, 3000, 4000, 5000};

//                     switch (selectedIndex) {
//                         case 0: // Quick Sort
//                             selected_sort = "Quick Sort";
//                             sort_function_merge = quick_sort;
//                             break;
//                         case 1: // Bubble Sort
//                             selected_sort = "Bubble Sort";
//                             sort_function = bubble_sort;
//                             break;
//                         case 2: // Merge Sort
//                             selected_sort = "Merge Sort";
//                             sort_function_merge = merge_sort;
//                             break;
//                         // Add other sorting algorithms similarly...
//                         default:
//                             update_label(hwnd, "Algorithm not implemented.");
//                             return 0;
//                     }

//                     // Sorting and timing for different input sizes
//                     for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
//                         int size = sizes[i];
//                         int *data = (int *)malloc(size * sizeof(int));
//                         memcpy(data, current_dataset, size * sizeof(int));

//                         if (selectedIndex == 0 || selectedIndex == 2) {
//                             times[i] = measure_time_merge(sort_function_merge, data, 0, size - 1);
//                         } else {
//                             times[i] = measure_time(sort_function, data, size);
//                         }

//                         free(data);
//                     }

//                     // Write the time results for the selected algorithm to the file
//                     FILE *fp = fopen("time_results.txt", "w");
//                     if (fp == NULL) {
//                         update_label(hwnd, "Error opening file for writing.");
//                         return 0;
//                     }

//                     fprintf(fp, "# Inputs %s\n", selected_sort);
//                     for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
//                         fprintf(fp, "%d %f\n", sizes[i], times[i]);
//                     }
//                     fclose(fp);

//                     // Add this algorithm's results to history
//                     add_to_history(selected_sort, times, sizes, sizeof(sizes) / sizeof(sizes[0]));

//                     update_label(hwnd, "Sorting completed and results saved.");
//                     break;
//                 }
//                 case IDC_BUTTON_COMPARE: {
//                     plot_results(); // Use the data in `time_results.txt`
//                     update_label(hwnd, "Comparison graph plotted.");
//                     break;
//                 }
//             }
//             break;
//         }
//         case WM_DESTROY:
//             if (current_dataset != NULL) {
//                 free(current_dataset);
//             }
//             PostQuitMessage(0);
//             break;
//         default:
//             return DefWindowProc(hwnd, uMsg, wParam, lParam);
//     }
//     return 0;
// }

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//     const char *CLASS_NAME = "SortingAlgorithmsWindowClass";

//     WNDCLASS wc = {0};
//     wc.lpfnWndProc = WindowProc;
//     wc.hInstance = hInstance;
//     wc.lpszClassName = CLASS_NAME;
//     wc.hCursor = LoadCursor(NULL, IDC_ARROW);

//     RegisterClass(&wc);

//     HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Sorting Algorithms GUI", WS_OVERLAPPEDWINDOW,
//                                CW_USEDEFAULT, CW_USEDEFAULT, 420, 220,
//                                NULL, NULL, hInstance, NULL);

//     if (hwnd == NULL) {
//         return 0;
//     }

//     ShowWindow(hwnd, nCmdShow);
//     UpdateWindow(hwnd);

//     MSG msg = {0};
//     while (GetMessage(&msg, NULL, 0, 0)) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }

//     return 0;
// }




// #include <windows.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include "random_generator.h"
// #include "sorting_algorithms.h"
// #include "time_measurement.h"
// #include "gnuplot_integration.h"

// #define IDC_COMBOBOX 1001
// #define IDC_BUTTON_GENERATE 1002
// #define IDC_BUTTON_SORT 1003
// #define IDC_BUTTON_COMPARE 1004
// #define IDC_LABEL 1005

// #define MAX_HISTORY 5

// typedef struct {
//     char name[50];
//     double time_taken[5]; // Time for each input size
//     int input_size[5];    // Input sizes
// } SortHistory;

// // Various values
// SortHistory history[MAX_HISTORY];
// int history_index = 0;
// int *current_dataset = NULL;
// int dataset_size = 5000; // Generate dataset of 5000 elements

// void add_to_history(const char *name, double times[], int sizes[], int count) {
//     if (history_index < MAX_HISTORY) {
//         strcpy(history[history_index].name, name);
//         for (int i = 0; i < count; i++) {
//             history[history_index].time_taken[i] = times[i];
//             history[history_index].input_size[i] = sizes[i];
//         }
//         history_index++;
//     } else {
//         // Shift the history array to make room for the new entry
//         for (int i = 0; i < MAX_HISTORY - 1; i++) {
//             history[i] = history[i + 1];
//         }
//         // Add the new entry to the last position
//         strcpy(history[MAX_HISTORY - 1].name, name);
//         for (int i = 0; i < count; i++) {
//             history[MAX_HISTORY - 1].time_taken[i] = times[i];
//             history[MAX_HISTORY - 1].input_size[i] = sizes[i];
//         }
//     }
// }

// void update_time_results_file() {
//     FILE *fp = fopen("time_results.txt", "w");
//     if (fp == NULL) {
//         return;
//     }

//     // Write each algorithm's data to the file
//     fprintf(fp, "# Inputs Cycle_Sort Selection_Sort Quick_Sort Shell_Sort Odd-Even_Sort\n");
//     for (int i = 0; i < history_index; i++) {
//         fprintf(fp, "# Algorithm: %s\n", history[i].name);
//         for (int j = 0; j < 5; j++) {
//             fprintf(fp, "%d %f\n", history[i].input_size[j], history[i].time_taken[j]);
//         }
//     }

//     fclose(fp);
// }

// void update_label(HWND hwnd, const char *message) {
//     SetWindowText(GetDlgItem(hwnd, IDC_LABEL), message);
// }

// LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//     switch (uMsg) {
//         case WM_CREATE: {
//             HWND hComboBox = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
//                                           20, 20, 200, 200, hwnd, (HMENU)IDC_COMBOBOX, NULL, NULL);
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Quick Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Bubble Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Merge Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Heap Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Shell Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Odd-Even Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Tree Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Cycle Sort");
//             SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Selection Sort");
            

//             CreateWindow("BUTTON", "Generate Dataset", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//                          240, 20, 150, 30, hwnd, (HMENU)IDC_BUTTON_GENERATE, NULL, NULL);
//             CreateWindow("BUTTON", "Sort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//                          240, 60, 150, 30, hwnd, (HMENU)IDC_BUTTON_SORT, NULL, NULL);
//             CreateWindow("BUTTON", "Compare", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//                          240, 100, 150, 30, hwnd, (HMENU)IDC_BUTTON_COMPARE, NULL, NULL);

//             CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE, 20, 140, 370, 30, hwnd, (HMENU)IDC_LABEL, NULL, NULL);
//             break;
//         }
//         case WM_COMMAND: {
//             int wmId = LOWORD(wParam);
//             switch (wmId) {
//                 case IDC_BUTTON_GENERATE: {
//                     if (current_dataset != NULL) {
//                         free(current_dataset);
//                     }
//                     current_dataset = (int *)malloc(dataset_size * sizeof(int));
//                     generate_unique_random_numbers(current_dataset, dataset_size, 10000);
//                     save_to_csv(current_dataset, dataset_size, "dataset.csv");
//                     update_label(hwnd, "Dataset generated and saved to dataset.csv");
//                     break;
//                 }
//                 case IDC_BUTTON_SORT: {
//                     HWND hComboBox = GetDlgItem(hwnd, IDC_COMBOBOX);
//                     int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
//                     if (selectedIndex == CB_ERR) {
//                         update_label(hwnd, "Please select a sorting algorithm.");
//                         return 0;
//                     }

//                     const char *selected_sort;
//                     void (*sort_function)(int[], int);
//                     void (*sort_function_merge)(int[], int, int);
//                     double times[5];
//                     int sizes[] = {1000, 2000, 3000, 4000, 5000};

//                     switch (selectedIndex) {
//                         case 0: // Quick Sort
//                             selected_sort = "Quick Sort";
//                             sort_function_merge = quick_sort;
//                             break;
//                         case 1: // Bubble Sort
//                             selected_sort = "Bubble Sort";
//                             sort_function = bubble_sort;
//                             break;
//                         case 2: // Merge Sort
//                             selected_sort = "Merge Sort";
//                             sort_function_merge = merge_sort;
//                             break;
//                         case 3:
//                             selected_sort="Heap Sort";
//                             sort_function=heap_sort;
//                             break;
//                         case 4:
//                             selected_sort="Shell Sort";
//                             sort_function=shell_sort;
//                             break;
//                         case 5:
//                             selected_sort="Odd-Even Sort";
//                             sort_function=odd_even_sort;
//                             break;
//                         case 6:
//                             selected_sort="Tree Sort";
//                             sort_function=tree_sort;
//                             break;
//                         case 7:
//                             selected_sort="Cycle Sort";
//                             sort_function=cycle_sort;
//                             break;
//                         case 8:
//                             selected_sort="Selection Sort";
//                             sort_function=selection_sort;
//                             break;
//                         // Add other sorting algorithms similarly...
//                         default:
//                             update_label(hwnd, "Algorithm not implemented.");
//                             return 0;
//                     }

//                     // Sorting and timing for different input sizes
//                     for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
//                         int size = sizes[i];
//                         int *data = (int *)malloc(size * sizeof(int));
//                         memcpy(data, current_dataset, size * sizeof(int));

//                         if (selectedIndex == 0 || selectedIndex == 2) {
//                             times[i] = measure_time_merge(sort_function_merge, data, 0, size - 1);
//                         } else {
//                             times[i] = measure_time(sort_function, data, size);
//                         }

//                         free(data);
//                     }

//                     // Add this algorithm's results to history
//                     add_to_history(selected_sort, times, sizes, sizeof(sizes) / sizeof(sizes[0]));

//                     // Update the time_results.txt file with the latest 5 algorithms
//                     update_time_results_file();

//                     update_label(hwnd, "Sorting completed and results saved.");
//                     break;
//                 }
//                 case IDC_BUTTON_COMPARE: {
//                     // Plot the graph based on the last 5 algorithms in time_results.txt
//                     plot_results(); // Use the data in `time_results.txt`
//                     update_label(hwnd, "Comparison graph plotted.");
//                     break;
//                 }
//             }
//             break;
//         }
//         case WM_DESTROY:
//             if (current_dataset != NULL) {
//                 free(current_dataset);
//             }
//             PostQuitMessage(0);
//             break;
//         default:
//             return DefWindowProc(hwnd, uMsg, wParam, lParam);
//     }
//     return 0;
// }

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//     const char *CLASS_NAME = "SortingAlgorithmsWindowClass";

//     WNDCLASS wc = {0};
//     wc.lpfnWndProc = WindowProc;
//     wc.hInstance = hInstance;
//     wc.lpszClassName = CLASS_NAME;
//     wc.hCursor = LoadCursor(NULL, IDC_ARROW);

//     RegisterClass(&wc);

//     HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Sorting Algorithms GUI", WS_OVERLAPPEDWINDOW,
//                                CW_USEDEFAULT, CW_USEDEFAULT, 420, 220,
//                                NULL, NULL, hInstance, NULL);

//     if (hwnd == NULL) {
//         return 0;
//     }

//     ShowWindow(hwnd, nCmdShow);
//     UpdateWindow(hwnd);

//     MSG msg = {0};
//     while (GetMessage(&msg, NULL, 0, 0)) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }

//     return 0;
// }


#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "random_generator.h"
#include "sorting_algorithms.h"
#include "time_measurement.h"
#include "gnuplot_integration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALGORITHMS 10
#define MAX_LINE_LENGTH 256
#define MAX_INPUTS 100
#define IDC_COMBOBOX 1001
#define IDC_BUTTON_GENERATE 1002
#define IDC_BUTTON_SORT 1003
#define IDC_BUTTON_COMPARE 1004
#define IDC_LABEL 1005
#define IDC_BUTTON_PROCESS_DATA 1006


#define MAX_HISTORY 5

typedef struct {
    char name[50];
    double time_taken[5]; // Time for each input size
    int input_size[5];    // Input sizes
} SortHistory;

// Various values
SortHistory history[MAX_HISTORY];
int history_index = 0;
int *current_dataset = NULL;
int dataset_size = 5000; // Generate dataset of 5000 elements
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
    fprintf(outfile, "Inputs");
    
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
void add_to_history(const char *name, double times[], int sizes[], int count) {
    if (history_index < MAX_HISTORY) {
        strcpy(history[history_index].name, name);
        for (int i = 0; i < count; i++) {
            history[history_index].time_taken[i] = times[i];
            history[history_index].input_size[i] = sizes[i];
        }
        history_index++;
    } else {
        // Shift the history array to make room for the new entry
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            history[i] = history[i + 1];
        }
        // Add the new entry to the last position
        strcpy(history[MAX_HISTORY - 1].name, name);
        for (int i = 0; i < count; i++) {
            history[MAX_HISTORY - 1].time_taken[i] = times[i];
            history[MAX_HISTORY - 1].input_size[i] = sizes[i];
        }
    }
}

void update_time_results_file() {
    FILE *fp = fopen("time_results.txt", "w");
    if (fp == NULL) {
        return;
    }

    // Write each algorithm's data to the file
   // fprintf(fp, "Cycle_Sort Selection_Sort Quick_Sort Shell_Sort Odd-Even_Sort\n");
    for (int i = 0; i < history_index; i++) {
        fprintf(fp, "# Algorithm: %s\n", history[i].name);
        for (int j = 0; j < 5; j++) {
            fprintf(fp, "%d %f\n", history[i].input_size[j], history[i].time_taken[j]);
        }
    }

    fclose(fp);
}

void update_label(HWND hwnd, const char *message) {
    SetWindowText(GetDlgItem(hwnd, IDC_LABEL), message);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            HWND hComboBox = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
                                          20, 20, 200, 200, hwnd, (HMENU)IDC_COMBOBOX, NULL, NULL);
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Quick_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Bubble_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Merge_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Heap_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Shell_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Odd-Even_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Tree_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Cycle_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Selection_Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"insertion_sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"radix_sort");
            
            

            CreateWindow("BUTTON", "Generate Dataset", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         240, 20, 150, 30, hwnd, (HMENU)IDC_BUTTON_GENERATE, NULL, NULL);
            CreateWindow("BUTTON", "Sort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         240, 60, 150, 30, hwnd, (HMENU)IDC_BUTTON_SORT, NULL, NULL);
            CreateWindow("BUTTON", "Compare", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         240, 100, 150, 30, hwnd, (HMENU)IDC_BUTTON_COMPARE, NULL, NULL);
            CreateWindow("BUTTON", "Process Data", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
             90, 100, 150, 30, hwnd, (HMENU)IDC_BUTTON_PROCESS_DATA, NULL, NULL);


            CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE, 20, 140, 370, 30, hwnd, (HMENU)IDC_LABEL, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            switch (wmId) {
                case IDC_BUTTON_GENERATE: {
                    if (current_dataset != NULL) {
                        free(current_dataset);
                    }
                    current_dataset = (int *)malloc(dataset_size * sizeof(int));
                    generate_unique_random_numbers(current_dataset, dataset_size, 10000);
                    save_to_csv(current_dataset, dataset_size, "dataset.csv");
                    update_label(hwnd, "Dataset generated and saved to dataset.csv");
                    break;
                }
                case IDC_BUTTON_SORT: {
                    HWND hComboBox = GetDlgItem(hwnd, IDC_COMBOBOX);
                    int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                    if (selectedIndex == CB_ERR) {
                        update_label(hwnd, "Please select a sorting algorithm.");
                        return 0;
                    }

                    const char *selected_sort;
                    void (*sort_function)(int[], int);
                    void (*sort_function_merge)(int[], int, int);
                    double times[5];
                    int sizes[] = {1000, 2000, 3000, 4000, 5000};

                    switch (selectedIndex) {
                        case 0: 
                            selected_sort = "Quick_Sort";
                            sort_function_merge = quick_sort;
                            break;
                        case 1: 
                            selected_sort = "Bubble_Sort";
                            sort_function = bubble_sort;
                            break;
                        case 2: // Merge Sort
                            selected_sort = "Merge_Sort";
                            sort_function_merge = merge_sort;
                            break;
                        case 3:
                            selected_sort="Heap_Sort";
                            sort_function=heap_sort;
                            break;
                        case 4:
                            selected_sort="Shell_Sort";
                            sort_function=shell_sort;
                            break;
                        case 5:
                            selected_sort="Odd-Even_Sort";
                            sort_function=odd_even_sort;
                            break;
                        case 6:
                            selected_sort="Tree_Sort";
                            sort_function=tree_sort;
                            break;
                        case 7:
                            selected_sort="Cycle_Sort";
                            sort_function=cycle_sort;
                            break;
                        case 8:
                            selected_sort="Selection_Sort";
                            sort_function=selection_sort;
                            break;
                        case 9:
                            selected_sort="insertion_sort";
                            sort_function=insertion_sort;
                            break;
                        case 10:
                            selected_sort="radix_sort";
                            sort_function=radix_sort;
                            break;
                        
                        default:
                            update_label(hwnd, "Algorithm not implemented.");
                            return 0;
                    }

                    // Sorting and timing for different input sizes
                    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
                        int size = sizes[i];
                        int *data = (int *)malloc(size * sizeof(int));
                        memcpy(data, current_dataset, size * sizeof(int));

                        if (selectedIndex == 0 || selectedIndex == 2) {
                            times[i] = measure_time_merge(sort_function_merge, data, 0, size - 1);
                        } else {
                            times[i] = measure_time(sort_function, data, size);
                        }

                        free(data);
                    }

                    // Add this algorithm's results to history
                    add_to_history(selected_sort, times, sizes, sizeof(sizes) / sizeof(sizes[0]));

                    // Update the time_results.txt file with the latest 5 algorithms
                    update_time_results_file();

                    update_label(hwnd, "Sorting completed and results saved.");
                    break;
                }
                case IDC_BUTTON_PROCESS_DATA: {
            const char *input_filename = "time_results.txt";
            const char *output_filename = "time_results_transformed.txt";
            process_data(input_filename, output_filename);
            update_label(hwnd, "Data processed and saved to transformed file.");
            break;
        }
                case IDC_BUTTON_COMPARE: {
                    // Plot the graph based on the last 5 algorithms in time_results.txt
                    plot_results(); // Use the data in `time_results.txt`
                    update_label(hwnd, "Comparison graph plotted.");
                    break;
                }
            }
            break;
        }
        case WM_DESTROY:
            if (current_dataset != NULL) {
                free(current_dataset);
            }
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char *CLASS_NAME = "SortingAlgorithmsWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Sorting Algorithms GUI", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 420, 220,
                               NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
