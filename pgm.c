#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

//Pizzignacco Michael


void map_mandelbrot_set(int **mandelbrot_set, int nrows, int ncols, int max_iterations, const char *filename) {
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    size_t data_size = nrows * ncols * sizeof(unsigned char) + 100; // Extra space for header
    if (ftruncate(fd, data_size) == -1) {
        perror("Error truncating file");
        exit(EXIT_FAILURE);
    }
    char *mapped_data = mmap(NULL, data_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_data == MAP_FAILED) {
        perror("Error mapping data");
        exit(EXIT_FAILURE);
    }
    // Write PGM header
    int len = sprintf(mapped_data, "P5\n%d %d\n255\n", ncols, nrows);
    // Copy the Mandelbrot set data to the mapped memory
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            int m = mandelbrot_set[i][j];
            unsigned char hue = m < max_iterations ? floor(255 * log(m + 1) / log(max_iterations)) : 255;
            mapped_data[len++] = hue;
        }
    }
    // Unmap the memory after it is no longer needed
    if (munmap(mapped_data, data_size) == -1) {
        perror("Error unmapping data");
        exit(EXIT_FAILURE);
    }
    close(fd);
}
