#pragma once

#include "editor.h"
#include "shape.h"
#include "resource.h"
#include "rubberBending.h"

class ShapeEditor : public Editor
{
protected:
    int currentShapeID_ = ID_SHAPE_POINT;
    static Shape** pcshape_;
    static int currentCapacity_;
    static int currentSize_;

    int _currentIndex = -1;
    int _startX = 0;
    int _startY = 0;

    virtual Shape* CreateShape(long x1, long y1, long x2, long y2) = 0;

public:
    static void ClearAllShapes();

    void SetCurrentShapeID(int shapeID) { currentShapeID_ = shapeID; }
    bool GetMousePos(HWND hWnd, POINT& pt);

    virtual void SaveShape(HWND hWnd);

    void OnLBtnDown(HWND hWnd) override;
    void OnLBtnUp(HWND hWnd) override;
    void OnMouseMove(HWND hWnd) override;
    void OnPaint(HWND hWnd) override;
    void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};