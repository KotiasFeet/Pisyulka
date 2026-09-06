#pragma once

#include <windows.h>

class Shape
{
protected:
	long x1_, y1_, x2_, y2_;

public:
	Shape();
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC hdc) = 0;


};