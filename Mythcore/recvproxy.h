#pragma once

namespace Mythcore
{
	class RecvTable;
	class RecvProp;

	typedef enum
	{
		DPT_Int = 0,
		DPT_Float,
		DPT_Vector,
		DPT_VectorXY, // Only encodes the XY of a vector, ignores Z
		DPT_String,
		DPT_Array,	// An array of the base types (can't be of datatables).
		DPT_DataTable,
		DPT_NUMSendPropTypes

	} SendPropType;
	class CRecvProxyData;
	class RecvProp;

	class CRecvProxyData;

	typedef void(*DataTableRecvVarProxyFn)(const RecvProp *pProp, void **pOut, void *pData, int objectID);
	typedef void(*ArrayLengthRecvProxyFn)(void *pStruct, int objectID, int currentArrayLength);
	typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

	class RecvProp
	{
		// This info comes from the receive data table.
	public:
		RecvProp();

		void					InitArray(int nElements, int elementStride);

		int						GetNumElements() const;
		void					SetNumElements(int nElements);

		int						GetElementStride() const;
		void					SetElementStride(int stride);

		int						GetFlags() const;

		const char*				GetName() { return m_pVarName; }
		SendPropType			GetType() { return m_RecvType; }

		RecvTable*				GetDataTable() { return m_pDataTable; };
		void					SetDataTable(RecvTable *pTable);

		RecvVarProxyFn			GetProxyFn() const { return m_ProxyFn; }
		void					SetProxyFn(RecvVarProxyFn fn)
		{
			m_ProxyFn = fn;
		}

		DataTableRecvVarProxyFn	GetDataTableProxyFn() const;
		void					SetDataTableProxyFn(DataTableRecvVarProxyFn fn);

		int						GetOffset() { return m_Offset; }
		void					SetOffset(int o);

		// Arrays only.
		RecvProp*				GetArrayProp() const;
		void					SetArrayProp(RecvProp *pProp);

		// Arrays only.
		void					SetArrayLengthProxy(ArrayLengthRecvProxyFn proxy);
		ArrayLengthRecvProxyFn	GetArrayLengthProxy() const;

		bool					IsInsideArray() const;
		void					SetInsideArray();

		// Some property types bind more data to the prop in here.
		const void*			GetExtraData() const;
		void				SetExtraData(const void *pData);

		// If it's one of the numbered "000", "001", etc properties in an array, then
		// these can be used to get its array property name for debugging.
		const char*			GetParentArrayPropName();
		void				SetParentArrayPropName(const char *pArrayPropName);

	public:

		const char              *m_pVarName;
		SendPropType			m_RecvType;
		int						m_Flags;
		int						m_StringBufferSize;

		bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.

		// Extra data that certain special property types bind to the property here.
		const void *m_pExtraData;

		// If this is an array (DPT_Array).
		RecvProp				*m_pArrayProp;
		ArrayLengthRecvProxyFn	m_ArrayLengthProxy;

		RecvVarProxyFn			m_ProxyFn;
		DataTableRecvVarProxyFn	m_DataTableProxyFn;	// For RDT_DataTable.

		RecvTable				*m_pDataTable;		// For RDT_DataTable.
		int						m_Offset;

		int						m_ElementStride;
		int						m_nElements;

		// If it's one of the numbered "000", "001", etc properties in an array, then
		// these can be used to get its array property name for debugging.
		const char				*m_pParentArrayPropName;
	};


	class RecvTable
	{
	public:

		typedef RecvProp	PropType;

		RecvTable();
		RecvTable(RecvProp *pProps, int nProps, const char *pNetTableName);
		~RecvTable();

		void		Construct(RecvProp *pProps, int nProps, const char *pNetTableName);

		int			GetNumProps() { return m_nProps; }
		RecvProp*	GetPropPtr(int i){ return &m_pProps[i]; }

		const char*	GetName() { return m_pNetTableName; }

		// Used by the engine while initializing array props.
		void		SetInitialized(bool bInitialized);
		bool		IsInitialized() const;

		// Used by the engine.
		void		SetInMainList(bool bInList);
		bool		IsInMainList() const;


	public:

		// Properties described in a table.
		RecvProp		*m_pProps;
		int				m_nProps;

		// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
		// will have their own decoders that include props for all their children).
		void	*m_pDecoder;

		const char		*m_pNetTableName;	// The name matched between client and server.


	private:

		bool			m_bInitialized;
		bool			m_bInMainList;
	};

	class DVariant
	{
	public:
		DVariant()				{ m_Type = DPT_Float; }
		DVariant(float val)		{ m_Type = DPT_Float; m_Float = val; }

		const char *ToString()
		{
			static char text[128];



			return text;
		}

		union
		{
			float	m_Float;
			long	m_Int;
			char	*m_pString;
			void	*m_pData;	// For DataTables.
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
			float	m_Vector[4];
#else
			float	m_Vector[3];
#endif
			__int64	m_Int64;
		};
		SendPropType	m_Type;
	};


	class CRecvProxyData
	{
	public:
		const RecvProp	*m_pRecvProp;		// The property it's receiving.

		DVariant		m_Value;			// The value given to you to store.

		int				m_iElement;			// Which array element you're getting.

		int				m_ObjectID;			// The object being referred to.
	};

}