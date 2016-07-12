#ifndef SPRAYCAN_H
#define SPRAYCAN_H
#include "Mask.h"
#include "Tool.h"
class SprayCan : public Tool
{
	public:
        SprayCan():Tool(Mask::getSprayCanMask(41), 41, 41)
	{
		
	}
};

#endif
