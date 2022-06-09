//
// Created by lmwang4321 on 2022-06-07.
//

//
// Created by lmwang4321 on 2022-06-07.
//

/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object.
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{


    FILE * fp = fopen(filename, "r");
    if (fp == NULL){
        printf("file does not exist.");
        return 0;
    }
    char type[3];
    uint32_t rows;
    uint32_t cols;
    uint8_t  maxColor;
    fscanf(fp, "%s", type);
    if (strcmp(type, "P3") != 0){
        printf("file need to be P3 formatted");
        return 0;
    }
    fscanf(fp, "%u %u %hhu", &rows, &cols, &maxColor);
    Image * img = (Image *) malloc(sizeof(Image));
    // Color * color;
    img->image = (Color**) malloc(rows*cols*sizeof(Color*));
    img->rows = rows;
    img->cols = cols;
    uint8_t R;
    uint8_t G;
    uint8_t B;
    int i = 0;
    while (fscanf(fp, "%hhu %hhu %hhu", &R, &G, &B) == 3){
        *(img->image+i) = (Color *) malloc(sizeof(Color));

        (*(img->image+i))->R = R;
        (*(img->image+i))->G = G;
        (*(img->image+i))->B = B;
        i++;
    }
    fclose(fp);
    return img;
    //YOUR CODE HERE
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
    //YOUR CODE HERE
    Color ** img = image -> image;
    uint32_t rows = image->rows;
    uint32_t cols = image->cols;
    printf("P3\n%d %d\n%d\n", rows, cols, 255);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols - 1; j++){
            printf("%3hhu %3hhu %3hhu   ", (*img) -> R, (*img) -> G, (*img) -> B);
            img++;
        }
        printf("%3hhu %3hhu %3hhu\n", (*img) -> R, (*img) -> G, (*img) -> B);
        img++;
    }
}

//Frees an image
void freeImage(Image *image)
{
    Color ** img = image -> image;
    uint32_t rows = image->rows;
    uint32_t cols = image->cols;
    uint32_t totPixels = rows * cols;
    for (int i = 0; i < totPixels; i++) {
        free(*(img+i));
    }
    free(img);
    free(image);
    //YOUR CODE HERE
}
