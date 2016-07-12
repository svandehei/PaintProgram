/*
FMotionBlur.h
Created by 3081 Group App
*/


#ifndef MOTIONBLUR_H
#define MOTIONBLUR_H

#include "ConvolutionFilter.h"

class FMotionBlur : public ConvolutionFilter
{
 public:
    FMotionBlur(float *level, int *direction);


 private:
    void filterfunc(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas);
    void createMatrix();
};


#endif
