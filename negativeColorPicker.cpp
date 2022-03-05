/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  img = inputimg;
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  HSLAPixel color = *img.getPixel(p.x, p.y);
  color.h = fmod(color.h + 180, 360);
  color.l = 1 - color.l;
  
  return color; 
}
