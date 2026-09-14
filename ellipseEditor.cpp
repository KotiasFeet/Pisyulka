#include "ellipseEditor.h"

EllipseEditor::EllipseEditor()
{
	currentShapeID_ = ID_SHAPE_ELLIPSE;
}

Shape* EllipseEditor::CreateShape(long x1, long y1, long x2, long y2)
{
	return new EllipseShape(x1, y1, x2, y2);
}