#include "Actor.h"


Actor::~Actor()
{
}

//===================================================================================================
AABB2D* Actor::GetAABB2D()
{
    return &m_bbox;
}
