#pragma once

#include "framework.h"
#include "table.h"
#include <commctrl.h>
#include <stdio.h>
#pragma comment(lib, "comctl32.lib")

// Define a custom message for refreshing the table
#define WM_REFRESH_TABLE (WM_USER + 1)
#define WM_USER_END_EDIT (WM_USER + 2)

#include <functional>

using ShapeEditorRemoveByIdCallback = std::function<void(long id)>;
void SetShapeEditorRemoveByIdCallback(ShapeEditorRemoveByIdCallback callback);

using ShapeEditorHighlightByIdCallback = std::function<void(long id)>;
void SetShapeEditorHighlightByIdCallback(ShapeEditorHighlightByIdCallback callback);

using ShapeEditorUnhighlightUnselectedByIdCallback = std::function<void(long id)>;
void SetShapeEditorUnhighlightUnselectedByIdCallback(ShapeEditorUnhighlightUnselectedByIdCallback callback);



const wchar_t* GetShapeName(ShapeType type);
void AddColumn(HWND hListView, int index, const wchar_t* text, int width);
void AddRow(HWND hListView, int rowIndex, const wchar_t* col0, const wchar_t* col1, const wchar_t* col2, const wchar_t* col3, const wchar_t* col4);
void RefreshTableData(HWND hListView);
LRESULT CALLBACK ModelessWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OpenModelessTableWindow(HWND hParentMain);
