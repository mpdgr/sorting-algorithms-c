#include <stdlib.h>
#include <stdio.h>
#include "tim_sort.h"

#define MAXRUN 64

/* timsort */

void tim_sort(int *arr, int size);
static int run_length(int n);
static void merge_runs(int* arr, int left, int mid, int right);
static void insertion_sort(int *arr, int left, int right);

void tim_sort(int *arr, int size)
{
    // determine run size
    int rl = run_length(size);

    // perform insertion sort within runs
    for (int i = 0; i < size; i += rl)
        insertion_sort(arr, i, i + rl < size ? i + rl : size);

    // merge adjacent runs recursively
    while (rl < size)
    {
        for (int i = 0; i < size - rl; i += rl * 2)
        {
            int right_bound = i + rl * 2 - 1 < size ? i + rl * 2 - 1 : size - 1;
            merge_runs(arr, i, i + rl - 1, right_bound);
        }
        rl *= 2;
    }
}

// range 32 - 64
static int run_length(int n)
{
    int rem = 0;
    while (n > MAXRUN)
    {
        rem |= 1;
        n >>= 1;
    }
    return n + rem;
}

static void insertion_sort(int *arr, int left, int right)
{
    for (int i = left; i < right; i++)
    {
        int pos = i;
        int val = arr[i];

        while (pos > left && val < arr[pos - 1])
        {
            arr[pos] = arr[pos - 1];
            pos--;
        }
        arr[pos] = val;
    }
}

// mid = index of last element in the left run
static void merge_runs(int* arr, int left, int mid, int right)
{
    int *merged = malloc((right - left + 1) * sizeof(int));
    if (merged == NULL) {
        printf("Memory allocation error for %d integers\n", right - left + 1);
        exit(1);
    }
    // int merged[right - left + 1];
    int merged_ptr = 0;
    int left_ptr = left;
    int right_ptr = mid + 1;

    while (left_ptr <= mid && right_ptr <= right)
    {
        if (arr[left_ptr] < arr[right_ptr])
            merged[merged_ptr++] = arr[left_ptr++];
        else
            merged[merged_ptr++] = arr[right_ptr++];
    }

    while (left_ptr <= mid)
        merged[merged_ptr++] = arr[left_ptr++];

    while (right_ptr <= right)
        merged[merged_ptr++] = arr[right_ptr++];

    // copy results to source array
    for(int i = 0; i < right - left + 1; i++)
        *(arr + i + left) = *(merged + i);

    free(merged);
}
