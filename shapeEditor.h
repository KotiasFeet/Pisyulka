#pragma once

#include "editor.h"
#include "shape.h"
#include "resource.h"

class ShapeEditor : public Editor
{
protected:
	int currentShapeID_ = ID_SHAPE_POINT;
	static Shape* pcshape_[MY_SHAPE_ARRAY_SIZE];
public:
	//ShapeEditor(void);

	void SetCurrentShapeID(int shapeID) { currentShapeID_ = shapeID; }

	//virtual void OnLBtnDown(HWND hWnd);
	//virtual void OnLBtnUp(HWND hWnd);
	//virtual void OnMouseMove(HWND hWnd);

	//void OnPaint(HWND hWnd);

	static void ClearAllShapes();

	void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};