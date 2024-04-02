#pragma once
#include <sal.h>

namespace Zonai::Math
{
	class Vector2D
	{
	public:
		constexpr Vector2D() noexcept : e{}
		{}
		constexpr Vector2D(float _a) noexcept :
			e{ _a, _a }
		{}
		constexpr Vector2D(float _x, float _y) noexcept :
			e{ _x, _y }
		{}
		constexpr Vector2D(const Vector2D& other) noexcept = default;
		constexpr Vector2D(Vector2D&& other) noexcept = default;
		constexpr Vector2D(_In_reads_(2) const float* arr) noexcept :
			e{ arr[0], arr[1] }
		{}
		~Vector2D() noexcept = default;

		constexpr Vector2D& operator = (const Vector2D&) noexcept = default;
		constexpr Vector2D& operator = (Vector2D&&) noexcept = default;

		union
		{
			struct
			{
				float x, y;
			};
			float e[2];
		};

		static const Vector2D Zero;

		/// ���� �Լ�
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		float Cross(const Vector2D&) const noexcept;
		float Dot(const Vector2D&) const noexcept;
		float FastInvSqrt(float number) const noexcept;
		Vector2D& Normalize() noexcept;
		Vector2D Normalized() const noexcept;


		/// ������ �����ε�
		Vector2D& operator += (const Vector2D&) noexcept;
		Vector2D& operator -= (const Vector2D&) noexcept;

		Vector2D operator + (const Vector2D&) const noexcept;
		Vector2D operator - () const noexcept;
		Vector2D operator - (const Vector2D&) const noexcept;

		Vector2D& operator*= (float) noexcept;
		Vector2D& operator /= (float) noexcept;

		Vector2D operator * (float) noexcept;
		Vector2D operator / (float) noexcept;

		friend Vector2D operator* (float, const Vector2D&) noexcept;	// ���� ��Į�� ��

		bool operator == (const Vector2D&) const noexcept;			// ���� �����ΰ�?
	};

	Vector2D operator* (float, const Vector2D&) noexcept;

	const Vector2D Vector2D::Zero = {};
}