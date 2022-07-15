/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

void processCLI(int argc, char **argv, char **filename)
{
    if (argc != 2) {
        printf("usage: %s filename\n",argv[0]);
        printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
        exit(-1);
    }
    *filename = argv[1];
}

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
    uint32_t totCols = image->cols;
    int idx = col + row * totCols;
    Color* imageColor = *(image->image + idx);
    Color* colr = (Color *) malloc(sizeof(Color));
    int LSB = (imageColor->B)&1;
    colr->R = LSB*255;
    colr->G = LSB*255;
    colr->B = LSB*255;
    return colr;
}

// Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
    uint32_t totRows = image->rows;
    uint32_t totCols = image->cols;
    uint32_t totPix = totRows * totCols;

    Image* newImg = (Image *) malloc(sizeof(Image));
    newImg->rows = image->rows;
    newImg->cols = image->cols;
    newImg->image = (Color**) malloc(totPix*sizeof(Color*));
    Color ** pCol = newImg->image;
    for (int i = 0; i < totRows; i++){
        for (int j = 0; j < totCols; j++){
            *pCol = evaluateOnePixel(image, i, j);
            pCol++;
        }
    }
    return newImg;
}
/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    char* filename;
    processCLI(argc,argv,&filename);
    Image * image = readData(filename);
    Image * newImg = steganography(image);
    writeData(newImg);
    freeImage(image);
    freeImage(newImg);
    int a = 1;
}
