/*
MaskTool.h
Created by 3081 Group App
Inherits from Tool class, which is just a template for a tool structure.
MaskTool has a mask and apply function which iterates through a mask and uses values
    to set the colors/alpha of a pixel buffer
*/

#ifndef MASKTOOL_H
#define MASKTOOL_H

#include "Mask.h"
#include "Tool.h"
#include <memory> //necessary for unique_ptr

class MaskTool : public Tool
{
 public:
	MaskTool(int height, int width);
	MaskTool();
	virtual ~MaskTool();
	void apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor);

 protected:
	std::unique_ptr<Mask> m_mask;

	int m_height;
	int m_width;
};

#endif
