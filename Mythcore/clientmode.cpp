#include "SDK.h"

namespace Mythcore {

	namespace HOOK {

		using namespace VMTHooks;

		bool __fastcall hookIsTimedOut(PVOID Self, int EDX) {
			
			return false;
		}

		void __fastcall	hookLevelInit(PVOID self, int edx, const char *newmap) {
			VMTManager& hook = VMTManager::GetHook(self);
			hook.GetMethod<void(__thiscall*)(PVOID, const char *)>(25)(self, newmap);
			VMTBaseManager * vmt = new VMTBaseManager();
			vmt->Init(pEngine->GetNetChannelInfo());
			vmt->HookMethod(&hookIsTimedOut, 60);
			vmt->Rehook();
			pCvar->ConsoleColorPrintf(Color::Green(), "Ready ^^!\n");
		}
	}
}