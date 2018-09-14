#include "SDK.h"

namespace Mythcore {

	namespace CSUtils {

		CreateInterfaceFn CaptureFactory(char *pszFactoryModule) {

			CreateInterfaceFn fn = NULL;

			while (fn == NULL) {

				HMODULE hFactoryModule = GetModuleHandleA(pszFactoryModule);
				if (hFactoryModule) {
					fn = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(hFactoryModule, "CreateInterface"));
				}

				Sleep(10);
			}
			return fn;
		}

		PVOID CaptureInterface(CreateInterfaceFn fn, char *pszInterfaceName) {

			unsigned long *ptr = NULL;

			while (ptr == NULL) {
				ptr = reinterpret_cast<unsigned long*>(fn(pszInterfaceName, NULL));
				Sleep(10);
			}
			return ptr;
		}
	}
}