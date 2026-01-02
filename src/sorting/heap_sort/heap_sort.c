#include "heap_sort.h"

/* heap sort */

void heap_sort(int *arr, int size);
static void heapify(int *arr, int size, int pos);
static void swap(int *v, int *i, int *j);

void heap_sort(int *arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = 1; i < size; i++)
    {
        swap(arr, &arr[0], &arr[size - i]);
        heapify(arr, size - i, 0);
    }
}

static void heapify(int *arr, int size, int pos)
{
    short cnt = 1;

    while (cnt)
    {
        int max = pos;
        int left_child = 2 * pos + 1;
        int right_child = 2 * pos + 2;

        if (left_child < size && arr[max] < arr[left_child])
            max = left_child;

        if (right_child < size && arr[max] < arr[right_child])
            max = right_child;

        if (pos != max)
        {
            swap(arr, &arr[pos], &arr[max]);
            pos = max;
        }
        else
            cnt = 0;
    }
}

static void swap(int *v, int *i, int *j)
{
    int t = *i;
    *i = *j;
    *j = t;
}