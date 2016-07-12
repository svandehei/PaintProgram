/*
Filter.cpp
Created by 3081 Group App
Has an apply function which takes in a PixelBuffer object and calls filterfunc on each pixel. Filterfunc is
    specified in each individual filter.
*/


#include "Filter.h"
#include <iostream>
Filter::Filter()
{
}

Filter::Filter(float *level)
{
    m_level = level;
}
Filter::Filter(int *intlevel)
{
	m_intlevel = intlevel;
}
Filter::Filter(float *r_level, float *g_level, float *b_level)
{
	m_rlevel = r_level;
	m_glevel = g_level;
	m_blevel = b_level;
}

Filter::~Filter()
{
}

void Filter::apply(PixelBuffer *canvas)
{
    int canHeight = canvas->getHeight();
    int canWidth = canvas->getWidth();

	for(int j = 0; j < canHeight; j++)
	{
		for(int i = 0; i < canWidth; i++)
		{
			ColorData pixel = canvas->getPixel(i, j);
            filterfunc(i, j, canvas, &pixel);
		}
	}
}

void Filter::filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel)
{
}

void Filter::filterfunc(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas)
{
}
