#include "color.h"

void Color::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMainMenu = GetMenu(hWnd);

	// ### FILLING COLORS ###
	CheckMenuRadioItem(
		hMainMenu,
		ID_FILLING_BLACK,
		ID_FILLING_TRANSPARENT,
		currentColorFillingID_, MF_BYCOMMAND
	);

	// ### OUTLINE COLORS ###
	CheckMenuRadioItem(
		hMainMenu,
		ID_OUTLINE_BLACK,
		ID_OUTLINE_TRANSPARENT,
		currentColorOutlineID_, MF_BYCOMMAND
	);

	// ### RUBBERBANDING COLORS ###
	CheckMenuRadioItem(
		hMainMenu,
		ID_RB_COLOR_BLACK,
		ID_RB_COLOR_BLUE,
		currentColorRubberBandingID_, MF_BYCOMMAND
	);
}




RGBColor Color::GetCurrentFillingColor()
{
	return GetColor(_filling);
}

RGBColor Color::GetCurrentOutlineColor()
{
	return GetColor(_outline);
}

RGBColor Color::GetCurrentRubberBandingColor()
{
	return GetColor(_colorRB);
}
