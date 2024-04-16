#include "Renderer2D.h"
#include "Actor.h"


//===================================================================================================
Renderer2D* Renderer2D::Create()
{
	return new Renderer2D;
}

//===================================================================================================
void Renderer2D::RegisterForDraw( Actor* actor, RenderLayer renderLayer )
{
	m_renderableObjs[renderLayer].emplace( actor->GetPivot().y, actor );
}


//===================================================================================================
void Renderer2D::OnRender()
{
	for ( auto& objsInLayer : m_renderableObjs )
	{
		for ( auto actor : objsInLayer.second )
		{
			actor.second->OnRender();
		}
	}
}


//===================================================================================================
void Renderer2D::OnPostRender()
{
	m_renderableObjs.clear();
}
