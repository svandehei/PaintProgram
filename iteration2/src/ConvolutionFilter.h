/*
ConvolutionFilter.h
Created by 3081 Group App
Inherits from Filter, but overloads the apply function to create a new matrix every time based on changes
    made to the user-specified variable "level"
*/

#ifndef CONVOLUTIONFILTER_H
#define CONVOLUTIONFILTER_H

#include "Filter.h"


class ConvolutionFilter : public Filter
{
 public:
 	ConvolutionFilter();
	ConvolutionFilter(float *level);
	ConvolutionFilter(float *level, int *ftype);
	~ConvolutionFilter();

	void apply(PixelBuffer *temp_canvas);

 protected:
    virtual void createMatrix(); // meant to be implemented inside of subclasses
    // uses member variables to create unique matrix for a ConvolutionFilter object
    // called within constructor


    // convolution matrix represented by 2D vector of floats
    // vector automatically deallocates itself and objects within it upon program end
    std::vector<std::vector<float>> m_convMatrix;

    float *m_level;
    int *m_blurDirection;
    int *m_blur;
    int m_matrixSize;
    int m_numElements;
};

#endif
