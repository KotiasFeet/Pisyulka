#include "lineEditor.h"

LineEditor::LineEditor() 
{
	currentShapeID_ = ID_SHAPE_LINE;
}

Shape* LineEditor::CreateShape(long x1, long y1, long x2, long y2)
{
	return new LineShape(x1, y1, x2, y2);
}
