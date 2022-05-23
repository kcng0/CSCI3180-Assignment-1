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
	// Program : pixelate the image with given filter size
	// Input format: ascii1 <bmp file> <filter size> <output file name>
	//
	// Open BMP file
	//
	Bitmap image_data(argv[1]);
	if(image_data.getData() == NULL)
	{
		printf("unable to load bmp image!\n");
		return -1;
	}

	int height = image_data.getHeight();
	int width = image_data.getWidth();
	int filter_h,filter_w;
	
    // reading the address of the color of image_data
	// printf("Height : %d \n Width : %d \n", height, width);
	// printf("arg[3] : %s\n argc : %d\n",argv[3],argc);
	
	
	char w[10],h[10];
	int pos_of_x = 0;
	int w_scale, h_scale, w_rem, h_rem;
	if (argc > 2)
	{
		for (int i = 0; i < strlen(argv[2]); i++) {
			if (argv[2][i] == 'x') { 
				pos_of_x = i;
				continue;
				}

			if (pos_of_x == 0) w[i] = argv[2][i];
			else if (pos_of_x != 0) h[i-pos_of_x-1] = argv[2][i];
		
	}
	filter_h = stoi(h);
	filter_w = stoi(w);

	// printf("Orignal New Height: %d New Width %d \n", new_height, new_width);

	}
	
	
	if (argc > 3)
	{
	//
	//  Resize image
	//

	Bitmap newimage(width, height);
	
	unsigned char  tr,tg,tb;
	int r,g,b;
	int w_r, h_r;
	int w_scale = width / filter_w;
	int h_scale = height / filter_h;
	// printf("filter_h: %d filter_w: %d\n",filter_h,filter_w);
	// printf("w_scale :%d h_scale:%d",w_scale,h_scale);
	w_r = width % filter_w;
	h_r = height % filter_h;
	
	for (int i = 0; i < h_scale; i++) {
		for (int j = 0; j < w_scale; j++) {
			r = 0;
			g = 0;
			b = 0;
			for (int k = i*filter_h; k < (i+1)*filter_h; k++) {
				for (int l = j*filter_w; l < (j+1)*filter_w; l++) {
					image_data.getColor(l,k,tr,tg,tb);
					r += tr;
					g += tg;
					b += tb;
				}
			}
			r = (int) round( (double) r / (filter_h*filter_w));
			g = (int) round( (double) g / (filter_h*filter_w));
			b = (int) round( (double) b / (filter_h*filter_w));
			for (int k = i*filter_h; k < (i+1)*filter_h; k++)
				for (int l = j*filter_w; l < (j+1)*filter_w; l++) {
					newimage.setColor(l,k,r,g,b);
				}
			
		}
	}
	for (int i = h_scale*filter_h; i < h_scale*filter_h + h_r; i++) 

		for (int j = 0; j < width; j++) {
			
			image_data.getColor(j,i-1,tr,tg,tb);
			
			newimage.setColor(j,i,tr,tg,tb);
		}
		
	for (int j = w_scale*filter_w; j < w_scale*filter_w + w_r; j++) 

		for (int i = 0; i < height; i++) {
			
			image_data.getColor(j-1,i,tr,tg,tb);
			newimage.setColor(j,i,tr,tg,tb);
			
		}
	newimage.save(argv[3]);
    // printf("i : %d j:%d\n",i , j);

	


	}

	


	return 0;
} 
