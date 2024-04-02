#include <cmath>
#include <utility>

#include "Vector4D.h"


#include "Quaternion.h"


namespace Zonai::Math
{
	Quaternion::operator Vector4D() noexcept
	{
		return Vector4D{ x, y, z, w };
	}

	float Quaternion::Length() const noexcept
	{
		return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(m, m, 0xff)));
	}

	float Quaternion::LengthSquare() const noexcept
	{
		return _mm_cvtss_f32(_mm_dp_ps(m, m, 0xff));
	}

	float Quaternion::FastInvSqrt(float number) const noexcept
	{
		return _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set_ps1(number)));
	}

	/// <summary>
	/// ����� ����
	/// </summary>
	float Quaternion::Dot(const Quaternion& other) const noexcept
	{
		return _mm_cvtss_f32(_mm_dp_ps(this->m, other.m, 0xff));
	}

	/// <summary>
	/// ����� �ӷ�
	/// </summary>
	Quaternion Quaternion::Conjugate() const noexcept
	{
		return Quaternion{ w, -x, -y, -z };
	}

	/// <summary>
	/// ����� ����
	/// </summary>
	Quaternion Quaternion::Inverse() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0.0f)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

		return Quaternion
		(
			w * invSqrt,
			-x * invSqrt,
			-y * invSqrt,
			-z * invSqrt
		);
	}

	Quaternion& Quaternion::Normalize() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0.0f)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

		this->m = _mm_mul_ps(
			this->m,
			_mm_set_ps1(invSqrt)
		);

		return *this;
	}

	Quaternion Quaternion::Normalized() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return Quaternion(*this);
		}

		float invSqrt = FastInvSqrt(temp);

		Quaternion q{ *this };

		q.m = _mm_mul_ps(
			this->m,
			_mm_set_ps1(invSqrt)
		);

		return q;
	}

	/// <summary>
	/// ����� ����
	/// </summary>
	Quaternion& Quaternion::operator+=(const Quaternion& other) noexcept
	{
		this->m = _mm_add_ps(this->m, other.m);
		return *this;
	}

	/// <summary>
	/// ����� ����
	/// </summary>
	Quaternion& Quaternion::operator-=(const Quaternion& other) noexcept
	{
		this->m = _mm_sub_ps(this->m, other.m);
		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& other) const noexcept
	{
		Quaternion temp(*this);
		return temp += other;
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const noexcept
	{
		Quaternion temp(*this);
		return temp -= other;
	}

	Quaternion Quaternion::operator-() const noexcept
	{
		return Quaternion
		(
			-this->w,
			-this->x,
			-this->y,
			-this->z
		);
	}

	/// <summary>
	/// ����� ����
	/// </summary>
	Quaternion& Quaternion::operator*=(const Quaternion& other) noexcept
	{
		// �ع��� ��
		float newW =
			this->w * other.w -
			this->x * other.x -
			this->y * other.y -
			this->z * other.z;

		float newX =
			this->w * other.x +
			this->x * other.w +
			this->y * other.z -
			this->z * other.y;

		float newY =
			this->w * other.y -
			this->x * other.z +
			this->y * other.w +
			this->z * other.x;

		float newZ =
			this->w * other.z +
			this->x * other.y -
			this->y * other.x +
			this->z * other.w;

		this->w = newW;
		this->x = newX;
		this->y = newY;
		this->z = newZ;

		return *this;
	}

	/// <summary>
	/// ����� ������
	/// </summary>
	Quaternion& Quaternion::operator/=(const Quaternion& other) noexcept
	{
		Quaternion conjugate = other.Conjugate();
		float temp = other.Length();

		/// ����� �������� �ش� ������� �ӷ��� ���ϰ�
		*this *= conjugate;

		/// ũ���� ������ ���� �Ͱ� ����.
		*this /= temp;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const noexcept
	{
		Quaternion result = *this;
		result *= other;
		return result;
	}

	Quaternion Quaternion::operator/(const Quaternion& other) const noexcept
	{
		Quaternion result = *this;
		result /= other;
		return result;
	}

	/// <summary>
	/// ����� ��Į�� ����
	/// </summary>
	Quaternion& Quaternion::operator*=(const float n) noexcept
	{
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(n));
		return *this;
	}

	/// <summary>
	/// ����� ��Į�� ������
	/// </summary>
	Quaternion& Quaternion::operator/=(const float n) noexcept
	{
		this->m = _mm_div_ps(this->m, _mm_set_ps1(n));
		return *this;
	}

	Quaternion Quaternion::operator*(const float n) const noexcept
	{
		Quaternion result(*this);

		return result *= n;
	}

	Quaternion Quaternion::operator/(const float n) const noexcept
	{
		Quaternion result(*this);

		return result /= n;
	}

	bool Quaternion::operator==(const Quaternion& other) const noexcept
	{
		return (this->w == other.w && this->x == other.x && this->y == other.y && this->z == other.z);
	}


	Quaternion operator*=(const float n, Quaternion& other) noexcept
	{
		return other *= n;
	}

	Quaternion operator/=(const float n, Quaternion& other) noexcept
	{
		return other /= n;
	}

	Quaternion operator*(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		return result *= n;
	}

	Quaternion operator/(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		return result /= n;
	}
}