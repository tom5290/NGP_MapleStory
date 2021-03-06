// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>


// 윈속 헤더
#pragma comment(lib, "ws2_32")
#include <winsock2.h>

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#include <mutex>

#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

// TransparentBlt함수를 사용하기 위한 라이브러리 추가.
#pragma comment(lib, "msimg32.lib")

//// 동영상을 재생하기 위한 라이브러리 삽입
//#include <Vfw.h>
//#pragma comment(lib, "vfw32.lib")


#include "Include.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "MathMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "MyBmp.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"

