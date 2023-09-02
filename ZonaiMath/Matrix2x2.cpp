#include "Matrix2x2.h"

namespace ZonaiMath
{
	float Matrix2x2::Determinant() const noexcept
	{
	}

	ZonaiMath::Matrix2x2 Matrix2x2::Transpose() const noexcept
	{
		return Matrix2x2
		{
			e00, e10,
			e01, e11
		};
	}

	ZonaiMath::Matrix2x2 Matrix2x2::Inverse() const noexcept
	{

	}

	ZonaiMath::Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const noexcept
	{
		return Matrix2x2
		(
			(this->e[0][0] + other.e[0][0]),
			(this->e[0][1] + other.e[0][1]),

			(this->e[1][0] + other.e[1][0]),
			(this->e[1][1] + other.e[1][1])
		);
	}

	ZonaiMath::Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& other) noexcept
	{
		this->e00 += other.e00;
		this->e01 += other.e01;

		this->e10 += other.e10;
		this->e11 += other.e11;

		return *this;
	}

	ZonaiMath::Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const noexcept
	{
		return Matrix2x2
		(
			(this->e[0][0] - other.e[0][0]),
			(this->e[0][1] - other.e[0][1]),

			(this->e[1][0] - other.e[1][0]),
			(this->e[1][1] - other.e[1][1])
		);
	}

	ZonaiMath::Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& other) noexcept
	{
		this->e00 -= other.e00;
		this->e01 -= other.e01;

		this->e10 -= other.e10;
		this->e11 -= other.e11;

		return *this;
	}

	ZonaiMath::Matrix2x2 Matrix2x2::operator*(const Matrix2x2& other) const noexcept
	{
		return Matrix2x2
		(
			(this->e[0][0] * other.e[0][0] + this->e[0][1] * other.e[1][0]),
			(this->e[0][0] * other.e[0][1] + this->e[0][1] * other.e[1][1]),

			(this->e[1][0] * other.e[0][0] + this->e[1][1] * other.e[1][0]),
			(this->e[1][0] * other.e[0][1] + this->e[1][1] * other.e[1][1])
		);
	}

	ZonaiMath::Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& other) noexcept
	{
		(this->e[0][0] * other.e[0][0] + this->e[0][1] * other.e[1][0]);
		(this->e[0][0] * other.e[0][1] + this->e[0][1] * other.e[1][1]);

		(this->e[1][0] * other.e[0][0] + this->e[1][1] * other.e[1][0]);
		(this->e[1][0] * other.e[0][1] + this->e[1][1] * other.e[1][1]);

		return *this;
	}

	ZonaiMath::Matrix2x2 Matrix2x2::operator/(const Matrix2x2& other) const noexcept
	{

	}

	ZonaiMath::Matrix2x2& Matrix2x2::operator/=(const Matrix2x2& other) noexcept
	{

	}

	bool Matrix2x2::operator==(const Matrix2x2& n) noexcept
	{

	}
}