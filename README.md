# Histogram-Equalization-Algorithm

A comparitive analysis of the serial and parallel implementation of the Histogram Equalization algorithm that is widely used in image processing.

- bmp.c and bmp.h are used to read from and write to a bmp image file.
- histogram_serial.c is the serial implementation of the program.
- histogram_omp.c is the parallel implementation of the program

To compile, the serial version :
gcc -std=c99 -Wall hist_serial.c bmp.c -o hist_serial

To run the program : 
./hist_serial image_name

To compile the parallel program : 
gcc -std=c99 -Wall hist_omp.c bmp.c -o hist_omp -fopenmp

To run the program : 
./hist_omp image_name num_threads

The output image will be generated as out.bmp. This name can be changed in the write_bmp function in bmp.c.
