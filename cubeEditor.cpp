#include "cubeEditor.h"

CubeEditor::CubeEditor()
{
	currentShapeID_ = ID_SHAPE_CUBE;
}

Shape* CubeEditor::CreateShape(long x1, long y1, long x2, long y2)
{
	return new CubeShape(x1, y1, x2, y2);
}