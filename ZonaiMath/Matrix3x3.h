#pragma once
#include "Matrix1x3.h"

namespace ZonaiMath
{
	class Vector3D;
	class Matrix1x3;

	class Matrix3x3
	{
	public:
		/// <summary>
	/// Ư�� ��� �Լ�
	/// </summary>
		constexpr Matrix3x3() noexcept :
			e{}
		{}
		constexpr Matrix3x3(
			float _e00, float _e01, float _e02,
			float _e10, float _e11, float _e12,
			float _e20, float _e21, float _e22) noexcept :
			e
			{
				_e00, _e01, _e02,
				_e10, _e11, _e12,
				_e20, _e21, _e22
			}
		{}
		constexpr Matrix3x3(
			const Matrix1x3& _m1,
			const Matrix1x3& _m2,
			const Matrix1x3& _m3) noexcept :
			e
			{
				_m1.e00, _m1.e01, _m1.e02,
				_m2.e00, _m2.e01, _m2.e02,
				_m3.e00, _m3.e01, _m3.e02,
			}
		{}
		constexpr Matrix3x3(const Matrix3x3&) noexcept = default;
		constexpr Matrix3x3(Matrix3x3&&) noexcept = default;
		~Matrix3x3() noexcept = default;

		constexpr Matrix3x3& operator= (const Matrix3x3&) noexcept = default;
		constexpr Matrix3x3& operator= (Matrix3x3&&) noexcept = default;

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct
			{
				float 
					e00, e01, e02, 
					e10, e11, e12, 
					e20, e21, e22;
			};
			struct
			{
				float 
					Ixx, Ixy, Ixz, 
					Iyx, Iyy, Iyz, 
					Izx, Izy, Izz;
			};
			float e[3][3];
			Matrix1x3 r[3];
		};

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		static const Matrix3x3 Zero;
		static const Matrix3x3 Identity;

		/// <summary>
		/// ��� �Լ�
		/// </summary>
		float Determinant() noexcept;
		Matrix3x3 Transpose() noexcept;
		Matrix3x3 Inverse() noexcept;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Matrix3x3 operator+ (const Matrix3x3&) const noexcept;
		Matrix3x3& operator+= (const Matrix3x3&) noexcept;
		Matrix3x3 operator- (const Matrix3x3&) const noexcept;
		Matrix3x3& operator-= (const Matrix3x3&) noexcept;
		Matrix3x3 operator* (const Matrix3x3&) const noexcept;
		Matrix3x3& operator*= (const Matrix3x3&) noexcept;

		bool operator== (const Matrix3x3&) const noexcept;
	};

	const Matrix3x3 Matrix3x3::Zero = {};
	const Matrix3x3 Matrix3x3::Identity = {
				1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				0.f, 0.f, 1.f,
			};
}
