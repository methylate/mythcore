#include "SDK.h"

namespace Mythcore
{
	using namespace Mythcore;
	using namespace Mythcore::CSGOSDK;
	using namespace Mythcore::Math;

	namespace Engine {

		bool IsVisible(IClientEntity* pLocalBaseEntity, IClientEntity* pBaseEntity, Vector vStart, Vector vEnd) {
			trace_t pTrace;
			Ray_t pRay;
			CTraceFilter traceFilter(pLocalBaseEntity);
			pRay.Init(vStart, vEnd);
			pEngineTrace->TraceRay(pRay, MASK_SHOT | MASK_SOLID/*0x46004003*/, &traceFilter, &pTrace);
			if (pBaseEntity)
				return (pTrace.m_pEnt == pBaseEntity || pTrace.fraction >= 1.0f);
			return (pTrace.fraction >= 1.0F);
		}

		Vector GetEyePosition(IClientEntity* pEntity) {
			Vector vecViewOffset = *reinterpret_cast<Vector*>(reinterpret_cast<int>(pEntity)+0x104); //DT_BasePlayer -> m_vecViewOffset[0]: __________ 0x00000104
			return pEntity->GetOrigin() + vecViewOffset;
		}

		Vector GetPunchAngles(IClientEntity* pEntity){
			static DWORD offset = pNetworkedVariables->GetNetvar("DT_BasePlayer", "m_aimPunchAngle");
			if (!offset)
				offset = pNetworkedVariables->GetNetvar("DT_BasePlayer", "m_aimPunchAngle");
			Vector vecPA = *reinterpret_cast<Vector*>(reinterpret_cast<int>(pEntity) + offset); // m_Local + m_aimPunchAngle
			return Vector(vecPA.X, vecPA.Y, 0);
		}

		Vector GetVecVelocity(IClientEntity* pEntity) {
			Vector vec = *reinterpret_cast<Vector*>(reinterpret_cast<int>(pEntity)+0x110); // DT_BasePlayer -> m_vecVelocity[0]: ____________ 0x00000110
			return vec;
		}


		CBaseCombatWeapon* GetBaseCombatWeapon(IClientEntity* pEntity) {
			static DWORD offset = pNetworkedVariables->GetNetvar("DT_BasePlayer", "m_hActiveWeapon");
			if (!offset)
				offset = pNetworkedVariables->GetNetvar("DT_BasePlayer", "m_hActiveWeapon");
			HANDLE hHandle = (HANDLE)*(PDWORD)((DWORD)pEntity + offset); // DT_BasePlayer -> m_hActiveWeapon: _____________ 0x000012B8
			CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pClientEntList->GetClientEntityFromHandle(hHandle);
			return pWeapon;
		}

		int GetWeaponAmmo(CBaseCombatWeapon * pWeapon) {
			static DWORD offset = pNetworkedVariables->GetNetvar("DT_BaseCombatWeapon", "m_iClip1");
			if (!offset)
				offset = pNetworkedVariables->GetNetvar("DT_BaseCombatWeapon", "m_iClip1");
			int  iClip1 = *reinterpret_cast<int*>(reinterpret_cast<int>(pWeapon)+offset); // DT_BaseCombatWeapon -> m_iClip1: ______________ 0x000015B8
			return iClip1;

		}


		IClientEntity * GetLocalPlayer() {
			return pClientEntList->GetClientEntity(pEngine->GetLocalPlayer()); // dwClientState_GetLocalPlayer pattern": "8B 80 ? ? ? ? 40 C3
		}


		float GetTickBase(IClientEntity * pEntity) {
			return (float)(pEntity->GetTickBase() * pGlobals->interval_per_tick);
		}

		///\\\\\\\\\\\\\\\\\\ Needefull stuff

		int GetHealth(IClientEntity* pEntity) {
			return *reinterpret_cast<int*>(reinterpret_cast<int>(pEntity)+0xFC); // DT_BasePlayer -> m_iHealth: ___________________ 0x000000FC
		}

		bool IsAlive(IClientEntity* pEntity) {
			char szLifeState = *(char*)((DWORD)pEntity + 0x25B); // m_lifeState 
			return (szLifeState == 0);
		}

		bool IsWeaponPistol(int iWeaponID) {

			return(iWeaponID == WEAPON_DEAGLE || iWeaponID == WEAPON_DUALS || iWeaponID == WEAPON_FIVE7 || iWeaponID == WEAPON_GLOCK
				|| iWeaponID == WEAPON_P250 || iWeaponID == WEAPON_USPS || iWeaponID == WEAPON_TEC9 || iWeaponID == WEAPON_TASER || iWeaponID == WEAPON_P2000);
		}

		bool IsWeaponNonAim(int iWeaponID) {
			if (iWeaponID == WEAPON_KNIFE_T || iWeaponID == WEAPON_KNIFE_CT || iWeaponID == WEAPON_KNIFE_BAYONET ||
				iWeaponID == WEAPON_KNIFE_BUTTERFLY || iWeaponID == WEAPON_KNIFE_M9BAYONET ||
				iWeaponID == WEAPON_KNIFE_GUT || iWeaponID == WEAPON_KNIFE_KARAMBIT || iWeaponID == WEAPON_KNIFE_HUNTSMAN || iWeaponID == WEAPON_KNIFE_FLIP ||
				iWeaponID == WEAPON_FLASH || iWeaponID == WEAPON_HE || iWeaponID == WEAPON_SMOKE ||
				iWeaponID == WEAPON_MOLOTOV || iWeaponID == WEAPON_DECOY || iWeaponID == WEAPON_INC || iWeaponID == WEAPON_C4)
				return true;

			return false;
		}

		bool IsWeaponSniper(int iWeaponID) {
			if (iWeaponID == WEAPON_SCAR20 || iWeaponID == WEAPON_G3SG1 || iWeaponID == WEAPON_SCOUT || iWeaponID == WEAPON_AWP)
				return true;
			return false;
		}

		bool IsWeaponKnife(int iWeaponID) {

			if (iWeaponID == WEAPON_KNIFE_CT ||
				iWeaponID == WEAPON_KNIFE_T ||
				iWeaponID == WEAPON_KNIFE_BAYONET ||
				iWeaponID == WEAPON_KNIFE_FLIP ||
				iWeaponID == WEAPON_KNIFE_GUT ||
				iWeaponID == WEAPON_KNIFE_KARAMBIT ||
				iWeaponID == WEAPON_KNIFE_M9BAYONET ||
				iWeaponID == WEAPON_KNIFE_HUNTSMAN ||
				iWeaponID == WEAPON_KNIFE_BUTTERFLY) {
				return true;
			} return false;
		}
	}
}