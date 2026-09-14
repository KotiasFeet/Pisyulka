#pragma once

#include <windows.h>
#include "colorEnums.h"
#include "RGBColor.h"


class Color
{
private:
	COLOR_OUTLINE _outline = COLOR_OUTLINE::BLACK;
	int currentColorFillingID_ = ID_FILLING_BLACK;

	COLOR_FILLING _filling = COLOR_FILLING::BLACK;
	int currentColorOutlineID_ = ID_OUTLINE_BLACK;

	COLOR_RB _colorRB = COLOR_RB::BLACK;
	int currentColorRubberBandingID_ = ID_RB_COLOR_BLACK;

public:
	//Color() = default;

	void SetCurrentFillingID(int shapeID) { currentColorFillingID_ = shapeID; _filling = static_cast<COLOR_FILLING>(shapeID); }
	void SetCurrentOutlineID(int shapeID) { currentColorOutlineID_ = shapeID; _outline = static_cast<COLOR_OUTLINE>(shapeID); }
	void SetCurrentRubberBandingID(int shapeID) { currentColorRubberBandingID_ = shapeID; _colorRB = static_cast<COLOR_RB>(shapeID); }

	RGBColor GetCurrentFillingColor();
	RGBColor GetCurrentOutlineColor();
	RGBColor GetCurrentRubberBandingColor();

	void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};

// Declaration to reference the single global instance defined in Pisyulka.cpp
extern Color color;
