#include "CSVHandler.h"


std::string WideToUTF8(const wchar_t* wstr) {
    if (!wstr || *wstr == L'\0') return "";

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);

    std::string strTo(size_needed - 1, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &strTo[0], size_needed, NULL, NULL);

    return strTo;
}

// SAVE CANVA TO CSV FILE
void PopulateFileLineWithCSVData(std::ofstream& file, const ShapeRecord& rec) {
    file << rec.id << ","
        << WideToUTF8(GetShapeName(rec.type)) << ","
        << rec.x1 << ","
        << rec.y1 << ","
        << rec.x2 << ","
        << rec.y2 << ","
        << GetColorName(rec.outline) << ","
        << GetColorName(rec.filling) << "\n";
}

bool CSVManager::SaveCSVFileDialog(HWND hwnd, char* szFileName, DWORD nMaxFile) {
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;

    ofn.lpstrFile = szFileName;
    strncpy_s(szFileName, nMaxFile, "output.csv", _TRUNCATE);

    ofn.nMaxFile = nMaxFile;
    ofn.lpstrFilter = "CSV Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;

    ofn.lpstrDefExt = "csv";

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

    if (GetSaveFileNameA(&ofn) == TRUE) {
        return true;
    }
    return false;
}

void CSVManager::ExportTableToCSV(const char* filepath) {
    Table* table = Table::GetInstance();

    //std::string filename = "output.csv";

    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filepath << std::endl;
        return;
    }

    file << "ID,Type,X1,Y1,X2,Y2,Outline,Filling\n";

    for (size_t i = 0; i < table->Size(); ++i) {
        const ShapeRecord& rec = table->GetAt(i);
		PopulateFileLineWithCSVData(file, rec);
    }

    file.close();
    std::cout << "Table exported to CSV: " << filepath << std::endl;
}

// OPEN CSV FILE AND PARSE IT
void GetCSVTableLineContent(ShapeRecord* record, const std::vector<std::string>& row) {
    record->id = std::stol(row[0]);
    record->type = GetShapeTypeFromName(row[1]);
    record->x1 = std::stol(row[2]);
    record->y1 = std::stol(row[3]);
    record->x2 = std::stol(row[4]);
    record->y2 = std::stol(row[5]);
    record->outline = GetColorFromName(row[6]);
    record->filling = GetColorFromName(row[7]);
}

void SplitLineByComma(const std::string& line, std::vector<std::string>& row) {
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        row.push_back(cell);
    }
}

bool CSVManager::OpenCSVFileDialog(HWND hwnd, char* szFileName, DWORD nMaxFile) {
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = nMaxFile;
    ofn.lpstrFilter = "CSV Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileNameA(&ofn) == TRUE) {
        return true;
    }
    return false;
}

void CSVManager::ParseCSVFile(const char* filepath, ShapeEditor* pse){
    std::ifstream file(filepath);
    if (!file.is_open()) {
        MessageBox(NULL, L"Failed to open the CSV file.", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    std::string line;
    std::getline(file, line); // skipping the header line

    std::vector<ShapeRecord> _records;
    while (std::getline(file, line)) {
        std::vector<std::string> row;

        SplitLineByComma(line, row);

        try {
            ShapeRecord record;
            GetCSVTableLineContent(&record, row);
			_records.push_back(record);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << ". Exception: " << e.what() << std::endl;
            continue;
        }
    }

	// seting Table instance with the new records and updating ShapeEditor
    Table::GetInstance()->SetTable(_records);
	pse->SetPCShape(_records);

    file.close();
}

