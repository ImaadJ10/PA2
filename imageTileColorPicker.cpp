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
  unsigned int width = img_other.width();
  unsigned int height = img_other.height();
  HSLAPixel color = *img_other.getPixel(p.x % width, p.y % height); 
  return color;
}