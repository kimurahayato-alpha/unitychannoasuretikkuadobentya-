#pragma once
#include "Level3DRender/LevelRender.h"
#include "sound/SoundSource.h"


class Player;
class GameCamera;
class BackGround;
class Load;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	FontRender m_timerFontRender;

	float m_timer = 51.0f;

private:
	void InitSky();
	ModelRender m_modelRender;
	Vector3 m_pos;
	Player* m_player;
	GameCamera* m_gameCamera;
	SkyCube* m_skyCube;
	BackGround* m_backGround = nullptr;
	SoundSource* gameBGM;
	bool					m_isWaitLoadout = false;
	Load* m_fade = nullptr;
	int						m_skyCubeType = enSkyCubeType_Day;
};