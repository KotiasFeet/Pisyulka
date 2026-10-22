#pragma once

#include "framework.h"
#include "resource.h"

enum class ShapeType : int
{
    POINT = 0,
    LINE = 1,
    RECTANGLE = 2,
    ELLIPSE = 3,
    OOLINE = 4,
    CUBE = 5,
    UNKNOWN
};

enum class COLOR
{
    BLACK = 0,
    WHITE = 1,
    YELLOW = 2,
    LIGHT_GREEN = 3,
    CYAN = 4,
    PINK = 5,
    ORANGE = 6,
    LILAC = 7,
    CTRANSPARENT = 8
};

inline ShapeType GetShapeTypeFromID(int shapeID) {
    switch (shapeID) {
    case ID_SHAPE_POINT: return ShapeType::POINT;
    case ID_SHAPE_LINE: return ShapeType::LINE;
    case ID_SHAPE_RECT: return ShapeType::RECTANGLE;
    case ID_SHAPE_ELLIPSE: return ShapeType::ELLIPSE;
    case ID_SHAPE_OOLINE: return ShapeType::OOLINE;
    case ID_SHAPE_CUBE: return ShapeType::CUBE;
    default: return ShapeType::UNKNOWN;
    }
}

inline const wchar_t* GetShapeName(ShapeType type) {
    switch (type) {
    case ShapeType::POINT: return L"Point";
    case ShapeType::LINE: return L"Line";
    case ShapeType::RECTANGLE: return L"Rectangle";
    case ShapeType::ELLIPSE: return L"Ellipse";
    case ShapeType::OOLINE: return L"OOLine";
    case ShapeType::CUBE: return L"Cube";
    default: return L"Unknown";
    }
}

inline const ShapeType GetShapeTypeFromName(const std::string& shapeName) {
    if (shapeName == "Point") return ShapeType::POINT;
    else if (shapeName == "Line") return ShapeType::LINE;
    else if (shapeName == "Rectangle") return ShapeType::RECTANGLE;
    else if (shapeName == "Ellipse") return ShapeType::ELLIPSE;
    else if (shapeName == "OOLine") return ShapeType::OOLINE;
    else if (shapeName == "Cube") return ShapeType::CUBE;
    else return ShapeType::UNKNOWN;
}

inline COLOR GetColorFromName(const std::string& colorName) {
    if (colorName == "Black") return COLOR::BLACK;
    else if (colorName == "White") return COLOR::WHITE;
    else if (colorName == "Yellow") return COLOR::YELLOW;
    else if (colorName == "Light Green") return COLOR::LIGHT_GREEN;
    else if (colorName == "Cyan") return COLOR::CYAN;
    else if (colorName == "Pink") return COLOR::PINK;
    else if (colorName == "Orange") return COLOR::ORANGE;
    else if (colorName == "Lilac") return COLOR::LILAC;
    else if (colorName == "Transparent") return COLOR::CTRANSPARENT;
    else return COLOR::BLACK;
}

inline const std::string GetColorName(COLOR color) {
    switch (color) {
    case COLOR::BLACK: return "Black";
    case COLOR::WHITE: return "White";
    case COLOR::YELLOW: return "Yellow";
    case COLOR::LIGHT_GREEN: return "Light Green";
    case COLOR::CYAN: return "Cyan";
    case COLOR::PINK: return "Pink";
    case COLOR::ORANGE: return "Orange";
    case COLOR::LILAC: return "Lilac";
    case COLOR::CTRANSPARENT: return "Transparent";
    default: return "Unknown";
    }
}

/// <summary>
/// long id; - Unique identifier for the shape record.
/// ShapeType type; - Enum representing the type of shape (Point, Line, Rect, Ellipse, OOLine, Cube).
/// long x1, y1; - Coordinates for the first point of the shape.
/// long x2, y2; - Coordinates for the second point of the shape (if applicable).
/// COLOR outline; - Enum representing the outline color of the shape.
/// COLOR filling; - Enum representing the filling color of the shape.
/// </summary>
struct ShapeRecord
{
    long id;
    ShapeType type;
    long x1, y1;
    long x2, y2;
	COLOR outline;
	COLOR filling;

    ShapeRecord()
        : id(-1)
        , type(ShapeType::UNKNOWN)
        , x1(0), y1(0), x2(0), y2(0) 
        , outline(COLOR::BLACK)
        , filling(COLOR::BLACK)
    {}
};

