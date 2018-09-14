#include "SDK.h"

namespace Mythcore {

	//ќбъ€вл€ем глобальные (extern в SDK.h)
	CSGOSDK::CLocalPlayer gLocalPlayerInfo;
	CSGOSDK::CPlayersListPlayer GamePlayers[65]; // adv player list
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

	if (fdwReason == DLL_PROCESS_ATTACH) {

		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Mythcore::CustomThread, 0, 0, NULL);
	}
	return true;
}