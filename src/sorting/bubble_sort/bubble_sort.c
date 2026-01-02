#include "bubble_sort.h"

/* bubble sort */

void bubble_sort(int *arr, int size);
static void swap(int *arr, int index_1, int index_2);

void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int sorted = 1;
        for (int j = 0; j < size - 1 - i; j++)
            if (arr[j] > arr[j + 1])
            {
                swap(arr, j, j + 1);
                sorted = 0;
            }

        if (sorted)
            break;
    }
}

static void swap(int *arr, int index_1, int index_2)
{
    int tmp = arr[index_1];
    arr[index_1] = arr[index_2];
    arr[index_2] = tmp;
}
