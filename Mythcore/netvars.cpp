#include "SDK.h"

namespace Mythcore
{
	CNetworkedVariableManager * pNetworkedVariables = nullptr;


	void CNetworkedVariableManager::Init(void)
	{
		m_tables.clear();
		m_savedproxy.clear();

		ClientClass *clientClass = pClient->GetAllClasses(); //g_InterfaceManager->Client()->GetOriginalMethod<GetAllClasses_t>( INDEX_GETALLCLASSES )( g_InterfaceManager->Client()->thisptr() );

		if (!clientClass)
		{
			ConColorMsg(Color::Red(),"ClientClass was not found");
			return;
		}

		while (clientClass)
		{
			RecvTable *recvTable = clientClass->m_pRecvTable;

			m_tables.push_back(recvTable);

			clientClass = clientClass->m_pNext;
		}
	}

	CNetworkedVariableManager::~CNetworkedVariableManager(void)
	{
		for (unsigned int i = 0; i < m_savedproxy.size(); i++)
		{
			RecvProp *recvProp = 0;
			GetPr0p(m_savedproxy[i].szTableName, m_savedproxy[i].szPropName, &recvProp);

			if (!recvProp)
				return;

			recvProp->SetProxyFn(m_savedproxy[i].SavedProxy);
		}
	}

	// calls GetProp wrapper to get the absolute offset of the prop
	int CNetworkedVariableManager::GetNetvar(const char *tableName, const char *propName)
	{
		
		int offset = GetPr0p(tableName, propName);

		if (!offset)
		{
			// Utils::DebugMSG("Failed to find offset for prop: %s from table: %s", propName, tableName);
			// ConColorMsg(Color::Red(), "Failed to find offset for prop: %s from table: %s", propName, tableName);
			MessageBoxA(0, "GetOffset failed", "Error", MB_OK);
			return 0;
		}

		return offset;
	}


	// calls GetProp wrapper to get prop and sets the proxy of the prop
	bool CNetworkedVariableManager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn function)
	{
		RecvProp *recvProp = 0;
		GetPr0p(tableName, propName, &recvProp);

		if (!recvProp)
		{
			MessageBoxA(0, "HookProp failed", "Error", MB_OK);
			return false;
		}

		//kolonote:
		//make a list of hooked proxies, then when we eject dll we dont have to worry about proxies that point to a pointer where the pointee doesnt exist
		Oldproxy_t oldproxyinfo;

		strcpy_s(oldproxyinfo.szTableName, tableName);
		strcpy_s(oldproxyinfo.szPropName, propName);

		oldproxyinfo.SavedProxy = recvProp->GetProxyFn();

		m_savedproxy.push_back(oldproxyinfo);

		//kolonote:
		//now we replace without worries
		recvProp->SetProxyFn(function);

		return true;
	}


	// wrapper so we can use recursion without too much performance loss
	int CNetworkedVariableManager::GetPr0p(const char *tableName, const char *propName, RecvProp **prop)
	{
		RecvTable *recvTable = GetTable(tableName);

		if (!recvTable)
		{
			//printf("Failed to find table: %s", tableName);
			return 0;
		}


		int offset = GetPr0p(recvTable, propName, prop);

		if (!offset)
		{
			//printf("Failed to find prop: %s from table: %s", propName, tableName);
			return 0;
		}


		return offset;
	}


	// uses recursion to return a the relative offset to the given prop and sets the prop param
	int CNetworkedVariableManager::GetPr0p(RecvTable *recvTable, const char *propName, RecvProp **prop)
	{
		int extraOffset = 0;

		for (int i = 0; i < recvTable->m_nProps; ++i)
		{
			RecvProp *recvProp = &recvTable->m_pProps[i];


			RecvTable *child = recvProp->m_pDataTable;

			if (child
				&& (child->m_nProps > 0))
			{
				int tmp = GetPr0p(child, propName, prop);

				if (tmp)
				{
					extraOffset += (recvProp->m_Offset + tmp);
				}
			}


			if (_stricmp(recvProp->m_pVarName, propName))
			{
				continue;
			}


			if (prop)
			{
				*prop = recvProp;
			}

			return (recvProp->m_Offset + extraOffset);
		}

		return extraOffset;
	}


	RecvTable *CNetworkedVariableManager::GetTable(const char *tableName)
	{
		if (m_tables.empty())
		{
			printf("Failed to find table: %s (m_tables is empty)", tableName);

			return 0;
		}


		for each (RecvTable *table in m_tables)
		{
			if (!table)
			{
				continue;
			}


			if (_stricmp(table->m_pNetTableName, tableName) == 0)
			{
				return table;
			}
		}

		return 0;
	}
}