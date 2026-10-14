#include "rectangleEditor.h"

RectangleEditor::RectangleEditor() 
{
	currentShapeID_ = ID_SHAPE_RECT;
}

Shape* RectangleEditor::CreateShape(long x1, long y1, long x2, long y2) 
{
	return new RectangleShape(x1, y1, x2, y2);
}