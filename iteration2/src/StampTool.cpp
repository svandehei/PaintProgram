/*
StampTool.cpp
Created by 3081 Group App
*/


#include "StampTool.h"
#include "png.h"
#include <setjmp.h>
#include "jpeglib.h"

StampTool::StampTool() {}

StampTool::~StampTool() {}

void StampTool::apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor)
{
	//Is there a stamp image? If not, return
	if(!m_stampImage)
	{
		return;
	}

	int toolHeight = m_stampImage->getHeight();
	int toolWidth = m_stampImage->getWidth();
	int x_offset;
	int y_offset;
	int canvas_w = pixelbuff->getWidth();
	int canvas_h = pixelbuff->getHeight();
	ColorData canvasPixel;
	ColorData stampPixel;

	//iterate through 2d vector
	for(int i = 0; i < toolHeight; i++)
	{
		y_offset = yCoord - (toolHeight/2) + i;
		if((y_offset < 0) || (y_offset >= canvas_h)) //Checking to see if mask goes out of bounds
		{
			continue;
		}

		for(int j = 0; j < toolWidth; j++)
		{
			x_offset = xCoord - (toolWidth/2) + j;
			if ((x_offset < 0) || (x_offset >= canvas_w)) //Checking to see if mask goes out of bounds
			{
				continue;
			}
			float alpha;
			stampPixel = m_stampImage->getPixel(j, i);
			canvasPixel = pixelbuff->getPixel(x_offset, y_offset);
			alpha = stampPixel.getAlpha();
			canvasPixel.setRed((1.0 - alpha) * (canvasPixel.getRed()) + (stampPixel.getRed() * alpha));
			canvasPixel.setGreen((1.0 - alpha) * (canvasPixel.getGreen()) + (stampPixel.getGreen() * alpha));
			canvasPixel.setBlue((1.0 - alpha) * (canvasPixel.getBlue()) + (stampPixel.getBlue() * alpha));
			pixelbuff->setPixel(x_offset, y_offset, canvasPixel);
		}
	}
}

void StampTool::setStamp(PixelBuffer *stampImage)
{
	m_stampImage.reset(stampImage);
}
