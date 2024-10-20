#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <windows.h>
#include <psapi.h>
#include "matrix_multiplication.c"

// Function to calculate the time difference in milliseconds
double get_time_difference(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

// Function to get memory usage in bytes (Windows-specific)
SIZE_T get_memory_usage()
{
    PROCESS_MEMORY_COUNTERS memCounter;
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    return memCounter.PeakWorkingSetSize; // Peak memory usage in bytes
}

// Benchmark matrix multiplication
void benchmark_matrix_multiplication(int size)
{
    // Allocate memory for matrices
    double **a = (double **)malloc(size * sizeof(double *));
    double **b = (double **)malloc(size * sizeof(double *));
    double **c = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++)
    {
        a[i] = (double *)malloc(size * sizeof(double));
        b[i] = (double *)malloc(size * sizeof(double));
        c[i] = (double *)malloc(size * sizeof(double));
    }

    // Initialize matrices
    initialize_matrix(a, b, c, size);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Perform matrix multiplication
    multiply_matrix(a, b, c, size);

    gettimeofday(&end, NULL);
    double elapsed_time = get_time_difference(start, end);
    SIZE_T memory_used = get_memory_usage();

    printf("Matrix Size: %dx%d\n", size, size);
    printf("Execution Time: %.2f ms\n", elapsed_time);
    printf("Memory Usage: %.2f MB\n", memory_used / (1024.0 * 1024.0));

    // Free allocated memory
    for (int i = 0; i < size; i++)
    {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
}

int main()
{
    // Run benchmarks for different matrix sizes
    int sizes[] = {10, 100, 500, 1024}; // Add more sizes if needed
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++)
    {
        benchmark_matrix_multiplication(sizes[i]);
        printf("\n");
    }

    // Add a pause before exiting
    printf("Press Enter to exit...\n");
    getchar(); // Wait for user input before closing the program

    return 0;
}
