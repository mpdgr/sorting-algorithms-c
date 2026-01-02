#include "insertion_sort.h"

/* insertion sort */

void insertion_sort(int *arr, int size);

void insertion_sort(int *arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        int pos = i;
        int val = arr[i];

        while (pos > 0 && val < arr[pos - 1])
        {
            arr[pos] = arr[pos - 1];
            pos--;
        }

        arr[pos] = val;
    }
}
