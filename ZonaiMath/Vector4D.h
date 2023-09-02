#pragma once
#include <smmintrin.h>
#include <sal.h>

namespace ZonaiMath
{
	class Vector3D;
	class Matrix1x4;
	class Matrix4x4;
	class Quaternion;

	class Vector4D
	{
	public:
		/// <summary>
			/// Ư�� ��� �Լ�
			/// </summary>
		constexpr Vector4D() noexcept :
			e{}
		{}
		constexpr Vector4D(__m128 _m) noexcept :
			m{ _m }
		{}
		constexpr Vector4D(float _a) noexcept :
			e{ _a, _a, _a, _a }
		{}
		constexpr Vector4D(float _x, float _y, float _z, float _w) noexcept :
			e{ _x, _y, _z, _w }
		{}
		constexpr Vector4D(const Vector4D& other) noexcept = default;
		constexpr Vector4D(Vector4D&& other) noexcept = default;
		constexpr Vector4D(_In_reads_(4) const float* _arr) noexcept :
			e{ _arr[0], _arr[1], _arr[2], _arr[3] }
		{}
		Vector4D(const Vector3D&, const float) noexcept;
		~Vector4D() noexcept = default;

		constexpr Vector4D& operator= (const Vector4D&) noexcept = default;
		constexpr Vector4D& operator= (Vector4D&&) noexcept = default;

		explicit operator Matrix1x4() noexcept;
		explicit operator Quaternion() noexcept;

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float e[4];
			__m128 m;
		};

		static const Vector4D Zero;

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		Vector4D Cross(const Vector4D&) const noexcept;
		float Dot(const Vector4D&) const noexcept;
		float FastInvSqrt(float) const noexcept;			// ��� �� �Լ��� ���⿡ ������� �� ������..
		Vector4D& Normalize() noexcept;
		Vector4D Normalized() const noexcept;

		// Vector3D ������� ó���ϰ� ���� ��
		float Dot3(const Vector4D&) const noexcept;
		Vector4D& Normalize3() noexcept;
		Vector4D Normalized3() const noexcept;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Vector4D& operator += (const Vector4D&) noexcept;
		Vector4D& operator -= (const Vector4D&) noexcept;

		Vector4D operator + (const Vector4D&) const noexcept;
		Vector4D operator - (const Vector4D&) const noexcept;
		Vector4D operator - () const noexcept;

		Vector4D& operator *= (const float) noexcept;
		Vector4D& operator /= (const float) noexcept;

		Vector4D operator * (const float) const noexcept;
		Vector4D operator / (const float) const noexcept;

		Vector4D& operator *= (const Matrix4x4&) noexcept;
		Vector4D operator * (const Matrix4x4&) const noexcept;

		bool operator == (const Vector4D&) const noexcept;
	};
	
	const Vector4D Vector4D::Zero = {};
}

