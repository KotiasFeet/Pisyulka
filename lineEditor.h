#pragma once

#include "shapeEditor.h"
#include "line.h"

class LineEditor : public ShapeEditor
{
private:
	//LineShape _lineShape;
	int _currentIndex = -1;
	int _startX = 0;
	int _startY = 0;
public:
	LineEditor();
	void OnLBtnDown(HWND hWnd) override;
	void OnLBtnUp(HWND hWnd) override;
	void OnMouseMove(HWND hWnd) override;
	void OnPaint(HWND hWnd) override;
};