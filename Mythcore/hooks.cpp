#include "SDK.h"

using namespace Mythcore::VMTHooks;
using namespace Mythcore::CSUtils;
using namespace Mythcore;
using namespace Mythcore::CSGOSDK;

namespace Mythcore {
	oConColorMsg ConColorMsg;
	
	__declspec(naked) void hookCreateMoveAsm(int seqnr, float time, bool active) {
		__asm {
		    push ebp
			mov ebp, esp
			push ebx
			lea ecx, [esp]
			push ecx
			movzx eax, active
			push eax
			mov eax, time
			push eax
			mov eax, seqnr
			push eax
			call Mythcore::HOOK::hookCreateMove
			pop ebx
			pop ebp
			retn 0xC
		}
	}

	void First() {
		pConfig = new CConfig();
		pNetworkedVariables = new CNetworkedVariableManager();
		ConColorMsg = (oConColorMsg)((DWORD)MemoryAPI::GetModuleHandleSafe("tier0.dll") + 0x6700);
	}

	void InitOffsets() {
		Offsets::dwClient = (DWORD)GetModuleHandle("client.dll");
	}
	void Init() {
		Sleep(500);
		First();

		CreateInterfaceFn fnVguiMatSurface = CaptureFactory("vguimatsurface.dll");
		CreateInterfaceFn fnMatSystem = CaptureFactory("materialsystem.dll");
		CreateInterfaceFn fnDatacache = CaptureFactory("datacache.dll");
		CreateInterfaceFn fnVPhysics = CaptureFactory("vphysics.dll");
		CreateInterfaceFn fnEngine = CaptureFactory("engine.dll");
		CreateInterfaceFn fnClient = CaptureFactory("client.dll");
		CreateInterfaceFn fnServer = CaptureFactory("server.dll");
		CreateInterfaceFn fnVgui2 = CaptureFactory("vgui2.dll");
		CreateInterfaceFn fnVstdlib = CaptureFactory("vstdlib.dll");

		Sleep(2000);

		//Получаем интерфейсы
		pGameEventManager = reinterpret_cast<IGameEventManager2*>(CaptureInterface(fnEngine, INTERFACEVERSION_GAMEEVENTSMANAGER2));
		pPhysics = reinterpret_cast<IPhysicsSurfaceProps*>(CaptureInterface(fnVPhysics, VPHYSICS_SURFACEPROPS_INTERFACE_VERSION));
		pModelRender = reinterpret_cast<IVModelRender*>(CaptureInterface(fnEngine, VENGINE_HUDMODEL_INTERFACE_VERSION));
		pClientEntList = reinterpret_cast<IClientEntityList*>(CaptureInterface(fnClient, "VClientEntityList003"));
		pMatSystem = reinterpret_cast<IMaterialSystem*>(CaptureInterface(fnMatSystem, "VMaterialSystem080"));
		pEngineTrace = reinterpret_cast<IEngineTrace*>(CaptureInterface(fnEngine, "EngineTraceClient004"));
		pSurface = reinterpret_cast<ISurface*>(CaptureInterface(fnVguiMatSurface, "VGUI_Surface031"));
		pEngine = reinterpret_cast<IVEngineClient*>(CaptureInterface(fnEngine, "VEngineClient014"));
		pClient = reinterpret_cast<IBaseClientDLL*>(CaptureInterface(fnClient, "VClient018"));
		pModelInfo = reinterpret_cast<IVModelInfo*>(CaptureInterface(fnEngine, "VModelInfoClient004"));
		pPanel = reinterpret_cast<IPanel*>(CaptureInterface(fnVgui2, "VGUI_Panel009"));
		pGameConsole = reinterpret_cast<IGameConsole*>(CaptureInterface(fnClient, "GameConsole004"));
		pCvar = reinterpret_cast<ICvar*>(CaptureInterface(fnVstdlib, "VEngineCvar007"));
		pInput = *(CInput**)((*(DWORD**)pClient)[15] + 0x1);
		pGlobals = **(CGlobalVarsBase***)((*(DWORD**)pClient)[0] + 0x1B);
		InitOffsets();

		pNetworkedVariables->Init();
		pPanelHook = new VMTBaseManager();
		pPanelHook->Init(pPanel);
		pPanelHook->Rehook();
		pClientHook = new VMTBaseManager();
		pClientHook->Init(pClient);
		pClientHook->HookMethod(&hookCreateMoveAsm, 21);
		pClientHook->Rehook();

		string csgo_path = string(pEngine->GetGameDirectory());
		pConfig->Load(csgo_path + "\\cfg\\mcore.cfg");
		pEngine->ExecuteClientCmd("sv_lan 1"); pGameConsole->Clear();
		if (!pGameConsole->IsConsoleVisible()) pGameConsole->Activate();
		pCvar->ConsoleColorPrintf(Color(2, 153, 253), "[MYTHCORE] ");
		pCvar->ConsoleColorPrintf(Color::Green(), "SUCCESSFULLY LOADED!\n");
	}

	DWORD WINAPI CustomThread(PVOID pThreadParameter) {
		HMODULE hModEngine = NULL;
		HMODULE hModClient = NULL;
		HMODULE hD3d = NULL;
		do {
			hModEngine = GetModuleHandleA("engine.dll");
			hModClient = GetModuleHandleA("client.dll");
			hD3d = GetModuleHandleA("shaderapidx9");
			Sleep(500);
		} while (!hModEngine || !hModClient || !hD3d);
		Init();
		return 0;
	}
}
