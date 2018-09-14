#include "SDK.h"

namespace Mythcore
{
	CConfig * pConfig = nullptr;

	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	std::vector<std::string> StringSplit(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	string WeaponIDToString(int i) {
		switch (i) {
		case 1: return "WEAPON_DEAGLE_";
		case 2: return "WEAPON_DUALS_";
		case 3: return "WEAPON_FIVE7_";
		case 4: return "WEAPON_GLOCK_";
		case 7: return "WEAPON_AK47_";
		case 8: return "WEAPON_AUG_";
		case 9: return "WEAPON_AWP_";
		case 10: return "WEAPON_FAMAS_";
		case 11: return "WEAPON_G3SG1_";
		case 13: return "WEAPON_GALIL_";
		case 14: return "WEAPON_M249_";
		case 16: return "WEAPON_M4A1_";
		case 17: return "WEAPON_MAC10_";
		case 19: return "WEAPON_P90_";
		case 24: return "WEAPON_UMP45_";
		case 25: return "WEAPON_XM1014_";
		case 26: return "WEAPON_BIZON_";
		case 27: return "WEAPON_MAG7_";
		case 28: return "WEAPON_NEGEV_";
		case 29: return "WEAPON_SAWEDOFF_";
		case 30: return "WEAPON_TEC9_";
		case 31: return "WEAPON_TASER_";
		case 32: return "WEAPON_P2000_";
		case 33: return "WEAPON_MP7_";
		case 34: return "WEAPON_MP9_";
		case 35: return "WEAPON_NOVA_";
		case 36: return "WEAPON_P250_";
		case 38: return "WEAPON_SCAR20_";
		case 39: return "WEAPON_SG553_";
		case 40: return "WEAPON_SCOUT_";
		case 42: return "WEAPON_KNIFE_T_";
		case 43: return "WEAPON_FLASH_";
		case 44: return "WEAPON_HE_";
		case 45: return "WEAPON_SMOKE_";
		case 46: return "WEAPON_MOLOTOV_";
		case 47: return "WEAPON_DECOY_";
		case 48: return "WEAPON_INC_";
		case 49: return "WEAPON_C4_";
		case 59: return "WEAPON_KNIFE_CT_";
		case 60: return "WEAPON_M4A1S_";
		case 61: return "WEAPON_USPS_";
		case 63: return "WEAPON_CZ75_";
		case 64: return "WEAPON_MAX_";

		default:
			return "";
		}
	}

	void CConfig::OnWeaponChanged(int ID) {
		if (ID >= 0 && ID < 65) {
			aim_enabled = Weapons[ID].aim_enabled;
			aim_psilent = Weapons[ID].aim_psilent;
			aim_fov = Weapons[ID].aim_fov;
			aim_spot = Weapons[ID].aim_spot;
		}
	}


	void CConfig::Load(string nPath) {

		if (nPath.length() != 0)
			mPath = nPath;
		// Console.WriteLine("Loading cfg from %s", nPath.c_str());
		vector<std::string> lines;
		std::ifstream file(mPath);
		std::string temp_str;

		while (std::getline(file, temp_str)) {
			lines.push_back(temp_str);
		}

		for (int i = 0; i < lines.size(); i++) {
			if (lines[i].find("=") != std::string::npos && lines[i].find("//") == std::string::npos && lines[i].length() > 0) {
				std::vector<std::string> temp = StringSplit(lines[i], '=');
				string param = temp[0];
				string value = temp[1];

				// config vars
				if (param == "aim_enabled") {
					aim_enabled = atoi(value.c_str()); continue;
				}
				if (param == "aim_psilent") {
					aim_psilent = atoi(value.c_str()); continue;
				}
				if (param == "aim_psilent") {
					aim_psilent = atoi(value.c_str()); continue;
				}
				if (param == "aim_fov") {
					aim_fov = atof(value.c_str()); continue;
				}
				if (param == "aim_spot") {
					aim_spot = atoi(value.c_str()); continue;
				}
				if (param == "set_wpn_cfg") {
					set_wpn_cfg = atoi(value.c_str()); continue;
				}
				if (param == "bhop_enabled") {
					bhop_enabled = atoi(value.c_str()); continue;
				}
			}
		}

		//Load weapons.
		for (int J = 0; J < 65; J++) {
			string weapon = WeaponIDToString(J);
			if (weapon != "") {
				for (int i = 0; i < lines.size(); i++) {
					if (lines[i].find("=") != std::string::npos && lines[i].find("//") == std::string::npos && lines[i].length() > 0) {
						std::vector<std::string> temp = StringSplit(lines[i], '=');
						string param = temp[0];
						string value = temp[1];


						if (param == (weapon + "aim_enabled")) {
							Weapons[J].aim_enabled = atoi(value.c_str()); continue;
						}
						if (param == (weapon + "aim_psilent")) {
							Weapons[J].aim_psilent = atoi(value.c_str()); continue;
						}
						if (param == (weapon + "aim_fov")) {
							Weapons[J].aim_fov = atof(value.c_str()); continue;
						}
						if (param == (weapon + "aim_spot")) {
							Weapons[J].aim_spot = atoi(value.c_str()); continue;
						}
					}
				}
			}
		}

		//Console.WriteLine("Loaded %d phrases", EpicPhrases.size());

		if (set_wpn_cfg) {
		}
	}
}