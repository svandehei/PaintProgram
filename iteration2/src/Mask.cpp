/*
Mask.cpp
Created by 3081 Group App
*/


#include "Mask.h"

Mask::Mask()
{
//    m_mask = NULL
    m_height = 0;
    m_width = 0;
}

Mask::Mask(std::vector<std::vector<float> > maskData): m_mask(maskData)
{
    m_height = m_mask.size();
    m_width = m_mask[0].size();
}

Mask::Mask(int height, int width): m_height(height), m_width(width)
{
    m_mask.resize(m_height);
    for (int i = 0; i < m_height; i++)
    {
        m_mask[i].resize(m_width);
        for(int j = 0; j < m_width; j++)
        {
            m_mask[i][j] = 0.0;
        }
    }
}

Mask::~Mask()
{
}

int Mask::getHeight()
{
    return m_height;
}

int Mask::getWidth()
{
    return m_width;
}

const std::vector<std::vector<float> > & Mask::get_mask()
{
    return this->m_mask;
}

void Mask::setSimpleRectangularMask(float opacity)
{
    for(int i = 0; i < m_height; i++)
    {
        for(int j = 0; j < m_width; j++)
        {
                m_mask[i][j] = opacity;
        }
    }
}

void Mask::setSimpleSquareMask(float opacity)
{
    this->setSimpleRectangularMask(opacity);
}

void Mask::setSprayCanMask()
{

    int offs = m_height/2;

    for (int i = 0; i < m_height; i++)
    {
        int ioffs = i - offs;
        //storing this saves some calculations later

        for (int j = 0; j < m_width; j++)
        {
            int joffs = j - offs;
            //this equation uses the index's distance from the center of the mask to calculate the opacity (linear falloff)
            float opacval = 0.2 - ( (float)(0.2/offs) * (float) sqrtf( (float) ((ioffs*ioffs) + (joffs*joffs))  ) );

            if (opacval <= 0.0)
            {
                m_mask[i][j] = 0.0;
            }
            else
            {
                m_mask[i][j] = opacval;
            }
        }
    }
}

void Mask::setCrayonMask()
{

    //iterate through each column
    for(int i = 0; i < m_height; i++)
    {
        //iterate through each row
        for(int j = 0; j < m_width; j++)
        {
            //Creating random opacity values for crayon look
            m_mask[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }
    }
}

void Mask::setCircleMask(float opacity)
{

    int offs = m_height/2;
    for(int i = 0; i < m_height; i++)
    {
        int ioffs = i - offs;
        for(int j = 0; j < m_width; j++)
        {
            int joffs = j - offs;
            float hyp = sqrt(ioffs*ioffs + joffs*joffs);
            if (hyp > (m_width / 2)) { //we will need a slight change here for ovals
                m_mask[i][j] = 0.0;
            } else {
                m_mask[i][j] = opacity;
            }
        }
    }
}
