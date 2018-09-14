#include "SDK.h"

namespace Mythcore
{
	using namespace Mythcore::CSGOSDK;

	namespace Math
	{
		Vector::Vector()
		{
			this->X = 0.0f;
			this->Y = 0.0f;
			this->Z = 0.0f;
		}

		Vector::Vector(float _X, float _Y, float _Z)
		{
			this->X = _X;
			this->Y = _Y;
			this->Z = _Z;
		}

		Vector Vector::operator+ (const Vector &A)
		{
			return Vector(this->X + A.X, this->Y + A.Y, this->Z + A.Z);
		}

		Vector Vector::operator+ (const float A)
		{
			return Vector(this->X + A, this->Y + A, this->Z + A);
		}

		Vector Vector::operator+= (const Vector &A)
		{
			this->X += A.X;
			this->Y += A.Y;
			this->Z += A.Z;
			return *this;
		}

		Vector Vector::operator+= (const float A)
		{
			this->X += A;
			this->Y += A;
			this->Z += A;
			return *this;
		}

		Vector Vector::operator- (const Vector &A)
		{
			return Vector(this->X - A.X, this->Y - A.Y, this->Z - A.Z);
		}

		Vector Vector::operator- (const float A)
		{
			return Vector(this->X - A, this->Y - A, this->Z - A);
		}

		Vector Vector::operator-= (const Vector &A)
		{
			this->X -= A.X;
			this->Y -= A.Y;
			this->Z -= A.Z;
			return *this;
		}

		Vector Vector::operator-= (const float A)
		{
			this->X -= A;
			this->Y -= A;
			this->Z -= A;
			return *this;
		}

		Vector Vector::operator* (const Vector &A)
		{
			return Vector(this->X * A.X, this->Y * A.Y, this->Z * A.Z);
		}

		Vector Vector::operator* (const float A)
		{
			return Vector(this->X * A, this->Y * A, this->Z * A);
		}

		Vector Vector::operator*= (const Vector &A)
		{
			this->X *= A.X;
			this->Y *= A.Y;
			this->Z *= A.Z;
			return *this;
		}

		Vector Vector::operator*= (const float A)
		{
			this->X *= A;
			this->Y *= A;
			this->Z *= A;
			return *this;
		}

		Vector Vector::operator/ (const Vector &A)
		{
			return Vector(this->X / A.X, this->Y / A.Y, this->Z / A.Z);
		}

		Vector Vector::operator/ (const float A)
		{
			return Vector(this->X / A, this->Y / A, this->Z / A);
		}

		Vector Vector::operator/= (const Vector &A)
		{
			this->X /= A.X;
			this->Y /= A.Y;
			this->Z /= A.Z;
			return *this;
		}

		Vector Vector::operator/= (const float A)
		{
			this->X /= A;
			this->Y /= A;
			this->Z /= A;
			return *this;
		}

		bool Vector::operator== (const Vector &A)
		{
			if (this->X == A.X
				&& this->Y == A.Y
				&& this->Z == A.Z)
				return true;

			return false;
		}

		bool Vector::operator!= (const Vector &A)
		{
			if (this->X != A.X
				|| this->Y != A.Y
				|| this->Z != A.Z)
				return true;

			return false;
		}

		bool Vector::IsValid()
		{
			return *this != Vector(0, 0, 0);
		}

		FLOAT fScreenX, fScreenY;

		BOOL ScreenTransform(CONST Vector& point, OUT Vector& screen)
		{
			const auto& worldToScreen = pEngine->WorldToScreenMatrix();
			screen.X = worldToScreen.m[0][0] * point.X + worldToScreen.m[0][1] * point.Y + worldToScreen.m[0][2] * point.Z + worldToScreen.m[0][3];
			screen.Y = worldToScreen.m[1][0] * point.X + worldToScreen.m[1][1] * point.Y + worldToScreen.m[1][2] * point.Z + worldToScreen.m[1][3];

			FLOAT w;
			w = worldToScreen.m[3][0] * point.X + worldToScreen.m[3][1] * point.Y + worldToScreen.m[3][2] * point.Z + worldToScreen.m[3][3];
			screen.Z = 0.0f;

			BOOL behind = FALSE;
			if (w < 0.001f)
			{
				behind = TRUE;
				screen.X *= 100000;
				screen.Y *= 100000;
			}
			else
			{
				FLOAT invw = 1.0f / w;
				screen.X *= invw;
				screen.Y *= invw;
			}

			return behind;
		}

		BOOL WorldToScreen(CONST Vector &origin, OUT Vector &screen)
		{
			BOOL bRet = FALSE;

			if (!ScreenTransform(origin, screen))
			{
				INT width, height;
				pEngine->GetScreenSize(width, height);

				fScreenX = width / 2;
				fScreenY = height / 2;

				fScreenX += 0.5f * screen.X * width + 0.5f;
				fScreenY -= 0.5f * screen.Y * height + 0.5f;

				screen.X = fScreenX;
				screen.Y = fScreenY;

				bRet = TRUE;
			}

			return bRet;
		}


		void CalculateAngles(Vector &src, Vector &dst, Vector &angles)
		{
			Vector delta = Vector((src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]));
			double hyp = sqrtf(delta[0] * delta[0] + delta[1] * delta[1]);
			angles[0] = atan(delta[2] / hyp)        *(180.0 / M_PI);
			angles[1] = atan(delta[1] / delta[0])    *(180.0 / M_PI);
			angles[2] = 0.0f;

			if (delta[0] >= 0.0)
			{
				angles[1] += 180.0f;
			}
		}

		void MakeVector(Vector & angle, Vector& vec)
		{
			float pitch;
			float yaw;
			float tmp;

			pitch = (float)(angle[0] * M_PI / 180);
			yaw = (float)(angle[1] * M_PI / 180);
			tmp = (float)cos(pitch);

			vec[0] = (float)(-tmp * -cos(yaw));
			vec[1] = (float)(sin(yaw)*tmp);
			vec[2] = (float)-sin(pitch);
		}

		float CalculateFov(Vector Angles, Vector Source, Vector Dst)
		{
			Vector ang, aim;
			float fov;
			CalculateAngles(Source, Dst, ang);
			MakeVector(Angles, aim);
			MakeVector(ang, ang);
			float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
			float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
			float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
			fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / 3.14159265358979323846);
			return fov;
		}


		void AnglesToVector(const Vector &angles, Vector *forward, Vector *right, Vector *up)
		{
			float angle;
			static float sr, sp, sy, cr, cp, cy, cpi = static_cast<float>(M_PI * 2 / 360);

			angle = angles.Y * cpi;
			sy = sin(angle);
			cy = cos(angle);
			angle = angles.X * cpi;
			sp = sin(angle);
			cp = cos(angle);
			angle = angles.Z * cpi;
			sr = sin(angle);
			cr = cos(angle);

			if (forward)
			{
				forward->X = cp*cy;
				forward->Y = cp*sy;
				forward->Z = -sp;
			}

			if (right)
			{
				right->X = (-1 * sr*sp*cy + -1 * cr*-sy);
				right->Y = (-1 * sr*sp*sy + -1 * cr*cy);
				right->Z = -1 * sr*cp;
			}

			if (up)
			{
				up->X = (cr*sp*cy + -sr*-sy);
				up->Y = (cr*sp*sy + -sr*cy);
				up->Z = cr*cp;
			}
		}

		void VectorToAngles(Vector *forward, Vector *angles)
		{
			float   tmp, yaw, pitch;

			if (forward->Y == 0 && forward->X == 0)
			{
				yaw = 0;
				if (forward->Z > 0)
					pitch = 90.0;
				else
					pitch = 270.0;
			}
			else
			{
				yaw = (float)(atan2(forward->Y, forward->X) * 180.0 / M_PI);

				if (yaw < 0) yaw += 360.0;

				tmp = (float)sqrt(forward->X*forward->X + forward->Y*forward->Y);

				pitch = (float)(atan2(forward->Z, tmp) * 180 / M_PI);
			}

			angles->X = -pitch;
			angles->Y = yaw;
			angles->Z = 0;
		}


		void AngleVectors(const Vector &angles, Vector *forward)
		{
			float	sp, sy, cp, cy;

			sy = sin(DEG2RAD(angles[1]));
			cy = cos(DEG2RAD(angles[1]));
			sp = sin(DEG2RAD(angles[0]));
			cp = cos(DEG2RAD(angles[0]));

			forward->X = cp*cy;
			forward->Y = cp*sy;
			forward->Z = -sp;
		}


		//////////////////////////////////////////////////////////////////////////

		void NormalizeAngles(Vector & angles)
		{
			int i;

			// Normalize angles to -180 to 180 range
			for (i = 0; i < 3; i++)
			{
				if (angles[i] > 180.0)
				{
					angles[i] -= 360.0;
				}
				else if (angles[i] < -180.0)
				{
					angles[i] += 360.0;
				}
			}
		}


		void ClampAngles(Vector & viewangles)
		{
			if (viewangles.X > 89.0f)
			{
				viewangles.X = 89.0f;
			}

			if (viewangles.X < -89.0f)
			{
				viewangles.X = -89.0f;
			}
		}

		void AntiUntrustedYaw(Vector & viewangles)
		{
			if (viewangles.Y > 180.0f)
				viewangles.Y -= 360.0f;

			if (viewangles.Y < -180.0f)
				viewangles.Y += 360.0f;

			if (viewangles.Y > 180.0f || viewangles.Y < -180.0f)
				AntiUntrustedYaw(viewangles);
		}
	}
}