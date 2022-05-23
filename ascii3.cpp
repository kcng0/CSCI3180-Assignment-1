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
    // input: ascii2 <bmp file name> <resize dimension>  <save bmp file name> <html file name>
	//
    // function: resize to specific height and width and save bmp files and output in html format colored ascii art
    //
	//	 Open BMP file
	//
	Bitmap image_data(argv[1]);
	if(image_data.getData() == NULL)
	{
		printf("unable to load bmp image!\n");
		return -1;
	}
	//
	//
	//	 Obtain Luminance
	//
	int height = image_data.getHeight();
	int width = image_data.getWidth();
	

	int new_height,new_width;
	
	

	
	char w[10],h[10];
	int pos_of_x = 0;
	double w_scale, h_scale;
	if (argc > 1)
	{
		for (int i = 0; i < strlen(argv[2]); i++) {
			if (argv[2][i] == 'x') { 
				pos_of_x = i;
				continue;
				}

			if (pos_of_x == 0) w[i] = argv[2][i];
			else if (pos_of_x != 0) h[i-pos_of_x-1] = argv[2][i];
		
	}
	new_height = stoi(h);
	new_width = stoi(w);
	// printf("Orignal New Height: %d New Width %d \n", new_height, new_width);

	}
	
	
	if (argc > 2)
	{
	//
	//   Resize image
	//
	
	w_scale = width / (double) new_width;
    h_scale = height / (double) new_height;
	printf("New_height is : %d \nNew_width is : %d \n",new_height,new_width);

	Bitmap newimage(new_width, new_height);

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
			r = (int) round( r / ((round((i+1)*h_scale)-round(i*h_scale)) * (round((j+1)*w_scale)-round(j*w_scale)))) ;
			g = (int) round( g / ((round((i+1)*h_scale)-round(i*h_scale)) * (round((j+1)*w_scale)-round(j*w_scale))));
			b = (int) round( b / ((round((i+1)*h_scale)-round(i*h_scale)) * (round((j+1)*w_scale)-round(j*w_scale))));
            newimage.setColor(j,i,r,g,b);
		}
	}
    newimage.save(argv[3]);
	//   ASCII html file
	FILE *html;
    int temp;
    char color[7];
    char c;
    unsigned char rgb[4];
	html = fopen( argv[4] , "w");
    fputs("<html>\n<body bgcolor = #ffffff>\n<font face = \"Courier New\">\n",html);
	fputs("<p style = \" line-height:0.625\">", html);
    for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
            newimage.getColor(j,i,rgb[0],rgb[1],rgb[2]);
            fputs("<font color = #",html);
            int x = 0;
            strcpy(color,"");
            while (3>x) {
            temp = rgb[x] % 16;
            if (temp >= 10) {
                color[x*2 + 1] = temp + 55;
            }
            else color[x*2 + 1] = temp + 48;
            temp = rgb[x] / 16 % 16;
            if (temp >= 10) {
                color[x*2] = temp + 55;
            }
            else color[x*2] = temp + 48;

            x++;
            } 
            fprintf(html, "%.6s",color);
           
            fputc('>',html);
            char temp_c = round(33+(rgb[0]+rgb[1]+rgb[2])/((double)765/93));
            fputc(temp_c,html);
            fputs("</font>",html);
        }
        fputs("<br>\n",html);
    }
    fputs("</body>\n</html>",html);
	fclose(html);
	printf("Save success!");
	
	

	}

	


	return 0;
} 
