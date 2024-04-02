#pragma once
#include <smmintrin.h>

namespace Zonai::Math
{
	class Vector4D;

	class Quaternion
	{
	public:
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Quaternion() noexcept :
			m{}
		{}
		constexpr Quaternion(float _w, float _x, float _y, float _z) noexcept :
			x(_x), y(_y), z(_z), w(_w)
		{}
		constexpr Quaternion(const Quaternion&) noexcept = default;
		constexpr Quaternion(Quaternion&&) noexcept = default;
		~Quaternion() noexcept = default;

		constexpr Quaternion& operator= (const Quaternion&) noexcept = default;
		constexpr Quaternion& operator= (Quaternion&&) noexcept = default;

		explicit operator Vector4D() noexcept;

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct
			{
				float w, x, y, z;
			};
			float e[4];
			__m128 m;
		};

		static const Quaternion Zero;
		static const Quaternion Identity;

		/// <summary>
		/// ���ʹϾ� �Լ�
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		float FastInvSqrt(float) const noexcept;
		float Dot(const Quaternion&) const noexcept;

		Quaternion Conjugate() const noexcept;
		Quaternion Inverse() const noexcept;
		Quaternion& Normalize() noexcept;
		Quaternion Normalized() const noexcept;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Quaternion& operator += (const Quaternion&) noexcept;
		Quaternion& operator -= (const Quaternion&) noexcept;

		Quaternion operator + (const Quaternion&) const noexcept;
		Quaternion operator - (const Quaternion&) const noexcept;
		Quaternion operator - () const noexcept;

		Quaternion& operator *= (const Quaternion&) noexcept;
		Quaternion& operator /= (const Quaternion&) noexcept;

		Quaternion operator * (const Quaternion&) const noexcept;
		Quaternion operator / (const Quaternion&) const noexcept;

		Quaternion& operator *= (const float) noexcept;
		Quaternion& operator /= (const float) noexcept;

		Quaternion operator * (const float) const noexcept;
		Quaternion operator / (const float) const noexcept;

		friend Quaternion operator *= (const float, const Quaternion&) noexcept;
		friend Quaternion operator /= (const float, const Quaternion&) noexcept;

		friend Quaternion operator * (const float, const Quaternion&) noexcept;
		friend Quaternion operator / (const float, const Quaternion&) noexcept;

		bool operator == (const Quaternion&) const noexcept;
	};

	Quaternion operator *= (const float, const Quaternion&) noexcept;
	Quaternion operator /= (const float, const Quaternion&) noexcept;
	Quaternion operator * (const float, const Quaternion&) noexcept;
	Quaternion operator / (const float, const Quaternion&) noexcept;

	const Quaternion Quaternion::Zero = { 0.f, 0.f, 0.f, 0.f };
	const Quaternion Quaternion::Identity = { 1.f, 0.f, 0.f, 0.f };
}
