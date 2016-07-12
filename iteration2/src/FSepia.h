/*
FSepia.h
Created by 3081 Group App
*/


#ifndef FSEPIA_H
#define FSEPIA_H

#include "Filter.h"

class FSepia : public Filter
{
 public:
    FSepia();

 private:
    void filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel);
};


#endif
