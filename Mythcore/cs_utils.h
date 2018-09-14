namespace Mythcore {

	namespace CSUtils {

		typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
		extern CreateInterfaceFn CaptureFactory(char *pszFactoryModule);
		extern PVOID CaptureInterface(CreateInterfaceFn fn, char *pszInterfaceName);
	}
}