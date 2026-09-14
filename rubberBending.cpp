#include "rubberBending.h"

bool Rubber::isRubberShown_ = false;
int Rubber::rubberStyleID_ = ID_RUBBER_STYLE_DOT;

Rubber rubberbending;



void DrawRubberShape(HDC hdc, int shapeID, int x1, int y1, int x2, int y2)
{
	RGBColor rb = color.GetCurrentRubberBandingColor();

	int penStyle = GetRubberBandingStyle(Rubber::GetRBStyleID());

	HPEN hPen = CreatePen(penStyle, 1, RGB(rb.r, rb.g, rb.b));
	HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	
	int oldROP = SetROP2(hdc, R2_NOTXORPEN);

	switch (shapeID) 
	{
	case ID_SHAPE_LINE: {
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
		break;
	}
	case ID_SHAPE_RECTANGLE: {
		//Rectangle(hdc, std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2));
		Rectangle(hdc, x1, y1, x2, y2);
		break;
	}
	case ID_SHAPE_ELLIPSE: {
		//Ellipse(hdc, std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2));
		Ellipse(hdc, x1, y1, x2, y2);
		break;
	}
	case ID_SHAPE_POINT: {
		// small cross just becouse i feel like it 
		MoveToEx(hdc, x2 - 3, y2, NULL);
		LineTo(hdc, x2 + 3, y2);
		MoveToEx(hdc, x2, y2 - 3, NULL);
		LineTo(hdc, x2, y2 + 3);
		break;
	}
	default:
		break;
	}


	SetROP2(hdc, oldROP);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);

	DeleteObject(hPen);
}

void Rubber::StartRubber(int startX, int startY)
{
	rubberActive_ = true;
	startX_ = startX;
	startY_ = startY;
	prevX_ = startX;
	prevY_ = startY;
}

void Rubber::UpdateRubber(HWND hWnd, int shapeID, int startX, int startY, int curX, int curY)
{
	if (!rubberActive_) return;

	HDC hdc = GetDC(hWnd);

	DrawRubberShape(hdc, shapeID, startX, startY, prevX_, prevY_);
	DrawRubberShape(hdc, shapeID, startX, startY, curX, curY);

	ReleaseDC(hWnd, hdc);

	prevX_ = curX;
	prevY_ = curY;
}

void Rubber::EndRubber(HWND hWnd, int shapeID, int startX, int startY, int curX, int curY)
{
	if (!rubberActive_) return;

	HDC hdc = GetDC(hWnd);

	DrawRubberShape(hdc, shapeID, startX, startY, prevX_, prevY_);
	ReleaseDC(hWnd, hdc);

	rubberActive_ = false;
}


void Rubber::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu = GetMenu(hWnd);
	HMENU hSubMenu = GetSubMenu(hMenu, 1);

	// ### IS SHOWN ###
	UINT rubberState = IsRubberShown() ? MF_CHECKED : MF_UNCHECKED;
	CheckMenuItem(hMenu, ID_RUBBER_SHOW, MF_BYCOMMAND | rubberState);

	// ### STYLE ###
	CheckMenuRadioItem(
		hMenu,
		ID_RUBBER_STYLE_SOLID,
		ID_RUBBER_STYLE_DASH_DOT_DOT,
		rubberStyleID_, MF_BYCOMMAND
	);
}
