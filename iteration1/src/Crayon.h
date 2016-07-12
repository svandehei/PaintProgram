#ifndef CRAYON_H
#define CRAYON_H
#include "CrayonMask.h"
#include "Tool.h"
class Crayon : public Tool
{
	public:
	Crayon():Tool(CrayonMask::getCrayonMask(10), 10, 10)
	{
		
	}

};

#endif
