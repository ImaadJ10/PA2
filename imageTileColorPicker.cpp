/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) {
  img_other = otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) {
  HSLAPixel* otherPixel = img_other.getPixel(p.x, p.y);
  HSLAPixel color = p.color;
  color.h = otherPixel->h;
  color.s = otherPixel->s;
  color.l = otherPixel->l;
  color.a = otherPixel->a;
  
  return color;
}