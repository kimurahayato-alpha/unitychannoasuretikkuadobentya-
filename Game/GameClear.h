#pragma once
class Load;
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
private:
	Load* m_load;
};