#pragma once

#include <windows.h>
#include "resource.h"

enum class RB_STYLE
{
	SOLID = PS_SOLID,
	DASH = PS_DASH,
	DOT = PS_DOT,
	DASHDOT = PS_DASHDOT,
	DASHDOTDOT = PS_DASHDOTDOT
};

inline int GetRubberBandingStyle(int ID)
{
	switch (ID) {
	case ID_RUBBER_STYLE_SOLID:			return PS_SOLID;		break;
	case ID_RUBBER_STYLE_DASH:			return PS_DASH;			break;
	case ID_RUBBER_STYLE_DOT:			return PS_DOT;			break;
	case ID_RUBBER_STYLE_DASH_DOT:		return PS_DASHDOT;		break;
	case ID_RUBBER_STYLE_DASH_DOT_DOT:	return PS_DASHDOTDOT;	break;
	default:							return PS_DASH;
	}
}