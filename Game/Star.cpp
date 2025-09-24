#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "Game.h"

Star::Star()
{
	m_modelRender.Init("Assets/modelData/star.tkm");

	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

}

Star::~Star()
{

}

void Star::Update()
{
	Move();

	Rotation();

	m_modelRender.Update();

	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 120.0f)
	{
		m_player->m_starCount += 1;
		DeleteGO(this);
	}

	if (m_game->m_timer <= 0.0f)
	{
		DeleteGO(this);
	}
}

void Star::Move()
{
	if (m_moveCount == 0)
	{
		m_position.y += 1.0f;
	}
	else if (m_moveCount == 1)
	{
		m_position.y -= 1.0f;
	}

	if (m_position.y >= m_firstPosition.y + 100.0f)
	{
		m_moveCount = 1;
	}
	else if (m_position.y <= m_firstPosition.y - 100.0f)
	{
		m_moveCount = 0;
	}

	m_modelRender.SetPosition(m_position);
}

void Star::Rotation()
{
	m_rotation.AddRotationDegY(2.0f);

	m_modelRender.SetRotation(m_rotation);
}

void Star::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}