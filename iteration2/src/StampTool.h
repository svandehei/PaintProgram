/*
StampTool.h
Created by 3081 Group App
*/


#ifndef STAMPTOOL_H
#define STAMPTOOL_H
#include <memory>
#include "Tool.h"

class StampTool : public Tool
{
 public:
	StampTool();
	virtual ~StampTool();
	void apply(int xCoord, int yCoord, PixelBuffer *pixelbuff, ColorData curColor);
	void setStamp(PixelBuffer *stampImage);

 protected:
 	std::unique_ptr<PixelBuffer> m_stampImage;
};

#endif
