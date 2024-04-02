#include <cmath>

#include "ZonaiMath.h"

namespace Zonai::Math
{
	/// <summary>
	/// ���Ϸ����� ��Ʈ������ ��ȯ
	/// </summary>
	Matrix4x4 ToTranslateMatrix(const Vector3D& _euler) noexcept
	{
		return Matrix4x4
		{
			1.f,		0.f,		0.f,		0.f,
			0.f,		1.f,		0.f,		0.f,
			0.f,		0.f,		1.f,		0.f,
			_euler.x,	_euler.y,	_euler.z,	1.f
		};
	}

	/// <summary>
	/// ������ ��Ʈ������ ��ȯ
	/// </summary>
	Matrix4x4 ToScaleMatrix(const Vector3D& _scl) noexcept
	{
		return Matrix4x4
		{
			_scl.x,		0.f,		0.f,		0.f,
			0.f,		_scl.y,		0.f,		0.f,
			0.f,		0.f,		_scl.z,		0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}

	/// <summary>
	/// ������ ��Ʈ������ ��ȯ
	/// </summary>
	Matrix4x4 ToScaleMatrix(const float _scl) noexcept
	{
		return Matrix4x4
		{
			_scl,		0.f,		0.f,		0.f,
			0.f,		_scl,		0.f,		0.f,
			0.f,		0.f,		_scl,		0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}

	/// <summary>
	/// Ʈ������ ��Ʈ������ ��ȯ
	/// </summary>
	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept
	{
		return ToScaleMatrix(_scl) * ToMatrix4(_rot) * ToTranslateMatrix(_pos);
	}

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const float _scl) noexcept
	{
		return ToScaleMatrix(_scl) * ToMatrix4(_rot) * ToTranslateMatrix(_pos);
	}


	Vector3D DecomposPosition(const Matrix4x4& _mat) noexcept
	{
		return Vector3D(_mat.e30, _mat.e31, _mat.e32);
	}

	Quaternion DecomposRotation(const Matrix4x4& _mat) noexcept
	{
		Vector3D scl{ DecomposScale(_mat) };

		Matrix1x3 row00{ _mat.e00, _mat.e01, _mat.e02 };
		row00 /= scl.x;
		Matrix1x3 row01{ _mat.e10, _mat.e11, _mat.e12 };
		row01 /= scl.y;
		Matrix1x3 row02{ _mat.e20, _mat.e21, _mat.e22 };
		row02 /= scl.z;

		return ToQuaternion({ row00 , row01, row02 });
	}

	Vector3D DecomposScale(const Matrix4x4& _mat) noexcept
	{
		return Vector3D(
			Vector3D(_mat.e00, _mat.e01, _mat.e02).Length(),
			Vector3D(_mat.e10, _mat.e11, _mat.e12).Length(),
			Vector3D(_mat.e20, _mat.e21, _mat.e22).Length()
		);
	}

	/// <summary>
	/// Ʈ������ ��� ����?
	/// </summary>
	void Decompose(const Matrix4x4& _matrix, Vector3D& _pos, Quaternion& _rot, Vector3D& _scl) noexcept
	{
		// ���� ����� ������ ���
		_pos.x = _matrix.r[3].e00;
		_pos.y = _matrix.r[3].e01;
		_pos.z = _matrix.r[3].e02;

		// ���� ����� �� ������ ũ�Ⱑ ������ ��
		_scl.x = Vector3D(_matrix.e00, _matrix.e10, _matrix.e20).Length();
		_scl.y = Vector3D(_matrix.e01, _matrix.e11, _matrix.e21).Length();
		_scl.z = Vector3D(_matrix.e02, _matrix.e12, _matrix.e22).Length();

		// ����ȭ�ؼ� ȸ������ ����
		Matrix4x4 rotationMatrix = _matrix;
		rotationMatrix.r[0] /= _scl.x;
		rotationMatrix.r[1] /= _scl.y;
		rotationMatrix.r[2] /= _scl.z;

		// ȸ�� ����� ���ʹϾ����� ��ȯ
		_rot = ToQuaternion(rotationMatrix);
	}

	/// <summary>
	/// ����� ���� ����
	/// ����ȭ�� �� ���ʹϾ��� �޾� ������.
	/// t�� 1.f ~ 0.f
	/// </summary>
	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		/// Q(t) = start - t * start  + t * end
		/// Q(t)�� ����ȭ���� �ϸ� �ȴ�.

		// Quaternion result{ q1 + (q2 - q1) * t };
		// return result.Normalized();

		return (q1 + (q2 - q1) * t).Normalized();
	}

	/// <summary>
	/// ����� ���� ����
	/// ����ȭ�� �� ���ʹϾ��� �޾� ������.
	/// t�� 1.f ~ 0.f
	/// </summary>
	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		/// Q(t) = 
		/// ( (sin(1 - t) * theta) / sin theta ) * start + 
		/// ( (sin(theta * t) ) / sin theta ) * end
		/// �׸��� ����ȭ

		Quaternion q1N{ q1 };
		Quaternion q2N{ q2 };

		// ������ ������� cos theta
		float cosTheta = q1N.Dot(q2N);

		// cos���� ������ ���ʹϾ� �ϳ��� ����ȭ �Ѵٴµ�
		// �� ������ �𸣰����� ��ư ã�ƺ� ����Ʈ���� �׸� �϶�� ��.
		// ���ʹϾ� ���� ������ 90���� �Ѿ�ϱ� ���� ���ϴ°� �� ª�� ��ζ� �׷��ɱ�
		// ��¥ ���� �𸣰���

		/// ��Ī ���
		/// �� ���ʹϾ� ������ ������ 90������ ũ�ٴ� ��
		/// ���� ���� ��, �� �� ���ȣ�� ���󰡰� �ȴ�.
		/// ���� ª�� ���ȣ�� ���󰡰� �ϱ� ���� ������ ���ϴ� ���ε�
		/// ���ʹϾ𿡼��� q�� -q�� ���� ȸ���� �ǹ��ϱ� ������ ȸ�� ��������� �ƹ��� ������ ����.
		/// ������ ���� ���������� ��ȣ�� �߿��ϴ�
		/// ���� ������ ���ȣ �󿡼� �� ���ʹϾ��� ���� ���ϰ� �մ� ���̱⿡
		/// ��ȣ�� ���� ������ �޶�����.
		if (cosTheta < 0.f)
		{
			q2N = -q2N;
			cosTheta = -cosTheta;
		}

		// cos Theta�� 1�� �Ѿ�� ū�ϳ���!! acos���� NaN�� ���� �����̴�!!!
		// �̰� ������ 1���� �� ����ߴ�
		if (cosTheta > 0.9999f)
		{
			// cosTheta�� 1�̰ų� -1�� ����
			// q1 = q2�ų� ���� �� �ݴ��� �ǹ�
			return Lerp(q1, q2, t);
		}

		// ���ʹϾ� ������ ������ ����
		float theta = std::acos(cosTheta);

		// ������ �� sin theta �̸� ����ص���
		float invSinTheta = 1 / std::sin(theta);

		// ���� ���� �����̴�
		float factorA{ std::sin((1.0f - t) * theta) * invSinTheta };
		float factorB{ std::sin(t * theta) * invSinTheta };

		// Quaternion result{ (factorA * q1N) + (factorB * q2N) };
		// return result.Normalized();
		return ((factorA * q1N) + (factorB * q2N)).Normalized();
	}

	Vector3D VectorRotateFromQuaternion(const Vector3D& _vec, const Quaternion& _q) noexcept
	{
		Quaternion q_con{ _q.Conjugate() };
		Quaternion vec{ 0.f, _vec.x, _vec.y, _vec.z };

		Quaternion result{ _q * vec * q_con };

		return Vector3D(result.x, result.y, result.z);
	}

	/// <summary>
	/// ���͸� ��ǥ�ϴ� ���ͷ� ��ȯ�ϱ� ���� ���ʹϾ��� ��ȯ
	/// </summary>
	Quaternion RotateVectorToVectorQuaternion(const Vector3D& _from, const Vector3D& _to) noexcept
	{
		Vector3D normalizedFrom = _from.Normalized();
		Vector3D normalizedTo = _to.Normalized();

		Vector3D rotationAxis = normalizedFrom.Cross(normalizedTo);

		float rotationAngle = std::acosf(normalizedFrom.Dot(normalizedTo));

		return ToQuaternion(rotationAxis, rotationAngle);
	}

	/// <summary>
	/// ���Ϸ� ���� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Vector3D& _euler) noexcept
	{
		Vector3D eulerRad = _euler * 0.5f;

		float roll = eulerRad.x;        // ��ũ
		float pitch = eulerRad.z;       // ��ƼƩ��
		float yaw = eulerRad.y;         // ���

		// float roll = eulerRad.z;        // 
		// float pitch = eulerRad.x;
		// float yaw = eulerRad.y;

		float c1 = std::cosf(yaw);
		float s1 = std::sinf(yaw);
		float c2 = std::cosf(pitch);
		float s2 = std::sinf(pitch);
		float c3 = std::cosf(roll);
		float s3 = std::sinf(roll);

		float c1c2 = c1 * c2;
		float s1s2 = s1 * s2;

		Quaternion q;

		q.w = c1c2 * c3 - s1s2 * s3;
		q.x = c1c2 * s3 + s1s2 * c3;
		q.y = s1 * c2 * c3 + c1 * s2 * s3;
		q.z = c1 * s2 * c3 - s1 * c2 * s3;

		return q;
	}

	/// <summary>
	/// �ఢ�� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Vector3D& _axis, float _angle) noexcept
	{
		Vector3D axis = _axis.Normalized();
		float halfAngle = _angle * 0.5f;
		float sinhalf = std::sinf(halfAngle);
		float coshalf = std::cosf(halfAngle);

		return Quaternion
		(
			coshalf,
			axis.x * sinhalf,
			axis.y * sinhalf,
			axis.z * sinhalf
		);
	}

	/// <summary>
	/// ȸ�� ����� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Matrix3x3& _rotMatrix) noexcept
	{
		Quaternion quaternion;

		float trace = _rotMatrix.e00 + _rotMatrix.e11 + _rotMatrix.e22;

		if (trace > 0.0f) {
			float s = 0.5f / std::sqrt(trace + 1.0f);
			quaternion.w = 0.25f / s;
			quaternion.x = (_rotMatrix.e21 - _rotMatrix.e12) * s;
			quaternion.y = (_rotMatrix.e02 - _rotMatrix.e20) * s;
			quaternion.z = (_rotMatrix.e10 - _rotMatrix.e01) * s;
		}
		else
		{
			if (_rotMatrix.e00 > _rotMatrix.e11 && _rotMatrix.e00 > _rotMatrix.e22)
			{
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e00 - _rotMatrix.e11 - _rotMatrix.e22);
				quaternion.w = (_rotMatrix.e21 - _rotMatrix.e12) / s;
				quaternion.x = 0.25f * s;
				quaternion.y = (_rotMatrix.e01 + _rotMatrix.e10) / s;
				quaternion.z = (_rotMatrix.e02 + _rotMatrix.e20) / s;
			}
			else if (_rotMatrix.e11 > _rotMatrix.e22) {
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e11 - _rotMatrix.e00 - _rotMatrix.e22);
				quaternion.w = (_rotMatrix.e02 - _rotMatrix.e20) / s;
				quaternion.x = (_rotMatrix.e01 + _rotMatrix.e10) / s;
				quaternion.y = 0.25f * s;
				quaternion.z = (_rotMatrix.e12 + _rotMatrix.e21) / s;
			}
			else {
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e22 - _rotMatrix.e00 - _rotMatrix.e11);
				quaternion.w = (_rotMatrix.e10 - _rotMatrix.e01) / s;
				quaternion.x = (_rotMatrix.e02 + _rotMatrix.e20) / s;
				quaternion.y = (_rotMatrix.e12 + _rotMatrix.e21) / s;
				quaternion.z = 0.25f * s;
			}
		}

		return quaternion;
	}

	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept
	{
		Quaternion q;
		float r22 = _rotMatrix.e22;
		if (r22 <= 0.f)  // x^2 + y^2 >= z^2 + w^2
		{
			float dif10 = _rotMatrix.e11 - _rotMatrix.e00;
			float omr22 = 1.f - r22;
			if (dif10 <= 0.f)  // x^2 >= y^2
			{
				float fourXSqr = omr22 - dif10;
				float inv4x = 0.5f / sqrtf(fourXSqr);
				q.w = fourXSqr * inv4x;
				q.x = (_rotMatrix.e01 + _rotMatrix.e10) * inv4x;
				q.y = (_rotMatrix.e02 + _rotMatrix.e20) * inv4x;
				q.z = (_rotMatrix.e12 - _rotMatrix.e21) * inv4x;
			}
			else  // y^2 >= x^2
			{
				float fourYSqr = omr22 + dif10;
				float inv4y = 0.5f / sqrtf(fourYSqr);
				q.w = (_rotMatrix.e01 + _rotMatrix.e10) * inv4y;
				q.x = fourYSqr * inv4y;
				q.y = (_rotMatrix.e12 + _rotMatrix.e21) * inv4y;
				q.z = (_rotMatrix.e20 - _rotMatrix.e02) * inv4y;
			}
		}
		else  // z^2 + w^2 >= x^2 + y^2
		{
			float sum10 = _rotMatrix.e11 + _rotMatrix.e00;
			float opr22 = 1.f + r22;
			if (sum10 <= 0.f)  // z^2 >= w^2
			{
				float fourZSqr = opr22 - sum10;
				float inv4z = 0.5f / sqrtf(fourZSqr);
				q.w = (_rotMatrix.e02 + _rotMatrix.e20) * inv4z;
				q.x = (_rotMatrix.e12 + _rotMatrix.e21) * inv4z;
				q.y = fourZSqr * inv4z;
				q.z = (_rotMatrix.e01 - _rotMatrix.e10) * inv4z;
			}
			else  // w^2 >= z^2
			{
				float fourWSqr = opr22 + sum10;
				float inv4w = 0.5f / sqrtf(fourWSqr);
				q.w = (_rotMatrix.e12 - _rotMatrix.e21) * inv4w;
				q.x = (_rotMatrix.e20 - _rotMatrix.e02) * inv4w;
				q.y = (_rotMatrix.e01 - _rotMatrix.e10) * inv4w;
				q.z = fourWSqr * inv4w;
			}
		}

		return q;
	}

	/// <summary>
	/// ���ʹϾ��� ���Ϸ������� �ٲ�
	/// </summary>
	Vector3D ToEuler(const Quaternion& q) noexcept
	{
		// YZX ���Ϸ��� ��ȯ
		float roll, pitch, yaw;

		double sqw = q.w * q.w;
		double sqx = q.x * q.x;
		double sqy = q.y * q.y;
		double sqz = q.z * q.z;
		double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
		double test = q.x * q.y + q.z * q.w;

		if (test > 0.499f * unit)
		{ // singularity at north pole
			yaw = 2.f * std::atan2f(q.x, q.w);
			pitch = PI / 2.f;
			roll = 0.f;
			return  Vector3D(roll, yaw, pitch);
		}

		if (test < -0.499f * unit)
		{ // singularity at south pole
			yaw = -2.f * std::atan2f(q.x, q.w);
			pitch = -PI / 2.f;
			roll = 0.f;
			return  Vector3D(roll, yaw, pitch);
		}

		yaw = std::atan2f(2 * q.y * q.w - 2 * q.x * q.z, sqx - sqy - sqz + sqw);
		pitch = std::asinf(2 * test / unit);
		roll = std::atan2f(2 * q.x * q.w - 2 * q.y * q.z, -sqx + sqy - sqz + sqw);

		return Vector3D(roll, yaw, pitch);
	}

	/// <summary>
	/// ���ʹϾ��� �ఢ���� �ٲ�
	/// </summary>
	Vector4D ToAxisAngle(const Quaternion& _q) noexcept
	{
		float squaredLength = _q.LengthSquare();

		if (squaredLength < Epsilon)
		{
			return Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
		}

		float inverseLength = 1.0f / std::sqrt(squaredLength);
		float angle = 2.0f * std::acos(_q.w);
		float sinAngle = std::sqrt(1.0f - _q.w * _q.w) * inverseLength;

		return Vector4D(_q.x * inverseLength, _q.y * inverseLength, _q.z * inverseLength, angle);
	}

	/// <summary>
	/// ���ʹϾ��� ��ķ� �ٲ�
	/// </summary>
	Matrix3x3 ToMatrix3(const Quaternion& _q) noexcept
	{
		Matrix3x3 matrix;

		const float w2 = _q.w * _q.w;
		const float x2 = _q.x * _q.x;
		const float y2 = _q.y * _q.y;
		const float z2 = _q.z * _q.z;
		const float xy = _q.x * _q.y;
		const float xz = _q.x * _q.z;
		const float yz = _q.y * _q.z;
		const float wx = _q.w * _q.x;
		const float wy = _q.w * _q.y;
		const float wz = _q.w * _q.z;

		matrix.e00 = 1.0f - 2.0f * (y2 + z2);
		matrix.e01 = 2.0f * (xy + wz);
		matrix.e02 = 2.0f * (xz - wy);

		matrix.e10 = 2.0f * (xy - wz);
		matrix.e11 = 1.0f - 2.0f * (x2 + z2);
		matrix.e12 = 2.0f * (yz + wx);

		matrix.e20 = 2.0f * (xz + wy);
		matrix.e21 = 2.0f * (yz - wx);
		matrix.e22 = 1.0f - 2.0f * (x2 + y2);

		return matrix;
	}

	Matrix4x4 ToMatrix4(const Quaternion& _q) noexcept
	{
		Matrix4x4 matrix;

		const float w2 = _q.w * _q.w;
		const float x2 = _q.x * _q.x;
		const float y2 = _q.y * _q.y;
		const float z2 = _q.z * _q.z;
		const float xy = _q.x * _q.y;
		const float xz = _q.x * _q.z;
		const float yz = _q.y * _q.z;
		const float wx = _q.w * _q.x;
		const float wy = _q.w * _q.y;
		const float wz = _q.w * _q.z;

		matrix.e00 = 1.0f - 2.0f * (y2 + z2);
		matrix.e01 = 2.0f * (xy + wz);
		matrix.e02 = 2.0f * (xz - wy);
		matrix.e03 = 0.0f;

		matrix.e10 = 2.0f * (xy - wz);
		matrix.e11 = 1.0f - 2.0f * (x2 + z2);
		matrix.e12 = 2.0f * (yz + wx);
		matrix.e13 = 0.0f;

		matrix.e20 = 2.0f * (xz + wy);
		matrix.e21 = 2.0f * (yz - wx);
		matrix.e22 = 1.0f - 2.0f * (x2 + y2);
		matrix.e23 = 0.0f;

		matrix.e30 = 0.0f;
		matrix.e31 = 0.0f;
		matrix.e32 = 0.0f;
		matrix.e33 = 1.0f;

		return matrix;
	}

	/// <summary>
	/// �ఢ�� ��ķ� �ٲ�
	/// </summary>
	Matrix3x3 ToMatrix3(const Vector3D& _axis, const float _angle) noexcept
	{
		float cos = std::cos(_angle);
		float sin = std::sin(_angle);
		float x = _axis.x;
		float y = _axis.y;
		float z = _axis.z;

		return Matrix3x3(
			cos + x * x * (1 - cos),
			x * y * (1 - cos) - z * sin,
			x * z * (1 - cos) + y * sin,

			y * x * (1 - cos) + z * sin,
			cos + y * y * (1 - cos),
			y * z * (1 - cos) - x * sin,

			z * x * (1 - cos) - y * sin,
			z * y * (1 - cos) + x * sin,
			cos + z * z * (1 - cos)
		);
	}

	Matrix4x4 ToMatrix4(const Vector3D& _axis, const float _angle) noexcept
	{
		float cos = std::cos(_angle);
		float sin = std::sin(_angle);
		float x = _axis.x;
		float y = _axis.y;
		float z = _axis.z;

		return Matrix4x4(
			cos + x * x * (1 - cos),
			x * y * (1 - cos) - z * sin,
			x * z * (1 - cos) + y * sin,
			0.f,

			y * x * (1 - cos) + z * sin,
			cos + y * y * (1 - cos),
			y * z * (1 - cos) - x * sin,
			0.f,

			z * x * (1 - cos) - y * sin,
			z * y * (1 - cos) + x * sin,
			cos + z * z * (1 - cos),
			0.f,

			0.f,
			0.f,
			0.f,
			1.f
		);
	}
}