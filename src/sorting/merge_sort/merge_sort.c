#include <stdlib.h>
#include <stdio.h>
#include "merge_sort.h"

/* merge sort */

void merge_sort(int *arr, int size);
static void merge_by_index(int *arr, int index, int size);

void merge_sort(int *arr, int size)
{
    int complete = 0;
    int sub_size = 2;
    while (!complete)
    {
        for (int start = 0; start < size; start += sub_size)
        {
            int arr_size = sub_size > size - start ? size - start : sub_size;
            if (arr_size > sub_size / 2)
            {
                merge_by_index(arr + start, sub_size / 2, arr_size);
            }
        }
        complete = sub_size >= size ? 1 : 0;
        sub_size *= 2;
    }
}

static void merge_by_index(int *arr, int index, int size)
{
    int *arr_t = malloc(size * sizeof(int));

    if (arr_t == NULL) {
        printf("Memory allocation error for %d integers\n", size);
        exit(1);
    }

    int *p_left = arr;
    int *p_right = arr + index;

    int pos_merge = 0;
    int pos_left = 0;
    int pos_right = 0;

    int max_left = index;
    int max_right = size - index;

    while (pos_merge < size)
    {
        if (pos_left >= max_left)
        {
            arr_t[pos_merge] = *(p_right + pos_right);
            pos_right++;
        }
        else if (pos_right >= max_right || *(p_right + pos_right) >= *(p_left + pos_left))
        {
            arr_t[pos_merge] = *(p_left + pos_left);
            pos_left++;
        }
        else
        {
            arr_t[pos_merge] = *(p_right + pos_right);
            pos_right++;
        }
        pos_merge++;
    }

    for (int i = 0; i < size; i++)
        *(arr + i) = *(arr_t + i);

	free(arr_t);
}
