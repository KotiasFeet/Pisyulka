#include "shapeEditor.h"

#include "AllShapesEditors.h"

long ShapeEditor::shapeIDs_[MY_SHAPE_ARRAY_SIZE] = { 0 };
Shape** ShapeEditor::pcshape_ = new Shape * [MY_SHAPE_ARRAY_SIZE] {};
int ShapeEditor::currentCapacity_ = MY_SHAPE_ARRAY_SIZE;
int ShapeEditor::currentSize_ = MY_SHAPE_ARRAY_SIZE;



void ShapeEditor::ClearAllShapes()
{
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
		if (pcshape_[i]) {
			delete pcshape_[i];
			pcshape_[i] = nullptr;
		}
	}
}

int ShapeEditor::RemoveElementByID(long id) {
	int index = -1;
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
		if (shapeIDs_[i] == id) {
			index = i;
			break;
		}
	}
	if (index == -1) return -1;
	if (pcshape_[index]) {
		delete pcshape_[index];
		pcshape_[index] = nullptr;
	}
	shapeIDs_[index] = -1;
	return index;
}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);

	CheckMenuRadioItem(
		hSubMenu, 
		ID_SHAPE_POINT,						// FIRST ID
		ID_SHAPE_CUBE,						// LAST ID
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

			ShapeType type = GetShapeTypeFromID(currentShapeID_);
			long id = Table::GetInstance()
				->Add(type, _startX, _startY, _startX, _startY
						, GetColorFromRGB(color.GetCurrentOutlineColor())
						, GetColorFromRGB(color.GetCurrentFillingColor()));
			//tableIDtoCurIndexMap_[_currentIndex] = id;
			shapeIDs_[_currentIndex] = id;
			SendMessage(hWnd, WM_COMMAND, ID_REFRESH_TABLE_VIEW, 0);

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	}
}

ShapeEditor* ShapeEditor::GetCorrectEditorFromShapeType(ShapeType type) {
	ShapeEditor* editor = nullptr;
	switch (type) {
	case ShapeType::POINT:
		editor = new PointEditor();
		break;
	case ShapeType::LINE:
		editor = new LineEditor();
		break;
	case ShapeType::OOLINE:
		editor = new OOLineEditor();
		break;
	case ShapeType::RECTANGLE:
		editor = new RectangleEditor();
		break;
	case ShapeType::ELLIPSE:
		editor = new EllipseEditor();
		break;
	case ShapeType::CUBE:
		editor = new CubeEditor();
		break;
	default:
		break;
	}
	return editor;
}

void ShapeEditor::SetPCShape(std::vector<ShapeRecord> table) {
	ClearAllShapes();
	for (int i = 0; i < table.size() && i < MY_SHAPE_ARRAY_SIZE; i++) {
		ShapeRecord& record = table[i];

		ShapeEditor* editor = GetCorrectEditorFromShapeType(record.type);
		pcshape_[i] = editor->CreateShape(record.x1, record.y1, record.x2, record.y2);
		
		pcshape_[i]->SetFillingColor(GetRGBFromColor(record.filling));
		pcshape_[i]->SetOutlineColor(GetRGBFromColor(record.outline));
		
		shapeIDs_[i] = record.id;
		delete editor;
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

		//auto it = tableIDtoCurIndexMap_.find(_currentIndex);
		//long id = it->second;
		long id = shapeIDs_[_currentIndex];
		Table::GetInstance()->UpdateCoordsByID(id, _startX, _startY, pt.x, pt.y);
		SendMessage(hWnd, WM_COMMAND, ID_REFRESH_TABLE_VIEW, 0);
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
