#include "Tool.h"
#include <iostream>

Tool::~Tool(){}
void Tool::apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor)
{
	//creating tool mask offsets for the boundary checking
	int toolHeight = this->getHeight();
	int toolWidth = this->getWidth();
	int x_offset;
	int y_offset;
	int canvas_w = pixelbuff->getWidth();
	int canvas_h = pixelbuff->getHeight();
	ColorData pixel;
	const std::vector<std::vector<float> > &tool_mask = this->mask.get_mask();
	
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
			
			pixel = pixelbuff->getPixel(x_offset, y_offset);
			pixel.setRed((pixel.getRed()*(1 - tool_mask[i][j])) + (curColor.getRed()*tool_mask[i][j]));
			pixel.setBlue((pixel.getBlue()*(1 - tool_mask[i][j])) + (curColor.getBlue()*tool_mask[i][j]));
			pixel.setGreen((pixel.getGreen()*(1 - tool_mask[i][j])) + (curColor.getGreen()*tool_mask[i][j]));
			pixel.setAlpha((pixel.getAlpha()*(1 - tool_mask[i][j])) + tool_mask[i][j]);
			pixelbuff->setPixel(x_offset, y_offset, pixel);
		}
	}
}
