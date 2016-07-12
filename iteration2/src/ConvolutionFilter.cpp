/*
ConvolutionFilter.h
Created by 3081 Group App
*/

#include "ConvolutionFilter.h"

ConvolutionFilter::ConvolutionFilter()
{
}

ConvolutionFilter::ConvolutionFilter(float *level) : m_level(level)
{
}

ConvolutionFilter::ConvolutionFilter(float *level, int *ftype) : m_level(level), m_blurDirection(ftype)
{
}

ConvolutionFilter::~ConvolutionFilter()
{
}

void ConvolutionFilter::createMatrix()
{
}

void ConvolutionFilter::apply(PixelBuffer *canvas)
{
    createMatrix();
    int canHeight = canvas->getHeight();
    int canWidth = canvas->getWidth();

    PixelBuffer * temp_canvas = new PixelBuffer(canWidth, canHeight, canvas->getBackgroundColor());
 	canvas->copyPixelBuffer(canvas, temp_canvas);

	for(int j = 0; j < canHeight; j++)
	{
		for(int i = 0; i < canWidth; i++)
		{
			ColorData pixel = temp_canvas->getPixel(i, j);
			//takes in the temp_canvas without editing it, and use those values to compute a new pixel
			//then resets appropriate pixel in canvas.
            filterfunc(i, j, temp_canvas, canvas);
		}
	}
	delete temp_canvas;
}
