#pragma once

#include "shapeEditor.h"
#include "point.h"

class PointEditor : public ShapeEditor
{
private:
	PointShape pointShape;
public:
	PointEditor();
	void OnLBtnDown(HWND hWnd) override;
	void OnPaint(HWND hWnd) override;
};