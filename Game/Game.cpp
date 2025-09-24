#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "GameClear.h"
#include "GameOver.h"
#include "sound/SoundEngine.h"
#include "Star.h"
#include "Load.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_skyCube);
	DeleteGO(gameBGM);
	DeleteGO(m_backGround);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_backGround = NewGO<BackGround>(0, "background");
	InitSky();

	Star* star1 = NewGO<Star>(0, "star");
	star1->m_position = { -100.0f,950.0f,0.0f };
	star1->m_firstPosition = star1->m_position;

	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(1);
	gameBGM->Play(true);

	//m_fade = FindGO<Load>("load");
	//m_fade->StartLoadIn();

	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();

	m_timer -= g_gameTime->GetFrameDeltaTime();
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;

	wchar_t text[256];
	swprintf_s(text, 256, L"%02d:%02d", minute, sec);
	m_timerFontRender.SetText(text);
	m_timerFontRender.SetPosition({ -100.0f,500.0f,0.0f });
	m_timerFontRender.SetScale({ 2.0f });
	m_timerFontRender.SetColor(g_vec4White);

	if (m_player->m_starCount == 1)
	{
		NewGO<GameClear>(0);
		DeleteGO(this);
	}

	if (m_timer <= 0.0f)
	{
		NewGO<GameOver>(0);
		DeleteGO(this);
	}


	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_timerFontRender.Draw(rc);
}

void Game::InitSky()
{
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
}