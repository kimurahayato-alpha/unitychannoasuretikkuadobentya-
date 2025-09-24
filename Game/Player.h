#pragma once
class GameCamera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	bool StartPoint();
	bool Start();


	ModelRender m_modelRender;
	Vector3 m_position;
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Vector3 m_moveSpeed;
	Quaternion m_rotation;
	Vector3 m_saveposition;
	int m_playerState = 0;
	int m_starCount = 0;
	GameCamera* m_gameCamera;
};

