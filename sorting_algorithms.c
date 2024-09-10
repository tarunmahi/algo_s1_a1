#include "sorting_algorithms.h"
#include <stdlib.h>
#include <stdio.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to find the median of a small chunk of the array
int findmedian(int arr[], int low, int high) {
    // Sort the chunk of the array
    for (int i = low; i < high - 1; i++) {
        for (int j = i + 1; j < high; j++) {
            if (arr[i] > arr[j]) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
    return arr[low + (high - low) / 2];  // Return the median element
}

// Function to partition the array based on the selected pivot
int partition(int arr[], int low, int high, int median) {
    // Move the median element to the end
    for (int i = low; i < high; i++) {
        if (arr[i] == median) {
            swap(&arr[i], &arr[high]);
            break;
        }
    }

    int pivotval = arr[high];  // Pivot value is the median of medians
    int storind = low;

    // Partitioning the array based on pivot
    for (int i = low; i < high; i++) {
        if (arr[i] < pivotval) {
            swap(&arr[storind], &arr[i]);
            storind++;
        }
    }
    swap(&arr[storind], &arr[high]);  // Placing the pivot in the correct position
    return storind;
}

// Function to find the kth smallest element using the median of medians
int kthsmallest(int arr[], int low, int high, int k) {
    int n = high - low + 1;
    int medians[(n + 4) / 5];  // Array to store the medians of groups of 5
    int medianIdx = 0;

    // Finding the medians of chunks of size 5
    for (int i = 0; i < n / 5; i++) {
        int median = findmedian(arr, low + (i * 5), low + (i * 5) + 5);
        medians[medianIdx++] = median;
    }

    // If there are remaining elements, find the median for them too
    if (n % 5 != 0) {
        int median = findmedian(arr, low + (n / 5) * 5, low + (n / 5) * 5 + (n % 5));
        medians[medianIdx++] = median;
    }

    int mom;  // Median of medians
    if (medianIdx == 1) mom = medians[0];
    else mom = kthsmallest(medians, 0, medianIdx - 1, medianIdx / 2);

    // Partition the array based on the median of medians and get the pivot index
    int pivotindex = partition(arr, low, high, mom);
    int rank = pivotindex - low + 1;

    // Return the kth smallest element or recurse to find it
    if (rank == k) return arr[pivotindex];
    else if (rank > k) return kthsmallest(arr, low, pivotindex - 1, k);
    else return kthsmallest(arr, pivotindex + 1, high, k - rank);
}

// QuickSort function using the median of medians to select pivot
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int n = high - low + 1;
        int median_of_medians = kthsmallest(arr, low, high, (n + 1) / 2);  // Finding the median of medians

        // Partitioning the array and getting the pivot index
        int pivotindex = partition(arr, low, high, median_of_medians);

        // Recursively sorting the sub-arrays
        quick_sort(arr, low, pivotindex - 1);
        quick_sort(arr, pivotindex + 1, high);
    }
}

// int partition(int arr[], int low, int high) {
//     int pivot = arr[high];
//     int i = (low - 1);

//     for (int j = low; j <= high - 1; j++) {
//         if (arr[j] < pivot) {
//             i++;
//             int temp = arr[i];
//             arr[i] = arr[j];
//             arr[j] = temp;
//         }
//     }
//     int temp = arr[i + 1];
//     arr[i + 1] = arr[high];
//     arr[high] = temp;
//     return (i + 1);
// }

// void quick_sort(int arr[], int low, int high) {
//     if (low < high) {
//         int pi = partition(arr, low, high);
//         quick_sort(arr, low, pi - 1);
//         quick_sort(arr, pi + 1, high);
//     }
// }
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Move elements of arr[0..i-1] that are greater than key to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void count_sort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radix_sort(int arr[], int n) {
    int m = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > m)
            m = arr[i];

    for (int exp = 1; m / exp > 0; exp *= 10)
        count_sort(arr, n, exp);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void odd_even_sort(int arr[], int n) {
    int is_sorted = 0;
    while (!is_sorted) {
        is_sorted = 1;
        for (int i = 1; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                is_sorted = 0;
            }
        }
        for (int i = 0; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                is_sorted = 0;
            }
        }
    }
}

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* new_node(int item) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(Node* root, int arr[], int* index) {
    if (root != NULL) {
        inorder(root->left, arr, index);
        arr[(*index)++] = root->key;
        inorder(root->right, arr, index);
    }
}

Node* insert(Node* node, int key) {
    if (node == NULL) return new_node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
}

void tree_sort(int arr[], int n) {
    Node* root = NULL;
    root = insert(root, arr[0]);
    for (int i = 1; i < n; i++)
        insert(root, arr[i]);
    int index = 0;
    inorder(root, arr, &index);
}

void cycle_sort(int arr[], int n) {
    for (int cycle_start = 0; cycle_start < n - 1; cycle_start++) {
        int item = arr[cycle_start];
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i] < item)
                pos++;

        if (pos == cycle_start)
            continue;

        while (item == arr[pos])
            pos++;

        if (pos != cycle_start) {
            int temp = item;
            item = arr[pos];
            arr[pos] = temp;
        }

        while (pos != cycle_start) {
            pos = cycle_start;
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    pos++;

            while (item == arr[pos])
                pos++;

            if (item != arr[pos]) {
                int temp = item;
                item = arr[pos];
                arr[pos] = temp;
            }
        }
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}
