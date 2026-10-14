#pragma once

#include "resource.h"
#include "shapesIconsBitmapIndexes.h"

#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#define TOOLBAR_BUTTONS 6


class ToolBarHandler
{
private:
	HWND hwndToolBar;
	void registerTBButton(TBBUTTON* tbb, int index, int iBitmap, int idCommand);

public:
	ToolBarHandler();
	void OnCreate(HWND hWnd, HINSTANCE hInst);
	void OnSize(HWND hWnd);
	void OnNotify(LPARAM lParam);
};