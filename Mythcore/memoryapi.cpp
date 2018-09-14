#include "SDK.h"

namespace Mythcore
{
	namespace MemoryAPI
	{
		DWORD GetModule(PCHAR moduleName, bool Size)
		{
			HANDLE hSnap;
			MODULEENTRY32 xModule;

			hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(GetCurrentProcess()));
			xModule.dwSize = sizeof(MODULEENTRY32);

			if (Module32First(hSnap, &xModule)) {
				while (Module32Next(hSnap, &xModule)) {
					if (!strncmp((PCHAR)xModule.szModule, moduleName, 8)) {
						CloseHandle(hSnap);
						if (Size)
							return(DWORD)xModule.modBaseSize;
						else
							return *(PDWORD)xModule.modBaseAddr;
					}
				}
			}

			CloseHandle(hSnap);
			return 0;
		}

		DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE * bMask, char * szMask)
		{
			for (DWORD i = 0; i < dwLen; i++)
			{
				if (DataCompare((BYTE *)(dwAddress + i), bMask, szMask))
					return (DWORD)(dwAddress + i);
			}

			return 0;
		}

		DWORD FindPattern2(PCHAR pattern, PCHAR mask, DWORD start, DWORD end, DWORD offset)
		{
			int patternLength = strlen(mask);
			bool found = false;

			for (DWORD i = start; i < end - patternLength; i++)
			{
				found = true;
				for (int idx = 0; idx < patternLength; idx++)
				{
					if (mask[idx] == 'x' && pattern[idx] != *(PCHAR)(i + idx))
					{
						found = false;
						break;
					}
				}
				if (found)
				{
					return i + offset;
				}
			}

			return NULL;
		}

		bool DataCompare(const BYTE * pData, const BYTE * bMask, const char * szMask)
		{
			for (; *szMask; ++szMask, ++pData, ++bMask)
			{
				if (*szMask == 'x' && *pData != *bMask)
					return false;
			}

			return (*szMask) == 0;
		}



		DWORD dwFindPattern(DWORD dwAddress, DWORD dwLength, const char* szPattern)
		{
			const char* pat = szPattern;
			DWORD firstMatch = NULL;
			for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
			{
				if (!*pat) return firstMatch;
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
					if (!firstMatch) firstMatch = pCur;
					if (!pat[2]) return firstMatch;
					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
					else pat += 2;
				}
				else {
					pat = szPattern;
					firstMatch = 0;
				}
			}
			return NULL;
		}
		//===================================================================================
		HMODULE GetModuleHandleSafe(const char* pszModuleName)
		{
			HMODULE hmModuleHandle = NULL;

			do
			{
				hmModuleHandle = GetModuleHandle(pszModuleName);
				Sleep(1);
			} while (hmModuleHandle == NULL);

			return hmModuleHandle;
		}
		//===================================================================================
		void LogToFile(const char * pszMessage, ...)
		{


		}
		//===================================================================================
		DWORD GetClientSignature(char* chPattern)
		{
			static HMODULE hmModule = GetModuleHandleSafe("client_panorama.dll");
			static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
			static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
			return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
		}
		//===================================================================================
		DWORD GetEngineSignature(char* chPattern)
		{
			static HMODULE hmModule = GetModuleHandleSafe("engine.dll");
			static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
			static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
			return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
		}
		//===================================================================================
		void ErrorBox(char* error)
		{
			string s = error;
			int len;
			int slength = (int)s.length() + 1;
			len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
			wchar_t* buf = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
			wstring r(buf);
			delete[] buf;
			MessageBoxW(NULL, r.c_str(), 0, 0);
		}
	}
}