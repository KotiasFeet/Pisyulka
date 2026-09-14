#pragma once

#include "colorEnums.h"

class RGBColor
{
public:
	int r;
	int g;
	int b;
	constexpr RGBColor(int red, int green, int blue) : r(red), g(green), b(blue) {}
    
};

namespace Palette {
    constexpr RGBColor Black{ 0, 0, 0 };
    constexpr RGBColor White{ 255, 255, 255 };
    constexpr RGBColor Yellow{ 255, 255, 0 };
    constexpr RGBColor LightGreen{ 144, 238, 144 };
    constexpr RGBColor Cyan{ 0, 255, 255 };
    constexpr RGBColor Pink{ 255, 192, 203 };
    constexpr RGBColor Orange{ 255, 165, 0 };
    constexpr RGBColor Lilac{ 200, 162, 200 };
    constexpr RGBColor Red{ 255, 0, 0 };
    constexpr RGBColor Blue{ 0, 0, 255 };
	constexpr RGBColor Transparent{ -1, -1, -1 };
}


constexpr RGBColor GetColor(COLOR_FILLING color)
{
    switch (color)
    {
    case COLOR_FILLING::BLACK:          return Palette::Black;
    case COLOR_FILLING::WHITE:          return Palette::White;
    case COLOR_FILLING::YELLOW:         return Palette::Yellow;
    case COLOR_FILLING::LIGHT_GREEN:    return Palette::LightGreen;
    case COLOR_FILLING::CYAN:           return Palette::Cyan;
    case COLOR_FILLING::PINK:           return Palette::Pink;
    case COLOR_FILLING::ORANGE:         return Palette::Orange;
    case COLOR_FILLING::LILAC:          return Palette::Lilac;
	case COLOR_FILLING::CTRANSPARENT:   return Palette::Transparent;
    default:                            return Palette::Black;
    }
}

constexpr RGBColor GetColor(COLOR_OUTLINE color)
{
    switch (color)
    {
    case COLOR_OUTLINE::BLACK:          return Palette::Black;
    case COLOR_OUTLINE::WHITE:          return Palette::White;
    case COLOR_OUTLINE::YELLOW:         return Palette::Yellow;
    case COLOR_OUTLINE::LIGHT_GREEN:    return Palette::LightGreen;
    case COLOR_OUTLINE::CYAN:           return Palette::Cyan;
    case COLOR_OUTLINE::PINK:           return Palette::Pink;
    case COLOR_OUTLINE::ORANGE:         return Palette::Orange;
    case COLOR_OUTLINE::LILAC:          return Palette::Lilac;
	case COLOR_OUTLINE::CTRANSPARENT:   return Palette::Transparent;
    default:                            return Palette::Black;
    }
}

constexpr RGBColor GetColor(COLOR_RB color)
{
    switch (color)
    {
    case COLOR_RB::BLACK: return Palette::Black;
    case COLOR_RB::RED:   return Palette::Red;
    case COLOR_RB::BLUE:  return Palette::Blue;
    default:              return Palette::Black;
    }
}