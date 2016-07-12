#ifndef PEN_H
#define PEN_H
#include "Mask.h"
#include "Tool.h"
class Pen : public Tool
{
	public:
	Pen():Tool(Mask::getSimpleSquareMask(3, 1.0), 3, 3)
	{
		
	}
};

#endif
