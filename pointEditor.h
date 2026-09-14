#pragma once

#include "shapeEditor.h"
#include "point.h"


class PointEditor : public ShapeEditor
{
protected:
	Shape* CreateShape(long x1, long y1, long x2, long y2) override;
public:
	PointEditor();
};