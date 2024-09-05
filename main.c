#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "random_generator.h"
#include "sorting_algorithms.h"
#include "time_measurement.h"
#include "gnuplot_integration.h"

#define IDC_COMBOBOX 1001
#define IDC_BUTTON_GENERATE 1002
#define IDC_BUTTON_SORT 1003
#define IDC_BUTTON_COMPARE 1004
#define IDC_LABEL 1005

#define MAX_HISTORY 5

typedef struct {
    char name[50];
    double time_taken;
    int input_size;
} SortHistory;
//various values
SortHistory history[MAX_HISTORY];
int history_index = 0;
int *current_dataset = NULL;
int dataset_size = 5000; // Generate dataset of 5000 elements

void add_to_history(const char *name, double time_taken, int size) {
    if (history_index < MAX_HISTORY) {
        history[history_index].time_taken = time_taken;
        history[history_index].input_size = size;
        snprintf(history[history_index].name, 50, "%s", name);
        history_index++;
    }
}

void update_label(HWND hwnd, const char *message) {
    SetWindowText(GetDlgItem(hwnd, IDC_LABEL), message);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            HWND hComboBox = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
                                          20, 20, 200, 200, hwnd, (HMENU)IDC_COMBOBOX, NULL, NULL);
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Bubble Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Merge Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Quick Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Radix Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Heap Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Shell Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Odd-Even Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Tree Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Cycle Sort");
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Selection Sort");

            CreateWindow("BUTTON", "Generate Dataset", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         240, 20, 150, 30, hwnd, (HMENU)IDC_BUTTON_GENERATE, NULL, NULL);
            CreateWindow("BUTTON", "Sort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         240, 60, 150, 30, hwnd, (HMENU)IDC_BUTTON_SORT, NULL, NULL);
            CreateWindow("BUTTON", "Compare", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         240, 100, 150, 30, hwnd, (HMENU)IDC_BUTTON_COMPARE, NULL, NULL);

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
                    FILE *fp = fopen("time_results.txt", "w");
                    if (fp == NULL) {
                        update_label(hwnd, "Error opening file for writing.");
                        return 0;
                    }

                    fprintf(fp, "# Inputs Cycle_Sort Selection_Sort Quick_Sort Shell_Sort Odd-Even_Sort\n");

                    int sizes[] = {1000, 2000, 3000, 4000, 5000};
                    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
                        int size = sizes[i];
                        int *data = (int *)malloc(size * sizeof(int));
                        memcpy(data, current_dataset, size * sizeof(int));

                        double time_cycle = measure_time(cycle_sort, data, size);
                        double time_selection = measure_time(selection_sort, data, size);
                        double time_quick = measure_time_merge(quick_sort, data, 0, size - 1);
                        double time_shell = measure_time(shell_sort, data, size);
                        double time_odd_even = measure_time(odd_even_sort, data, size);

                        fprintf(fp, "%d %f %f %f %f %f\n", size, time_cycle, time_selection, time_quick, time_shell, time_odd_even);

                        free(data);
                    }

                    fclose(fp);
                    plot_results();
                    update_label(hwnd, "Comparison graph plotted.");
                    break;
                }
                case IDC_BUTTON_COMPARE: {
                    // Trigger the sorting and comparison again if needed
                    SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SORT, 0);
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
