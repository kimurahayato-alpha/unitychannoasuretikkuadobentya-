#pragma once
class Load : public IGameObject
{
public:
	Load();
	~Load();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void StartLoadIn()
	{
		m_state = enState_LoadIn;
	}
	void StartLoadOut()
	{
		m_state = enState_LoadOut;
	}

	bool IsLoad() const
	{
		return m_state != enState_Idle;
	}
	float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

	bool isLoadSucces = false;
	bool isClearLoad = false;
	bool isGameOverLoad = false;

private:
	float Loading = 0;
	enum EnState {
		enState_LoadIn,
		enState_LoadOut,
		enState_Idle,
	};
	SpriteRender	m_spriteRender;
	SpriteRender    m_spriteRender2;
	EnState			m_state = enState_Idle;
	float			m_currentAlpha = 1.0f;
	float m_Loadcount;
};