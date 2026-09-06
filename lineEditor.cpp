#include "lineEditor.h"

LineEditor::LineEditor() : _currentIndex(-1), _startX(0), _startY(0)
{
	currentShapeID_ = ID_SHAPE_LINE;
}

void LineEditor::OnLBtnDown(HWND hWnd)
{
	POINT pt;
	if (GetCursorPos(&pt)) {
		ScreenToClient(hWnd, &pt);
		_currentIndex = -1;
		if (currentShapeID_ == ID_SHAPE_LINE) {
			for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
				if (!pcshape_[i]) {
					_startX = pt.x;
					_startY = pt.y;
					pcshape_[i] = new LineShape(_startX, _startY, _startX, _startY);
					_currentIndex = i;

					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
			}
		}
	}
}

void LineEditor::OnLBtnUp(HWND hWnd)
{
	POINT pt;
	if (GetCursorPos(&pt)) {
		ScreenToClient(hWnd, &pt);
		if (currentShapeID_ == ID_SHAPE_LINE) {
			if (_currentIndex != -1 && pcshape_[_currentIndex]) {
				pcshape_[_currentIndex]->Set(_startX, _startY, pt.x, pt.y);

				InvalidateRect(hWnd, NULL, TRUE);
				_currentIndex = -1;
			}
		}
	}
}

void LineEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	if (GetCursorPos(&pt)) {
		ScreenToClient(hWnd, &pt);
		if (_currentIndex != -1 && pcshape_[_currentIndex]) {
			if (currentShapeID_ == ID_SHAPE_LINE) {
				pcshape_[_currentIndex]->Set(_startX, _startY, pt.x, pt.y);
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
}

void LineEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
		if (pcshape_[i]) {
			pcshape_[i]->Show(hdc);
		}
	}
	EndPaint(hWnd, &ps);
}