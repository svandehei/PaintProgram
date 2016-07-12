/*
FEdgeDetect.h
Created by 3081 Group App
*/

#ifndef FEDGEDETECT_H
#define FEDGEDETECT_H

#include "ConvolutionFilter.h"

class FEdgeDetect : public ConvolutionFilter
{
 public:
    FEdgeDetect();


 private:
    void filterfunc(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas);
    void createMatrix();
};


#endif
