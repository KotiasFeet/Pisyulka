#pragma once

#include "color.h"
//#include "resource.h"
//#include <windows.h>
#include <iostream>
#include "rubberBandingEnums.h"

class Rubber
{
protected:
	bool rubberActive_ = false;
	int startX_ = 0;
	int startY_ = 0;
	int prevX_ = 0;
	int prevY_ = 0;

	static bool isRubberShown_;
	static int rubberStyleID_;

public:
	static bool IsRubberShown() { return isRubberShown_; }
	static void ToggleRubberShown() { isRubberShown_ = !isRubberShown_; }

	static int GetRBStyleID() { return rubberStyleID_; }
	static void SetRubberStyle(int rubberStyle) { rubberStyleID_ = rubberStyle; }

	void StartRubber(int startX, int startY);
	void UpdateRubber(HWND hWnd, int shapeID, int startX, int startY, int curX, int curY);
	void EndRubber(HWND hWnd, int shapeID, int startX, int startY, int curX, int curY);

	void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};

extern Rubber rubberBending;