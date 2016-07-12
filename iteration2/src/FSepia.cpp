/*
FSepia.cpp
Created by 3081 Group App
*/


#include "FSepia.h"
#include <iostream>


FSepia::FSepia(): Filter()
{
}


void FSepia::filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel)
{
    ColorData *pixel_replace = new ColorData();

    float r = pixel->getRed();
    float g = pixel->getGreen();
    float b = pixel->getBlue();

    /* sepia filter formula found at:
    	https://software.intel.com/sites/default/files/article/346220/sepiafilter-intelcilkplus.pdf */
    pixel_replace->setRed((0.393 * r) + (0.769 * g) + (0.189 * b));
    pixel_replace->setGreen((0.349 * r) + (0.686 * g) + (0.168 * b));
    pixel_replace->setBlue((0.272 * r) + (0.534 * g) + (0.131 * b));


    canvas->setPixel(x, y, *pixel_replace);
}
