#pragma once

#include "shape.h"

class RectangleShape : public Shape
{
public:
	void Show(HDC hdc) override;
};