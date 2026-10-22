#pragma once

#include "tableType.h"

class Table
{
private:
    static Table* p_instance;
    Table() {}
    Table(const Table&);
    Table& operator=(Table&);

    std::vector<ShapeRecord> _records;
    long _nextID;
public:

    static Table* GetInstance();

    void SetTable(const std::vector<ShapeRecord>& records);

    /// <summary>
    /// Adds a record to the table
    /// </summary>
    /// <returns>Assigned ID as `long`</returns>
    long Add(     ShapeType type
                , long x1, long y1, long x2, long y2
                , COLOR outline, COLOR filling);

    /// <summary>
    /// Adds a record to the table of the already populated ShapeRecord
    /// </summary>
    /// <returns>Assigned ID as `long`</returns>
    long Add(const ShapeRecord& record);

    // Accessors
    size_t Size() const;
    bool Empty() const;
    const ShapeRecord& GetAt(size_t index) const;
    ShapeRecord& GetAt(size_t index);

    // Find by assigned id
    int FindIndexById(long id) const;

    // Update coords for an existing record by id
    bool UpdateCoordsByID(long id, long x1, long y1, long x2, long y2);

    // Removers
    bool RemoveById(long id);
    bool RemoveLast();
    void Clear();
};