#include "shape.h"

Shape::Shape() 
	: x1_(0)
	, y1_(0)
	, x2_(0)
	, y2_(0) 
{}

void Shape::Set(long x1, long y1, long x2, long y2)
{
	x1_ = x1;
	y1_ = y1;
	x2_ = x2;
	y2_ = y2;
}