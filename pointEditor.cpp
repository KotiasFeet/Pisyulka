#include "pointEditor.h"

PointEditor::PointEditor() : pointShape(0, 0)
{
	currentShapeID_ = ID_SHAPE_POINT;
}

void PointEditor::OnLBtnDown(HWND hWnd)
{
	POINT pt;
	if (GetCursorPos(&pt)) {
		ScreenToClient(hWnd, &pt);

		if (currentShapeID_ == ID_SHAPE_POINT) {
			for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
				if (!pcshape_[i]) {
					pcshape_[i] = new PointShape(pt.x, pt.y);

					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
			}
		}
	}
}

void PointEditor::OnPaint(HWND hWnd)
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