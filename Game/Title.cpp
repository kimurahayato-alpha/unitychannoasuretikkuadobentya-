#include "stdafx.h"
#include "Title.h"
#include "Load.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	m_spriteRender.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/titlebgm.wav");
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{
	DeleteGO(titleBGM);
}

bool Title::Start()
{
	m_load = FindGO<Load>("load");

	m_load->StartLoadIn();
	return true;
}

void Title::Update()
{
	/*if (m_isWaitLoadout) {
		if (!m_load->IsLoad()) {
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}
	else {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_isWaitLoadout = true;
			m_load->StartLoadOut();
		}
	}*/

	if (m_load->isLoadSucces == true)
	{
		DeleteGO(m_load);
	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Load>(0, "load");
		DeleteGO(this);
	}

	m_spriteRender.Update();
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}