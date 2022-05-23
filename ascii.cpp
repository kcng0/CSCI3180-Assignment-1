/*

CSCI 3280, Introduction to Multimedia Systems
Spring 2021

Assignment 01 Skeleton

ascii.cpp

*/
using namespace std;
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include "stdio.h"
#include "malloc.h"
#include "memory.h"
#include "math.h"
#include "bmp.h"		//	Simple .bmp library

#define MAX_SHADES 8
char shades[MAX_SHADES] = {'@','#','%','*','|','-','.',' '};

#define SAFE_FREE(p)  { if(p){ free(p);  (p)=NULL;} }

int main(int argc, char** argv) //argc: arguments number , argv: array indicates the number ith string
{
	//
	//	1. Open BMP file
	//
	Bitmap image_data(argv[2]);
	if(image_data.getData() == NULL)
	{
		printf("unable to load bmp image!\n");
		return -1;
	}
	//
	//	Your code goes here ....
	//
	//	2. Obtain Luminance
	//
	int height = image_data.getHeight();
	int width = image_data.getWidth();
	unsigned char r,g,b;
	image_data.getColor(50,50, r,g,b);
	printf("R: %d, G: %d B: %d", r,g,b);
	double *luma = (double *)malloc(10*height*width*sizeof(double));

	int *quant = (int *)malloc(10*height*width*sizeof(double));
	int new_height,new_width;
	
	Color * pc_data = image_data.getData(); // reading the address of the color of image_data
	// printf("Height : %d \n Width : %d \n", height, width);
	// printf("arg[3] : %s\n argc : %d\n",argv[3],argc);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			
			image_data.getColor(j, i, pc_data->R, pc_data->G, pc_data->B);
			*(luma + i*width + j) = 0.299 * (pc_data -> R) + 0.587 * (pc_data -> G) + 0.114 * (pc_data -> B);
			
		}
	}
	

	
	char w[10],h[10];
	int pos_of_x = 0;
	int w_scale, h_scale;
	if (argc > 2)
	{
		for (int i = 0; i < strlen(argv[3]); i++) {
			if (argv[3][i] == 'x') { 
				pos_of_x = i;
				continue;
				}

			if (pos_of_x == 0) w[i] = argv[3][i];
			else if (pos_of_x != 0) h[i-pos_of_x-1] = argv[3][i];
		
	}
	new_height = stoi(h);
	new_width = stoi(w);
	// printf("Orignal New Height: %d New Width %d \n", new_height, new_width);

	}
	
	
	if (argc > 3)
	{
	//
	//  3. Resize image
	//
	if (new_height == 0) {
		new_height = new_width;
		w_scale = ceil((double) width / new_width); 
		h_scale = w_scale;
		if (height / w_scale > new_height ) {
			h_scale = ceil((double) height / new_height);
			w_scale = h_scale;
		}
	}
	 else {
		w_scale = ceil((double) width / new_width);
	 	h_scale = ceil((double) height / new_height);
	 }
	new_height = (int) (height / h_scale);
	new_width = (int) (width / w_scale); 
	printf("New_height is : %d \nNew_width is : %d \n",new_height,new_width);


	double merge;
	double *new_luma = (double *)malloc(10*new_height*new_width*sizeof(double));

	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			merge = 0;
			for (int k = i*h_scale; k < (i+1)*h_scale; k++)
				for (int l = j*w_scale; l < (j+1)*w_scale; l++) {
					merge = merge + *(luma + k*width + l);
				}
			*(new_luma + i*width + j) = merge / (h_scale * w_scale);
		}
	}
	
	// 4. Quantization
	
	for (int i = 0; i < new_height ; i++) {
		for (int j = 0; j < new_width ; j++) {
			*(quant + i*width + j) = floor(*(new_luma + i*width + j)/256*8);
		}
	}

	//  free memory
	SAFE_FREE(new_luma);

	//  5. ASCII Mapping and printout
	

	if (argv[1][0] == 'p')
			for (int i = 0; i < new_height; i++) {
				for (int j = 0; j < new_width; j++) {
				printf("%c",shades[*(quant + i*width + j)]);
			}
			printf("\n");
		}
		else if (argv[1][0] == 's')
			for (int i = 0; i < new_height; i++) {
			for (int j = 0; j < new_width; j++) {
				printf("%c",shades[7-*(quant + i*width + j)]);
			}
			printf("\n");
		}

	//  6. ASCII art txt file
	FILE *ftxt;
	ftxt = fopen( argv[4] , "w");
	if (argv[1][0] == 'p') 
		for (int i = 0; i < new_height; i++) {
				for (int j = 0; j < new_width; j++) {
				fputc(shades[*(quant + i*width + j)], ftxt);
			}
				fputs("\n", ftxt);
		}
	else if (argv[1][0] == 's') 
		for (int i = 0; i < new_height; i++) {
				for (int j = 0; j < new_width; j++) {
				fputc(shades[7- *(quant + i*width + j)], ftxt);
			}
				fputs("\n", ftxt);
		}
		fclose(ftxt);
		printf("Save success!");
	
	

	}

	//  free memory
	SAFE_FREE(quant);
	SAFE_FREE(luma);
	


	return 0;
} 
