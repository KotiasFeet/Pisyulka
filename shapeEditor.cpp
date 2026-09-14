#include "ShapeEditor.h"

Shape* ShapeEditor::pcshape_[MY_SHAPE_ARRAY_SIZE] = { nullptr };

void ShapeEditor::ClearAllShapes()
{
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
		if (pcshape_[i]) {
			delete pcshape_[i];
			pcshape_[i] = nullptr;
		}
	}
}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);

	CheckMenuRadioItem(
		hSubMenu, 
		ID_SHAPE_POINT,					// FIRST ID
		ID_SHAPE_ELLIPSE,				// LAST ID
		currentShapeID_, MF_BYCOMMAND	
	);
}


bool ShapeEditor::GetMousePos(HWND hWnd, POINT& pt) 
{
	if (!GetCursorPos(&pt)) return false;
	ScreenToClient(hWnd, &pt);
	return true;
}


void ShapeEditor::SaveShape(HWND hWnd)
{
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
		if (!pcshape_[i]) {
			pcshape_[i] = CreateShape(_startX, _startY, _startX, _startY);

			pcshape_[i]->SetFillingColor(color.GetCurrentFillingColor());
			pcshape_[i]->SetOutlineColor(color.GetCurrentOutlineColor());

			_currentIndex = i;

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	}
}



void ShapeEditor::OnLBtnDown(HWND hWnd) {
	POINT pt;
	if (!GetMousePos(hWnd, pt)) return;

	_currentIndex = -1;
	_startX = pt.x;
	_startY = pt.y;

	if (Rubber::IsRubberShown()) {
		rubberBending.StartRubber(_startX, _startY);
		return;
	}
	SaveShape(hWnd);
}

void ShapeEditor::OnLBtnUp(HWND hWnd) {
	POINT pt;
	if (!GetMousePos(hWnd, pt)) return;

	if (Rubber::IsRubberShown()) {
		rubberBending.EndRubber(hWnd, currentShapeID_, _startX, _startY, pt.x, pt.y);
		SaveShape(hWnd);
	}

	if (_currentIndex != -1 && pcshape_[_currentIndex]) {
		pcshape_[_currentIndex]->Set(_startX, _startY, pt.x, pt.y);
	}

	InvalidateRect(hWnd, NULL, TRUE);
	_currentIndex = -1;
}

void ShapeEditor::OnMouseMove(HWND hWnd) {
	POINT pt;
	if (!GetMousePos(hWnd, pt)) return;

	if (Rubber::IsRubberShown()) {
		rubberBending.UpdateRubber(hWnd, currentShapeID_, _startX, _startY, pt.x, pt.y);
		return;
	}

	if (_currentIndex == -1 || !pcshape_[_currentIndex]) return;

	pcshape_[_currentIndex]->Set(_startX, _startY, pt.x, pt.y);
	InvalidateRect(hWnd, NULL, TRUE);
}


void ShapeEditor::OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
		if (pcshape_[i]) {
			pcshape_[i]->Show(hdc);
		}
	}
	EndPaint(hWnd, &ps);
}
