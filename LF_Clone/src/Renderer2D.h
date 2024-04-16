#pragma once

#include <map>

class Actor;

class Renderer2D
{
public:
	enum class RenderLayer
	{
		BACKGROUND = 0,
		BEHIND_DYNAMIC_OBJECTS = 1,
		DYNAMIC_OBJECTS = 2,
		IN_FRONT_OF_DYNAMIC_OBJECTS = 4,
		UI = 8
	};


public:
	static Renderer2D* Create();

	void RegisterForDraw( Actor*, RenderLayer );
	void OnRender();
	void OnPostRender();

protected:

private:
	typedef std::map<float, Actor*> ActorsPivots;

	std::map<RenderLayer, ActorsPivots> m_renderableObjs;
};

