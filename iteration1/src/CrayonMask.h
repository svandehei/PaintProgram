#ifndef CRAYONMASK_H
#define CRAYONMASK_H
#include <stdlib.h>
#include "Mask.h"
class CrayonMask : public Mask
{
	public:
	CrayonMask():Mask(getCrayonMask(10))
	{
		
	}
	
	static Mask getCrayonMask(int size)
	{
		std::vector<std::vector<float> > mask;
		mask.resize(size);
		//iterate through each column
		for(int i = 0; i < size; i++)
		{
			mask[i].resize(size);
			//iterate through each row
			for(int j = 0; j < size; j++)
			{
				//Creating random opacity values for crayon look
				mask[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
			}
		}
		return Mask(mask);
	}
};

#endif
