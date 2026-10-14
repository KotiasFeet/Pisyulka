#pragma once


#include "shapeEditor.h"
#include "cube.h"
#include "color.h"

class CubeEditor : public ShapeEditor
{

protected:
	Shape* CreateShape(long x1, long y1, long x2, long y2) override;
public:
	CubeEditor();
};