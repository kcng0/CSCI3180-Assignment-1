/*

CSCI 3280, Introduction to Multimedia Systems
Spring 2021

Assignment 01 Skeleton

ascii.cpp

*/
using namespace std;
#include <string.h>
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
    // input: ascii2 <s/other character> <bmp file name> <resize dimension> <save bmp file name>
	//
    // function: resize to specific height and width and save bmp files and output in html format colored ascii art
    //
	//	 Open BMP file
	//
	Bitmap image_data(argv[2]);
	if(image_data.getData() == NULL)
	{
		printf("unable to load bmp image!\n");
		return -1;
	}
    Bitmap ascii[8] = {("./shades/0.bmp"),("./shades/1.bmp"),("./shades/2.bmp"),("./shades/3.bmp"),("./shades/4.bmp"),("./shades/5.bmp"),("./shades/6.bmp"),("./shades/7.bmp")};


	int height = image_data.getHeight();
	int width = image_data.getWidth();
	

	int new_height,new_width;
	

	

	
	char w[10],h[10];
	int pos_of_x = 0;
	double w_scale, h_scale;

	
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
	//
	//   Resize image
	//
	
	w_scale = width / (double) new_width;
    h_scale = height / (double) new_height;
	printf("New_height is : %d \nNew_width is : %d \n",new_height,new_width);

	Bitmap newimage(new_width, new_height);
    double *quant = (double *)malloc(10*new_height*new_width*sizeof(double));
	double merge;
    int r,g,b;
    unsigned char tr,tg,tb;
    printf("w_scale : %.3f h_scale : %.3f\n",w_scale,h_scale);
	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			r = 0;
            g = 0;
            b = 0;
			for (int k = (int) round(i*h_scale); k < (int) round((i+1)*h_scale); k++)
				for (int l = (int) round(j*w_scale); l < (int) round((j+1)*w_scale); l++) {
                    image_data.getColor(l,k,tr,tg,tb);
                    r += tr;
                    g += tg;
                    b += tb;
				}
			r = (int) round( r / ((round((i+1)*h_scale)-round(i*h_scale)) * (round((j+1)*w_scale)-round(j*w_scale))));
			g = (int) round( g / ((round((i+1)*h_scale)-round(i*h_scale)) * (round((j+1)*w_scale)-round(j*w_scale))));
			b = (int) round( b / ((round((i+1)*h_scale)-round(i*h_scale)) * (round((j+1)*w_scale)-round(j*w_scale))));
            newimage.setColor(j,i,r,g,b);
            *(quant + i*width + j) = floor((0.299*r + 0.587*g + 0.114*b)/(256/8));
		}
	}
	//   ASCII bmp file
	Bitmap ascii_image(8*new_width,8*new_height);
	for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            int temp = *(quant + i*width + j);
            if (argv[1][0] == 's') temp = 7 - temp;
            for (int k = i*8; k < (i+1)*8; k++) {
                for (int l = j*8; l < (j+1)*8; l++) {
                    ascii[temp].getColor(l - j*8 ,k - i*8 ,tr,tg,tb);
                    
                    ascii_image.setColor(l,k,tr,tg,tb);
                }
            }
        }
    }
    ascii_image.save(argv[4]);
    
    // Free memory
	SAFE_FREE(quant);

	}

	


	return 0;
} 
