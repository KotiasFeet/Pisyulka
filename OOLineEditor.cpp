#include "OOLineEditor.h"

OOLineEditor::OOLineEditor()
{
	currentShapeID_ = ID_SHAPE_OOLINE;
}

Shape* OOLineEditor::CreateShape(long x1, long y1, long x2, long y2)
{
	return new OOLineShape(x1, y1, x2, y2);
}