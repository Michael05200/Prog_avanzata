#include "mandelbrot.h"
#include <complex.h>
#include <stdlib.h>
#include <omp.h>


//Pizzignacco Michael


int **calculate_mandelbrot_set(int nrows, int ncols, int max_iterations) {
    int **mandelbrot_set = malloc(nrows * sizeof(int *));
    for (int i = 0; i < nrows; i++) {
        mandelbrot_set[i] = malloc(ncols * sizeof(int));
    }
    double complex c, z;
    double real_min = -2.0, real_max = 1.0;
    double imag_min = -1.0, imag_max = 1.0;
    double real_step = (real_max - real_min) / ncols;
    double imag_step = (imag_max - imag_min) / nrows;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            c = real_min + j * real_step + (imag_max - i * imag_step) * I;
            z = 0.0 + 0.0 * I;
            int iteration = 0;
            while (cabs(z) <= 2.0 && iteration < max_iterations) {
                z = z * z + c;
                iteration++;
            }
            mandelbrot_set[i][j] = iteration;
        }
    }
    return mandelbrot_set;
}
