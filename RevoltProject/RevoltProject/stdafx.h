#pragma once

#include "targetver.h"

//======================================
// - ## 09.29.17 ##
// - written by 김선호
// - 헤더파일 선언 및 쓸만한 기능함수 선언
//======================================


//======================================
// - ## 헤더파일 선언 및 전역 변수
//======================================

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/*   C++ 헤더파일   */
#include <iostream>
#include <fstream>

/*   STL 헤더파일   */
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <bitset>

/*   프로세스 관련 헤더파일   */
#include <assert.h>
#include <thread>
#include <process.h>

/*   다이렉트3D 관련 헤더파일   */
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

/*   사운드 관련 헤더파일   */
#include "fmodinc/fmod.hpp"
#pragma comment (lib, "fmodlib/fmodex_vc.lib")

/*   전역변수 설정   */
extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;

//======================================
// - ## 매크로 함수 및 변수 ##
//======================================
#define WINSIZEX 1024
#define WINSIZEY 768

#define SAFE_RELEASE(p) { if(p) p->Release() ; p = NULL ;}
#define SAFE_DELETE(p) { if(p) delete p ; p = NULL ; }
#define SAFE_DELETE_ARRAY(p) {if(p) delete[] p; p = NULL;}

#define SINGLETONE(class_name) \
	private : \
		class_name(void); \
		~class_name(void); \
	public: \
		static class_name* GetInstance() \
		{ \
			static class_name instance; \
			return &instance; \
		}

#define SYNTHESIZE( varType , varName , funName) \
protected: varType varName ; \
public : inline varType Get##funName(void) const { return varName ; } \
public : inline void Set##funName(varType var) { varName = var ; }

#define SYNTHESIZE_PASS_BY_REF( varType , varName , funName) \
protected: varType varName ; \
public : inline varType& Get##funName(void)  { return varName ; } \
public : inline void Set##funName(varType& var) { varName = var ; }

#define SAFE_ADD_REF(p) { if(p) p->AddRef() ; }

#define SYNTHESIZE_ADD_REF( varType , varName, funName) \
	protected : varType  varName ; \
	public : virtual varType Get##funName(void) const { \
									return varName ; } \
	public : virtual void Set##funName(varType var) { \
				if( varName != var ) { \
					SAFE_ADD_REF(var) ; \
					SAFE_RELEASE(varName) ; \
					varName = var ; \
				} \
		}\

//======================================
// - ## 구조체 선언 ##
//======================================
struct ST_SIZE
{
	int nWitdh;
	int nHeight;
	ST_SIZE() : nWitdh(0), nHeight(0) {}
	ST_SIZE(int _nWidth, int _nHeight)
		: nWitdh(_nWidth), nHeight(_nHeight) {}
};

struct ST_PC_VERTEX
{
	D3DXVECTOR3  p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3  p;
	D3DXVECTOR3  n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3  p;
	D3DXVECTOR3  n;
	D3DXVECTOR2  t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3  p;
	D3DXVECTOR2  t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_RHWC_VERTEX
{
	D3DXVECTOR4  p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};

struct ST_POS_SAMPLE
{
	int			n;
	D3DXVECTOR3	v;
	ST_POS_SAMPLE() : n(0), v(0, 0, 0) {}
};
struct ST_ROT_SAMPLE
{
	int			n;
	D3DXQUATERNION	q;
	ST_ROT_SAMPLE() : n(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};

struct BoundingSphere
{
	D3DXVECTOR3 v;
	float radius;
	bool isPicking;
};

struct ST_SPHERE
{
	float				fRadius;
	D3DXVECTOR3 vCenter;
	bool				isPicked;
	ST_SPHERE() : fRadius(0.0f), vCenter(0, 0, 0), isPicked(false) { }
};

struct ST_ASTAR
{
	POINT wall;
	POINT path;
};

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}

//Line
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//Rect					50     50       300        300
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

//Rectangle
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//Ellipse
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

// = XRGB COLOR
#define C_RED      D3DCOLOR_XRGB(255,0,0)
#define C_BLUE      D3DCOLOR_XRGB(0,0,255)
#define C_GREEN      D3DCOLOR_XRGB(0,255,0)
#define C_BLACK      D3DCOLOR_XRGB(0,0,0)
#define C_WHITE      D3DCOLOR_XRGB(255,255,255)
#define C_MAGENTA   D3DCOLOR_XRGB(255,0,255)
#define C_CYAN      D3DCOLOR_XRGB(0,255,255)
#define C_YELLOW   D3DCOLOR_XRGB(255,255,0)
#define C_GRAY      D3DCOLOR_XRGB(128, 128, 128)

// = D3DXCOLOR
#define CX_RED      D3DXCOLOR(1,0,0,1)
#define CX_BLUE      D3DXCOLOR(0,0,1,1)
#define CX_GREEN   D3DXCOLOR(0,1,0,1)
#define CX_BLACK   D3DXCOLOR(0,0,0,1)
#define CX_WHITE   D3DXCOLOR(1,1,1,1)
#define CX_GRAY      D3DXCOLOR(0.5,0.5,0.5,1)

//======================================
// - ## 매니저 헤더파일 선언 ##
//======================================
#include "DeviceManager.h"
#include "Object.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SkinnedMeshManager.h"