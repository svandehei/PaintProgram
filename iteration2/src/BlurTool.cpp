/*
BlurTool.cpp
Created by 3081 Group App
Inherits from MaskTool, but overloads apply function which includes an instance of an FBlur object.
*/

#include "BlurTool.h"
#include "FBlur.h"

BlurTool::BlurTool(): MaskTool(71, 71)
{
    m_mask->setSprayCanMask();
}

void BlurTool::apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor)
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

	//set up FBlur object
	float blurval;
	FBlur blurfilter = FBlur(&blurval);

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

            // Because we interpolate the pixels, blur overlaps
			// and increases intensity quickly. We found that cubing
			// the mask intensity compensated for this.
			float slimmaskval = powf(tool_mask[i][j],3);

            //calls blurByPixel function within the blurfilter to replicate a blur brush
            if (slimmaskval != 0) {
                blurfilter.blurByPixel(x_offset, y_offset, pixelbuff, pixelbuff, &pixel, slimmaskval);
            }
		}
	}
}
