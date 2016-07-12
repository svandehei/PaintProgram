/*
FThreshold.cpp
Created by 3081 Group App
*/


#include "FThreshold.h"
#include <iostream>


FThreshold::FThreshold(float *level): Filter(level)
{
}


void FThreshold::filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel)
{
    ColorData *pixel_replace = new ColorData();
    float r = pixel->getRed();
    float g = pixel->getGreen();
    float b = pixel->getBlue();
    if (r >= *m_level)
    {
        pixel_replace->setRed(1.0);
    }
    else
    {
        pixel_replace->setRed(0.0);
    }

    if (g >= *m_level)
    {
        pixel_replace->setGreen(1.0);
    }
    else
    {
        pixel_replace->setGreen(0.0);
    }

    if (b >= *m_level)
    {
        pixel_replace->setBlue(1.0);
    }
    else
    {
        pixel_replace->setBlue(0.0);
    }

    canvas->setPixel(x, y, *pixel_replace);
}
