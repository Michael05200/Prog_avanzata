CC = gcc-13
CFLAGS = -fopenmp -Wall -Wextra -O3 -ftree-vectorize -fopt-info-vec -std=c17
LDFLAGS = -lm
OBJS = main.o mandelbrot.o pgm.o

.PHONY: clean all 

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o 

