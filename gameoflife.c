/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE: Chao Wang (Dalhousie University)
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

int circular(int n, int m){
    return (n + m) % m;
}

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void processCLI(int argc, char **argv, char **filename)
{
    if (argc != 3) {
        printf("usage: %s filename rule\n",argv[0]);
        printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
        printf("rule is a hex number beginning with 0x; Life is rule is a hex number beginning with 0x; Life is 0x1808.");
        exit(-1);
    }
    *filename = argv[1];
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
    Color * cell = (Color*) malloc (sizeof(Color));
    Color ** img = image->image;
    uint32_t totRows = image->rows;
    uint32_t totCols = image->cols;

    // *(img + idx) should be the Color* where we want
    int idx = col + row * totCols;

    uint8_t R = (*(img+idx))->R;
    uint8_t G = (*(img+idx))->G;
    uint8_t B = (*(img+idx))->B;

    int isAliveR = R == 255;
    int isAliveG = G == 255;
    int isAliveB = B == 255;

    int aliveNeighboursR = 0;
    int aliveNeighboursG = 0;
    int aliveNeighboursB = 0;

    for(int i = 0; i < 8; i++){
        int neighbourRow = circular(row + dx[i], totRows);
        int neighbourCol = circular(row + dy[i], totCols);
        int neighbourIdx = neighbourCol + neighbourRow * totCols;

        uint8_t neighbourColorR = (*(img+neighbourIdx))->R;
        uint8_t neighbourColorG = (*(img+neighbourIdx))->G;
        uint8_t neighbourColorB = (*(img+neighbourIdx))->B;

        if (neighbourColorR == 255){
            aliveNeighboursR++;
        }

        if (neighbourColorG == 255){
            aliveNeighboursG++;
        }

        if (neighbourColorB == 255){
            aliveNeighboursB++;
        }
    }

    // after for loops, we have the code now
    int codeR = 9 * isAliveR + aliveNeighboursR;
    int codeG = 9 * isAliveG + aliveNeighboursG;
    int codeB = 9 * isAliveB + aliveNeighboursB;

    cell -> R = (rule & (1 << codeR)) ? 255: 0;
    cell -> G = (rule & (1 << codeG)) ? 255: 0;
    cell -> B = (rule & (1 << codeB)) ? 255: 0;

    return cell;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
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
            *pCol = evaluateOneCell(image, i, j, rule);
            pCol++;
        }
    }
    return newImg;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    char* filename;
    uint32_t rule;
    processCLI(argc,argv,&filename);
    Image * image = readData(filename);
    rule = strtol(argv[2], NULL, 16);
    Image * newImg = life(image, rule);
    writeData(newImg);
    freeImage(image);
    freeImage(newImg);
    int a = 1;
}

