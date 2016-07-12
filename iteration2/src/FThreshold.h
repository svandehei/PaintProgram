/*
FThreshold.h
Created by 3081 Group App
*/


#ifndef FTHRESHOLD_H
#define FTHRESHOLD_H

#include "Filter.h"

class FThreshold : public Filter
{
 public:
    FThreshold(float *level);

 private:
    void filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel);
};


#endif
