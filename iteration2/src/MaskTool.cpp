/*
MaskTool.cpp
Created by 3081 Group App
*/

#include "MaskTool.h"
#include <iostream>


MaskTool::MaskTool(int height, int width)
{
    m_mask.reset(new Mask(height, width));
}

MaskTool::~MaskTool() {}

void MaskTool::apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor)
{
    if (m_mask == NULL)
    {
        printf("Tried to draw with a tool with no mask");
    }

	//creating tool mask offsets for the boundary checking
	int toolHeight = m_mask->getHeight();
	int toolWidth = m_mask->getWidth();
	int x_offset;
	int y_offset;
	int canvas_w = pixelbuff->getWidth();
	int canvas_h = pixelbuff->getHeight();
	ColorData pixel;
	const std::vector<std::vector<float> > &tool_mask = this->m_mask->get_mask();

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

            // Because we interpolate the pixels, colors overlap
			// and increase intensity quickly. We found that cubing
			// the mask intensity compensated for this.
			float slimmaskval = powf(tool_mask[i][j],2);


			pixel.setRed((pixel.getRed()*(1 - slimmaskval)) + (curColor.getRed()*slimmaskval));
			pixel.setBlue((pixel.getBlue()*(1 - slimmaskval)) + (curColor.getBlue()*slimmaskval));
			pixel.setGreen((pixel.getGreen()*(1 - slimmaskval)) + (curColor.getGreen()*slimmaskval));
			pixel.setAlpha((pixel.getAlpha()*(1 - slimmaskval)) + slimmaskval);
			pixelbuff->setPixel(x_offset, y_offset, pixel);
		}
	}
}
