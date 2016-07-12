//
// Tool.h
//
// group App

#ifndef TOOL_H
#define TOOL_H

#include "Mask.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <vector>


class Tool 
{
 public:
	Tool(Mask mask, int height, int width):mask(mask),height(height),width(width)
	{
		
	}

	virtual ~Tool();
	int getHeight()
	{
		return height;
	}
	int getWidth()
	{
		return width;
	}
	
	void apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor);

 protected:
	Mask mask;
	
	//Masks are square, this is the length of one side
	int height;
	int width;
};

#endif
