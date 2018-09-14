#include "SDK.h"

namespace Mythcore
{
	namespace HOOK
	{
		using namespace VMTHooks;
		class GlowObjectDefinition_t
		{
		public:
			void set(float r, float g, float b, float a)
			{
				m_vGlowColor = Vector(r, g, b);
				m_flAlpha = a;
				m_bRenderWhenOccluded = true;
				m_bRenderWhenUnoccluded = false;
				//m_flBloomAmount = 1.0f;
			}

			IClientEntity* getEnt()
			{
				return m_hEntity;
			}

			bool IsUnused() const { return m_nNextFreeSlot != GlowObjectDefinition_t::ENTRY_IN_USE; }

		public:
			IClientEntity *    m_hEntity;
			Vector  m_vGlowColor;
			float   m_flAlpha;                 //0x0010
			uint8_t pad_0014[4];               //0x0014
			float   m_flSomeFloat;             //0x0018
			uint8_t pad_001C[4];               //0x001C
			float   m_flAnotherFloat;          //0x0020
			bool    m_bRenderWhenOccluded;     //0x0024
			bool    m_bRenderWhenUnoccluded;   //0x0025
			bool    m_bFullBloomRender;        //0x0026
			uint8_t pad_0027[5];               //0x0027
			int32_t m_nGlowStyle;              //0x002C
			int32_t m_nSplitScreenSlot;        //0x0030
			int32_t m_nNextFreeSlot;           //0x0034


			// Special values for GlowObjectDefinition_t::m_nNextFreeSlot 
			static const int END_OF_FREE_LIST = -1;
			static const int ENTRY_IN_USE = -2;
		};

		static DWORD dwGlowObjectBase = 0;

		DWORD GetGlowObjectManagerPointer()
		{
			DWORD address = MemoryAPI::FindPattern((DWORD)GetModuleHandle("client.dll"),
				MemoryAPI::GetModule("client.dll", true),
				(BYTE*)"\x0F\x11\x05\x00\x00\x00\x00\x83\xC8\x01",
				"xxx????xxx") + 0x3;
			return address;
		}

		DWORD GetGlowObjectCount()
		{
			return *(PDWORD)(dwGlowObjectBase + 0x4);
		}
	}
}
		/*void __stdcall hookPaintTraverse(unsigned vguiPanel, bool forceRepaint, bool allowForce)
		{
			pPanelHook->GetMethod<void(__thiscall*)(PVOID, unsigned, bool, bool)>(41)(pPanel, vguiPanel, forceRepaint, allowForce);

			if (!dwGlowObjectBase)
				dwGlowObjectBase = GetGlowObjectManagerPointer();

			static unsigned int overlayPanel = 0;
			if (overlayPanel == 0)
			{
				if (!strstr(pPanel->GetName(vguiPanel), "MatSystemTopPanel"))
					return;

				overlayPanel = vguiPanel;
			}
			if (vguiPanel == overlayPanel)
			{
				if (pEngine->IsInGame() && pEngine->IsConnected())
				{
					IClientEntity* pLocalEntity = Engine::GetLocalPlayer();

					if (!pLocalEntity)
						return;

					if (pLocalEntity->IsDormant())
						return;

					for (int i = 1; i < 64; i++)
					{
						IClientEntity* pEntity = pClientEntList->GetClientEntity(i);

						if (pEntity == NULL)
							continue;

						if (pEntity->IsDormant())
							continue;

						if (!Engine::IsAlive(pEntity))
							continue;

						if (pEntity->Index() == pLocalEntity->Index())
							continue;

						bool bIsEnemy = pEntity->GetTeamNum() != pLocalEntity->GetTeamNum();
						if (!bIsEnemy)
							continue;

						player_info_t pi;
						if (!pEngine->GetPlayerInfo(i, &pi))
							continue;
						// GlowObjectDefinition_t * pGlowObjects = (GlowObjectDefinition_t*)(*(DWORD*)dwGlowObjectBase);

						// DWORD nGlowID = pEntity->GetGlowIndex();
						if (nGlowID >= 0 && nGlowID < GetGlowObjectCount())
						{
							pGlowObjects[nGlowID].set(1.f, 1.f, 0.f, 0.35f);
						}
					}
				}
			}
		}
	}
}*/