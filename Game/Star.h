#pragma once

class Player;
class Game;

class Star : public IGameObject
{
public:
	Star();
	~Star();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();

	ModelRender m_modelRender;
	Vector3 m_position;
	int m_moveCount;
	Vector3 m_firstPosition;
	Quaternion m_rotation;
	Player* m_player;
	Game* m_game;
};

