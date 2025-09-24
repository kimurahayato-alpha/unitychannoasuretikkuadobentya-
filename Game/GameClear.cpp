#include "stdafx.h"
#include "GameClear.h"
#include "Load.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameClear::GameClear()
{
	m_spriteRender.Init("Assets/sprite/gameclear.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameclearbgm.wav");
}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Load>(0, "load");
		m_load = FindGO<Load>("load");
		m_load->isClearLoad = true;
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}