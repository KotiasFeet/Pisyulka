#include "pointEditor.h"

PointEditor::PointEditor() 
{
	currentShapeID_ = ID_SHAPE_POINT;
}

Shape* PointEditor::CreateShape(long x1, long y1, long x2, long y2)
{
	return new PointShape(x1, y1);
}