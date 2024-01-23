#include "mandelbrot.h"
#include "pgm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Pizzignacco Michael



int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <output_filename> <max_iterations> <nrows>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    int max_iterations = atoi(argv[2]);
    int nrows = atoi(argv[3]);
    int ncols = nrows * 1.5;

    // inizio conto tempo in cpu
    clock_t start = clock();

    // Calculate the Mandelbrot set
    int **mandelbrot_set = calculate_mandelbrot_set(nrows, ncols, max_iterations);

    clock_t end = clock();
    double time_spend = ((double) (end-start)/ CLOCKS_PER_SEC);
    printf("Time spent calculating the Mandelbrot set: %f seconds\n", time_spend);

    //start del clock ancora
    start = clock();
    // Save the image in PGM format
    map_mandelbrot_set(mandelbrot_set, nrows, ncols, max_iterations, filename);
    
    end = clock();
    double tempo_speso_cpu = ((double) (end - start)/ CLOCKS_PER_SEC);
    printf("il tempo speso per salvare l\'immagine è: %f second\n", tempo_speso_cpu);

    //verifica tempo per libero memoria
    start = clock();

    // Free the memory allocated for mandelbrot_set
    for (int i = 0; i < nrows; i++) {
        free(mandelbrot_set[i]);
    }
    free(mandelbrot_set);

    end = clock();
    double liberty_pizzi = ((double) (end -start) / CLOCKS_PER_SEC);
    printf("il tempo usato per liberare la memoria è: %f seconds\n", liberty_pizzi);

    double tempo_tot = liberty_pizzi + tempo_speso_cpu + time_spend;
    printf("il tempo speso in cpu totale per tutti i processi è: %f seconds, pizzi is best xd\n", tempo_tot);
    return 0;
}
