#pragma once

class Camera;
class Grid;
class MtlTex;

class Lobby;

class XFileLoader;

//======================================
// - ## 10.03.17 ##
// - written by 김선호
// -  게임 시작 헤더파일
// - 매니저 규칙 - g_p클래스이름
//======================================

class MainGame
{
public:
	MainGame();
	~MainGame();

	/*   기본 세팅   */
	void Setup();
	void Update();
	void Render();
	void MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	void Setup_Object();
	void Render_Object();

private:
	/*   기본 세팅   */
	Camera* m_pCamera;
	Grid*	m_pGrid;

	Lobby* m_pLobby;

	LPD3DXMESH				m_pObjMesh;
	std::vector<MtlTex*>	m_vecObjMtlTex;

	XFileLoader*			m_xFileLoad;
};

