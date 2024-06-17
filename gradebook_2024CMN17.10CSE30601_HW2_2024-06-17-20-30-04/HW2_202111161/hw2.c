// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

// This implementation is simply copied from "main.c".
// Your job is to modify and optimize it for better performance!

void filter_optimized(void* args[]) {
    register int width = *(int*)args[0];
    register int height = *(int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    register float* filter = args[4];
	
    Pixel p;
    

    for (register int y = 0; y < height; ++y) {
	    for (register int x = 0; x < width; ++x){
        
            	
		
            	register float r = 0;
	    	register float g = 0;	
	    	register float b = 0;
		register int f;
		register int index = x+y*width;

		if ((y - 1) >= 0){
			
			
			
			if ((x - 1) >= 0){

				
				
				p = input[index-1-width];
				f = filter[0];
            			r += p.r * f;
            			g += p.g * f;
            			b += p.b * f;
			}
	
			
			
			
			p = input[index-width];
			f = filter[1];
	       	     	r += p.r * f;
	            	g += p.g * f;
	            	b += p.b * f;

	

			if((x + 1) < width){
				
			
				p = input[index+1-width];
	            		f = filter[2];
				r += p.r * f;
	            		g += p.g * f;
	            		b += p.b * f;
			}

		}


		
		

		
		if ((x - 1) >= 0){

			
			
			p = input[index-1];
			f = filter[3];
            		r += p.r * f;
            		g += p.g * f;
            		b += p.b * f;
		}


		
		
		
		p = input[index];
		f = filter[4];
            	r += p.r * f;
            	g += p.g * f;
            	b += p.b * f;



		if((x + 1) < width){
			
				
			p = input[index+1];
            		f = filter[5];
			r += p.r * f;
            		g += p.g * f;
            		b += p.b * f;
		}



		if((y + 1) < height){
			
	
			if ((x - 1) >= 0){
	
				
				
				p = input[index+width-1];
	            		f = filter[6];
				r += p.r * f;
	            		g += p.g * f;
	            		b += p.b * f;
			}



		
			
			
			p = input[index+width];
			f = filter[7];
        	    	r += p.r * f;
        	    	g += p.g * f;
            		b += p.b * f;



			if((x + 1) < width){
	
				
				p = input[index+width+1];
            			f = filter[8];
				r += p.r * f;
				g += p.g * f;
            			b += p.b * f;
			}
		}


		
		
		output[index].r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    		output[index].g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    		output[index].b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
            

	
	    }            
        
    }

}
