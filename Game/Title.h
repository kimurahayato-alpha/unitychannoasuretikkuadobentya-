#pragma once
#include "sound/SoundSource.h"

class Load;

class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	SoundSource* titleBGM;
	bool				m_isWaitLoadout = false;
	Load* m_load = nullptr;
};