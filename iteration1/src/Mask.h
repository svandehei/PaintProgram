//
// Mask.h
//

#ifndef MASK_H
#define MASK_H

#include <vector>
#include <math.h>
#include <iostream>

class Mask
{

 public: 
	Mask(std::vector<std::vector<float> > maskData):mask(maskData)
	{ 
		
	}
	const std::vector<std::vector<float> > &get_mask() const
	{
		return this->mask;
	}
	static Mask getSimpleRectangularMask(int height, int width, float opacity)
	{
		std::vector<std::vector<float> > mask;
		mask.resize(height);
		for(int i = 0; i < height; i++)
		{
			mask[i].resize(width);
			for(int j = 0; j < width; j++)
			{
					mask[i][j] = opacity;
			}
		}
		return Mask(mask);
	}

	static Mask getSimpleSquareMask(int size, float opacity)
	{
		return getSimpleRectangularMask(size, size, opacity);
	}

	static Mask getSprayCanMask(int width)
	{
	        // allocate the vector mask
		std::vector<std::vector<float> > mask;
		mask.resize(width);
		int offs = width/2;
		
		for (int i = 0; i < width; i++)
		{
			mask[i].resize(width);
			int ioffs = i - offs; 
			//storing this saves some calculations later
		
			for (int j = 0; j < width; j++)
			{
				int joffs = j - offs;
				//this equation uses the index's distance from the center of the mask to calculate the opacity (linear falloff)
				float opacval = 0.2 - ( (float)(0.2/offs) * (float) sqrtf( (float) ((ioffs*ioffs) + (joffs*joffs))  ) );

				if (opacval <= 0.0) 
				{
					mask[i][j] = 0.0;
				}
				else 
				{
					mask[i][j] = opacval;
				}
			}
		}
		return Mask(mask);
	}

 private:
  std::vector<std::vector<float> > mask; 
  //using 2d vector structure to structure mask

};

#endif
