#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/time.h>
#include "sorting.h"

/*
 * generate random arrays of ints and compare sort timing
 * for custom sorting implementations vs library qsort function
 */

#define MAX_RAND 100000
#define ARR_SIZE 10000000
#define HANDICAP 200

void customSortBenchmark();
void librarySortBenchmark();
void errCheck(int *arr, int size);
void randInts(int *arr, int size, int max);
int compareInts(const void *a, const void *b);
long long timeInNanoS(void);
void output(int count, char *name, long long ns);

// sorting function
typedef void (*sort_func)(int *arr, int size);

// test characteristic
typedef struct {
    sort_func function;
    char* name;
    short handicap;
} sort_test;

int main(void)
{
    customSortBenchmark();
    librarySortBenchmark();
    return 0;
}

void customSortBenchmark()
{
    // sorting implementations tests
    sort_test tests[] = {
        {heap_sort, "heap sort", 1},
        {merge_sort, "merge sort", 1},
        {quick_sort, "quick sort", 1},
        {radix_sort, "radix sort", 1},
        {tim_sort, "tim sort", 1},
        {insertion_sort, "insertion sort", HANDICAP},
        {bubble_sort, "bubble sort", HANDICAP},
    };

    int *arr, size;
    sort_func sort_function;
    long long start, end;

    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        // prepare array
        // for weak algorithms array size will be divided by HANDICAP to avoid long runs
        size = ARR_SIZE / tests[i].handicap;
        arr = malloc(size * sizeof(int));
        randInts(arr, size, MAX_RAND);

        sort_function = tests[i].function;
        start = timeInNanoS();

        sort_function(arr, size);

        end = timeInNanoS();
        output(size, tests[i].name, end - start);

        errCheck(arr, size);

        free(arr);
    }
}

void librarySortBenchmark()
{
    int *arr;
    long long start, end;

    arr = malloc(ARR_SIZE * sizeof(int));
    randInts(arr, ARR_SIZE, MAX_RAND);
    start = timeInNanoS();

    qsort(arr, ARR_SIZE, sizeof(int), compareInts);

    end = timeInNanoS();
    output(ARR_SIZE, "stdlib qsort", end - start);
    errCheck(arr, ARR_SIZE);

    free(arr);
}

long long timeInNanoS(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

// fills input array with random ints, range 0 to max
void randInts(int *arr, int size, int max)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % (max + 1);
    }
}

// comparator for standard library qsort
int compareInts(const void *a, const void *b)
{
    int intA = *(const int *)a;
    int intB = *(const int *)b;
    return (intA > intB) - (intA < intB);
}

void output(int count, char *name, long long ns)
{
    printf("Sorting %d elements using %s took %.1f ms", count, name, ns / 1e6);
}

void errCheck(int *arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            printf(" - sort errors!\n");
            return;
        }
    }
    printf(" - no errors!\n");
}
