namespace Mythcore
{

#define M_PI 3.14159265358979323846

	namespace Math
	{



		struct Vector;
		struct matrix3x4_t;

		extern BOOL WorldToScreen(CONST Vector& point, OUT Vector& screen);
		extern BOOL ScreenTransform(CONST Vector& point, OUT Vector& screen);
		extern void CalculateAngles(Vector &src, Vector &dst, Vector &angles);
		extern void MakeVector(Vector & angle, Vector& vec);
		extern float CalculateFov(Vector Angles, Vector Source, Vector Dst);
		extern void AnglesToVector(const Vector &angles, Vector *forward, Vector *right, Vector *up);
		extern void VectorToAngles(Vector *forward, Vector *angles);
		extern void AngleVectors(const Vector &angles, Vector *forward);

		extern void NormalizeAngles(Vector & viewangles);
		extern void ClampAngles(Vector & viewangles);
		extern void AntiUntrustedYaw(Vector & viewangles);

		struct Vector
		{
			float X;
			float Y;
			float Z;

			Vector();
			Vector(float _X, float _Y, float _Z);

			Vector operator+ (const Vector &A);
			Vector operator+ (const float A);
			Vector operator+= (const Vector &A);
			Vector operator+= (const float A);
			Vector operator- (const Vector &A);
			Vector operator- (const float A);
			Vector operator-= (const Vector &A);
			Vector operator-= (const float A);
			Vector operator* (const Vector &A);
			Vector operator* (const float A);
			Vector operator*= (const Vector &A);
			Vector operator*= (const float A);
			Vector operator/ (const Vector &A);
			Vector operator/ (const float A);
			Vector operator/= (const Vector &A);
			Vector operator/= (const float A);

			bool operator== (const Vector &A);
			bool operator!= (const Vector &A);

			operator float *()								{ return &X; } // Vectors will now automatically convert to float * when needed
			operator const float *() const					{ return &X; } // Vectors will now automatically convert to float * when needed

			float Size()
			{
				return (X*X + Y*Y + Z*Z);
			}

			float Dot(const Vector a, const Vector b)
			{
				return(a.X*b.X + a.Y*b.Y + a.Z*b.Z);
			}

			float Dot(Vector V)
			{
				return Dot(*this, V);
			}


			inline float Length(void) const					{ return sqrt(X*X + Y*Y + Z*Z); }
			inline void Reset(void) { X = 0; Y = 0; Z = 0; }

			bool IsValid();
		};

		struct matrix3x4_t
		{
			matrix3x4_t() {}
			matrix3x4_t(
				float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23)
			{
				m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
				m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
				m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
			}
			void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
			{
				m_flMatVal[0][0] = xAxis.X; m_flMatVal[0][1] = yAxis.X; m_flMatVal[0][2] = zAxis.X; m_flMatVal[0][3] = vecOrigin.X;
				m_flMatVal[1][0] = xAxis.Y; m_flMatVal[1][1] = yAxis.Y; m_flMatVal[1][2] = zAxis.Y; m_flMatVal[1][3] = vecOrigin.Y;
				m_flMatVal[2][0] = xAxis.Z; m_flMatVal[2][1] = yAxis.Z; m_flMatVal[2][2] = zAxis.Z; m_flMatVal[2][3] = vecOrigin.Z;
			}

			matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
			{
				Init(xAxis, yAxis, zAxis, vecOrigin);
			}
			float *operator[](int i)
			{
				return m_flMatVal[i];
			}
			const float *operator[](int i) const
			{
				return m_flMatVal[i];
			}
			float *Base()
			{
				return &m_flMatVal[0][0];
			}
			const float *Base() const
			{
				return &m_flMatVal[0][0];
			}

			float m_flMatVal[3][4];
		};



	}
}
