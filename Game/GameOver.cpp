#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "Load.h"
#include "sound/SoundEngine.h"
GameOver::GameOver()
{
	m_spriteRender.Init("Assets/sprite/gameover.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameoverbgm.wav");
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Load>(0, "load");
		m_load = FindGO<Load>("load");
		m_load->isGameOverLoad = true;
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}