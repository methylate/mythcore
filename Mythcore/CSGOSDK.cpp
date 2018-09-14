#include "SDK.h"

namespace Mythcore
{
	namespace CSGOSDK
	{
		IBaseClientDLL*			pClient = NULL;
		IVEngineClient*			pEngine = NULL;
		IPanel*					pPanel = NULL;
		IClientEntityList*		pClientEntList = NULL;
		ISurface*				pSurface = NULL;
		CGlobalVarsBase*		pGlobals = NULL;
		IEngineTrace*			pEngineTrace = NULL;
		unsigned long			espfont = NULL;
		CInput *                pInput = NULL;
		IPhysicsSurfaceProps *  pPhysics = NULL;
		IMDLCache *				pMDLCache = NULL;
		IVModelRender *			pModelRender = NULL;
		IVModelInfo *			pModelInfo = NULL;
		IMaterialSystem *		pMatSystem = NULL;
		IGameEventManager2 *	pGameEventManager = NULL;
		IGameConsole *			pGameConsole = NULL;
		ICvar*                  pCvar = NULL;

		bool CGameTrace::DidHitWorld() const {
			return m_pEnt == (IClientEntity*)pClientEntList->GetClientEntity(0);
		}


		bool CGameTrace::DidHitNonWorldEntity() const {
			return m_pEnt != nullptr && !DidHitWorld();
		}

		int IClientEntity::GetHitSet() {
			static  DWORD offset = pNetworkedVariables->GetNetvar("DT_BaseAnimating", "m_nHitboxSet");
			if(!offset)
				offset = pNetworkedVariables->GetNetvar("DT_BaseAnimating", "m_nHitboxSet");
			return *reinterpret_cast<int*>((DWORD)this + offset);
		}


		IClientEntity* IClientEntity::GetOwnerEntity() {
			CBaseHandle m_hOwnerEntity = *(CBaseHandle*)((DWORD)this + 0x148);
			return reinterpret_cast< IClientEntity*>(pClientEntList->GetClientEntity(m_hOwnerEntity.GetEntryIndex()));
		}

		 /////////////////// setvalue

		inline const void** getvtable(const void* inst, size_t offset = 0) {
			if (!inst && !offset)
				return nullptr;
			return *reinterpret_cast< const void*** >((size_t)inst + offset);
		}

		template< typename Fn >
		inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0) {
			if (!inst && offset == 0)
				return NULL;

			return reinterpret_cast< Fn >(getvtable(inst, offset)[index]);
		}

		enum EConVar {
			ConVar_GetName = 5,
			ConVar_GetBaseName = 6,
			ConVar_GetFloat = 12,
			ConVar_SetString = 14,
			ConVar_SetFloat,
			ConVar_SetInt
		};

		enum EICVar {
			ICVar_FindVar = 15
		};

		void ConVar::SetValue(const char* value) {
			typedef void(__thiscall* SetValueFn)(void*, const char*);
			return getvfunc< SetValueFn >(this, ConVar_SetString)(this, value);
		}

		void ConVar::SetValue(float value) {
			typedef void(__thiscall* SetValueFn)(void*, float);
			return getvfunc< SetValueFn >(this, ConVar_SetFloat)(this, value);
		}

		void ConVar::SetValue(int value) {
			typedef void(__thiscall* SetValueFn)(void*, int);
			return getvfunc< SetValueFn >(this, ConVar_SetInt)(this, value);
		}
	}
}