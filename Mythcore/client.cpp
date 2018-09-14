#include "SDK.h"

namespace Mythcore
{
	namespace HOOK
	{
		using namespace VMTHooks;

		FORCEINLINE float DotProductT(const float* a, const float* b) {
			return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
		}

		void VectorTransformA(const float *in1, const matrix3x4_t& in2, float *out) {

			out[0] = DotProductT(in1, in2[0]) + in2[0][3];
			out[1] = DotProductT(in1, in2[1]) + in2[1][3];
			out[2] = DotProductT(in1, in2[2]) + in2[2][3];
		}


		void VectorTransformZ(const Vector& in1, const matrix3x4_t &in2, Vector &out) {
			VectorTransformA(&in1.X, in2, &out.X);
		}

		bool GetHitbox(IClientEntity* pLocal, IClientEntity* pTarget, Vector &vOut, int index) {

			matrix3x4_t Matrix[128];

			float flCurTime = (float)pLocal->GetTickBase() * pGlobals->interval_per_tick;

			if (!pTarget->SetupBones(Matrix, 128, 0x00000100, 0.f))
				return false;

			studiohdr_t *pStudioHeader = pModelInfo->GetStudioModel((model_t*)pTarget->GetModel());
			if (!pStudioHeader)
				return false;

			mstudiohitboxset_t *set = pStudioHeader->pHitboxSet(pTarget->GetHitSet());
			if (!set)
				return false;

			mstudiobbox_t* pbox = set->pHitbox(index);
			if (!pbox)
				return false;

			Vector vMin, vMax;
			VectorTransformZ(pbox->bbmin, Matrix[pbox->bone], vMin);
			VectorTransformZ(pbox->bbmax, Matrix[pbox->bone], vMax);
			vOut = (vMin + vMin) * 0.5f;
			return true;
		}

		Vector IsHittable(IClientEntity* pLocalEntity, IClientEntity* pEntity, Vector vFrom, int iHitbox, bool & bCanHit) {
			Vector vTemp(0, 0, 0);

			if (!GetHitbox(pLocalEntity, pEntity, vTemp, iHitbox))
				return Vector(0, 0, 0);

			if (Engine::IsVisible(pLocalEntity, pEntity, vFrom, vTemp)) {
				bCanHit = true;
				return vTemp;
			}

			return Vector(0, 0, 0);
		}

		enum hitbox_e {
			Head,
			Head2,
			Neck,
			Body0,//низ 
			Body1,
			Body2,
			Body3,
			Body4,//верх, ближе к щее 
			R_knee,
			L_knee,
			R_leg,
			L_leg,
			R_leg2,
			L_leg2,
			R_hand,
			L_hand,
			R_shoulder,
			R_hand2,
			L_shoulde,
			L_hand2
		};


		void __fastcall hookCreateMove(PVOID self, int edx, int seqnr, float time_, bool active, bool & bSendPacket) {
			VMTManager& hook = VMTManager::GetHook(pClient);
			hook.GetMethod<void(__thiscall*)(PVOID, int, float, bool)>(21)(self, seqnr, time_, active);

			static Vector vOldPosition = Vector();
			static int iLastWeaponID;

			IClientEntity* pLocalEntity = Engine::GetLocalPlayer();
			if (!pLocalEntity)
				return;

			if (pLocalEntity->IsDormant())
				return;

			CUserCmd * Cmd = pInput->GetUserCmd(0, seqnr);
			if (!Cmd)
				return;

			CVerifiedUserCmd* pVerifiedCmd = &(*(CVerifiedUserCmd**)((DWORD)pInput + 0xF0))[seqnr % 150];
			if (!pVerifiedCmd)
				return;

			// bhop //
			if (pConfig->bhop_enabled) {
				static bool pLast = false;
				static bool pFake = false;

				if (!pLast && pFake) {
					pFake = false;
					Cmd->buttons |= IN_JUMP;
				}
				else if (Cmd->buttons & IN_JUMP) {
					if (pLocalEntity->GetFlags() & FL_ONGROUND) {
						pLast = true;
						pFake = true;
					}
					else {
						Cmd->buttons &= ~IN_JUMP;
						pLast = false;
					}
				}
				else {
					pLast = false;
					pFake = false;
				}
			}

			// Load Config //
			if (GetAsyncKeyState(VK_INSERT)) {
				string csgo_path = string(pEngine->GetGameDirectory());
				pConfig->Load(csgo_path + "\\cfg\\mcore.cfg");
				pGameConsole->Clear();
				pCvar->ConsoleColorPrintf(Color(2, 153, 253), "[MYTHCORE] ");
				pCvar->ConsoleColorPrintf(Color::Green(), "CONFIG SUCCESSFULLY LOADED! \n");
			}

			static bool pConVarSpoofed = false;

			if (!pConVarSpoofed && Engine::IsAlive(pLocalEntity)) {
				ConVar* mat_postprocess_enable = Mythcore::CSGOSDK::pCvar->FindVar("mat_postprocess_enable");
				pConVar* mat_postprocess_spoofed = new pConVar(mat_postprocess_enable);
				mat_postprocess_spoofed->SetInt(0);
				pConVarSpoofed = true;
			}

			Vector eye = Engine::GetEyePosition(pLocalEntity);

			CBaseCombatWeapon * pWeapon = Engine::GetBaseCombatWeapon(pLocalEntity);

			Vector qMove, qRealView(Cmd->viewangles), vMove(Cmd->forwardmove, Cmd->sidemove, Cmd->upmove);

			bool bBulletTime = false;

			if (pWeapon != nullptr && Engine::IsAlive(pLocalEntity)) {
				int iWeaponID = pWeapon->GetWeaponID();
				bool bIsWeaponNonAim = Engine::IsWeaponNonAim(iWeaponID);

				static int iLastCfgWeaponId = 0;

				if (pConfig->set_wpn_cfg && !bIsWeaponNonAim) {
					if (iLastCfgWeaponId != iWeaponID) {
						iLastCfgWeaponId = iWeaponID;

						pConfig->OnWeaponChanged(iWeaponID);
						//Gui.OnWeaponChange(iWeaponID);
					}
				}

				//AIMBAT NORECOIL ETC
				if (!bIsWeaponNonAim) {

					bool bTargetFounded = false;

					float flServerTime = (float)(pLocalEntity->GetTickBase() * pGlobals->interval_per_tick); // offsets.m_nTickBase
					static DWORD m_flNextPrimaryAttack = 0;
					if (!m_flNextPrimaryAttack)
						m_flNextPrimaryAttack = pNetworkedVariables->GetNetvar("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
					float flNextPrimaryAttack = *(float*)((DWORD)Engine::GetBaseCombatWeapon(pLocalEntity) + m_flNextPrimaryAttack); //offsets.m_flNextPrimaryAttack


					//ConColorMsg(Color::Red(), "S:%f | NEXT:%f\n", flServerTime, flNextPrimaryAttack);
					bBulletTime = true;

					if (flNextPrimaryAttack > flServerTime)
						bBulletTime = false;

					//if (bBulletTime && Engine::IsWeaponSniper(iWeaponID) && !pWeapon->IsZoomed())
					//	bBulletTime = false;

					//if (bBulletTime && pConfig->aa_fakedown && bSendPacket)
					//	bBulletTime = false;

					//Utils::DebugMSG("WEPID = %d; flServer = %f; flNextPrim = %f; IsZoomed = %d", iWeaponID, flServerTime, flNextPrimaryAttack, pWeapon->IsZoomed());

					if (pConfig->aim_enabled) {
						float flSmallestDist = 9999999.f;
						Vector Target(0, 0, 0);
						for (int i = 1; i < 64; i++) {
							IClientEntity* pEntity = pClientEntList->GetClientEntity(i);
							if (pEntity == NULL) continue;

							if (pEntity->IsDormant()) continue;

							if (!Engine::IsAlive(pEntity)) continue;

							if (pEntity->Index() == pLocalEntity->Index()) continue;

							if (pEntity->GetTeamNum() == pLocalEntity->GetTeamNum())
								continue;

							bool bCanHit = false;
							Vector vecTemp = IsHittable(pLocalEntity, pEntity, eye, pConfig->aim_spot, bCanHit);

							if (bCanHit) {
								float flDist = VectorDistance(eye, vecTemp);

								Vector view = qRealView + (Engine::GetPunchAngles(pLocalEntity) * 2.f);

								float flFov = Math::CalculateFov(view, eye, vecTemp);
								if (flDist < flSmallestDist && flFov <= pConfig->aim_fov) {
									Target = vecTemp;
									flSmallestDist = flDist;
									bTargetFounded = true;
								}
							}
						}

						//ConColorMsg(Color::Green(), "XYZ:%f %f %f\n", Target.X, Target.Y, Target.Z);

						if (bTargetFounded && Target.Length() != 0) {
							Vector vAimAngles;

							Math::CalculateAngles(Engine::GetEyePosition(pLocalEntity), Target, vAimAngles);

							//CAN BE HERE
							int iAmmo = Engine::GetWeaponAmmo(pWeapon);

							if (iWeaponID != WEAPON_AWP  && iWeaponID != WEAPON_SCOUT)
								vAimAngles -= Engine::GetPunchAngles(pLocalEntity) * 2.f;

							if (bBulletTime && Cmd->buttons & IN_ATTACK && iAmmo != 0) {
								if (pConfig->aim_psilent) {
									bSendPacket = false;
									gLocalPlayerInfo.iChokedcommands++;
								}

								Cmd->viewangles.X = vAimAngles.X;
								Cmd->viewangles.Y = vAimAngles.Y;
							}
						}
					}
				}
			}

			//remove lags
			if (bSendPacket)
				gLocalPlayerInfo.iChokedcommands = 0;

			if (gLocalPlayerInfo.iChokedcommands >= 10 && !bSendPacket) {
				bSendPacket = true;
				gLocalPlayerInfo.iChokedcommands = 0;
			}

			ClampAngles(Cmd->viewangles);
			NormalizeAngles(Cmd->viewangles);
			AntiUntrustedYaw(Cmd->viewangles);
			Cmd->viewangles.Z = 0.f;

			if ( !pConfig->aim_psilent && pConfig->aim_enabled && bSendPacket /*&& !pConfig->aim_recoil_control*/)
				pEngine->SetViewAngles(Cmd->viewangles);

			pVerifiedCmd->m_cmd = *Cmd;
			pVerifiedCmd->m_crc = Cmd->GetChecksum();
		}
	}
}