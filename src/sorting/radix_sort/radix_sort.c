#include <stdio.h>
#include <stdlib.h>
#include "radix_sort.h"

/* radix sort */

void radix_sort(int *arr, int size);
static void radix_sort_uint(unsigned int *arr, int size);

void radix_sort(int *arr, int size)
{
    radix_sort_uint((unsigned int *)arr, size);
}

static void radix_sort_uint(unsigned int *arr, int size)
{
    // determine size of integer in bits
    int bit_count = (int)sizeof(unsigned int) * 8;

	unsigned int *temp = malloc(size * sizeof(unsigned int));

    if (temp == NULL) {
        printf("Memory allocation error for %d integers\n", size);
        exit(1);
    }

    for (int bit_nr = 0; bit_nr < bit_count; bit_nr++)
    {
        int l_bucket_ptr = 0;
        int r_bucket_ptr = 0;

        // determine nr of elements with respective bit = 0 to set ones bucket start pointer
        for (int i = 0; i < size; i++)
            if ((arr[i] >> bit_nr & 1) == 0)
                r_bucket_ptr++;

        // copy values with 0/1 bit at bit_nr to correct buckets
        for (int i = 0; i < size; i++)
            if ((arr[i] >> bit_nr & 1) == 0)
                temp[l_bucket_ptr++] = arr[i];
            else
                temp[r_bucket_ptr++] = arr[i];

        // copy temp to source array
        for (int i = 0; i < size; i++)
            arr[i] = temp[i];
    }

	free(temp);
}
