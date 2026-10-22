#include "toolBarHandler.h"

ToolBarHandler::ToolBarHandler() : hwndToolBar(NULL) {};


void ToolBarHandler::OnCreate(HWND hWnd, HINSTANCE hInst) {
    hwndToolBar = CreateWindowEx(
        0,
        TOOLBARCLASSNAME,
        NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        0, 0, 0, 0,
        hWnd,
        (HMENU)IDC_MY_TOOLBAR,
        hInst,
        NULL
    );

    SendMessage(hwndToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);


    // START OF Icons for buttons shit
    int newIconSize = 32;

    HIMAGELIST hImageList = ImageList_Create(newIconSize, newIconSize, ILC_COLOR32 | ILC_MASK, TOOLBAR_MAX_BUTTONS, 0);
    HBITMAP hbmShapes = (HBITMAP)LoadImage(
        hInst,
        MAKEINTRESOURCE(IDB_SHAPES),
        IMAGE_BITMAP,
        newIconSize * TOOLBAR_MAX_BUTTONS,  // Stretched total width
        newIconSize,                    // Stretched height
        LR_CREATEDIBSECTION             // Required for scaling
    );

    ImageList_AddMasked(hImageList, hbmShapes, RGB(255, 255, 255));
    DeleteObject(hbmShapes);

    SendMessage(hwndToolBar, TB_SETIMAGELIST, 0, (LPARAM)hImageList);

    // END OF Icons for buttons shit

    TBBUTTON tbb[TOOLBAR_MAX_BUTTONS];
    ZeroMemory(tbb, sizeof(tbb));

    // Addind buttons to the toolbar
    registerTBButton(tbb, 0, IDI_ICON_POINT, ID_SHAPE_POINT);
    registerTBButton(tbb, 1, IDI_ICON_LINE, ID_SHAPE_LINE);
    registerTBButton(tbb, 2, IDI_ICON_RECT, ID_SHAPE_RECT);
    registerTBButton(tbb, 3, IDI_ICON_ELLIPSE, ID_SHAPE_ELLIPSE);
    registerTBButton(tbb, 4, IDI_ICON_OOLINE, ID_SHAPE_OOLINE);
    registerTBButton(tbb, 5, IDI_ICON_CUBE, ID_SHAPE_CUBE);

    //tbb[0].fsState |= TBSTATE_CHECKED;

    SendMessage(hwndToolBar, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
    SendMessage(hwndToolBar, TB_AUTOSIZE, 0, 0);
}


/// <summary>
/// Registers a new button on a Toolbar
/// </summary>
/// <param name="tbb">- Toolbar bnuttons array</param> 
/// <param name="index">- location serial number on the Toolbar</param>
/// <param name="iBitmap">- Icon ID</param>
/// <param name="idCommand">- Callback command</param>
void ToolBarHandler::registerTBButton(TBBUTTON* tbb, int index, int iBitmap, int idCommand) {
    tbb[index].iBitmap = iBitmap;
    tbb[index].fsState = TBSTATE_ENABLED;
    tbb[index].fsStyle = TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP;
    tbb[index].idCommand = idCommand;
}

void ToolBarHandler::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); // new main window size
        GetWindowRect(hwndToolBar, &rw); // Toolbar size
        MoveWindow(hwndToolBar, 0, 0,
            rc.right - rc.left, // width of the Toolbar same as the main window
            rw.bottom - rw.top, FALSE);
    }
}

void ToolBarHandler::OnNotify(LPARAM lParam) {
    LPNMHDR lpnmhdr = (LPNMHDR)lParam;

    if (lpnmhdr->code == TTN_NEEDTEXT) {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom) {
        case ID_SHAPE_POINT:
            lpttt->lpszText = (LPWSTR)L"Draw Point";
            break;
        case ID_SHAPE_LINE:
            lpttt->lpszText = (LPWSTR)L"Draw Line";
            break;
        case ID_SHAPE_RECT:
            lpttt->lpszText = (LPWSTR)L"Draw Rectangle";
            break;
        case ID_SHAPE_ELLIPSE:
            lpttt->lpszText = (LPWSTR)L"Draw Ellipse";
            break;
        case ID_SHAPE_OOLINE:
            lpttt->lpszText = (LPWSTR)L"Draw Linewithcirclesonbothends";
            break;
        case ID_SHAPE_CUBE:
            lpttt->lpszText = (LPWSTR)L"Draw Cube";
            break;
        }
    }
}





