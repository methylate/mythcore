#define _CRT_SECURE_NO_WARNINGS
#include "SDK.h"
#include "pConVar.h"

pConVar::pConVar() {
}

pConVar::pConVar(const char* szCVar) {
	m_pOriginalCVar = Mythcore::CSGOSDK::pCvar->FindVar(szCVar);
	Spoof();
}

pConVar::pConVar(Mythcore::CSGOSDK::ConVar* pCvar) {
	m_pOriginalCVar = pCvar;
	Spoof();
}

pConVar::~pConVar() {
	if (IsSpoofed()) {
		DWORD dwOld;
		SetFlags(m_iOriginalFlags);
		SetString(m_szOriginalValue);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);
		strcpy((char*)m_pOriginalCVar->pszName, m_szOriginalName);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);
		Mythcore::CSGOSDK::pCvar->UnregisterConCommand(m_pDummyCVar);
		free(m_pDummyCVar);
		m_pDummyCVar = nullptr;
	}
}

bool pConVar::IsSpoofed() {
	return m_pDummyCVar != nullptr;
}

void pConVar::Spoof() {
	if (!IsSpoofed() && m_pOriginalCVar) {

		//Save old name value and flags so we can restore the cvar lates if needed
		m_iOriginalFlags = m_pOriginalCVar->nFlags;
		strcpy(m_szOriginalName, m_pOriginalCVar->pszName);
		strcpy(m_szOriginalValue, m_pOriginalCVar->pszDefaultValue);
		sprintf_s(m_szDummyName, 128, "d_%s", m_szOriginalName);

		//Create the dummy cvar
		m_pDummyCVar = (Mythcore::CSGOSDK::ConVar*)malloc(sizeof(Mythcore::CSGOSDK::ConVar));
		if (!m_pDummyCVar) return;
		memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(Mythcore::CSGOSDK::ConVar));
		m_pDummyCVar->pNext = nullptr;

		//Register it
		Mythcore::CSGOSDK::pCvar->RegisterConCommand(m_pDummyCVar);

		//Fix "write access violation" bullshit
		DWORD dwOld;
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);

		//Rename the cvar
		strcpy((char*)m_pOriginalCVar->pszName, m_szDummyName);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);
		SetFlags(FCVAR_NONE);
	}
}

void pConVar::SetFlags(int flags) {
	if (IsSpoofed()) {
		m_pOriginalCVar->nFlags = flags;
	}
}

int pConVar::GetFlags() {
	return m_pOriginalCVar->nFlags;
}

void pConVar::SetInt(int iValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(iValue);
	}
}

void pConVar::SetBool(bool bValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(bValue);
	}
}

void pConVar::SetFloat(float flValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(flValue);
	}
}

void pConVar::SetString(const char* szValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(szValue);
	}
}
