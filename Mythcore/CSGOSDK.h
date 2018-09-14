
namespace Mythcore
{
	using namespace Mythcore::Math;
	using namespace Mythcore::CRC32Checksum;

	namespace CSGOSDK
	{

		struct model_t;

#define	MASK_ALL		(0xFFFFFFFF)
#define FCVAR_NONE			  0 // ConVar flags
#define	FL_ONGROUND		(1 << 0)
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_ATTACK3		(1 << 25)
#define M_PI_F 3.141592653589793f

#define DEG2RAD( a ) ( ( (a) * M_PI_F ) / 180.0F )
#define RAD2DEG( a ) ( ( (a) * 180.0f ) / M_PI )

		enum MoveType_t
		{
			MOVETYPE_NONE = 0,	// never moves
			MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
			MOVETYPE_WALK,				// Player only - moving on the ground
			MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
			MOVETYPE_FLY,				// No gravity, but still collides with stuff
			MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
			MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
			MOVETYPE_PUSH,				// no clip to world, push and crush
			MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
			MOVETYPE_LADDER,			// Used by players only when going onto a ladder
			MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
			MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

			// should always be defined as the last item in the list
			MOVETYPE_LAST = MOVETYPE_CUSTOM,

			MOVETYPE_MAX_BITS = 4
		};


		enum ClientFrameStage_t
		{
			FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
			FRAME_START,

			// A network packet is being recieved
			FRAME_NET_UPDATE_START,
			// Data has been received and we're going to start calling PostDataUpdate
			FRAME_NET_UPDATE_POSTDATAUPDATE_START,
			// Data has been received and we've called PostDataUpdate on all data recipients
			FRAME_NET_UPDATE_POSTDATAUPDATE_END,
			// We've received all packets, we can now do interpolation, prediction, etc..
			FRAME_NET_UPDATE_END,

			// We're about to start rendering the scene
			FRAME_RENDER_START,
			// We've finished rendering the scene.
			FRAME_RENDER_END
		};

		enum ItemSchemaIndex_e
		{
			ITEM_NONE = 0,
			WEAPON_DEAGLE = 1,
			WEAPON_DUALS = 2,
			WEAPON_FIVE7 = 3,
			WEAPON_GLOCK = 4,
			WEAPON_AK47 = 7,
			WEAPON_AUG = 8,
			WEAPON_AWP = 9,
			WEAPON_FAMAS = 10,
			WEAPON_G3SG1 = 11,
			WEAPON_GALIL = 13,
			WEAPON_M249 = 14,
			WEAPON_M4A1 = 16,
			WEAPON_MAC10 = 17,
			WEAPON_P90 = 19,
			WEAPON_UMP45 = 24,
			WEAPON_XM1014 = 25,
			WEAPON_BIZON = 26,
			WEAPON_MAG7 = 27,
			WEAPON_NEGEV = 28,
			WEAPON_SAWEDOFF = 29,
			WEAPON_TEC9 = 30,
			WEAPON_TASER = 31,
			WEAPON_P2000 = 32,
			WEAPON_MP7 = 33,
			WEAPON_MP9 = 34,
			WEAPON_NOVA = 35,
			WEAPON_P250 = 36,
			WEAPON_SCAR20 = 38,
			WEAPON_SG553 = 39,
			WEAPON_SCOUT = 40,
			WEAPON_KNIFE_T = 42,
			WEAPON_FLASH = 43,
			WEAPON_HE = 44,
			WEAPON_SMOKE = 45,
			WEAPON_MOLOTOV = 46,
			WEAPON_DECOY = 47,
			WEAPON_INC = 48,
			WEAPON_C4 = 49,
			WEAPON_KNIFE_CT = 59,
			WEAPON_M4A1S = 60,
			WEAPON_USPS = 61,
			WEAPON_CZ75 = 63,
			WEAPON_MAX = 64,
			WEAPON_KNIFE_BAYONET = 500,
			WEAPON_KNIFE_FLIP = 505,
			WEAPON_KNIFE_GUT = 506,
			WEAPON_KNIFE_KARAMBIT = 507,
			WEAPON_KNIFE_M9BAYONET = 508,
			WEAPON_KNIFE_HUNTSMAN = 509,
			WEAPON_KNIFE_FALCHION = 512,
			WEAPON_KNIFE_BUTTERFLY = 515,
		};

		class IBaseClientDLL;
		class IVEngineClient;
		class IPanel;
		class IClientEntityList;
		class ISurface;
		class IVModelInfo;
		class CGlobalVarsBase;
		class IEngineTrace;
		class CInput;
		class IMaterialSystem;
		class IVModelRender;
		class IGameMovement;
		class IPrediction;
		class IVEfx;
		class HFont;
		class IVPhysicsDebugOverlay;
		class IHandleEntity;
		class CBaseHandle;
		class IClientNetworkable;
		class IClientEntity;
		class IClientThinkable;
		class IClientUnknown;
		class IClientNetworkable;
		class SurfInfo;
		class IMaterial;
		class CSentence;
		class CAudioSource;
		class AudioState_t;
		class ISpatialQuery;
		class IMaterialSystem;
		class CPhysCollide;
		class IAchievementMgr;
		class INetChannelInfo;
		class ISPSharedMemory;
		class CGamestatsData;
		class KeyValues;
		class CSteamAPIContext;
		struct Frustum_t;
		typedef Vector QAngle;
		typedef void(*pfnDemoCustomDataCallback)(unsigned char *pData, size_t iSize);
		typedef struct InputContextHandle_t__ *InputContextHandle_t;

		//SOME STRUCTS//
		struct studiohdr_t;
		union mstudioanimvalue_t;
		struct mstudiohitboxset_t;
		struct mstudiobonecontroller_t;
		struct mstudiobbox_t;
		struct client_textmessage_t;
		struct Frustum_t;
		class AudioState_t;
		typedef float vec_t;
		struct virtualmodel_t;


		typedef void*	(*CreateClientClassFn)(int entnum, int serialNum);
		typedef void*	(*CreateEventFn)();

		template< typename Function > Function call_vfunc(PVOID Base, DWORD Index)
		{
			PDWORD* VTablePointer = (PDWORD*)Base;
			PDWORD VTableFunctionBase = *VTablePointer;
			DWORD dwAddress = VTableFunctionBase[Index];
			return (Function)(dwAddress);
		}

		enum FontDrawType_t
		{
			FONT_DRAW_DEFAULT = 0,
			FONT_DRAW_NONADDITIVE,
			FONT_DRAW_ADDITIVE,
			FONT_DRAW_TYPE_COUNT = 2,
		};

		enum EFontFlags
		{
			FONTFLAG_NONE,
			FONTFLAG_ITALIC = 0x001,
			FONTFLAG_UNDERLINE = 0x002,
			FONTFLAG_STRIKEOUT = 0x004,
			FONTFLAG_SYMBOL = 0x008,
			FONTFLAG_ANTIALIAS = 0x010,
			FONTFLAG_GAUSSIANBLUR = 0x020,
			FONTFLAG_ROTARY = 0x040,
			FONTFLAG_DROPSHADOW = 0x080,
			FONTFLAG_ADDITIVE = 0x100,
			FONTFLAG_OUTLINE = 0x200,
			FONTFLAG_CUSTOM = 0x400,
			FONTFLAG_BITMAP = 0x800,
		};

		struct AppSystemInfo_t
		{
			const char* m_pModuleName;
			const char* m_pInterfaceName;
		};

		enum InitReturnVal_t
		{
			INIT_FAILED = 0,
			INIT_OK,
			INIT_LAST_VAL,
		};

		enum AppSystemTier_t
		{
			APP_SYSTEM_TIER0 = 0,
			APP_SYSTEM_TIER1,
			APP_SYSTEM_TIER2,
			APP_SYSTEM_TIER3,
			APP_SYSTEM_TIER_OTHER,
		};

		class Color
		{
		public:
			// constructors
			Color()
			{
				*((int *)this) = 0;
			}
			Color(int r, int g, int b)
			{
				SetColor(r, g, b, 255);
			}
			Color(int a, int r, int g, int b)
			{
				SetColor(r, g, b, a);
			}
			void SetColor(int r, int g, int b, int a = 0)
			{
				_color[0] = (unsigned char)r;
				_color[1] = (unsigned char)g;
				_color[2] = (unsigned char)b;
				_color[3] = (unsigned char)a;
			}

			void GetColor(int &r, int &g, int &b, int &a) const
			{
				r = _color[0];
				g = _color[1];
				b = _color[2];
				a = _color[3];
			}

			void SetRawColor(int color32)
			{
				*((int *)this) = color32;
			}

			int GetRawColor() const
			{
				return *((int *)this);
			}

			inline int r() const	{ return _color[0]; }
			inline int g() const	{ return _color[1]; }
			inline int b() const	{ return _color[2]; }
			inline int a() const	{ return _color[3]; }

			unsigned char &operator[](int index)
			{
				return _color[index];
			}

			const unsigned char &operator[](int index) const
			{
				return _color[index];
			}

			bool operator == (const Color &rhs) const
			{
				return (*((int *)this) == *((int *)&rhs));
			}

			bool operator != (const Color &rhs) const
			{
				return !(operator==(rhs));
			}

			Color &operator=(const Color &rhs)
			{
				SetRawColor(rhs.GetRawColor());
				return *this;
			}

			DWORD ToDirectX()
			{
				return D3DCOLOR_ARGB(a(), r(), g(), b());
			}


			static Color Red()		{ return Color(255, 0, 0); }
			static Color Green()	{ return Color(0, 255, 0); }
			static Color Blue()		{ return Color(0, 0, 255); }
			static Color Grey()		{ return Color(128, 128, 128); }
			static Color DarkGrey()	{ return Color(45, 45, 45); }
			static Color Black()	{ return Color(0, 0, 0); }
			static Color White()	{ return Color(255, 255, 255); }

		private:
			unsigned char _color[4];
		};

		class player_info_t
		{
		public:
			char unknown0[0x10];
			char name[32];
			char unknown2[0x200];

			int userID()
			{
				return *(PINT)((DWORD)this + (8 + 8 + 128));
			}
		};

		class CGlobalVarsBase
		{
		public:
			float    realtime;
			int      framecount;
			float    absoluteframetime;
			float    absoluteframestarttimestddev;
			float    curtime;
			float    frametime;
			int      maxClients;
			int      tickcount;
			float    interval_per_tick;
			float    interpolation_amount;
			int      simTicksThisFrame;
			int      network_protocol;
			void*    pSaveData;
			bool     m_bClient;
			int      nTimestampNetworkingBase;
			int      nTimestampRandomizeWindow;
		};
#pragma region NETVAR

		class ClientClass
		{
		public:
			ClientClass()
			{
			}

			const char* GetName()
			{
				return m_pNetworkName;
			}

		public:
			CreateClientClassFn		m_pCreateFn;
			CreateEventFn			m_pCreateEventFn;	// Only called for event objects.
			const char				*m_pNetworkName;
			RecvTable				*m_pRecvTable;
			ClientClass				*m_pNext;
			int						m_ClassID;	// Managed by the engine.
		};


#pragma endregion NETVAR

		class VMatrix
		{
		public:

			VMatrix();
			VMatrix(
				vec_t m00, vec_t m01, vec_t m02, vec_t m03,
				vec_t m10, vec_t m11, vec_t m12, vec_t m13,
				vec_t m20, vec_t m21, vec_t m22, vec_t m23,
				vec_t m30, vec_t m31, vec_t m32, vec_t m33
			);

			// Creates a matrix where the X axis = forward
			// the Y axis = left, and the Z axis = up
			VMatrix(const Vector& forward, const Vector& left, const Vector& up);

			// Construct from a 3x4 matrix
			VMatrix(const matrix3x4_t& matrix3x4);

			// Set the values in the matrix.
			void		Init(
				vec_t m00, vec_t m01, vec_t m02, vec_t m03,
				vec_t m10, vec_t m11, vec_t m12, vec_t m13,
				vec_t m20, vec_t m21, vec_t m22, vec_t m23,
				vec_t m30, vec_t m31, vec_t m32, vec_t m33
			);


			// Initialize from a 3x4
			void		Init(const matrix3x4_t& matrix3x4);

			// array access
			inline float* operator[](int i)
			{
				return m[i];
			}

			inline const float* operator[](int i) const
			{
				return m[i];
			}

			// Get a pointer to m[0][0]
			inline float *Base()
			{
				return &m[0][0];
			}

			inline const float *Base() const
			{
				return &m[0][0];
			}

			void		SetLeft(const Vector &vLeft);
			void		SetUp(const Vector &vUp);
			void		SetForward(const Vector &vForward);

			void		GetBasisVectors(Vector &vForward, Vector &vLeft, Vector &vUp) const;
			void		SetBasisVectors(const Vector &vForward, const Vector &vLeft, const Vector &vUp);

			// Get/set the translation.
			Vector &	GetTranslation(Vector &vTrans) const;
			void		SetTranslation(const Vector &vTrans);

			void		PreTranslate(const Vector &vTrans);
			void		PostTranslate(const Vector &vTrans);

			matrix3x4_t& As3x4();
			const matrix3x4_t& As3x4() const;
			void		CopyFrom3x4(const matrix3x4_t &m3x4);
			void		Set3x4(matrix3x4_t& matrix3x4) const;

			bool		operator==(const VMatrix& src) const;
			bool		operator!=(const VMatrix& src) const { return !(*this == src); }

			// Access the basis vectors.
			Vector		GetLeft() const;
			Vector		GetUp() const;
			Vector		GetForward() const;
			Vector		GetTranslation() const;


			// Matrix->vector operations.
		public:
			// Multiply by a 3D vector (same as operator*).
			void		V3Mul(const Vector &vIn, Vector &vOut) const;

			// Multiply by a 4D vector.
			//void		V4Mul( const Vector4D &vIn, Vector4D &vOut ) const;

			// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
			Vector		ApplyRotation(const Vector &vVec) const;

			// Multiply by a vector (divides by w, assumes input w is 1).
			Vector		operator*(const Vector &vVec) const;

			// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
			Vector		VMul3x3(const Vector &vVec) const;

			// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
			Vector		VMul3x3Transpose(const Vector &vVec) const;

			// Multiply by the upper 3 rows.
			Vector		VMul4x3(const Vector &vVec) const;

			// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
			Vector		VMul4x3Transpose(const Vector &vVec) const;


			// Matrix->plane operations.
			//public:
			// Transform the plane. The matrix can only contain translation and rotation.
			//void		TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

			// Just calls TransformPlane and returns the result.
			//VPlane		operator*(const VPlane &thePlane) const;

			// Matrix->matrix operations.
		public:

			VMatrix&	operator=(const VMatrix &mOther);

			// Multiply two matrices (out = this * vm).
			void		MatrixMul(const VMatrix &vm, VMatrix &out) const;

			// Add two matrices.
			const VMatrix& operator+=(const VMatrix &other);

			// Just calls MatrixMul and returns the result.	
			VMatrix		operator*(const VMatrix &mOther) const;

			// Add/Subtract two matrices.
			VMatrix		operator+(const VMatrix &other) const;
			VMatrix		operator-(const VMatrix &other) const;

			// Negation.
			VMatrix		operator-() const;

			// Return inverse matrix. Be careful because the results are undefined 
			// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
			VMatrix		operator~() const;

			// Matrix operations.
		public:
			// Set to identity.
			void		Identity();

			bool		IsIdentity() const;

			// Setup a matrix for origin and angles.
			void		SetupMatrixOrgAngles(const Vector &origin, const QAngle &vAngles);

			// General inverse. This may fail so check the return!
			bool		InverseGeneral(VMatrix &vInverse) const;

			// Does a fast inverse, assuming the matrix only contains translation and rotation.
			void		InverseTR(VMatrix &mRet) const;

			// Usually used for debug checks. Returns true if the upper 3x3 contains
			// unit vectors and they are all orthogonal.
			bool		IsRotationMatrix() const;

			// This calls the other InverseTR and returns the result.
			VMatrix		InverseTR() const;

			// Get the scale of the matrix's basis vectors.
			Vector		GetScale() const;

			// (Fast) multiply by a scaling matrix setup from vScale.
			VMatrix		Scale(const Vector &vScale);

			// Normalize the basis vectors.
			VMatrix		NormalizeBasisVectors() const;

			// Transpose.
			VMatrix		Transpose() const;

			// Transpose upper-left 3x3.
			VMatrix		Transpose3x3() const;

		public:
			// The matrix.
			vec_t		m[4][4];
		};

		class IBaseClientDLL
		{
		public:
			void CreateMove(int sequence_number, float frametime, bool active)
			{
				typedef void(__thiscall* oMove)(PVOID, int, float, bool);
				return call_vfunc< oMove >(this, 21)(this, sequence_number, frametime, active);
			}


			ClientClass * GetAllClasses()
			{
				typedef ClientClass*(__thiscall* xD)(PVOID);
				return call_vfunc< xD >(this, 8)(this);
			}
		};

		class IVEngineClient
		{
		public:
			public:
	virtual int                   GetIntersectingSurfaces(const model_t *model, const Vector &vCenter, const float radius, const bool bOnlyVisibleSurfaces, SurfInfo *pInfos, const int nMaxInfos) = 0;
	virtual Vector                GetLightForPoint(const Vector &pos, bool bClamp) = 0;
	virtual IMaterial*            TraceLineMaterialAndLighting(const Vector &start, const Vector &end, Vector &diffuseLightColor, Vector& baseColor) = 0;
	virtual const char*           ParseFile(const char *data, char *token, int maxlen) = 0;
	virtual bool                  CopyFile(const char *source, const char *destination) = 0;
	virtual void                  GetScreenSize(int& width, int& height) = 0;
	virtual void                  ServerCmd(const char *szCmdString, bool bReliable = true) = 0;
	virtual void                  ClientCmd(const char *szCmdString) = 0;
	virtual bool                  GetPlayerInfo(int ent_num, player_info_t *pinfo) = 0;
	virtual int                   GetPlayerForUserID(int userID) = 0;
	virtual client_textmessage_t* TextMessageGet(const char *pName) = 0; // 10
	virtual bool                  Con_IsVisible(void) = 0;
	virtual int                   GetLocalPlayer(void) = 0;
	virtual const model_t*        LoadModel(const char *pName, bool bProp = false) = 0;
	virtual float                 GetLastTimeStamp(void) = 0;
	virtual CSentence*            GetSentence(CAudioSource *pAudioSource) = 0; // 15
	virtual float                 GetSentenceLength(CAudioSource *pAudioSource) = 0;
	virtual bool                  IsStreaming(CAudioSource *pAudioSource) const = 0;
	virtual void                  GetViewAngles(QAngle& va) = 0;
	virtual void                  SetViewAngles(QAngle& va) = 0;
	virtual int                   GetMaxClients(void) = 0; // 20
	virtual   const char*         Key_LookupBinding(const char *pBinding) = 0;
	virtual const char*           Key_BindingForKey(int &code) = 0;
	virtual void                  Key_SetBinding(int, char const*) = 0;
	virtual void                  StartKeyTrapMode(void) = 0;
	virtual bool                  CheckDoneKeyTrapping(int &code) = 0;
	virtual bool                  IsInGame(void) = 0;
	virtual bool                  IsConnected(void) = 0;
	virtual bool                  IsDrawingLoadingImage(void) = 0;
	virtual void                  HideLoadingPlaque(void) = 0;
	virtual void                  Con_NPrintf(int pos, const char *fmt, ...) = 0; // 30
	virtual void                  Con_NXPrintf(const struct con_nprint_s *info, const char *fmt, ...) = 0;
	virtual int                   IsBoxVisible(const Vector& mins, const Vector& maxs) = 0;
	virtual int                   IsBoxInViewCluster(const Vector& mins, const Vector& maxs) = 0;
	virtual bool                  CullBox(const Vector& mins, const Vector& maxs) = 0;
	virtual void                  Sound_ExtraUpdate(void) = 0;
	virtual const char*           GetGameDirectory(void) = 0;
	virtual const VMatrix&        WorldToScreenMatrix() = 0;
	virtual const VMatrix&        WorldToViewMatrix() = 0;
	virtual int                   GameLumpVersion(int lumpId) const = 0;
	virtual int                   GameLumpSize(int lumpId) const = 0; // 40
	virtual bool                  LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
	virtual int                   LevelLeafCount() const = 0;
	virtual ISpatialQuery*        GetBSPTreeQuery() = 0;
	virtual void                  LinearToGamma(float* linear, float* gamma) = 0;
	virtual float                 LightStyleValue(int style) = 0; // 45
	virtual void                  ComputeDynamicLighting(const Vector& pt, const Vector* pNormal, Vector& color) = 0;
	virtual void                  GetAmbientLightColor(Vector& color) = 0;
	virtual int                   GetDXSupportLevel() = 0;
	virtual bool                  SupportsHDR() = 0;
	virtual void                  Mat_Stub(IMaterialSystem *pMatSys) = 0; // 50
	virtual void                  GetChapterName(char *pchBuff, int iMaxLength) = 0;
	virtual char const*           GetLevelName(void) = 0;
	virtual char const*           GetLevelNameShort(void) = 0;
	virtual char const*           GetMapGroupName(void) = 0;
	virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
	virtual void                  SetVoiceCasterID(unsigned int someint) = 0; // 56
	virtual void                  EngineStats_BeginFrame(void) = 0;
	virtual void                  EngineStats_EndFrame(void) = 0;
	virtual void                  FireEvents() = 0;
	virtual int                   GetLeavesArea(unsigned short *pLeaves, int nLeaves) = 0;
	virtual bool                  DoesBoxTouchAreaFrustum(const Vector &mins, const Vector &maxs, int iArea) = 0; // 60
	virtual int                   GetFrustumList(Frustum_t **pList, int listMax) = 0;
	virtual bool                  ShouldUseAreaFrustum(int i) = 0;
	virtual void                  SetAudioState(const AudioState_t& state) = 0;
	virtual int                   SentenceGroupPick(int groupIndex, char *name, int nameBufLen) = 0;
	virtual int                   SentenceGroupPickSequential(int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int                   SentenceIndexFromName(const char *pSentenceName) = 0;
	virtual const char*           SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int                   SentenceGroupIndexFromName(const char *pGroupName) = 0;
	virtual const char*           SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float                 SentenceLength(int sentenceIndex) = 0;
	virtual void                  ComputeLighting(const Vector& pt, const Vector* pNormal, bool bClamp, Vector& color, Vector *pBoxColors = nullptr) = 0;
	virtual void                  ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool                  IsOccluded(const Vector &vecAbsMins, const Vector &vecAbsMaxs) = 0; // 74
	virtual int                   GetOcclusionViewId(void) = 0;
	virtual void*                 SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void                  SaveFreeMemory(void *pSaveMem) = 0;
	virtual INetChannelInfo*      GetNetChannelInfo(void) = 0;
	virtual void                  DebugDrawPhysCollide(const CPhysCollide *pCollide, IMaterial *pMaterial, const matrix3x4_t& transform, const Color &color) = 0; //79
	virtual void                  CheckPoint(const char *pName) = 0; // 80
	virtual void                  DrawPortals() = 0;
	virtual bool                  IsPlayingDemo(void) = 0;
	virtual bool                  IsRecordingDemo(void) = 0;
	virtual bool                  IsPlayingTimeDemo(void) = 0;
	virtual int                   GetDemoRecordingTick(void) = 0;
	virtual int                   GetDemoPlaybackTick(void) = 0;
	virtual int                   GetDemoPlaybackStartTick(void) = 0;
	virtual float                 GetDemoPlaybackTimeScale(void) = 0;
	virtual int                   GetDemoPlaybackTotalTicks(void) = 0;
	virtual bool                  IsPaused(void) = 0; // 90
	virtual float                 GetTimescale(void) const = 0;
	virtual bool                  IsTakingScreenshot(void) = 0;
	virtual bool                  IsHLTV(void) = 0;
	virtual bool                  IsLevelMainMenuBackground(void) = 0;
	virtual void                  GetMainMenuBackgroundName(char *dest, int destlen) = 0;
	virtual void                  SetOcclusionParameters(const int /*OcclusionParams_t*/ &params) = 0; // 96
	virtual void                  GetUILanguage(char *dest, int destlen) = 0;
	virtual int                   IsSkyboxVisibleFromPoint(const Vector &vecPoint) = 0;
	virtual const char*           GetMapEntitiesString() = 0;
	virtual bool                  IsInEditMode(void) = 0; // 100
	virtual float                 GetScreenAspectRatio(int viewportWidth, int viewportHeight) = 0;
	virtual bool                  REMOVED_SteamRefreshLogin(const char *password, bool isSecure) = 0; // 100
	virtual bool                  REMOVED_SteamProcessCall(bool & finished) = 0;
	virtual unsigned int          GetEngineBuildNumber() = 0; // engines build
	virtual const char *          GetProductVersionString() = 0; // mods version number (steam.inf)
	virtual void                  GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
	virtual bool                  IsHammerRunning() const = 0;
	virtual void                  ExecuteClientCmd(const char *szCmdString) = 0; //108
	virtual bool                  MapHasHDRLighting(void) = 0;
	virtual bool                  MapHasLightMapAlphaData(void) = 0;
	virtual int                   GetAppID() = 0;
	virtual Vector                GetLightForPointFast(const Vector &pos, bool bClamp) = 0;
	virtual void                  ClientCmd_Unrestricted(char const*, int, bool);
	virtual void                  ClientCmd_Unrestricted(const char *szCmdString, bool bDelayed) = 0; // 114
	virtual void                  SetRestrictServerCommands(bool bRestrict) = 0;
	virtual void                  SetRestrictClientCommands(bool bRestrict) = 0;
	virtual void                  SetOverlayBindProxy(int iOverlayID, void *pBindProxy) = 0;
	virtual bool                  CopyFrameBufferToMaterial(const char *pMaterialName) = 0;
	virtual void                  ReadConfiguration(const int iController, const bool readDefault) = 0;
	virtual void                  SetAchievementMgr(IAchievementMgr *pAchievementMgr) = 0;
	virtual IAchievementMgr*      GetAchievementMgr() = 0;
	virtual bool                  MapLoadFailed(void) = 0;
	virtual void                  SetMapLoadFailed(bool bState) = 0;
	virtual bool                  IsLowViolence() = 0;
	virtual const char*           GetMostRecentSaveGame(void) = 0;
	virtual void                  SetMostRecentSaveGame(const char *lpszFilename) = 0;
	virtual void                  StartXboxExitingProcess() = 0;
	virtual bool                  IsSaveInProgress() = 0;
	virtual bool                  IsAutoSaveDangerousInProgress(void) = 0;
	virtual unsigned int          OnStorageDeviceAttached(int iController) = 0;
	virtual void                  OnStorageDeviceDetached(int iController) = 0;
	virtual char* const           GetSaveDirName(void) = 0;
	virtual void                  WriteScreenshot(const char *pFilename) = 0;
	virtual void                  ResetDemoInterpolation(void) = 0;
	virtual int                   GetActiveSplitScreenPlayerSlot() = 0;
	virtual int                   SetActiveSplitScreenPlayerSlot(int slot) = 0;
	virtual bool                  SetLocalPlayerIsResolvable(char const *pchContext, int nLine, bool bResolvable) = 0;
	virtual bool                  IsLocalPlayerResolvable() = 0;
	virtual int                   GetSplitScreenPlayer(int nSlot) = 0;
	virtual bool                  IsSplitScreenActive() = 0;
	virtual bool                  IsValidSplitScreenSlot(int nSlot) = 0;
	virtual int                   FirstValidSplitScreenSlot() = 0; // -1 == invalid
	virtual int                   NextValidSplitScreenSlot(int nPreviousSlot) = 0; // -1 == invalid
	virtual ISPSharedMemory*      GetSinglePlayerSharedMemorySpace(const char *szName, int ent_num = (1 << 11)) = 0;
	virtual void                  ComputeLightingCube(const Vector& pt, bool bClamp, Vector *pBoxColors) = 0;
	virtual void                  RegisterDemoCustomDataCallback(const char* szCallbackSaveID, pfnDemoCustomDataCallback pCallback) = 0;
	virtual void                  RecordDemoCustomData(pfnDemoCustomDataCallback pCallback, const void *pData, size_t iDataLength) = 0;
	virtual void                  SetPitchScale(float flPitchScale) = 0;
	virtual float                 GetPitchScale(void) = 0;
	virtual bool                  LoadFilmmaker() = 0;
	virtual void                  UnloadFilmmaker() = 0;
	virtual void                  SetLeafFlag(int nLeafIndex, int nFlagBits) = 0;
	virtual void                  RecalculateBSPLeafFlags(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomNew(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomChanged(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomSkyAbove(void) = 0;
	virtual float                 DSPGetCurrentDASRoomSkyPercent(void) = 0;
	virtual void                  SetMixGroupOfCurrentMixer(const char *szgroupname, const char *szparam, float val, int setMixerType) = 0;
	virtual int                   GetMixLayerIndex(const char *szmixlayername) = 0;
	virtual void                  SetMixLayerLevel(int index, float level) = 0;
	virtual int                   GetMixGroupIndex(char  const* groupname) = 0;
	virtual void                  SetMixLayerTriggerFactor(int i1, int i2, float fl) = 0;
	virtual void                  SetMixLayerTriggerFactor(char  const* char1, char  const* char2, float fl) = 0;
	virtual bool                  IsCreatingReslist() = 0;
	virtual bool                  IsCreatingXboxReslist() = 0;
	virtual void                  SetTimescale(float flTimescale) = 0;
	virtual void                  SetGamestatsData(CGamestatsData *pGamestatsData) = 0;
	virtual CGamestatsData*       GetGamestatsData() = 0;
	virtual void                  GetMouseDelta(int &dx, int &dy, bool b) = 0; // unknown
	virtual   const char*         Key_LookupBindingEx(const char *pBinding, int iUserId = -1, int iStartCount = 0, int iAllowJoystick = -1) = 0;
	virtual int                   Key_CodeForBinding(char  const*, int, int, int) = 0;
	virtual void                  UpdateDAndELights(void) = 0;
	virtual int                   GetBugSubmissionCount() const = 0;
	virtual void                  ClearBugSubmissionCount() = 0;
	virtual bool                  DoesLevelContainWater() const = 0;
	virtual float                 GetServerSimulationFrameTime() const = 0;
	virtual void                  SolidMoved(class IClientEntity *pSolidEnt, class ICollideable *pSolidCollide, const Vector* pPrevAbsOrigin, bool accurateBboxTriggerChecks) = 0;
	virtual void                  TriggerMoved(class IClientEntity *pTriggerEnt, bool accurateBboxTriggerChecks) = 0;
	virtual void                  ComputeLeavesConnected(const Vector &vecOrigin, int nCount, const int *pLeafIndices, bool *pIsConnected) = 0;
	virtual bool                  IsInCommentaryMode(void) = 0;
	virtual void                  SetBlurFade(float amount) = 0;
	virtual bool                  IsTransitioningToLoad() = 0;
	virtual void                  SearchPathsChangedAfterInstall() = 0;
	virtual void                  ConfigureSystemLevel(int nCPULevel, int nGPULevel) = 0;
	virtual void                  SetConnectionPassword(char const *pchCurrentPW) = 0;
	virtual CSteamAPIContext*     GetSteamAPIContext() = 0;
	virtual void                  SubmitStatRecord(char const *szMapName, unsigned int uiBlobVersion, unsigned int uiBlobSize, const void *pvBlob) = 0;
	virtual void                  ServerCmdKeyValues(KeyValues *pKeyValues) = 0; // 203
	virtual void                  SpherePaintSurface(const model_t* model, const Vector& location, unsigned char chr, float fl1, float fl2) = 0;
	virtual bool                  HasPaintmap(void) = 0;
	virtual void                  EnablePaintmapRender() = 0;
	//virtual void                TracePaintSurface( const model_t *model, const Vector& position, float radius, CUtlVector<Color>& surfColors ) = 0;
	virtual void                  SphereTracePaintSurface(const model_t* model, const Vector& position, const Vector &vec2, float radius, /*CUtlVector<unsigned char, CUtlMemory<unsigned char, int>>*/ int& utilVecShit) = 0;
	virtual void                  RemoveAllPaint() = 0;
	virtual void                  PaintAllSurfaces(unsigned char uchr) = 0;
	virtual void                  RemovePaint(const model_t* model) = 0;
	virtual bool                  IsActiveApp() = 0;
	virtual bool                  IsClientLocalToActiveServer() = 0;
	virtual void                  TickProgressBar() = 0;
	virtual InputContextHandle_t  GetInputContext(int /*EngineInputContextId_t*/ id) = 0;
	virtual void                  GetStartupImage(char* filename, int size) = 0;
	virtual bool                  IsUsingLocalNetworkBackdoor(void) = 0;
	virtual void                  SaveGame(const char*, bool, char*, int, char*, int) = 0;
	virtual void                  GetGenericMemoryStats(/* GenericMemoryStat_t */ void **) = 0;
	virtual bool                  GameHasShutdownAndFlushedMemory(void) = 0;
	virtual int                   GetLastAcknowledgedCommand(void) = 0;
	virtual void                  FinishContainerWrites(int i) = 0;
	virtual void                  FinishAsyncSave(void) = 0;
	virtual int                   GetServerTick(void) = 0;
	virtual const char*           GetModDirectory(void) = 0;
	virtual bool                  AudioLanguageChanged(void) = 0;
	virtual bool                  IsAutoSaveInProgress(void) = 0;
	virtual void                  StartLoadingScreenForCommand(const char* command) = 0;
	virtual void                  StartLoadingScreenForKeyValues(KeyValues* values) = 0;
	virtual void                  SOSSetOpvarFloat(const char*, float) = 0;
	virtual void                  SOSGetOpvarFloat(const char*, float &) = 0;
	virtual bool                  IsSubscribedMap(const char*, bool) = 0;
	virtual bool                  IsFeaturedMap(const char*, bool) = 0;
	virtual void                  GetDemoPlaybackParameters(void) = 0;
	virtual int                   GetClientVersion(void) = 0;
	virtual bool                  IsDemoSkipping(void) = 0;
	virtual void                  SetDemoImportantEventData(const KeyValues* values) = 0;
	virtual void                  ClearEvents(void) = 0;
	virtual int                   GetSafeZoneXMin(void) = 0;
	virtual bool                  IsVoiceRecording(void) = 0;
	virtual void                  ForceVoiceRecordOn(void) = 0;
	virtual bool                  IsReplay(void) = 0;
		};

		class ISurface
		{
		public:
			void		DrawSetColor(int r, int g, int b, int a);
			void		DrawSetColor(Color col);
			void		DrawFilledRect(int x0, int y0, int x1, int y1);
			void		DrawOutlinedRect(int x0, int y0, int x1, int y1);
			void		DrawLine(int x0, int y0, int x1, int y1);
			void		DrawPolyLine(int *px, int *py, int numPoints);
			void		DrawSetTextFont(HFont font);
			void		DrawSetTextColor(int r, int g, int b, int a);
			void		DrawSetTextColor(Color col);
			void		DrawSetTextPos(int x, int y);
			void		DrawPrintText(const wchar_t *text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT);
			void		DrawSetTextureRGBA(int id, const unsigned char *rgba, int wide, int tall);
			void		DrawSetTexture(int id);
			int			CreateNewTextureID(bool procedural = false);
			HFont		Create_Font();
			bool		SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0);
			void		GetTextSize(HFont font, const wchar_t *text, int &wide, int &tall);
			void		DrawOutlinedCircle(int x, int y, int radius, int segments);
			// void		DrawTexturedPolygon(int n, Vertex_t *pVertice, bool bClipVertices = true);
		};

		typedef unsigned short ClientShadowHandle_t;
		class IClientRenderable
		{
		public:
			virtual IClientUnknown*	GetIClientUnknown() = 0;

			// Data accessors
			virtual Vector const&			GetRenderOrigin(void) = 0;
			virtual Vector const&			GetRenderAngles(void) = 0;
			virtual bool					ShouldDraw(void) = 0;
			virtual int					    GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
			virtual void					Unused(void) const {}

			virtual ClientShadowHandle_t	GetShadowHandle() const = 0;

			// Used by the leaf system to store its render handle.
			virtual unsigned short	RenderHandle() = 0;

			// Render baby!
			virtual const void*			GetModel() const = 0;
			virtual int						DrawModel(int flags) = 0;
			virtual int						GetBody() = 0;
			virtual void					ComputeFxBlend() = 0;

			bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
			{
				typedef bool(__thiscall* oSetupBones)(PVOID, matrix3x4_t*, int, int, float);
				return call_vfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
			}
		};

		class IClientNetworkable
		{
		public:
			virtual IClientUnknown*	GetIClientUnknown() = 0;
			virtual void			Release() = 0;
			virtual ClientClass*			GetClientClass() = 0;// FOR NETVARS FIND YOURSELF ClientClass* stuffs
			virtual void			NotifyShouldTransmit( /* ShouldTransmitState_t state*/) = 0;
			virtual void			OnPreDataChanged( /*DataUpdateType_t updateType*/) = 0;
			virtual void			OnDataChanged( /*DataUpdateType_t updateType*/) = 0;
			virtual void			PreDataUpdate( /*DataUpdateType_t updateType*/) = 0;
			virtual void			PostDataUpdate( /*DataUpdateType_t updateType*/) = 0;
			virtual void			unknown();
			virtual bool			IsDormant(void) = 0;
			virtual int				Index(void) const = 0;
			virtual void			ReceiveMessage(int classID /*, bf_read &msg*/) = 0;
			virtual void*			GetDataTableBasePtr() = 0;
			virtual void			SetDestroyedOnRecreateEntities(void) = 0;
		};


		class IClientColidable
		{
		public:
			void WorldSpaceSurroundingBounds(Vector * a, Vector * b)
			{
				typedef void(__thiscall* fn)(PVOID, Vector*, Vector*);
				call_vfunc< fn>(this, 15)(this, a, b);
			}
		};

		class IClientUnknown
		{
		public:
			virtual void*		GetCollideable() = 0;
			virtual IClientNetworkable*	GetClientNetworkable() = 0;
			virtual IClientRenderable*	GetClientRenderable() = 0;
			virtual IClientEntity*		GetIClientEntity() = 0;
			virtual IClientEntity*		GetBaseEntity() = 0;
			virtual IClientThinkable*	GetClientThinkable() = 0;
		};

		class IClientThinkable
		{
		public:
			virtual IClientUnknown*		GetIClientUnknown() = 0;
			virtual void				ClientThink() = 0;
			virtual void*				GetThinkHandle() = 0;
			virtual void				SetThinkHandle(void* hThink) = 0;
			virtual void				Release() = 0;
		};


		class __declspec (novtable)IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
		{
		public:
			virtual void			Release(void) = 0;
			virtual void			blahblahpad(void) = 0;
			virtual Vector&	GetAbsOrigin(void) const = 0;//in broken place use GetOrigin Below
			virtual const Vector&	GetAbsAngles(void) const = 0;

			Vector GetOrigin()
			{
				return *reinterpret_cast< Vector* >((DWORD)this + (DWORD)0x134); //m_vecOrigin   
			}

			int GetTeamNum()
			{
				return *reinterpret_cast< int* >((DWORD)this + (DWORD)0xF0); // DT_BaseEntity -> m_iTeamNum:
			}

			int GetFlags()
			{
				return *reinterpret_cast< int* >((DWORD)this + (DWORD)0x100); // m_iFlags
			}

			unsigned char GetMoveType()
			{
				return *reinterpret_cast<unsigned char*>((DWORD)this + (DWORD)0x258); // m_bMoveType
			}

			int GetTickBase()
			{
				static DWORD offset = pNetworkedVariables->GetNetvar("DT_BasePlayer", "m_nTickBase");
				if (!offset)
					offset = pNetworkedVariables->GetNetvar("DT_BasePlayer", "m_nTickBase");
				return *reinterpret_cast<int*>((DWORD)this + offset);
			}


			int GetHitSet();

			int GetGlowIndex()
			{
				static DWORD offset = 0;
				if (!offset)
					offset = pNetworkedVariables->GetNetvar("DT_CSPlayer", "m_flFlashDuration");
				return *reinterpret_cast<int*>((DWORD)this + offset + 0x18); // flashduration + 0x18
			}

			IClientColidable* GetColidable2()//member of baseentity
			{
				return (IClientColidable*)((DWORD)this + 0x318);// change to netvar m_Collision
			}

			int GetHealth()
			{
				return *reinterpret_cast<int*>(reinterpret_cast<int>(this) + 0xFC); // DT_BasePlayer -> m_iHealth: ___________________ 0x000000FC
			}

			bool IsAlive()
			{
				char szLifeState = *(char*)((DWORD)this + 0x25B);
				return (szLifeState == 0);
			}

			IClientEntity* GetOwnerEntity();

		};

		class IClientEntityList
		{
		public:
			virtual void Function0() = 0;
			virtual void Function1() = 0;
			virtual void Function2() = 0;

			virtual IClientEntity*	GetClientEntity(int iIndex) = 0;
			virtual IClientEntity*	GetClientEntityFromHandle(HANDLE hHandle) = 0;
			virtual int				NumberOfEntities(bool bIncludeNonNetworkable) = 0;
			virtual int				GetHighestEntityIndex() = 0;
		};

		class IVPanel
		{
		public:
			const char* GetName(int iPanel);
		};

		class CBaseHandle
		{
			friend class CBaseEntityList;
#define MAX_EDICT_BITS  11                      // # of bits needed to represent max edicts
#define MAX_EDICTS (1 << MAX_EDICT_BITS)
#define NUM_ENT_ENTRY_BITS (MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES (1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK (NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX   0xFFFFFFFF



		public:

			CBaseHandle(){};

			void Init(int iEntry, int iSerialNumber);
			void Term();

			// Even if this returns true, Get() still can return return a non-null value.
			// This just tells if the handle has been initted with any values.
			bool IsValid() const;

			inline int CBaseHandle::GetEntryIndex() const
			{
				return m_Index & ENT_ENTRY_MASK;
			}

			int GetSerialNumber() const;

			int ToInt() const;
			bool operator !=(const CBaseHandle &other) const;
			bool operator ==(const CBaseHandle &other) const;
			bool operator ==(const IHandleEntity* pEnt) const;
			bool operator !=(const IHandleEntity* pEnt) const;
			bool operator <(const CBaseHandle &other) const;
			bool operator <(const IHandleEntity* pEnt) const;

			// Assign a value to the handle.
			const CBaseHandle& operator=(const IHandleEntity *pEntity);
			const CBaseHandle& Set(const IHandleEntity *pEntity);

			// Use this to dereference the handle.
			// Note: this is implemented in game code (ehandle.h)
			IHandleEntity* Get() const;


		protected:
			// The low NUM_SERIAL_BITS hold the index. If this value is less than MAX_EDICTS, then the entity is networkable.
			// The high NUM_SERIAL_NUM_BITS bits are the serial number.
			unsigned long	m_Index;
		};

		class CUserCmd
		{
		public:
			virtual ~CUserCmd();//0x00
			int		command_number;//0x04
			int		tick_count;//0x08
			Vector viewangles;//0x0C
			Vector	aimdirection;
			float	forwardmove;
			float	sidemove;
			float	upmove;
			int		buttons; //0x30
			BYTE    impulse; //0x35
			int		weaponselect;//0x36	
			int		weaponsubtype;//0x3A
			int		random_seed; //0x3E
			short	mousedx;//0x42		
			short	mousedy;//0x43		
			bool	hasbeenpredicted;
			Vector headangles;
			Vector	headoffset;

			CRC32_t GetChecksum(void) const
			{
				CRC32_t crc;

				CRC32_Init(&crc);
				CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
				CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
				CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
				CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
				CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
				CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
				CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
				CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
				CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
				CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
				CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
				CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
				CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
				CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));
				//CRC32_ProcessBuffer(&crc, &hasbeenpredicted, sizeof(hasbeenpredicted));
				//CRC32_ProcessBuffer(&crc, &headangles, sizeof(headangles));
				//CRC32_ProcessBuffer(&crc, &headoffset, sizeof(headoffset));
				CRC32_Final(&crc);

				return crc;
			}

			void Reset()
			{
				command_number = 0;
				tick_count = 0;
				viewangles.Reset();
				forwardmove = 0.0f;
				sidemove = 0.0f;
				upmove = 0.0f;
				buttons = 0;
				impulse = 0;
				weaponselect = 0;
				weaponsubtype = 0;
				random_seed = 0;
				mousedx = 0;
				mousedy = 0;
				hasbeenpredicted = false;
			}

		};//Size=0x0100

		class CVerifiedUserCmd
		{
		public:
			CUserCmd        m_cmd;
			ULONG           m_crc;
		};

		class CBaseCombatWeapon
		{
		public:

			void SetViewModelIndex(int A);
			void SetDefIndex(int A);
			void SetWorldIndex(int A);

			int GetWeaponID()
			{
				// m_AttributeManager = 0x1140
				// m_Item = 0x40
				// m_iItemDefinitionIndex = 0x1D0
				static DWORD offset = pNetworkedVariables->GetNetvar("DT_BaseCombatWeapon", "m_iItemDefinitionIndex");
				if (!offset)
					offset = pNetworkedVariables->GetNetvar("DT_BaseCombatWeapon", "m_iItemDefinitionIndex");
				return *(int*)((DWORD)this + offset);
			}

			bool IsZoomed() // 1 or 2
			{
				//bool b = *reinterpret_cast<int*>(reinterpret_cast<int>(this) + 0x383C); //aM_bisscoped ; "m_bIsScoped"
				return 0;
			}
		
		};


		class CInput
		{
		public:
			void CreateMove(int sequence_number, float input_sample_frametime, bool active)
			{
				typedef void(__thiscall* CreateMoveFn)(PVOID, int, float, bool);
				return call_vfunc< CreateMoveFn >(this, 3)(this, sequence_number, input_sample_frametime, active);
			}

			CUserCmd * GetUserCmd(int nSlot, int sequence_number)
			{
				typedef CUserCmd* (__thiscall* GetUserCmdFn)(PVOID, int, int);
				return call_vfunc< GetUserCmdFn >(this, 8)(this, nSlot, sequence_number);
			}

			CUserCmd*               m_pCmd;
			CVerifiedUserCmd*       m_pVerifiedCmd;
		};

		//TRACE
#define POW(a) ( pow(a,2) )
#define VectorLengthSquared(v) ((v)[0]*(v)[0]+(v)[1]*(v)[1]+(v)[2]*(v)[2])
#define VectorDistance(a,b) sqrt(POW((a)[0]-(b)[0])+POW((a)[1]-(b)[1])+POW((a)[2]-(b)[2]))
#define VectorLength(a) sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorMul(vec,num,res){(res)[0]=(vec)[0]*(num);(res)[1]=(vec)[1]*(num);(res)[2]=(vec)[2]*(num);}
#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define Square(a) ((a)*(a))
#define VectorTransform(a,b,c){(c)[0]=DotProduct((a),(b)[0])+(b)[0][3];(c)[1]=DotProduct((a),(b)[1])+(b)[1][3];(c)[2]=DotProduct((a),(b)[2])+(b)[2][3];}
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
#define VectorClear(a) { a[0]=0.0;a[1]=0.0;a[2]=0.0;}

		//#define ALIGN16 


		typedef float vec_t;

		class VectorAligned : public Vector
		{

			float w;	// this space is used anyway
		};


		struct Ray_t
		{
			VectorAligned        m_Start;
			VectorAligned        m_Delta;
			VectorAligned        m_StartOffset;
			VectorAligned        m_Extents;

			const matrix3x4_t*    m_WorldAxisTransform;

			bool                m_IsRay;
			bool                m_IsSwept;

			Ray_t(void)
				: m_WorldAxisTransform(0)
			{

			}

			void Init(const Vector& start, const Vector& end)
			{
				VectorSubtract(end, start, m_Delta);

				m_IsSwept = (m_Delta.Size() != 0);

				VectorClear(m_Extents);
				m_IsRay = true;

				// Offset m_Start to be in the center of the box...
				VectorClear(m_StartOffset);
				VectorCopy(start, m_Start);
			}

		};

		struct cplane_t
		{
			Vector  normal;
			float   dist;
			BYTE    type;
			BYTE    signbits;
			BYTE    pad[2];
		};

		struct csurface_t
		{
			const char*             name;
			short                   surfaceProps;
			unsigned short          flags;
		};

		class CBaseTrace
		{
		public:
			Vector                  startpos;
			Vector                  endpos;
			cplane_t                plane;
			float                   fraction;
			int                     contents;
			unsigned short          dispFlags;
			bool                    allsolid;
			bool                    startsolid;
		};

		class CGameTrace : public CBaseTrace
		{
		public:
			bool                    DidHitWorld() const;
			bool                    DidHitNonWorldEntity() const;
			int                     GetEntityIndex() const;
			bool                    DidHit() const;

		public:
			float                   fractionleftsolid;
			csurface_t              surface;
			int                     hitgroup;
			short                   physicsbone;
			unsigned short          worldSurfaceIndex;
			IClientEntity*            m_pEnt;
			int                     hitbox;

			CGameTrace() { }
			CGameTrace(const CGameTrace& vOther);
		private:

		};

		inline bool CGameTrace::DidHit(VOID) const
		{
			return fraction < 1.0f || allsolid || startsolid;
		}

		typedef CGameTrace trace_t;

		enum TraceType_t
		{
			TRACE_EVERYTHING = 0,
			TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
			TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
			TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
		};



		class ITraceFilter
		{
		public:
			virtual bool ShouldHitEntity(IClientEntity *pEntity, int contentsMask) = 0;
			virtual TraceType_t     GetTraceType() const = 0;
		};

		class CTraceFilter : public ITraceFilter
		{
		public:
			CTraceFilter(IClientEntity* pPassEntity)
			{
				m_pClientEntityToSkip = pPassEntity;
			}

			CTraceFilter()
			{
				m_pClientEntityToSkip = nullptr;
			}

			bool ShouldHitEntity(IClientEntity* pHandleEntity, int contentsMask)
			{
				return !(pHandleEntity == m_pClientEntityToSkip);
			}

			virtual TraceType_t GetTraceType() const
			{
				return TRACE_EVERYTHING;
			}

			//private:
			IClientEntity* m_pClientEntityToSkip;
		};

		class CTraceFilterNoPlayers : public ITraceFilter
		{
		public:
			CTraceFilterNoPlayers() {}

			bool ShouldHitEntity(IClientEntity* pHandleEntity, int contentsMask)
			{
				char szLifeState = *(char*)((DWORD)pHandleEntity + 0x25B);
				return (szLifeState != 0);
			}

			virtual TraceType_t GetTraceType() const
			{
				return TRACE_EVERYTHING;
			}
		};

		class ITraceListData
		{
		public:
			virtual ~ITraceListData() {}

			virtual void Reset() = 0;
			virtual bool IsEmpty() = 0;
			// CanTraceRay will return true if the current volume encloses the ray
			// NOTE: The leaflist trace will NOT check this.  Traces are intersected
			// against the culled volume exclusively.
			virtual bool CanTraceRay(const Ray_t &ray) = 0;
		};

		class IEntityEnumerator
		{
		public:
			// This gets called with each handle
			virtual bool EnumEntity(IHandleEntity *pHandleEntity) = 0;
		};


		struct BrushSideInfo_t
		{
			Vector plane;			// The plane of the brush side
			float planec;
			unsigned short bevel;	// Bevel plane?
			unsigned short thin;	// Thin?
		};

		enum DebugTraceCounterBehavior_t
		{
			kTRACE_COUNTER_SET = 0,
			kTRACE_COUNTER_INC,
		};

		struct virtualmeshlist_t;
		class IEngineTrace
		{
		public:
			// Returns the contents mask + entity at a particular world-space position
			virtual int		GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL) = 0;

			// Returns the contents mask of the world only @ the world-space position (static props are ignored)
			virtual int		GetPointContents_WorldOnly(const Vector &vecAbsPosition, int contentsMask = MASK_ALL) = 0;

			// Get the point contents, but only test the specific entity. This works
			// on static props and brush models.
			//
			// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
			// bFailed to true if bFailed is non-null.
			virtual int		GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition) = 0;

			// Traces a ray against a particular entity
			virtual void	ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace) = 0;

			// Traces a ray against a particular entity
			virtual void	ClipRayToCollideable(const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace) = 0;

			// A version that simply accepts a ray (can work as a traceline or tracehull)
			virtual void	TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;

			// A version that sets up the leaf and entity lists and allows you to pass those in for collision.
			virtual void	SetupLeafAndEntityListRay(const Ray_t &ray, ITraceListData *pTraceData) = 0;
			virtual void    SetupLeafAndEntityListBox(const Vector &vecBoxMin, const Vector &vecBoxMax, ITraceListData *pTraceData) = 0;
			virtual void	TraceRayAgainstLeafAndEntityList(const Ray_t &ray, ITraceListData *pTraceData, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;

			// A version that sweeps a collideable through the world
			// abs start + abs end represents the collision origins you want to sweep the collideable through
			// vecAngles represents the collision angles of the collideable during the sweep
			virtual void	SweepCollideable(ICollideable *pCollide, const Vector &vecAbsStart, const Vector &vecAbsEnd,
				const QAngle &vecAngles, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;

			// Enumerates over all entities along a ray
			// If triggers == true, it enumerates all triggers along a ray
			virtual void	EnumerateEntities(const Ray_t &ray, bool triggers, IEntityEnumerator *pEnumerator) = 0;

			// Same thing, but enumerate entitys within a box
			virtual void	EnumerateEntities(const Vector &vecAbsMins, const Vector &vecAbsMaxs, IEntityEnumerator *pEnumerator) = 0;

			// Convert a handle entity to a collideable.  Useful inside enumer
			virtual ICollideable *GetCollideable(IHandleEntity *pEntity) = 0;

			// HACKHACK: Temp for performance measurments
			virtual int GetStatByIndex(int index, bool bClear) = 0;

			//finds brushes in an AABB, prone to some false positives
			virtual void lolignorethisaswellrifk() = 0;

			//Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
			virtual void GetCollidableFromDisplacementsInAABB() = 0;

			// gets the number of displacements in the world
			virtual int GetNumDisplacements() = 0;

			// gets a specific diplacement mesh
			virtual void GetDisplacementMesh(int nIndex, virtualmeshlist_t *pMeshTriList) = 0;

			//retrieve brush planes and contents, returns true if data is being returned in the output pointers, false if the brush doesn't exist
			virtual bool lolignorethis() = 0;

			virtual bool PointOutsideWorld(const Vector &ptTest) = 0; //Tests a point to see if it's outside any playable area

																	  // Walks bsp to find the leaf containing the specified point
			virtual int GetLeafContainingPoint(const Vector &ptTest) = 0;

			virtual ITraceListData *AllocTraceListData() = 0;
			virtual void FreeTraceListData(ITraceListData *) = 0;

			/// Used only in debugging: get/set/clear/increment the trace debug counter. See comment below for details.
			virtual int GetSetDebugTraceCounter(int value, DebugTraceCounterBehavior_t behavior) = 0;
		};

#define VPHYSICS_SURFACEPROPS_INTERFACE_VERSION	"VPhysicsSurfaceProps001"

		struct surfacephysicsparams_t
		{
			float			friction;
			float			elasticity;
			float			density;
			float			thickness;
			float			dampening;
		};

		struct surfaceaudioparams_t
		{
			float			reflectivity;
			float			hardnessFactor;
			float			roughnessFactor;
			float			roughThreshold;
			float			hardThreshold;
			float			hardVelocityThreshold;
		};

		struct surfacesoundnames_t
		{
			//unsigned short	walkStepLeft;
			//unsigned short	walkStepRight;
			unsigned short	runStepLeft;
			unsigned short	runStepRight;
			unsigned short	impactSoft;
			unsigned short	impactHard;
			unsigned short	scrapeSmooth;
			unsigned short	scrapeRough;
			unsigned short	bulletImpact;
			unsigned short	rolling;
			unsigned short	breakSound;
			unsigned short	strainSound;
		};

		struct surfacesoundhandles_t
		{
			short	walkStepLeft;
			short	walkStepRight;
			short	runStepLeft;
			short	runStepRight;
			short	impactSoft;
			short	impactHard;
			short	scrapeSmooth;
			short	scrapeRough;
			short	bulletImpact;
			short	rolling;
			short	breakSound;
			short	strainSound;
		};

		struct surfacegameprops_t
		{
		public:
			float				maxSpeedFactor;
			float				jumpFactor;
			char				pad00[0x4];
			float				flPenetrationModifier;
			float				flDamageModifier;
			unsigned short		material;
			char				pad01[0x3];
		};

		struct surfacedata_t
		{
			surfacephysicsparams_t	physics;
			surfaceaudioparams_t	audio;
			surfacesoundnames_t		sounds;
			surfacegameprops_t		game;
			surfacesoundhandles_t	soundhandles;
		};



		class IPhysicsSurfaceProps
		{
		public:
			virtual ~IPhysicsSurfaceProps(void) {}

			// parses a text file containing surface prop keys
			virtual int		ParseSurfaceData(const char *pFilename, const char *pTextfile) = 0;
			// current number of entries in the database
			virtual int		SurfacePropCount(void) const = 0;

			virtual int		GetSurfaceIndex(const char *pSurfacePropName) const = 0;
			virtual void	GetPhysicsProperties(int surfaceDataIndex, float *density, float *thickness, float *friction, float *elasticity) const = 0;

			virtual surfacedata_t	*GetSurfaceData(int surfaceDataIndex) = 0;
			virtual const char		*GetString(unsigned short stringTableIndex) const = 0;


			virtual const char		*GetPropName(int surfaceDataIndex) const = 0;

			// sets the global index table for world materials
			// UNDONE: Make this per-CPhysCollide
			virtual void	SetWorldMaterialIndexTable(int *pMapArray, int mapSize) = 0;

			// NOTE: Same as GetPhysicsProperties, but maybe more convenient
			virtual void	GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t *pParamsOut) const = 0;
		};

		enum soundlevel_t
		{
			SNDLVL_NONE = 0,

			SNDLVL_20dB = 20,			// rustling leaves
			SNDLVL_25dB = 25,			// whispering
			SNDLVL_30dB = 30,			// library
			SNDLVL_35dB = 35,
			SNDLVL_40dB = 40,
			SNDLVL_45dB = 45,			// refrigerator

			SNDLVL_50dB = 50,	// 3.9	// average home
			SNDLVL_55dB = 55,	// 3.0

			SNDLVL_IDLE = 60,	// 2.0	
			SNDLVL_60dB = 60,	// 2.0	// normal conversation, clothes dryer

			SNDLVL_65dB = 65,	// 1.5	// washing machine, dishwasher
			SNDLVL_STATIC = 66,	// 1.25

			SNDLVL_70dB = 70,	// 1.0	// car, vacuum cleaner, mixer, electric sewing machine

			SNDLVL_NORM = 75,
			SNDLVL_75dB = 75,	// 0.8	// busy traffic

			SNDLVL_80dB = 80,	// 0.7	// mini-bike, alarm clock, noisy restaurant, office tabulator, outboard motor, passing snowmobile
			SNDLVL_TALKING = 80,	// 0.7
			SNDLVL_85dB = 85,	// 0.6	// average factory, electric shaver
			SNDLVL_90dB = 90,	// 0.5	// screaming child, passing motorcycle, convertible ride on frw
			SNDLVL_95dB = 95,
			SNDLVL_100dB = 100,	// 0.4	// subway train, diesel truck, woodworking shop, pneumatic drill, boiler shop, jackhammer
			SNDLVL_105dB = 105,			// helicopter, power mower
			SNDLVL_110dB = 110,			// snowmobile drvrs seat, inboard motorboat, sandblasting
			SNDLVL_120dB = 120,			// auto horn, propeller aircraft
			SNDLVL_130dB = 130,			// air raid siren

			SNDLVL_GUNFIRE = 140,	// 0.27	// THRESHOLD OF PAIN, gunshot, jet engine
			SNDLVL_140dB = 140,	// 0.2

			SNDLVL_150dB = 150,	// 0.2

			SNDLVL_180dB = 180,			// rocket launching

			// NOTE: Valid soundlevel_t values are 0-255.
			//       256-511 are reserved for sounds using goldsrc compatibility attenuation.
		};

		class IRecipientFilter
		{
		public:
			virtual			~IRecipientFilter() {}

			virtual bool	IsReliable(void) const = 0;
			virtual bool	IsInitMessage(void) const = 0;

			virtual int		GetRecipientCount(void) const = 0;
			virtual int		GetRecipientIndex(int slot) const = 0;
		};

#define PITCH_NORM 100

		class IEngineSound
		{
		public:
			// Precache a particular sample
			virtual bool PrecacheSound(const char *pSample, bool bPreload = false, bool bIsUISound = false) = 0;
			virtual bool IsSoundPrecached(const char *pSample) = 0;
			virtual void PrefetchSound(const char *pSample) = 0;

			// Just loads the file header and checks for duration (not hooked up for .mp3's yet)
			// Is accessible to server and client though
			virtual float GetSoundDuration(const char *pSample) = 0;

			// Pitch of 100 is no pitch shift.  Pitch > 100 up to 255 is a higher pitch, pitch < 100
			// down to 1 is a lower pitch.   150 to 70 is the realistic range.
			// EmitSound with pitch != 100 should be used sparingly, as it's not quite as
			// fast (the pitchshift mixer is not native coded).

			// NOTE: setting iEntIndex to -1 will cause the sound to be emitted from the local
			// player (client-side only)
			virtual void EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSample,
				float flVolume, float flAttenuation, int iFlags = 0, int iPitch = PITCH_NORM, int iSpecialDSP = 0,
				const Vector *pOrigin = NULL, const Vector *pDirection = NULL, vector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

			virtual void EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSample,
				float flVolume, soundlevel_t iSoundlevel, int iFlags = 0, int iPitch = PITCH_NORM, int iSpecialDSP = 0,
				const Vector *pOrigin = NULL, const Vector *pDirection = NULL, vector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

			virtual void EmitSentenceByIndex(IRecipientFilter& filter, int iEntIndex, int iChannel, int iSentenceIndex,
				float flVolume, soundlevel_t iSoundlevel, int iFlags = 0, int iPitch = PITCH_NORM, int iSpecialDSP = 0,
				const Vector *pOrigin = NULL, const Vector *pDirection = NULL, vector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

			virtual void StopSound(int iEntIndex, int iChannel, const char *pSample) = 0;

			// stop all active sounds (client only)
			virtual void StopAllSounds(bool bClearBuffers) = 0;

			// Set the room type for a player (client only)
			virtual void SetRoomType(IRecipientFilter& filter, int roomType) = 0;

			// Set the dsp preset for a player (client only)
			virtual void SetPlayerDSP(IRecipientFilter& filter, int dspType, bool fastReset) = 0;

			// emit an "ambient" sound that isn't spatialized
			// only available on the client, assert on server
			virtual void EmitAmbientSound(const char *pSample, float flVolume, int iPitch = PITCH_NORM, int flags = 0, float soundtime = 0.0f) = 0;


			//	virtual EntChannel_t	CreateEntChannel() = 0;

			virtual float GetDistGainFromSoundLevel(soundlevel_t soundlevel, float dist) = 0;

			// Client .dll only functions
			virtual int		GetGuidForLastSoundEmitted() = 0;
			virtual bool	IsSoundStillPlaying(int guid) = 0;
			virtual void	StopSoundByGuid(int guid) = 0;
			// Set's master volume (0.0->1.0)
			virtual void	SetVolumeByGuid(int guid, float fvol) = 0;

			// Retrieves list of all active sounds
			//virtual void	GetActiveSounds(vector< SndInfo_t >& sndlist) = 0;

			virtual void	PrecacheSentenceGroup(const char *pGroupName) = 0;
			virtual void	NotifyBeginMoviePlayback() = 0;
			virtual void	NotifyEndMoviePlayback() = 0;
		};




#define INTERFACEVERSION_PLAYERINFOMANAGER			"PlayerInfoManager002"
		class IPlayerInfoManager
		{
		public:
			virtual void *GetPlayerInfo(void *pEdict) = 0;
			virtual void *GetGlobalVars() = 0;
		};

		struct Hitbox_t
		{
			int       iBone;
			Vector    vMin;
			Vector    vMax;
			void Setup(int bone, Vector min, Vector max)
			{
				iBone = bone;
				vMin = min;
				vMax = max;
			}
		};


#define MDLCACHE_INTERFACE_VERSION "MDLCache004"

		typedef unsigned short MDLHandle_t;
		class IMDLCache
		{
		public:
			virtual void unk0() = 0;
			virtual void unk1() = 0;
			virtual void unk2() = 0;
			virtual void unk3() = 0;
			virtual void unk4() = 0;
			virtual void unk5() = 0;
			virtual void unk6() = 0;
			virtual void unk7() = 0;
			virtual void unk8() = 0;
			virtual MDLHandle_t FindMDL(const char *pMDLRelativePath) = 0; // 9

		};


		enum modtype_t
		{
			mod_bad = 0,
			mod_brush,
			mod_sprite,
			mod_studio
		};

		struct model_t
		{
			char        name[255];

			// UNDONE: Choose between these two methods
			//int            registration_sequence;
			int            needload;        // mark loaded/not loaded

			modtype_t    type;
			int            flags;

			//
			// volume occupied by the model graphics
			//        
			Vector mins, maxs;
			float        radius;

			int            extradatasize;
			// 	cache_user_t    cache;
			// 
			// 	union
			// 	{
			// 		brushdata_t        brush;
			// 		studiodata_t    studio;
			// 		spritedata_t    sprite;
			// 	};
		};

#define VENGINE_HUDMODEL_INTERFACE_VERSION	"VEngineModel016"

		typedef unsigned short ModelInstanceHandle_t;

		enum
		{
			MODEL_INSTANCE_INVALID = (ModelInstanceHandle_t)~0
		};

		struct ModelRenderInfo_t
		{
			Vector origin;
			Vector angles;
			char pad[0x4]; // upd
			// IClientRenderable *pRenderable;
			void *pRenderable; // upd
			// const model_t *pModel;
			const void *pModel; // upd
			const matrix3x4_t *pModelToWorld;
			const matrix3x4_t *pLightingOffset;
			const Vector *pLightingOrigin;
			int flags;
			int entity_index;
			int skin;
			int body;
			int hitboxset;
			ModelInstanceHandle_t instance;

			ModelRenderInfo_t()
			{
				pModelToWorld = NULL;
				pLightingOffset = NULL;
				pLightingOrigin = NULL;
			}
		};

		struct DrawModelState_t
		{
			// 	studiohdr_t*			m_pStudioHdr;
			// 	studiohwdata_t*			m_pStudioHWData;
			// 	IClientRenderable*		m_pRenderable;
			// 	const matrix3x4_t		*m_pModelToWorld;
			// 	StudioDecalHandle_t		m_decals;
			// 	int						m_drawFlags;
			// 	int						m_lod;
		};

		struct StaticPropRenderInfo_t
		{
			const matrix3x4_t		*pModelToWorld;
			const model_t			*pModel;
			IClientRenderable		*pRenderable;
			Vector					*pLightingOrigin;
			short					skin;
			ModelInstanceHandle_t	instance;
		};

		enum MaterialPropertyTypes_t
		{
			MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,					// bool
			MATERIAL_PROPERTY_OPACITY,								// int (enum MaterialPropertyOpacityTypes_t)
			MATERIAL_PROPERTY_REFLECTIVITY,							// vec3_t
			MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
		};

		enum PreviewImageRetVal_t
		{
			MATERIAL_PREVIEW_IMAGE_BAD = 0,
			MATERIAL_PREVIEW_IMAGE_OK,
			MATERIAL_NO_PREVIEW_IMAGE,
		};

		enum MaterialVarFlags_t
		{
			MATERIAL_VAR_DEBUG = (1 << 0),
			MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
			MATERIAL_VAR_NO_DRAW = (1 << 2),
			MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

			MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
			MATERIAL_VAR_VERTEXALPHA = (1 << 5),
			MATERIAL_VAR_SELFILLUM = (1 << 6),
			MATERIAL_VAR_ADDITIVE = (1 << 7),
			MATERIAL_VAR_ALPHATEST = (1 << 8),
			//	MATERIAL_VAR_UNUSED					  = (1 << 9),
			MATERIAL_VAR_ZNEARER = (1 << 10),
			MATERIAL_VAR_MODEL = (1 << 11),
			MATERIAL_VAR_FLAT = (1 << 12),
			MATERIAL_VAR_NOCULL = (1 << 13),
			MATERIAL_VAR_NOFOG = (1 << 14),
			MATERIAL_VAR_IGNOREZ = (1 << 15),
			MATERIAL_VAR_DECAL = (1 << 16),
			MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
			//	MATERIAL_VAR_UNUSED					  = (1 << 18),
			MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
			MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
			MATERIAL_VAR_TRANSLUCENT = (1 << 21),
			MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
			MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
			MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
			MATERIAL_VAR_ENVMAPMODE = (1 << 25), // OBSOLETE
			MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
			MATERIAL_VAR_HALFLAMBERT = (1 << 27),
			MATERIAL_VAR_WIREFRAME = (1 << 28),
			MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
			MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
			MATERIAL_VAR_VERTEXFOG = (1 << 31),

			// NOTE: Only add flags here that either should be read from
			// .vmts or can be set directly from client code. Other, internal
			// flags should to into the flag enum in IMaterialInternal.h
		};

#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

		class IMaterial
		{
		public:
			// Get the name of the material.  This is a full path to 
			// the vmt file starting from "hl2/materials" (or equivalent) without
			// a file extension.
			virtual const char *	GetName() const = 0;
			virtual const char *	GetTextureGroupName() const = 0;

			// Get the preferred size/bitDepth of a preview image of a material.
			// This is the sort of image that you would use for a thumbnail view
			// of a material, or in WorldCraft until it uses materials to render.
			// separate this for the tools maybe
			virtual PreviewImageRetVal_t GetPreviewImageProperties(int *width, int *height,
				void*imageFormat, bool* isTranslucent) const = 0;

			// Get a preview image at the specified width/height and bitDepth.
			// Will do resampling if necessary.(not yet!!! :) )
			// Will do color format conversion. (works now.)
			virtual PreviewImageRetVal_t GetPreviewImage(unsigned char *data,
				int width, int height,
				void* imageFormat) const = 0;
			// 
			virtual int				GetMappingWidth() = 0;
			virtual int				GetMappingHeight() = 0;

			virtual int				GetNumAnimationFrames() = 0;

			// For material subrects (material pages).  Offset(u,v) and scale(u,v) are normalized to texture.
			virtual bool			InMaterialPage(void) = 0;
			virtual	void			GetMaterialOffset(float *pOffset) = 0;
			virtual void			GetMaterialScale(float *pScale) = 0;
			virtual IMaterial		*GetMaterialPage(void) = 0;

			// find a vmt variable.
			// This is how game code affects how a material is rendered.
			// The game code must know about the params that are used by
			// the shader for the material that it is trying to affect.
			virtual void *	FindVar(const char *varName, bool *found, bool complain = true) = 0;

			// The user never allocates or deallocates materials.  Reference counting is
			// used instead.  Garbage collection is done upon a call to 
			// IMaterialSystem::UncacheUnusedMaterials.
			virtual void			IncrementReferenceCount(void) = 0;
			virtual void			DecrementReferenceCount(void) = 0;

			inline void AddRef() { IncrementReferenceCount(); }
			inline void Release() { DecrementReferenceCount(); }

			// Each material is assigned a number that groups it with like materials
			// for sorting in the application.
			virtual int 			GetEnumerationID(void) const = 0;

			virtual void			GetLowResColorSample(float s, float t, float *color) const = 0;

			// This computes the state snapshots for this material
			virtual void			RecomputeStateSnapshots() = 0;

			// Are we translucent?
			virtual bool			IsTranslucent() = 0;

			// Are we alphatested?
			virtual bool			IsAlphaTested() = 0;

			// Are we vertex lit?
			virtual bool			IsVertexLit() = 0;

			// Gets the vertex format
			virtual unsigned long	GetVertexFormat() const = 0;

			// returns true if this material uses a material proxy
			virtual bool			HasProxy(void) const = 0;

			virtual bool			UsesEnvCubemap(void) = 0;

			virtual bool			NeedsTangentSpace(void) = 0;

			virtual bool			NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
			virtual bool			NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;

			// returns true if the shader doesn't do skinning itself and requires
			// the data that is sent to it to be preskinned.
			virtual bool			NeedsSoftwareSkinning(void) = 0;

			// Apply constant color or alpha modulation
			virtual void			AlphaModulate(float alpha) = 0;
			virtual void			ColorModulate(float r, float g, float b) = 0;

			// Material Var flags...
			virtual void			SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
			virtual bool			GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;

			// Gets material reflectivity
			virtual void			GetReflectivity(Vector& reflect) = 0;

			// Gets material property flags
			virtual bool			GetPropertyFlag(MaterialPropertyTypes_t type) = 0;

			// Is the material visible from both sides?
			virtual bool			IsTwoSided() = 0;

			// Sets the shader associated with the material
			virtual void			SetShader(const char *pShaderName) = 0;

			// Can't be const because the material might have to precache itself.
			virtual int				GetNumPasses(void) = 0;

			// Can't be const because the material might have to precache itself.
			virtual int				GetTextureMemoryBytes(void) = 0;

			// Meant to be used with materials created using CreateMaterial
			// It updates the materials to reflect the current values stored in the material vars
			virtual void			Refresh() = 0;

			// GR - returns true is material uses lightmap alpha for blending
			virtual bool			NeedsLightmapBlendAlpha(void) = 0;

			// returns true if the shader doesn't do lighting itself and requires
			// the data that is sent to it to be prelighted
			virtual bool			NeedsSoftwareLighting(void) = 0;

			// Gets at the shader parameters
			virtual int				ShaderParamCount() const = 0;
			virtual void	**GetShaderParams(void) = 0;

			// Returns true if this is the error material you get back from IMaterialSystem::FindMaterial if
			// the material can't be found.
			virtual bool			IsErrorMaterial() const = 0;

			virtual void			Unused() = 0;

			// Gets the current alpha modulation
			virtual float			GetAlphaModulation() = 0;
			virtual void			GetColorModulation(float *r, float *g, float *b) = 0;

			// Is this translucent given a particular alpha modulation?
			virtual bool			IsTranslucentUnderModulation(float fAlphaModulation = 1.0f) const = 0;

			// fast find that stores the index of the found var in the string table in local cache
			virtual void *	FindVarFast(char const *pVarName, unsigned int *pToken) = 0;

			// Sets new VMT shader parameters for the material
			virtual void			SetShaderAndParams(void *pKeyValues) = 0;
			virtual const char *	GetShaderName() const = 0;

			virtual void			DeleteIfUnreferenced() = 0;

			virtual bool			IsSpriteCard() = 0;

			virtual void			CallBindProxy(void *proxyData) = 0;

			virtual void			RefreshPreservingMaterialVars() = 0;

			virtual bool			WasReloadedFromWhitelist() = 0;

			virtual bool			SetTempExcluded(bool bSet, int nExcludedDimensionLimit) = 0;

			virtual int				GetReferenceCount() const = 0;

			bool IsERR(void)
			{
				typedef bool(__thiscall* oIsErrorMaterial)(PVOID);
				return call_vfunc< oIsErrorMaterial >(this, 42)(this);
			}
		};

		class CStudioHdr
		{

		};

		struct LightCacheHandle_t
		{

		};

		enum OverrideType_t
		{
			OVERRIDE_NORMAL = 0,
			OVERRIDE_BUILD_SHADOWS,
			OVERRIDE_DEPTH_WRITE,
			OVERRIDE_SSAO_DEPTH_WRITE,
		};

		struct DrawModelInfo_t
		{
			// 	studiohdr_t		*m_pStudioHdr;
			// 	studiohwdata_t	*m_pHardwareData;
			// 	StudioDecalHandle_t m_Decals;
			// 	int				m_Skin;
			// 	int				m_Body;
			// 	int				m_HitboxSet;
			// 	void			*m_pClientEntity;
			// 	int				m_Lod;
			// 	ColorMeshInfo_t	*m_pColorMeshes;
			// 	bool			m_bStaticLighting;
			// 	Vector			m_vecAmbientCube[6];		// ambient, and lights that aren't in locallight[]
			// 	int				m_nLocalLightCount;
			// 	LightDesc_t		m_LocalLightDescs[4];
		};

		enum
		{
			ADDDECAL_TO_ALL_LODS = -1
		};

		// UNDONE: Move this to hud export code, subsume previous functions
		class IVModelRender
		{
		public:
		};

#define VMODELINFO_CLIENT_INTERFACE_VERSION	"VModelInfoClient004"
#define VMODELINFO_SERVER_INTERFACE_VERSION	"VModelInfoServer002"

		enum RenderableTranslucencyType_t
		{
			RENDERABLE_IS_OPAQUE = 0,
			RENDERABLE_IS_TRANSLUCENT,
			RENDERABLE_IS_TWO_PASS,	// has both translucent and opaque sub-partsa
		};

		class CUtlBuffer;
		struct vcollide_t;

		class IVModelInfo
		{
		public:
			virtual							~IVModelInfo(void) { }
			virtual const model_t			*GetModel(int modelindex) const = 0;
			// Returns index of model by name
			virtual int						GetModelIndex(const char *name) const = 0;
			// Returns name of model
			virtual const char				*GetModelName(const model_t *model) const = 0;
			virtual vcollide_t				*GetVCollide(const model_t *model) const = 0;
			virtual vcollide_t				*GetVCollide(int modelindex) const = 0;
			virtual void					GetModelBounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
			virtual	void					GetModelRenderBounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
			virtual int						GetModelFrameCount(const model_t *model) const = 0;
			virtual int						GetModelType(const model_t *model) const = 0;
			virtual void					*GetModelExtraData(const model_t *model) = 0;
			virtual bool					ModelHasMaterialProxy(const model_t *model) const = 0;
			virtual bool					IsTranslucent(model_t const* model) const = 0;
			virtual bool					IsTranslucentTwoPass(const model_t *model) const = 0;
			virtual void					Unused0() {};
			virtual RenderableTranslucencyType_t ComputeTranslucencyType(const model_t *model, int nSkin, int nBody) = 0;
			virtual int						GetModelMaterialCount(const model_t* model) const = 0;
			// virtual void					GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterials) = 0;

			// update
			void GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterial) {
				typedef void *(__thiscall* oGetModelMaterials)(PVOID, const model_t*, int, IMaterial**);
				call_vfunc<oGetModelMaterials>(this, 19)(this, model, count, ppMaterial);
			}

			virtual bool					IsModelVertexLit(const model_t *model) const = 0;
			virtual const char				*GetModelKeyValueText(const model_t *model) = 0;
			virtual bool					GetModelKeyValue(const model_t *model, CUtlBuffer &buf) = 0; // supports keyvalue blocks in submodels
			virtual float					GetModelRadius(const model_t *model) = 0;

			virtual const studiohdr_t		*FindModel(const studiohdr_t *pStudioHdr, void **cache, const char *modelname) const = 0;
			virtual const studiohdr_t		*FindModel(void *cache) const = 0;
			virtual	virtualmodel_t			*GetVirtualModel(const studiohdr_t *pStudioHdr) const = 0;
			virtual byte					*GetAnimBlock(const studiohdr_t *pStudioHdr, int iBlock) const = 0;
			virtual bool					HasAnimBlockBeenPreloaded(studiohdr_t const*, int) const = 0;

			// Available on client only!!!
			virtual void					GetModelMaterialColorAndLighting(const model_t *model, Vector const& origin,
				QAngle const& angles, trace_t* pTrace,
				Vector& lighting, Vector& matColor) = 0;
			virtual void					GetIlluminationPoint(const model_t *model, IClientRenderable *pRenderable, Vector const& origin,
				QAngle const& angles, Vector* pLightingCenter) = 0;

			virtual int						GetModelContents(int modelIndex) const = 0;
			// virtual studiohdr_t				*GetStudioModel(const model_t *mod) = 0;

			studiohdr_t* GetStudioModel(const model_t* mod)
			{
				typedef studiohdr_t*(__stdcall* oGetStudiomodel)(const model_t*);
				return call_vfunc<oGetStudiomodel>(this, 32)(mod);
			}

			virtual int						GetModelSpriteWidth(const model_t *model) const = 0;
			virtual int						GetModelSpriteHeight(const model_t *model) const = 0;

			// Sets/gets a map-specified fade range (client only)
			virtual void					SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
			virtual void					GetLevelScreenFadeRange(float *pMinArea, float *pMaxArea) const = 0;

			// Sets/gets a map-specified per-view fade range (client only)
			virtual void					SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;

			// Computes fade alpha based on distance fade + screen fade (client only)
			virtual unsigned char			ComputeLevelScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
			virtual unsigned char			ComputeViewScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;

			// both client and server
			virtual int						GetAutoplayList(const studiohdr_t *pStudioHdr, unsigned short **pAutoplayList) const = 0;

			// Gets a virtual terrain collision model (creates if necessary)
			// NOTE: This may return NULL if the terrain model cannot be virtualized
			virtual CPhysCollide			*GetCollideForVirtualTerrain(int index) = 0;
			virtual bool					IsUsingFBTexture(const model_t *model, int nSkin, int nBody, void /*IClientRenderable*/ *pClientRenderable) const = 0;
			virtual const model_t			*FindOrLoadModel(const char *name) const = 0;
			virtual MDLHandle_t				GetCacheHandle(const model_t *model) const = 0;
			// Returns planes of non-nodraw brush model surfaces
			virtual int						GetBrushModelPlaneCount(const model_t *model) const = 0;
			virtual void					GetBrushModelPlane(const model_t *model, int nIndex, cplane_t &plane, Vector *pOrigin) const = 0;
			virtual int						GetSurfacepropsForVirtualTerrain(int index) = 0;
			virtual bool					UsesEnvCubemap(const model_t *model) const = 0;
			virtual bool					UsesStaticLighting(const model_t *model) const = 0;
		};

		typedef unsigned short MaterialHandle_t;
		class IMaterialSystem
		{
		public:
			IMaterial* CreateMaterial(bool flat, bool ignorez, bool wireframed);
			IMaterial* FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL);
			MaterialHandle_t FirstMaterial();
			MaterialHandle_t NextMaterial(MaterialHandle_t h);
			MaterialHandle_t InvalidMaterial();
			IMaterial * GetMaterial(MaterialHandle_t h);
		};




		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////




		struct mstudiobone_t
		{
			int					sznameindex;
			inline char * const pszName(void) const { return ((char *)this) + sznameindex; }
			int		 			parent;		// parent bone
			int					bonecontroller[6];	// bone controller index, -1 == none

			// default values
			Vector				pos;
			Vector			quat;
			Vector			rot;
			// compression scale
			Vector				posscale;
			Vector				rotscale;

			matrix3x4_t			poseToBone;
			Vector			qAlignment;
			int					flags;
			int					proctype;
			int					procindex;		// procedural rule
			mutable int			physicsbone;	// index into physically simulated bone
			inline void *pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
			int					surfacepropidx;	// index into string tablefor property name
			inline char * const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
			inline int			GetSurfaceProp(void) const { return surfacepropLookup; }

			int					contents;		// See BSPFlags.h for the contents flags
			int					surfacepropLookup;	// this index must be cached by the loader, not saved in the file
			int					unused[7];		// remove as appropriate

			mstudiobone_t(){}
		private:
			// No copy constructors allowed
			mstudiobone_t(const mstudiobone_t& vOther);
		};

		struct mstudiobonecontroller_t
		{
			int					bone;	// -1 == 0
			int					type;	// X, Y, Z, XR, YR, ZR, M
			float				start;
			float				end;
			int					rest;	// byte index value at rest
			int					inputfield;	// 0-3 user set controller, 4 mouth
			int					unused[8];
		};

		struct mstudiobbox_t
		{
			int					bone;
			int					group;				// intersection group
			Vector				bbmin;				// bounding box
			Vector				bbmax;
			int					szhitboxnameindex;	// offset to the name of the hitbox.
			int					unused[8];

			const char* pszHitboxName() const
			{
				if (szhitboxnameindex == 0)
					return "";

				return ((const char*)this) + szhitboxnameindex;
			}

			mstudiobbox_t() {}

		private:
			// No copy constructors allowed
			mstudiobbox_t(const mstudiobbox_t& vOther);
		};

		struct mstudiohitboxset_t
		{
			int					sznameindex;
			inline char * const	pszName(void) const { return ((char *)this) + sznameindex; }
			int					numhitboxes;
			int					hitboxindex;
			inline mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t *)(((byte *)this) + hitboxindex) + i; };
		};


		struct mstudiomovement_t
		{
			int					endframe;
			int					motionflags;
			float				v0;			// velocity at start of block
			float				v1;			// velocity at end of block
			float				angle;		// YAW rotation at end of this blocks movement
			Vector				vector;		// movement vector relative to this blocks initial angle
			Vector				position;	// relative to start of animation???

			mstudiomovement_t(){}
		private:
			// No copy constructors allowed
			mstudiomovement_t(const mstudiomovement_t& vOther);
		};

		union mstudioanimvalue_t
		{
			struct
			{
				byte	valid;
				byte	total;
			} num;
			short		value;
		};

		struct mstudioikerror_t
		{
			Vector		pos;
			Vector	q;

			mstudioikerror_t() {}

		private:
			// No copy constructors allowed
			mstudioikerror_t(const mstudioikerror_t& vOther);
		};

		struct mstudiocompressedikerror_t
		{
			float	scale[6];
			short	offset[6];
			inline mstudioanimvalue_t *pAnimvalue(int i) const { if (offset[i] > 0) return  (mstudioanimvalue_t *)(((byte *)this) + offset[i]); else return NULL; };
			mstudiocompressedikerror_t(){}

		private:
			// No copy constructors allowed
			mstudiocompressedikerror_t(const mstudiocompressedikerror_t& vOther);
		};


		struct mstudioikrule_t
		{
			int			index;

			int			type;
			int			chain;

			int			bone;

			int			slot;	// iktarget slot.  Usually same as chain.
			float		height;
			float		radius;
			float		floor;
			Vector		pos;
			Vector	q;

			int			compressedikerrorindex;
			inline mstudiocompressedikerror_t *pCompressedError() const { return (mstudiocompressedikerror_t *)(((byte *)this) + compressedikerrorindex); };
			int			unused2;

			int			iStart;
			int			ikerrorindex;
			inline mstudioikerror_t *pError(int i) const { return  (ikerrorindex) ? (mstudioikerror_t *)(((byte *)this) + ikerrorindex) + (i - iStart) : NULL; };

			float		start;	// beginning of influence
			float		peak;	// start of full influence
			float		tail;	// end of full influence
			float		end;	// end of all influence

			float		unused3;	// 
			float		contact;	// frame footstep makes ground concact
			float		drop;		// how far down the foot should drop when reaching for IK
			float		top;		// top of the foot box

			int			unused6;
			int			unused7;
			int			unused8;

			int			szattachmentindex;		// name of world attachment
			inline char * const pszAttachment(void) const { return ((char *)this) + szattachmentindex; }

			int			unused[7];

			mstudioikrule_t() {}

		private:
			// No copy constructors allowed
			mstudioikrule_t(const mstudioikrule_t& vOther);
		};

		struct studiohdr_t;
		struct mstudioanimdesc_t
		{
			int					baseptr;
			inline studiohdr_t	*pStudiohdr(void) const { return (studiohdr_t *)(((byte *)this) + baseptr); }

			int					sznameindex;
			inline char * const pszName(void) const { return ((char *)this) + sznameindex; }

			float				fps;		// frames per second	
			int					flags;		// looping/non-looping flags

			int					numframes;

			// piecewise movement
			int					nummovements;
			int					movementindex;
			inline mstudiomovement_t * const pMovement(int i) const { return (mstudiomovement_t *)(((byte *)this) + movementindex) + i; };

			int					ikrulezeroframeindex;
			DWORD *pIKRuleZeroFrame(int i) const { if (ikrulezeroframeindex) return (DWORD *)(((byte *)this) + ikrulezeroframeindex) + i; else return NULL; };

			int					unused1[5];			// remove as appropriate (and zero if loading older versions)	

			int					animblock;
			int					animindex;	 // non-zero when anim data isn't in sections
			byte *pAnimBlock(int block, int index) const; // returns pointer to a specific anim block (local or external)
			byte *pAnim(int *piFrame, float &flStall) const; // returns pointer to data and new frame index
			byte *pAnim(int *piFrame) const; // returns pointer to data and new frame index

			int					numikrules;
			int					ikruleindex;	// non-zero when IK rule is stored in the mdl
			int					animblockikruleindex; // non-zero when IK data is stored in animblock file
			mstudioikrule_t *pIKRule(int i) const;

			int					numlocalhierarchy;
			int					localhierarchyindex;
			void *pHierarchy(int i) const;

			int					sectionindex;
			int					sectionframes; // number of frames used in each fast lookup section, zero if not used
			inline DWORD * const pSection(int i) const { return (DWORD *)(((byte *)this) + sectionindex) + i; }

			short				zeroframespan;	// frames per span
			short				zeroframecount; // number of spans
			int					zeroframeindex;
			byte				*pZeroFrameData() const { if (zeroframeindex) return (((byte *)this) + zeroframeindex); else return NULL; };
			mutable float		zeroframestalltime;		// saved during read stalls

			mstudioanimdesc_t(){}
		private:
			// No copy constructors allowed
			mstudioanimdesc_t(const mstudioanimdesc_t& vOther);
		};

		struct studiohdr_t
		{
			int					id;
			int					version;

			long				checksum;		// this has to be the same in the phy and vtx files to load!

			inline const char *	pszName(void) const { return name; }
			char				name[64];

			int					length;

			Vector				eyeposition;	// ideal eye position

			Vector				illumposition;	// illumination center

			Vector				hull_min;		// ideal movement hull size
			Vector				hull_max;

			Vector				view_bbmin;		// clipping bounding box
			Vector				view_bbmax;

			int					flags;

			int					numbones;			// bones
			int					boneindex;
			inline mstudiobone_t *pBone(int i) const { return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };
			int					RemapSeqBone(int iSequence, int iLocalBone) const;	// maps local sequence bone to global bone
			int					RemapAnimBone(int iAnim, int iLocalBone) const;		// maps local animations bone to global bone

			int					numbonecontrollers;		// bone controllers
			int					bonecontrollerindex;
			inline mstudiobonecontroller_t *pBonecontroller(int i) const { return (mstudiobonecontroller_t *)(((byte *)this) + bonecontrollerindex) + i; };

			int					numhitboxsets;
			int					hitboxsetindex;

			// Look up hitbox set by index
			mstudiohitboxset_t	*pHitboxSet(int i) const
			{

				return (mstudiohitboxset_t *)(((byte *)this) + hitboxsetindex) + i;
			};

			// Calls through to hitbox to determine size of specified set
			inline mstudiobbox_t *pHitbox(int i, int set) const
			{
				mstudiohitboxset_t const *s = pHitboxSet(set);
				if (!s)
					return NULL;

				return s->pHitbox(i);
			};

			studiohdr_t() {}

		private:
			// No copy constructors allowed
			studiohdr_t(const studiohdr_t& vOther);

			friend struct virtualmodel_t;
		};


		class INetChannelInfo
		{
		public:
			enum {
				GENERIC = 0,	// must be first and is default group
				LOCALPLAYER,	// bytes for local player entity update
				OTHERPLAYERS,	// bytes for other players update
				ENTITIES,		// all other entity bytes
				SOUNDS,			// game sounds
				EVENTS,			// event messages
				TEMPENTS,		// temp entities
				USERMESSAGES,	// user messages
				ENTMESSAGES,	// entity messages
				VOICE,			// voice data
				STRINGTABLE,	// a stringtable update
				MOVE,			// client move cmds
				STRINGCMD,		// string command
				SIGNON,			// various signondata
				TOTAL,			// must be last and is not a real group
			};

			virtual const char  *GetName(void) const = 0;	// get channel name
			virtual const char  *GetAddress(void) const = 0; // get channel IP address as string
			virtual float		GetTime(void) const = 0;	// current net time
			virtual float		GetTimeConnected(void) const = 0;	// get connection time in seconds
			virtual int			GetBufferSize(void) const = 0;	// netchannel packet history size
			virtual int			GetDataRate(void) const = 0; // send data rate in byte/sec

			virtual bool		IsLoopback(void) const = 0;	// true if loopback channel
			virtual bool		IsTimingOut(void) const = 0;	// true if timing out
			virtual bool		IsPlayback(void) const = 0;	// true if demo playback

			virtual float		GetLatency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
			virtual float		GetAvgLatency(int flow) const = 0; // average packet latency in seconds
			virtual float		GetAvgLoss(int flow) const = 0;	 // avg packet loss[0..1]
			virtual float		GetAvgChoke(int flow) const = 0;	 // avg packet choke[0..1]
			virtual float		GetAvgData(int flow) const = 0;	 // data flow in bytes/sec
			virtual float		GetAvgPackets(int flow) const = 0; // avg packets/sec
			virtual int			GetTotalData(int flow) const = 0;	 // total flow in/out in bytes
			virtual int			GetTotalPackets(int flow) const = 0;
			virtual int			GetSequenceNr(int flow) const = 0;	// last send seq number
			virtual bool		IsValidPacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
			virtual float		GetPacketTime(int flow, int frame_number) const = 0; // time when packet was send
			virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0; // group size of this packet
			virtual bool		GetStreamProgress(int flow, int *received, int *total) const = 0;  // TCP progress if transmitting
			virtual float		GetTimeSinceLastReceived(void) const = 0;	// get time since last recieved packet in seconds
			virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
			virtual void		GetPacketResponseLatency(int flow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
			virtual void		GetRemoteFramerate(float *pflFrameTime, float *pflFrameTimeStdDeviation, float *pflFrameStartTimeStdDeviation) const = 0;
			virtual float		GetTimeoutSeconds() const = 0;
		};



		class INetMessage
		{

		};

		class INetChannel : public INetChannelInfo
		{
		public:
			virtual	~INetChannel(void) {};

			virtual void	SetDataRate(float rate) = 0;
			virtual bool	RegisterMessage(void *msg) = 0;
			virtual bool	UnregisterMessage(void *msg) = 0;
			virtual bool	StartStreaming(unsigned int challengeNr) = 0;
			virtual void	ResetStreaming(void) = 0;
			virtual void	SetTimeout(float seconds, bool bForceExact = false) = 0;
			virtual void	SetDemoRecorder(void *recorder) = 0;
			virtual void	SetChallengeNr(unsigned int chnr) = 0;

			virtual void	Reset(void) = 0;
			virtual void	Clear(void) = 0;
			virtual void	Shutdown(const char *reason) = 0;

			virtual void	ProcessPlayback(void) = 0;
			virtual bool	ProcessStream(void) = 0;
			virtual void	ProcessPacket(struct netpacket_s* packet, bool bHasHeader) = 0;

			virtual bool	SendNetMsg(INetMessage &msg, bool bForceReliable = false, bool bVoice = false) = 0;

			virtual bool	SendData(/*bf_write*/void* &msg, bool bReliable = true) = 0;
			virtual bool	SendFile(const char *filename, unsigned int transferID, bool isReplayDemo) = 0;
			virtual void	DenyFile(const char *filename, unsigned int transferID, bool isReplayDemo) = 0;
			virtual void	RequestFile_OLD(const char *filename, unsigned int transferID) = 0;	// get rid of this function when we version the 
			virtual void	SetChoked(void) = 0;
			virtual int		SendDatagram(/*bf_write*/void *data) = 0;
			virtual bool	Transmit(bool onlyReliable = false) = 0;

			virtual const void*	&GetRemoteAddress(void) const = 0;
			virtual void *GetMsgHandler(void) const = 0;
			virtual int				GetDropNumber(void) const = 0;
			virtual int				GetSocket(void) const = 0;
			virtual unsigned int	GetChallengeNr(void) const = 0;
			virtual void			GetSequenceData(int &nOutSequenceNr, int &nInSequenceNr, int &nOutSequenceNrAck) = 0;
			virtual void			SetSequenceData(int nOutSequenceNr, int nInSequenceNr, int nOutSequenceNrAck) = 0;

			virtual void	UpdateMessageStats(int msggroup, int bits) = 0;
			virtual bool	CanPacket(void) const = 0;
			virtual bool	IsOverflowed(void) const = 0;
			virtual bool	IsTimedOut(void) const = 0;
			virtual bool	HasPendingReliableData(void) = 0;

			virtual void	SetFileTransmissionMode(bool bBackgroundMode) = 0;
			virtual void	SetCompressionMode(bool bUseCompression) = 0;
			virtual unsigned int RequestFile(const char *filename, bool isReplayDemoFile) = 0;
			virtual float	GetTimeSinceLastReceived(void) const = 0;	// get time since last received packet in seconds

			virtual void	SetMaxBufferSize(bool bReliable, int nBytes, bool bVoice = false) = 0;

			virtual bool	IsNull() const = 0;
			virtual int		GetNumBitsWritten(bool bReliable) = 0;
			virtual void	SetInterpolationAmount(float flInterpolationAmount) = 0;
			virtual void	SetRemoteFramerate(float flFrameTime, float flFrameTimeStdDeviation, float flFrameStartTimeStdDeviation) = 0;

			// Max # of payload bytes before we must split/fragment the packet
			virtual void	SetMaxRoutablePayloadSize(int nSplitSize) = 0;
			virtual int		GetMaxRoutablePayloadSize() = 0;

			// For routing messages to a different handler
			virtual bool	SetActiveChannel(INetChannel *pNewChannel) = 0;
			virtual void	AttachSplitPlayer(int nSplitPlayerSlot, INetChannel *pChannel) = 0;
			virtual void	DetachSplitPlayer(int nSplitPlayerSlot) = 0;

			virtual bool	IsRemoteDisconnected() const = 0;

			virtual bool	WasLastMessageReliable() const = 0;
		};










		class IGameEvent
		{
		public:
			virtual ~IGameEvent() {};
			virtual const char *GetName() const = 0;	// get event name

			virtual bool  IsReliable() const = 0; // if event handled reliable
			virtual bool  IsLocal() const = 0; // if event is never networked
			virtual bool  IsEmpty(const char *keyName = NULL) = 0; // check if data field exists

			// Data access
			virtual bool  GetBool(const char *keyName = NULL, bool defaultValue = false) = 0;
			virtual int   GetInt(const char *keyName = NULL, int defaultValue = 0) = 0;
			virtual INT64 GetUint64(const char *keyName = NULL, INT64 defaultValue = 0) = 0;
			virtual float GetFloat(const char *keyName = NULL, float defaultValue = 0.0f) = 0;
			virtual const char *GetString(const char *keyName = NULL, const char *defaultValue = "") = 0;
			virtual const wchar_t * GetWString(char const *keyName = NULL, const wchar_t *defaultValue = L"") = 0;

			virtual void SetBool(const char *keyName, bool value) = 0;
			virtual void SetInt(const char *keyName, int value) = 0;
			virtual void SetUint64(const char *keyName, INT64 value) = 0;
			virtual void SetFloat(const char *keyName, float value) = 0;
			virtual void SetString(const char *keyName, const char *value) = 0;
			virtual void SetWString(const char *keyName, const wchar_t *value) = 0;
		};

		struct bf_read;
		struct bf_write;

		class IGameEventListener2 {
		public:
			virtual ~IGameEventListener2(void) {};
			virtual void FireGameEvent(IGameEvent* event) = 0;
			virtual int GetEventDebugID(void) = 0;
		};



#define INTERFACEVERSION_GAMEEVENTSMANAGER2	"GAMEEVENTSMANAGER002"	// new game event manager,

		class IGameEventManager2 {
		public:
			virtual ~IGameEventManager2(void) {};
			virtual int LoadEventsFromFile(const char* filename) = 0;
			virtual void Reset() = 0;
			virtual bool AddListener(IGameEventListener2* listener, const char* name, bool serverside) = 0;
			virtual bool FindListener(IGameEventListener2* listener, const char* name) = 0;
			virtual void RemoveListener(IGameEventListener2* listener) = 0;
			virtual void AddListenerGlobal(IGameEventListener2* listener, bool serverside) = 0;
			virtual IGameEvent* CreateEvent(const char* name, bool force = false, int* cookie = nullptr) = 0;
			virtual bool FireEvent(IGameEvent* event, bool bDontBroadcast = false) = 0;
			virtual bool FireEventClientSide(IGameEvent* event) = 0;
			virtual IGameEvent* DuplicateEvent(IGameEvent* event) = 0;
			virtual void FreeEvent(IGameEvent* event) = 0;
			virtual bool SerializeEvent(IGameEvent* event, bf_write* buffer) = 0;
			virtual IGameEvent* UnserializeEvent(bf_read* buffer) = 0;
			virtual KeyValues* GetEventDataTypes(IGameEvent* event) = 0;
		};


		class IGameConsole
		{
		public:
			virtual	~IGameConsole() {}
			// activates the console, makes it visible and brings it to the foreground
			virtual void Activate() = 0;

			virtual void Initialize() = 0;

			// hides the console
			virtual void Hide() = 0;

			// clears the console
			virtual void Clear() = 0;

			// return true if the console has focus
			virtual bool IsConsoleVisible() = 0;

			virtual void SetParent(int parent) = 0;
		};

		extern IGameConsole * pGameConsole;

		//////////////////////////////////////////////////////////////////////////

		struct c4_info_s
		{
			float ExplodeTime; // +45 ofc
			bool bPlanted; // yeeeee :D
		};

		class CLocalPlayer //Локальный игрок
		{
		public:
			Vector vViewAngles; //углы обзора
			Vector vEyePos; //позиция головы
			Vector vPunchAngle; //Угол из РКС

			float fSpeed; //Скорость передвижения
			int iChokedcommands; //сколько команд за раз не отправлено
			bool bJumped; //прыгнул ли игрок | для бхопа

			c4_info_s C4;

			CLocalPlayer()
			{

			}
		};

		class CPlayersListPlayer
		{
		public:
			CPlayersListPlayer()
			{
				bAutoYaw = false;
				bDidHitYou = false;
				bFixAA = false;
				iPitchMode = 0;
				fYawAngle = 0.0f;
				vAimTarget = Vector(0, 0, 0);
				IsVisible = false;
			}

			bool IsVisible; //visibility for entity by client (not visually)
			Vector vAimTarget; // позиция в пространстве //Куда целиться, ну типа если видим руку то стреляем в нее, приоритет с головы и до ног

			bool bAutoYaw; // autoyaw ofc
			bool bDidHitYou; // if enemy hit me make him first for aimbot :)
			bool bFixAA;
			int iPitchMode;
			float fYawAngle;


			struct w2s_bone_s
			{
			public:
				Vector vScreenPos = Vector(0, 0, 0);
				bool IsOnScreen = false;
			};

			struct AABB2DBox_s
			{
				float left;
				float top;
				float right;
				float bottom;
			};

			struct w2s_s
			{
			public:
				Vector vHeadScreen;
				Vector vLegScreen;
				Vector vAimSpot;
				bool IsOnScreen;

				bool bSpotted; // spotted by local player
				w2s_bone_s Bones[128];

			};

			IClientEntity * pEntity = nullptr;
			AABB2DBox_s AABBBox;
			w2s_s W2S;
		};

		class IAppSystem
		{
		public:
			virtual bool                            Connect(CSUtils::CreateInterfaceFn factory) = 0;                                  // 0
			virtual void                            Disconnect() = 0;                                                        // 1
			virtual void*                           QueryInterface(const char *pInterfaceName) = 0;                          // 2
			virtual InitReturnVal_t                 Init() = 0;                                                              // 3
			virtual void                            Shutdown() = 0;                                                          // 4
			virtual const AppSystemInfo_t*          GetDependencies() = 0;                                                   // 5
			virtual AppSystemTier_t                 GetTier() = 0;                                                           // 6
			virtual void                            Reconnect(CSUtils::CreateInterfaceFn factory, const char *pInterfaceName) = 0;    // 7
			virtual bool                            IsSingleton() = 0;                                                       // 8
		};

		class ConCommandBase;
		class ConCommand;
		
		class ConVar
		{
		public:

			const char* GetName();

			const char* GetBaseName();

			float GetFloat(void);

			int GetInt(void);

			// CColor GetColor(void);

			// const char* GetString(void);

			void SetValue(const char* value);

			void SetValue(float value);

			void SetValue(int value);

			char pad_0x0000[0x4]; //0x0000
			ConVar* pNext; //0x0004
			__int32 bRegistered; //0x0008
			char* pszName; //0x000C
			char* pszHelpString; //0x0010
			__int32 nFlags; //0x0014
			char pad_0x0018[0x4]; //0x0018
			ConVar* pParent; //0x001C
			char* pszDefaultValue; //0x0020
			char* strString; //0x0024
			__int32 StringLength; //0x0028
			float fValue; //0x002C
			__int32 nValue; //0x0030
			__int32 bHasMin; //0x0034
			float fMinVal; //0x0038
			__int32 bHasMax; //0x003C
			float fMaxVal; //0x0040
			void* fnChangeCallback; //0x0044
		};



		class IConVar
		{
		public:
			virtual void        SetValue(const char *pValue) = 0;
			virtual void        SetValue(float flValue) = 0;
			virtual void        SetValue(int nValue) = 0;
			virtual void        SetValue(Color value) = 0;
			virtual const char* GetName(void) const = 0;
			virtual const char* GetBaseName(void) const = 0;
			virtual bool        IsFlagSet(int nFlag) const = 0;
			virtual int         GetSplitScreenPlayerSlot() const = 0;
		};

		typedef int CVarDLLIdentifier_t;
		typedef void(*FnChangeCallback_t)(IConVar *var, const char *pOldValue, float flOldValue);

		class IConsoleDisplayFunc
		{
		public:
			virtual void ColorPrint(const uint8_t* clr, const char *pMessage) = 0;
			virtual void Print(const char *pMessage) = 0;
			virtual void DPrint(const char *pMessage) = 0;
		};

		class ICvar : public IAppSystem
		{
		public:
			virtual CVarDLLIdentifier_t        AllocateDLLIdentifier() = 0; // 9
			virtual void			RegisterConCommand(ConVar *pCommandBase) = 0;
			virtual void			UnregisterConCommand(ConVar *pCommandBase) = 0;
			virtual void                       UnregisterConCommands(CVarDLLIdentifier_t id) = 0;
			virtual const char*                GetCommandLineValue(const char *pVariableName) = 0; //11
			virtual ConCommandBase*            FindCommandBase(const char *name) = 0; //12
			virtual const ConCommandBase*      FindCommandBase(const char *name) const = 0;
			virtual ConVar*                    FindVar(const char *var_name) = 0;
			virtual const ConVar*              FindVar(const char *var_name) const = 0;
			virtual ConCommand*                FindCommand(const char *name) = 0;
			virtual const ConCommand*          FindCommand(const char *name) const = 0; //17
			virtual void                       InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
			virtual void                       RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
			virtual void                       CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) = 0;
			virtual void                       InstallConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
			virtual void                       RemoveConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
			virtual void                       ConsoleColorPrintf(const Color& clr, const char *pFormat, ...) const = 0;
			virtual void                       ConsolePrintf(const char *pFormat, ...) const = 0;
			virtual void                       ConsoleDPrintf(const char *pFormat, ...) const = 0;
			virtual void                       RevertFlaggedConVars(int nFlag) = 0;
		};


		extern IBaseClientDLL*			pClient;
		extern IVEngineClient*			pEngine;
		extern IPanel*					pPanel;
		extern IClientEntityList*		pClientEntList;
		extern ISurface*				pSurface;
		extern CGlobalVarsBase*		pGlobals;
		extern IEngineTrace*			pEngineTrace;
		extern CInput *                 pInput;
		extern IPhysicsSurfaceProps *   pPhysics;
		extern IMDLCache *				pMDLCache;
		extern IVModelRender *			pModelRender;
		extern IVModelInfo *			pModelInfo;
		extern IMaterialSystem *		pMatSystem;
		extern IGameEventManager2 *pGameEventManager;
		extern ICvar*                   pCvar;

	}
}