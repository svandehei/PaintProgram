/*
FQuantize.cpp
Created by 3081 Group App
*/


#include "FQuantize.h"
#include <iostream>
#include <math.h>


FQuantize::FQuantize(int *intlevel): Filter(intlevel)
{

}


void FQuantize::filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel)
{
    ColorData *pixel_replace = new ColorData();
    float r = pixel->getRed();
    float g = pixel->getGreen();
    float b = pixel->getBlue();
    float stepSize = 1.0 / (*m_intlevel);

    if(r < (stepSize / 2.0)){
    	pixel_replace->setRed(0);
    }
    if(g < (stepSize / 2.0)){
    	pixel_replace->setGreen(0);
    }
    if(b < (stepSize / 2.0)){
    	pixel_replace->setBlue(0);
    }
    if(r > stepSize){
    	float temp_r = ceil(r/stepSize);
   		pixel_replace->setRed(temp_r * stepSize);
    }
    if(g > stepSize){
    	float temp_g = ceil(g/stepSize);
   		pixel_replace->setGreen(temp_g * stepSize);
    }
    if(b > stepSize){
    	float temp_b = ceil(b/stepSize);
   		pixel_replace->setBlue(temp_b * stepSize);
    }

    canvas->setPixel(x, y, *pixel_replace);
}
