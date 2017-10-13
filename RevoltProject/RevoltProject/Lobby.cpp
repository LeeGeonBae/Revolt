#include "stdafx.h"
#include "Lobby.h"
#include "ObjectLoader.h"
#include "UIObject.h"
#include "UIImageView.h"

Lobby::Lobby()
	: m_pSprite(NULL)
	, m_stateLobby(INTRO1)
	, m_time(0.0f)
{
}


Lobby::~Lobby()
{
	SAFE_RELEASE(m_pSprite);
}

void Lobby::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	UIImageView* pImageView1 = new UIImageView;
	pImageView1->SetPosition(0, 0);
	pImageView1->SetTexture("lobby/intro/intro1.png");

	UIImageView* pImageView2 = new UIImageView;
	pImageView2->SetPosition(0, 0);
	pImageView2->SetTexture("lobby/intro/intro2.png");

	UIImageView* pImageView3 = new UIImageView;
	pImageView3->SetPosition(0, 0);
	pImageView3->SetTexture("lobby/intro/intro3.png");

	m_mapLobby[INTRO1] = new ST_Object;
	m_mapLobby[INTRO1]->m_time = 100.0f;
	m_mapLobby[INTRO1]->m_pObject = pImageView1;

	m_mapLobby[INTRO2] = new ST_Object;
	m_mapLobby[INTRO2]->m_time = 100.0f;
	m_mapLobby[INTRO2]->m_pObject = pImageView2;

	m_mapLobby[INTRO3] = new ST_Object;
	m_mapLobby[INTRO3]->m_time = 100.0f;
	m_mapLobby[INTRO3]->m_pObject = pImageView3;
}

void Lobby::Update()
{
	if (m_time > m_mapLobby[m_stateLobby]->m_time)
	{
		m_time = 0.0f;

		if (m_stateLobby == INTRO1)
			m_stateLobby = INTRO2;
		else if (m_stateLobby == INTRO2)
			m_stateLobby = INTRO3;
	}
	else
	{
		m_time += g_pTimeManager->GetElapsedTime();
	}

	m_mapLobby[m_stateLobby]->m_pObject->Update();
}

void Lobby::Render()
{
	if (m_mapLobby[m_stateLobby]->m_pObject)
		m_mapLobby[m_stateLobby]->m_pObject->Render(m_pSprite);
}
