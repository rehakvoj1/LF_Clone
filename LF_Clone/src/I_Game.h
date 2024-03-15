#pragma once
class I_Game
{
public:
	virtual void OnStart() = 0;
	virtual void OnBeforeUpdate( float dt ) = 0;
	virtual void OnUpdate( float dt ) = 0;
	virtual void OnPostUpdate( float dt ) = 0;

};

I_Game* CreateGame();
