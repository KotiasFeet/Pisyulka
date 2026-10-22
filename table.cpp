#include "table.h"

Table* Table::p_instance = 0;

Table* Table::GetInstance()
{
	if (!p_instance)
		p_instance = new Table;
	return p_instance;
}

void Table::SetTable(const std::vector<ShapeRecord>& records) {
    _records = records;
    _nextID = 0;
    for (const auto& rec : _records) {
        if (rec.id >= _nextID) {
            _nextID = rec.id + 1;
        }
    }
}

long Table::Add(ShapeType type, long x1, long y1, long x2, long y2, COLOR outline, COLOR filling)
{
    ShapeRecord rec;
    rec.id              = _nextID++;
    rec.type            = type;
    rec.x1              = x1; 
    rec.y1              = y1;
    rec.x2              = x2; 
    rec.y2              = y2;
	rec.outline         = outline;
	rec.filling         = filling;

    _records.push_back(rec);
    return rec.id;
}


long Table::Add(const ShapeRecord& record)
{
    ShapeRecord rec = record;
    rec.id = _nextID;
    _records.push_back(rec);
    return rec.id;
}

size_t Table::Size() const 
{
    return _records.size();
}

bool Table::Empty() const
{
    return _records.empty();
}

const ShapeRecord& Table::GetAt(size_t index) const
{
    if(index >= Size())
        throw std::out_of_range("Table::GetAt index out of range");
    return _records[index];
}

ShapeRecord& Table::GetAt(size_t index)
{
    if (index >= Size())
        throw std::out_of_range("Table::GetAt index out of range");
    return _records[index];
}

int Table::FindIndexById(long id) const
{
    for (size_t i = 0; i < _records.size(); ++i)
    {
        if (_records[i].id == id)
            return static_cast<int>(i);
    }
    return -1;
}

bool Table::RemoveById(long id)
{
    int index = FindIndexById(id);
    if (index < 0) return false;
    _records.erase(_records.begin() + index);
    return true;
}

bool Table::RemoveLast()
{
    if (_records.empty()) return false;
    _records.pop_back();
    return true;
}

void Table::Clear()
{
    _records.clear();
}




bool Table::UpdateCoordsByID(long id, long x1, long y1, long x2, long y2)
{
    int index = FindIndexById(id);
    if (index < 0) return false;
    _records[index].x1 = x1;
    _records[index].y1 = y1;
    _records[index].x2 = x2;
    _records[index].y2 = y2;
    return true;
}

