#ifndef ERASER_H
#define ERASER_H
#include "Mask.h"
#include "Tool.h"
class Eraser : public Tool
{
	public:
	Eraser():Tool(Mask::getSimpleSquareMask(3, 1.0), 3, 3)
	{
		
	}
};

#endif
