//
// Highlighter.h
//

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "Mask.h"
#include "Tool.h"

class Highlighter : public Tool
{
   public:
   Highlighter():Tool(Mask::getSimpleRectangularMask(15, 5, 0.4), 15, 5)
   {
      
   }


};

#endif
