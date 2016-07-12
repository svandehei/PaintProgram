/*
FChannels.h
Created by 3081 Group App
*/


#ifndef FCHANNELS_H
#define FCHANNELS_H

#include "Filter.h"

class FChannels : public Filter
{
 public:
    FChannels(float *r_level, float *g_level, float *b_level);

 private:
    void filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel);
};


#endif
