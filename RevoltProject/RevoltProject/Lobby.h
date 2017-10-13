#pragma once

class UIObject;

enum LOBBY{INTRO1,INTRO2,INTRO3};

struct ST_Object
{
	float		m_time;
	UIObject*	m_pObject;
};

class Lobby
{
private:
	std::map<LOBBY, ST_Object*>			m_mapLobby;
	LPD3DXSPRITE						m_pSprite;
	LOBBY m_stateLobby;
	float m_time;
public:
	Lobby();
	~Lobby();

	void Setup();
	void Update();
	void Render();
};

