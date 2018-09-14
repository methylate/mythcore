#pragma once

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace Mythcore {

	namespace MemoryAPI {

		extern bool DataCompare(const BYTE * pData, const BYTE * bMask, const char * szMask);
		extern DWORD dwFindPattern(DWORD dwAddress, DWORD dwLength, const char* szPattern);
		extern DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE * bMask, char * szMask);
		extern HMODULE GetModuleHandleSafe(const char* pszModuleName);
		extern void LogToFile(const char * pszMessage, ...);
		extern DWORD GetClientSignature(char* chPattern);
		extern DWORD GetEngineSignature(char* chPattern);
		extern void ErrorBox(char* error);
		extern DWORD GetModule(PCHAR moduleName, bool Size = false);
		extern DWORD FindPattern2(PCHAR pattern, PCHAR mask, DWORD start, DWORD end, DWORD offset);
	}
}