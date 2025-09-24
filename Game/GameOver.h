#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#pragma once
class Load;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
private:
	Load* m_load;
};