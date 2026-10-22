#pragma once

#include "framework.h"

#include "table.h"
#include "shapeEditor.h"
 

class CSVManager {
public:
    static bool SaveCSVFileDialog(HWND hwnd, char* szFileName, DWORD nMaxFile);
    static void ExportTableToCSV(const char* filepath);

    static bool OpenCSVFileDialog(HWND hwnd, char* szFileName, DWORD nMaxFile);
    static void ParseCSVFile(const char* filepath, ShapeEditor* pse);
};