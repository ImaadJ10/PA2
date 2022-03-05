/*
*  File: censorColorPicker.cpp
*  Implements the censor color picker for CPSC 221 PA2.
*
*/

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function

/*
*  Useful function for computing the Euclidean distance between two PixelPoints
*/
double PointDistance(PixelPoint a, PixelPoint b) {
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& inputimage)
{
  blockwidth = b_width;
  center = ctr;
  radius = rad;
  img = inputimage;

  blockyimg = PNG(inputimage);
  for (unsigned int x = 0; x < blockyimg.width(); x += blockwidth) {
    for (unsigned int y = 0; y < blockyimg.height(); y += blockwidth) {
      HSLAPixel averagepixel = AveragePixelsHSLA(x, y, blockyimg);
      SetPixels(x, y, blockyimg, averagepixel);
    }
  }
}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{
  bool in_region = IsInRegion(p);
  if (in_region) {
    return *blockyimg.getPixel(p.x, p.y);
  } else {
    return *img.getPixel(p.x, p.y);
  }
}

HSLAPixel CensorColorPicker::AveragePixelsHSLA(int x, int y, PNG& sourceimg) 
{
  double sum_h = 0;
  double sum_s = 0;
  double sum_l = 0;
  double sum_a = 0;

  double pixel_count = 0;
  unsigned int x_bound = x + blockwidth;
  unsigned int y_bound = y + blockwidth;
  for (unsigned int _x = x; _x < x_bound && _x < sourceimg.width(); _x++) {
    for (unsigned int _y = y; _y < y_bound && _y < sourceimg.height(); _y++) {
      sum_h += sourceimg.getPixel(_x, _y)->h;
      sum_s += sourceimg.getPixel(_x, _y)->s;
      sum_l += sourceimg.getPixel(_x, _y)->l;
      sum_a += sourceimg.getPixel(_x, _y)->a;
      pixel_count++;
    }
  }
  
  double average_h = (sum_h) / pixel_count;
  double average_s = (sum_s) / pixel_count;
  double average_l = (sum_l) / pixel_count;
  double average_a = (sum_a) / pixel_count;

  HSLAPixel averagepixel = HSLAPixel(average_h, average_s, average_l, average_a);
  return averagepixel;
}

void CensorColorPicker::SetPixels(int x, int y, PNG& sourceimg, HSLAPixel& averagepixel) 
{
  unsigned int x_bound = x + blockwidth;
  unsigned int y_bound = y + blockwidth;
  for (unsigned int _x = x; _x < x_bound && _x < sourceimg.width(); _x++) {
    for (unsigned int _y = y; _y < y_bound && _y < sourceimg.height(); _y++) {
      sourceimg.getPixel(_x, _y)->h = averagepixel.h;
      sourceimg.getPixel(_x, _y)->s = averagepixel.s;
      sourceimg.getPixel(_x, _y)->l = averagepixel.l;
      sourceimg.getPixel(_x, _y)->a = averagepixel.a;
    }
  }
}

bool CensorColorPicker::IsInRegion(PixelPoint p) {
  double point_distance = PointDistance(p, center);
  if (point_distance <= radius) {
    return true;
  } else {
    return false;
  }
}