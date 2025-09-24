#include "stdafx.h"
#include "Player.h"
#include"GameCamera.h"

Player::Player()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	m_characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{

}
bool Player::Start()
{
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	return true;
}

bool Player::StartPoint()
{
	m_saveposition = m_position;
	return true;
}

void Player::Update()
{
	Move();

	Rotation();

	ManageState();

	PlayAnimation();

	m_modelRender.Update();

	if (m_position.y < -300.0f)
	{
		m_position = m_saveposition;
		m_characterController.SetPosition(m_position);
		m_modelRender.SetPosition(m_position);
	}
}

void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	forward.y = 0.0f;
	right.y = 0.0f;

	right *= stickL.x * 200.0f;
	forward *= stickL.y * 200.0f;

	m_moveSpeed += right + forward;

	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.x *= 1.5;
		m_moveSpeed.z *= 1.5;
		m_playerState = 3;
	}

	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y = 180.0f;
		}
	}
	else
	{
		m_moveSpeed.y -= 3.0f;
	}


	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{
	if (m_characterController.IsOnGround() == false)
	{
		m_playerState = 1;
		return;
	}

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (m_playerState != 3)
		{
			m_playerState = 2;
		}
	}
	else
	{
		m_playerState = 0;
	}
}

void Player::PlayAnimation()
{
	switch (m_playerState) {
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	if (m_gameCamera->m_playerRenderFlag == true)
	{
		m_modelRender.Draw(rc);
	}
	if (m_gameCamera->m_playerRenderFlag == false)
	{

	}
}