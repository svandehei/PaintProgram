/*
FQuantize.h
Created by 3081 Group App
*/


#ifndef FQUANTIZE_H
#define FQUANTIZE_H

#include "Filter.h"

class FQuantize : public Filter
{
 public:
    FQuantize(int *intlevel);

 private:
    void filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel);
};


#endif
