/*
FSaturation.h
Created by 3081 Group App
*/


#ifndef FSATURATION_H
#define FSATURATION_H

#include "Filter.h"

class FSaturation : public Filter
{
 public:
    FSaturation(float *level);

 private:
    void filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel);
};


#endif
