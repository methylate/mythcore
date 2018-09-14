//Microsoft includes
#include <string>
#include <string.h>
#include <sstream> 
#include <fstream>

#include <Windows.h>
#include <Tlhelp32.h>
#include <cassert>
#include <math.h>
#include <cmath>

#include <iostream>
#include <vector>

#include <algorithm>
#include <unordered_map>
#include <map>
#include <time.h>

#pragma warning (disable: 4244) // loss of data
#pragma warning (disable: 4800) // warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning (disable: 4018) //C4018: '<' : signed/unsigned mismatch

using namespace std;

#include <ddraw.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <D3dx9tex.h>
#include <D3dx9shape.h>

#include "crc32.h"
#include "offsets.h"
#include "math.h"
#include "cs_utils.h"
#include "vmthooks.h"
#include "recvproxy.h"
#include "netvars.h"
#include "CSGOSDK.h"
#include "config.h"
#include "engine.h"
#include "memoryapi.h"
#include "pConVar.h"

namespace Mythcore {

	extern DWORD WINAPI CustomThread(PVOID pThreadParameter);
	extern CSGOSDK::CLocalPlayer gLocalPlayerInfo;
	extern CSGOSDK::CPlayersListPlayer GamePlayers[65]; // adv player list
	typedef void(*oConColorMsg)(const Color& clr, const char* pMsg, ...);
	extern oConColorMsg ConColorMsg;

	namespace HOOK {

		//clientmode
		extern void __fastcall	hookLevelInit(PVOID self, int edx, const char *newmap);

		//clint
		extern void __fastcall hookCreateMove(PVOID self, int edx, int seqnr, float time_, bool active, bool & bSendPacket);
	}
}