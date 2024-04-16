#include "Healthbar.h"
#include "imgui-SFML.h"
#include "C_Engine.h"
#include "Renderer2D.h"

#include <iostream>

Healthbar::Healthbar( std::string id, ImVec2 topLeft, ImVec2 size ) : 
	Actor(id),
	m_topLeft{ topLeft },
	m_size{ size },
	m_health{ 100.0f }
{
}

Healthbar::~Healthbar()
{
}

void Healthbar::OnUpdate( float dt )
{
	C_Engine::GetRenderer()->RegisterForDraw( this, Renderer2D::RenderLayer::UI );
}

void Healthbar::OnRender()
{
	ImGui::SetNextWindowPos( m_topLeft );
	ImGui::SetNextWindowSize( m_size );
	ImGui::Begin( "healthbar", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs );
	ImGui::DrawRectFilled( sf::FloatRect( { 0, 0 }, { m_size.x,m_size.y } ), sf::Color::Black );
	ImGui::DrawRectFilled( sf::FloatRect( { 0, 0 }, { m_health,m_size.y } ), sf::Color::Red );
	ImGui::End();
}


ImVec2 Healthbar::GetPivot()
{
	return ImVec2();
}

sf::Drawable* Healthbar::GetDrawable()
{
	return nullptr;
}


