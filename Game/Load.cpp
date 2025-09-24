#include "stdafx.h"
#include "Load.h"
#include "Game.h"
#include "Title.h"
namespace
{
	const Vector3	SCALE = Vector3(2.16f, 2.16f, 1.0f);
	const Vector3	POSITIOIN = Vector3(-128.0f, 0.0f, 0.0f);
}


Load::Load()
{
}

Load::~Load()
{
}

bool Load::Start()
{
	m_spriteRender2.Init("Assets/sprite/nowload.DDS", 1.0f, 33.0f);
	m_spriteRender.Init("Assets/sprite/loadlimit.DDS", 1920.0f, 1080.0f);
	m_spriteRender.SetScale(SCALE);
	m_spriteRender.SetPosition(POSITIOIN);
    //m_spriteRender2.SetScale(Vector3(0.001f, 1.0f, 0.5f));
	//m_spriteRender2.SetPosition(Vector3(-900.0f, -341.0f, 0.0f));
	//sm_spriteRender2.SetPivot(Vector2(0.0f, 0.5f));
	return true;
}

void Load::Update()
{
	m_Loadcount += g_gameTime->GetFrameDeltaTime();

	float scale = 1.0f + m_Loadcount * 360.00f;

	float wide = 1.0f * scale;

	m_spriteRender2.SetScale(Vector3(scale, 2.16f, 1.0f));
	
	m_spriteRender2.SetPosition(Vector3(-890.0f + wide / 2.0f, -341.0f, 0.0f));

	switch (m_state) {
	case enState_LoadIn:
		m_currentAlpha -= 2.0f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
			isLoadSucces = true;
		}
		break;
	case enState_LoadOut:
		m_currentAlpha += 2.0f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:

		break;
	}

	if (isGameOverLoad == true)
	{
		StartLoadIn();
		NewGO<Title>(0, "title");
		isGameOverLoad = false;
	}

	if (isClearLoad == true)
	{
		StartLoadIn();
		NewGO<Title>(0, "title");
		isClearLoad = false;
	}

	if (m_Loadcount > 5)
	{
		StartLoadIn();
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}

	m_spriteRender2.Update();
}

void Load::Render(RenderContext& rc)
{
	if (m_currentAlpha > 0.0f) {
		m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_spriteRender.Draw(rc);
	}
	m_spriteRender2.Draw(rc);
}
