#include "CollisionSystem.h"
#include "Event.h"

#include <iostream>


//===================================================================================================
CollisionSystem* CollisionSystem::Create()
{
    return new CollisionSystem;
}


//===================================================================================================
void CollisionSystem::RegisterCollider( GameObject* obj, CollisionFilter collider, CollisionFilter collidesWith )
{
    auto col = std::make_pair( collider, collidesWith );
    m_colliders.insert_or_assign( obj, col );
}


//===================================================================================================
void CollisionSystem::UnregisterCollider( GameObject* collider )
{
    m_colliders.erase( collider );
}


//===================================================================================================
void CollisionSystem::OnUpdate()
{
    for ( auto& src : m_colliders )
    {
        for ( auto& tar : m_colliders )
        {
            if ( src == tar )
                continue;

            AABB2D* srcCollider = src.first->GetAABB2D();
            AABB2D* tarCollider = tar.first->GetAABB2D();

            if ( ( src.second.first & tar.second.second ) > 0 &&    // if they can collide with each other
                 srcCollider->Overlaps( *tarCollider ) )            // if they actually colliding
            {
                OverlapEvent event( *(tar.first) );
                auto overlapCallbacks = m_callbacks.equal_range( typeid( OverlapEvent ) );
                for ( auto it = overlapCallbacks.first; it != overlapCallbacks.second; ++it )
                {
                    if ( dynamic_cast<GameObject*>( it->second.first )->GetID() == src.first->GetID() )
                    {
                        it->second.second->Exec( event, it->second.first );
                    }
                }
            }


        }
    }
}
