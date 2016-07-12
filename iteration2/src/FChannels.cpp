/*
FChannels.cpp
Created by 3081 Group App
*/


#include "FChannels.h"
#include <iostream>


FChannels::FChannels(float *r_level, float *g_level, float *b_level): Filter(r_level, g_level, b_level)
{
}


void FChannels::filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel)
{
    ColorData *pixel_replace = new ColorData();
    float r = pixel->getRed();
    float g = pixel->getGreen();
    float b = pixel->getBlue();

    pixel_replace->setRed(*m_rlevel * r);
    pixel_replace->setGreen(*m_glevel * g);
    pixel_replace->setBlue(*m_blevel * b);

    canvas->setPixel(x, y, *pixel_replace);
}