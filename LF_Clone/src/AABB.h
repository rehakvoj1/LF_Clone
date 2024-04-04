#pragma once

#include "imgui.h"


struct AABB2D
{
	//===================================================================================================
	AABB2D() :	t_lo( 0.0, 0.0 ),
				t_hi( 0.0, 0.0 )
	{
	}

	//===================================================================================================
	AABB2D( ImVec2 lo, ImVec2 hi ) :	t_lo( lo ),
										t_hi( hi )
	{
	}

	//===================================================================================================
	bool Overlaps( const AABB2D& aabb )
	{
		if ( t_hi.x < aabb.t_lo.x || t_lo.x > aabb.t_hi.x )
		{
			return false;
		}  
		if ( t_hi.y < aabb.t_lo.y || t_lo.y > aabb.t_hi.y )
		{
			return false;
		} 
		return true;
	}

	ImVec2 t_lo;
	ImVec2 t_hi;
};