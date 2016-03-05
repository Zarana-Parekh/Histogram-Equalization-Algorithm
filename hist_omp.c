/*
    parallel program for histogram equalisation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include "bmp.h"

// declare image dimensions and size as constant global variables
const int image_width = 512;
const int image_height = 512;
const int image_size = 512*512;
const int color_depth = 255;

int main(int argc, char** argv){

    if(argc != 3){
        printf("Usage: %s image n_threads\n", argv[0]);
        exit(-1);
    }
    int n_threads = atoi(argv[2]);

    // read from the input bmp image file
    unsigned char* image = read_bmp(argv[1]);
    unsigned char* output_image = malloc(sizeof(unsigned char) * image_size);

    // create a histogram for the pixel values
    int* histogram = (int*)calloc(sizeof(int), color_depth);
#pragma omp parallel for num_threads(n_threads)
    for(int i = 0; i < image_size; i++){
        int image_val = image[i]; 
        // histogram[] is a shared variable, hence to avoid race conditions, critical clause has been used
#pragma omp critical
        histogram[image_val]++;
    }


    float* transfer_function = (float*)calloc(sizeof(float), color_depth);
    
    // finding the normalised values using cumulative mass function
    // different scheduling clauses can be used here for comparative analysis
#pragma omp parallel for num_threads(n_threads) schedule(static,1) 
    for(int i = 0; i < color_depth; i++){
        float sum = 0.0;
        for(int j = 0; j < i+1; j++){
            sum += (float)histogram[j];
        }
        transfer_function[i] += color_depth*((float)sum)/(image_size);
    }


#pragma omp parallel for num_threads(n_threads)
    for(int i = 0; i < image_size; i++){
        output_image[i] = transfer_function[image[i]];
    }

    // write data to output bmp image file
    write_bmp(output_image, image_width, image_height);
}