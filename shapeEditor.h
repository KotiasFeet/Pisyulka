#pragma once

//#include <unordered_map>

#include "editor.h"
#include "shape.h"
#include "resource.h"
#include "rubberBending.h"

#include "tableType.h"

using AddItemToTableCallback = long (*)(ShapeType type, long startX, long startY, long endX, long endY, COLOR outlineColor, COLOR fillColor);
using UpdateItemTableCallback = bool (*)(long id, long startX, long startY, long endX, long endY);

class ShapeEditor : public Editor
{
private:
    AddItemToTableCallback _onAddItem = nullptr;
    UpdateItemTableCallback _onUpdateItem = nullptr;

protected:
    int currentShapeID_ = ID_SHAPE_POINT;

	//static std::unordered_map<long, int> tableIDtoCurIndexMap_;
    static long shapeIDs_[MY_SHAPE_ARRAY_SIZE];

    static Shape** pcshape_;
    static int currentCapacity_;
    static int currentSize_;

    int _currentIndex = -1;
    int _startX = 0;
    int _startY = 0;

    virtual Shape* CreateShape(long x1, long y1, long x2, long y2) = 0;

public:
    ~ShapeEditor() = default;

    void SetAddCallback(AddItemToTableCallback callback) { _onAddItem = callback; }
    void SetUpdateCallback(UpdateItemTableCallback callback) { _onUpdateItem = callback; }

	int RemoveElementByID(long id);
    static void ClearAllShapes();

    void SetCurrentShapeID(int shapeID) { currentShapeID_ = shapeID; }
    bool GetMousePos(HWND hWnd, POINT& pt);

    virtual void SaveShape(HWND hWnd);

    ShapeEditor* GetCorrectEditorFromShapeType(ShapeType type);
    void SetPCShape(std::vector<ShapeRecord> table);

    void Highlight(long id);

    void OnLBtnDown(HWND hWnd) override;
    void OnLBtnUp(HWND hWnd) override;
    void OnMouseMove(HWND hWnd) override;
    void OnPaint(HWND hWnd) override;
    void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};