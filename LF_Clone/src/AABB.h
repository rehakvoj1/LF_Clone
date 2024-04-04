#pragma once

#include "imgui.h"


struct AABB2D
{
	AABB2D() :	t_lo( 0.0, 0.0 ),
				t_hi( 0.0, 0.0 )
	{
	}

	AABB2D( ImVec2 lo, ImVec2 hi ) :	t_lo( lo ),
										t_hi( hi )
	{
	}

	ImVec2 t_lo;
	ImVec2 t_hi;
};