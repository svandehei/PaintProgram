/*
FSaturation.cpp
Created by 3081 Group App
*/


#include "FSaturation.h"
#include <iostream>


FSaturation::FSaturation(float *level): Filter(level)
{
}


void FSaturation::filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel)
{
    ColorData *pixel_replace = new ColorData();
    float l = pixel->getLuminance();
    float r = pixel->getRed();
    float g = pixel->getGreen();
    float b = pixel->getBlue();

    pixel_replace->setRed((*m_level * r) + ((1 - *m_level) * l));
    pixel_replace->setGreen((*m_level * g) + ((1 - *m_level) * l));
    pixel_replace->setBlue((*m_level * b) + ((1 - *m_level) * l));

    canvas->setPixel(x, y, *pixel_replace);
}
