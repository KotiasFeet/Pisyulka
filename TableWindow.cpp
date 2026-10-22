#include "TableWindow.h"

HWND hModelessWindow = NULL;

void AddColumn(HWND hListView, int index, const wchar_t* text, int width) {
    LVCOLUMN lvc = { 0 };
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    lvc.cx = width;
    lvc.pszText = (LPWSTR)text;
    ListView_InsertColumn(hListView, index, &lvc);
}

void AddRow(HWND hListView, int rowIndex, long id,const wchar_t* col0, const wchar_t* col1, const wchar_t* col2, const wchar_t* col3, const wchar_t* col4) {
    LVITEM lvi = { 0 };
    lvi.mask = LVIF_TEXT | LVIF_PARAM;
    lvi.iItem = rowIndex;

    lvi.iSubItem = 0;
    lvi.pszText = (LPWSTR)col0;
    lvi.lParam = (LPARAM)id;
    ListView_InsertItem(hListView, &lvi);

    ListView_SetItemText(hListView, rowIndex, 1, (LPWSTR)col1);
    ListView_SetItemText(hListView, rowIndex, 2, (LPWSTR)col2);
    ListView_SetItemText(hListView, rowIndex, 3, (LPWSTR)col3);
    ListView_SetItemText(hListView, rowIndex, 4, (LPWSTR)col4);
}

void RefreshTableData(HWND hListView) {
    ListView_DeleteAllItems(hListView); // Clear existing items

    Table* table = Table::GetInstance();
    size_t size = table->Size();

    for (size_t i = 0; i < size; ++i) {
        const ShapeRecord& rec = table->GetAt(i);

        wchar_t x1[16], y1[16], x2[16], y2[16];
        swprintf(x1, 16, L"%ld", rec.x1);
        swprintf(y1, 16, L"%ld", rec.y1);
        swprintf(x2, 16, L"%ld", rec.x2);
        swprintf(y2, 16, L"%ld", rec.y2);

        AddRow(hListView, (int)i, rec.id, GetShapeName(rec.type), x1, y1, x2, y2);
    }
}

LRESULT CALLBACK ModelessWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hListView;

    switch (msg) {
    case WM_CREATE: {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_LISTVIEW_CLASSES;
        InitCommonControlsEx(&icex);

        hListView = CreateWindowEx(0, WC_LISTVIEW, L"",
            WS_CHILD | WS_VISIBLE | LVS_REPORT | WS_BORDER,
            10, 10, 410, 140, hwnd, NULL, GetModuleHandle(NULL), NULL);

        ListView_SetExtendedListViewStyle(hListView, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

        AddColumn(hListView, 0, L"Type", 100);
        AddColumn(hListView, 1, L"x1", 70);
        AddColumn(hListView, 2, L"y1", 70);
        AddColumn(hListView, 3, L"x2", 70);
        AddColumn(hListView, 4, L"y2", 70);

        // Load data from the singleton immediately upon creation
        RefreshTableData(hListView);
        break;
    }
    case WM_REFRESH_TABLE: {
        RefreshTableData(hListView);
        break;
    }
    case WM_DESTROY: {
        hModelessWindow = NULL;
        break;
    }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void OpenModelessTableWindow(HWND hParentMain) {
    if (hModelessWindow != NULL) {
        SetForegroundWindow(hModelessWindow);
        return;
    }

    const wchar_t CLASS_NAME[] = L"ModelessTableClass";
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = ModelessWndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    hModelessWindow = CreateWindowEx(
        0, CLASS_NAME, L"Data View",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 200,
        hParentMain, NULL, GetModuleHandle(NULL), NULL
    );
}