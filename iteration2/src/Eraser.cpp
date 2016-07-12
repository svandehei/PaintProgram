/*
Eraser.cpp
Created by 3081 Group App
Eraser is a 21 x 21 circular mask. Its color is always set to the background color of the canvas. This is
    taken care of inside of FlashPhotoApp.cpp
*/

#include "Eraser.h"

Eraser::Eraser(): MaskTool(21, 21)
{
    m_mask->setCircleMask(1.0);
}
