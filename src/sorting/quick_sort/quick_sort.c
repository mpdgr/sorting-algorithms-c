#include "quick_sort.h"

/* quick sort */

void quick_sort(int *arr, int size);
static void q_sort(int v[], int left, int right);
static void swap(int v[], int i, int j);

void quick_sort(int *arr, int size)
{
    q_sort(arr, 0, size - 1);
}

static void q_sort(int v[], int left, int right)
{
    if (right - left <= 0)
        return;

    int index = left;
    int target = right - 1;

    for (int i = left; i < right; i++)
        if (v[index] > v[right])
            swap(v, index, target--);
        else
            index++;

    swap(v, right, index);
    q_sort(v, left, index - 1);
    q_sort(v, index + 1, right);
}

static void swap(int v[], int i, int j)
{
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}
