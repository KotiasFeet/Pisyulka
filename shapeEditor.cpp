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


//void ShapeEditor::OnLBtnDown(HWND hWnd){}
//void ShapeEditor::OnLBtnUp(HWND hWnd){}
//void ShapeEditor::OnMouseMove(HWND hWnd){}

//void ShapeEditor::OnPaint(HWND hWnd)
//{
//
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	hdc = BeginPaint(hWnd, &ps);
//	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
//		if (pcshape_[i]) {
//			pcshape_[i]->Show(hdc);
//		}
//	}
//	EndPaint(hWnd, &ps);
//}