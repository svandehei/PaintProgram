/*
FSharpen.h
Created by 3081 Group App
*/


#ifndef FSHARPEN_H
#define FSHARPEN_H

#include "ConvolutionFilter.h"

class FSharpen : public ConvolutionFilter
{
 public:
    FSharpen(float *level);


 private:
    void filterfunc(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas);
    void createMatrix();
};


#endif
