#pragma once

#include "shapeEditor.h"
#include "OOLine.h"
#include "color.h"

class OOLineEditor : public ShapeEditor
{
protected:
	Shape* CreateShape(long x1, long y1, long x2, long y2) override;

public:
	OOLineEditor();
};