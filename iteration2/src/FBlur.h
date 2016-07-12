/*
FBlur.h
Created by 3081 Group App
Inherits from Convolution Filter. CreateMatrix creates a blur matrix, which is akin to a circle mask.
Also has a function blurByPixel which is similar to filterfunc but takes in a blur level and creates a new matrix every time it is called.
*/

#ifndef BLUR_H
#define BLUR_H

#include "ConvolutionFilter.h"

class FBlur : public ConvolutionFilter
{
 public:
    FBlur(float *level);
    void blurByPixel(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas, ColorData *pixel, float bluramount);


 private:
    void filterfunc(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas);
    void createMatrix();
};


#endif