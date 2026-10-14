// Pisyulka.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Pisyulka.h"

#include "toolBarHandler.h"
ToolBarHandler toolBarHandler;

#include "shapesIconsBitmapIndexes.h"
#include "AllShapesEditors.h"
#include "shapeEditor.h"
ShapeEditor *pse = NULL;

#include "rubberBending.h"
Rubber rubberBending;

#include "color.h"
Color color;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void SetupDebugConsole();



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_BAR_CLASSES;
    InitCommonControlsEx(&icex);

    SetupDebugConsole();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PISYULKA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PISYULKA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PISYULKA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PISYULKA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

    case WM_CREATE:
		toolBarHandler.OnCreate(hWnd, hInst);
        break;
    case WM_NOTIFY: 
        toolBarHandler.OnNotify(lParam);
		break;
	case WM_SIZE:
		toolBarHandler.OnSize(hWnd);
		break;
    
    case WM_LBUTTONDOWN:
        if(pse) pse->OnLBtnDown(hWnd);
        break;
    case WM_LBUTTONUP:
        if(pse) pse->OnLBtnUp(hWnd);
        break;
    case WM_MOUSEMOVE:
        if(pse) pse->OnMouseMove(hWnd);
        break;
    case WM_PAINT:
        if(pse) pse->OnPaint(hWnd);
        break;
    case WM_INITMENUPOPUP:
        if(pse) pse->OnInitMenuPopup(hWnd, wParam);
        color.OnInitMenuPopup(hWnd, wParam);
        rubberBending.OnInitMenuPopup(hWnd, wParam);
		break;


    case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId) {

			case ID_SHAPE_POINT: {
                if (pse) delete pse;
                pse = new PointEditor();
                if (pse) pse->SetCurrentShapeID(wmId);
                break;
            }
			case ID_SHAPE_LINE: {
                if (pse) delete pse;
                pse = new LineEditor();
                if (pse) pse->SetCurrentShapeID(wmId);
                break;
            }
			case ID_SHAPE_RECT: {
                if (pse) delete pse;
                pse = new RectangleEditor();
                if (pse) pse->SetCurrentShapeID(wmId);
                break;
            }
			case ID_SHAPE_ELLIPSE: {
                if (pse) delete pse;
                pse = new EllipseEditor();
                if (pse) pse->SetCurrentShapeID(wmId);
                break;
            }
            case ID_SHAPE_OOLINE: {
                if (pse) delete pse;
                pse = new OOLineEditor();
                if (pse) pse->SetCurrentShapeID(wmId);
                break;
            }
            case ID_SHAPE_CUBE: {
                if (pse) delete pse;
                pse = new CubeEditor();
                if (pse) pse->SetCurrentShapeID(wmId);
                break;
            }


            /// Colors
            // #### Fillings ####
            case ID_FILLING_BLACK:
            case ID_FILLING_WHITE:
            case ID_FILLING_YELLOW:
            case ID_FILLING_LIGHT:
            case ID_FILLING_CYAN:
            case ID_FILLING_PINK:
            case ID_FILLING_ORANGE:
            case ID_FILLING_LILAC: 
            case ID_FILLING_TRANSPARENT: {
                color.SetCurrentFillingID(wmId);
                break;
            }

			// #### outlines ####
            case ID_OUTLINE_BLACK:
            case ID_OUTLINE_WHITE:
            case ID_OUTLINE_YELLOW:
            case ID_OUTLINE_LIGHT:
            case ID_OUTLINE_CYAN:
            case ID_OUTLINE_PINK:
            case ID_OUTLINE_ORANGE:
            case ID_OUTLINE_LILAC: 
            case ID_OUTLINE_TRANSPARENT: {
                color.SetCurrentOutlineID(wmId);
                break;
            }

            // #### RUBBER-BENDING COLOR ####
            case ID_RB_COLOR_BLACK:
            case ID_RB_COLOR_RED:
            case ID_RB_COLOR_BLUE: {
                color.SetCurrentRubberBandingID(wmId);
                break;
            }
            
            // ### RUBBER-BENDING STYLE ####
            case ID_RUBBER_STYLE_SOLID: 
            case ID_RUBBER_STYLE_DASH: 
            case ID_RUBBER_STYLE_DOT:
            case ID_RUBBER_STYLE_DASH_DOT: 
            case ID_RUBBER_STYLE_DASH_DOT_DOT: 
            {
                Rubber::SetRubberStyle(wmId);
                break;
            }
            
            case ID_RUBBER_SHOW: {
                Rubber::ToggleRubberShown();
                break;
            }

            case ID_HELP_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
		ShapeEditor::ClearAllShapes();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            ShellExecute(0, 0, L"https://youtu.be/dQw4w9WgXcQ?si=fN8eoUP0XnOnpCi_", 0, 0, SW_SHOW);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void SetupDebugConsole() {
    // Create the console window
    AllocConsole();

    // Route standard C/C++ output to the new console
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    // Now std::cout and printf will work normally
    std::cout << "Debug console initialized!" << std::endl;
}