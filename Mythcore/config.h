#pragma once 

namespace Mythcore {

	enum AIM_SPOTS {
		AIMSPOT_PELVIS,
		AIMSPOT_CHEST,
		AIMSPOT_HEAD,
		AIMSPOT_ANY,
		AIMSPOT_NEAREST
	};

	struct weapon_s {
	public:
		bool aim_enabled = false;
		bool aim_psilent = false;
		int aim_spot = 0;
		float aim_fov = 0.f;
	};

	struct KnifeInfo_s {
	public:
		int iViewIndex;
		int iWorldIndex;
		int iWeaponID;
	};

	class CConfig {
	public:

		CConfig() {
		}

		weapon_s Weapons[65];
		string mPath;

		bool aim_enabled = false;
		bool aim_psilent = false;
		int aim_spot = 0;
		float aim_fov = 0.f;
		bool bhop_enabled = false;
		bool set_wpn_cfg;

		//bool 
		//double 
		void OnWeaponChanged(int ID);
		void Load(string nPath);
	};

	extern CConfig * pConfig;

}