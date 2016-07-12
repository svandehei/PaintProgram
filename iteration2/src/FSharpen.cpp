/*
FSharpen.cpp
Created by 3081 Group App
*/


#include "FSharpen.h"
#include <iostream>
#include <math.h>


FSharpen::FSharpen(float *level): ConvolutionFilter(level)
{
}

void FSharpen::createMatrix()
{
    m_matrixSize = int(*m_level / 1.5);
    m_convMatrix.clear();
    if (!(m_matrixSize % 2))
    {
        m_matrixSize++;
    }

    m_convMatrix.resize(m_matrixSize);
    for (int i = 0; i < m_matrixSize; i++)
    {
        m_convMatrix[i].resize(m_matrixSize);
    }

    m_numElements = 0;
    int offs = m_matrixSize/2;
    for(int i = 0; i < m_matrixSize; i++)
    {
        int ioffs = i - offs;
        for(int j = 0; j < m_matrixSize; j++)
        {
            int joffs = j - offs;
            float hyp = sqrt(ioffs*ioffs + joffs*joffs);

            if (hyp > (m_matrixSize / 2)) { //we will need a slight change here for ovals
                m_convMatrix[i][j] = 0.0;
            } else {
                m_convMatrix[i][j] = -1.0;
                m_numElements++;
            }
        }
    }
    int mid = (m_matrixSize - 1) / 2;
    m_convMatrix[mid][mid] = m_numElements;
}

void FSharpen::filterfunc(int x, int y, PixelBuffer *temp_canvas, PixelBuffer *canvas)
{
    ColorData *pixel_replace = new ColorData();

    int w = temp_canvas->getWidth();
    int h = temp_canvas->getHeight();
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;

    //multiply every value of the filter with corresponding image pixel
    for(int filterY = 0; filterY < m_matrixSize; filterY++)
    {
        for(int filterX = 0; filterX < m_matrixSize; filterX++)
        {
            int imageX = (x - m_matrixSize / 2 + filterX + w) % w;
            int imageY = (y - m_matrixSize / 2 + filterY + h) % h;

            float pixelred, pixelgreen, pixelblue;

            pixelred = temp_canvas->getPixel(imageX, imageY).getRed();
            red += pixelred * m_convMatrix[filterY][filterX];
            pixelgreen = temp_canvas->getPixel(imageX, imageY).getGreen();
            green += pixelgreen * m_convMatrix[filterY][filterX];
            pixelblue = temp_canvas->getPixel(imageX, imageY).getBlue();
            blue += pixelblue * m_convMatrix[filterY][filterX];
        }
    }

    if (m_numElements > 0)
    {
        float factor = 1.0;
        pixel_replace->setRed((factor * red));
        pixel_replace->setGreen((factor * green));
        pixel_replace->setBlue((factor * blue));
    }
    else
    {
        printf("There are no elements in the convolution matrix. numEl is %d\n", m_numElements);
    }


    canvas->setPixel(x, y, *pixel_replace);
}
