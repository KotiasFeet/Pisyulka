#pragma once

#include "framework.h"

#include "tableType.h"
#include "shapeEditor.h"

using TableGetSizeCallback = size_t (*)();
using TableGetAtCallback = const ShapeRecord& (*)(size_t index);
using TableSetTable = void (*)(const std::vector<ShapeRecord>& records);

class CSVManager {
private:
	static TableGetSizeCallback _getTableSize;
	static TableGetAtCallback _getTableAt;
	static TableSetTable _setTable;
public:
    static bool SaveCSVFileDialog(HWND hwnd, char* szFileName, DWORD nMaxFile);
    static void ExportTableToCSV(const char* filepath);

    static bool OpenCSVFileDialog(HWND hwnd, char* szFileName, DWORD nMaxFile);
    static void ParseCSVFile(const char* filepath, ShapeEditor* pse);

    static void SetGetTableSizeCallback(TableGetSizeCallback callback) { _getTableSize = callback; }
    static void SetGetTableAtCallback(TableGetAtCallback callback) { _getTableAt = callback; }
    static void SetSetTableCallback(TableSetTable callback) { _setTable = callback; }

};