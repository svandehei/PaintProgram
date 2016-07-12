//
// Tool.h
//
// group App

#ifndef TOOL_H
#define TOOL_H

#include "PixelBuffer.h"
#include "ColorData.h"


class Tool
{
 public:
	Tool();
	virtual ~Tool();
	//Function set to 0 to indicate pure virtual function
	virtual void apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor) = 0;
};

#endif
