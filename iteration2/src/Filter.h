//
// Filter.h
//
// group App

#ifndef FILTER_H
#define FILTER_H

#include "PixelBuffer.h"
#include "ColorData.h"
#include <vector>


class Filter
{
 public:
	Filter(float *level);
	Filter(int *intlevel);
	Filter(float *r_level, float *g_level, float *b_level);
    Filter();
	~Filter();
	void apply(PixelBuffer *canvas);

 protected:
    virtual void filterfunc(int x, int y, PixelBuffer *canvas, ColorData *pixel);
    virtual void filterfunc(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas);
    // takes coordinates for a pixel in canvas and sets pixel according to filter rules
    // also takes pixel value for simple pixel-only filtering

    float *m_level;
    int *m_intlevel;
    float *m_rlevel;
    float *m_glevel;
    float *m_blevel;
};

#endif
