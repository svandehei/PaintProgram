/*
Mask.h
Created by 3081 Group App
*/

#ifndef MASK_H
#define MASK_H

#include <vector>
#include <math.h>
#include <cmath>
#include <iostream>

class Mask
{

 public:
    Mask();
    Mask(std::vector<std::vector<float> > maskData);
    Mask(int height, int width);
    ~Mask();


    int getHeight();
    int getWidth();
	const std::vector<std::vector<float> > &get_mask();
	void setSimpleRectangularMask(float opacity);
	void setSimpleSquareMask(float opacity);
	void setCircleMask(float opacity);
	void setSprayCanMask();
	void setCrayonMask();

 private:
    std::vector<std::vector<float>> m_mask;
    //using 2d vector structure to structure mask
    int m_height;
    int m_width;

};

#endif
