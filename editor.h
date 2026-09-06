#pragma once

#include <windows.h>

class Editor
{
public:
	virtual void OnLBtnDown(HWND hWnd) {};
	virtual void OnLBtnUp(HWND hWnd) {};
	virtual void OnMouseMove(HWND hWnd) {};
	virtual void OnPaint(HWND hWnd) {};
};