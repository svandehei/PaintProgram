/*
CalligraphyPen.cpp
Created by 3081 Group App
Calligraphy Pen has a 15x5 rectangular mask
*/

#include "CalligraphyPen.h"

CalligraphyPen::CalligraphyPen(): MaskTool(15, 5)
{
    m_mask->setSimpleRectangularMask(1.0);
}
