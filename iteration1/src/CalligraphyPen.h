//
// CalligraphyPen.h
//

#ifndef CALLIGRAPHYPEN_H
#define CALLIGRAPHYPEN_H

#include "Mask.h"
#include "Tool.h"

class CalligraphyPen : public Tool
{
   public:
   CalligraphyPen():Tool(Mask::getSimpleRectangularMask(15, 5, 1.0), 15, 5)
   {
      
   }


};

#endif
