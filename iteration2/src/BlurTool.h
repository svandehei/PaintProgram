/*
BlurTool.h
Created by 3081 Group App
*/

#ifndef BLURTOOL_H
#define BLURTOOL_H
#include <memory>
#include "Mask.h"
#include "MaskTool.h"

class BlurTool : public MaskTool
{
 public:
	BlurTool();
	void apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor);

};

#endif
