#pragma once
#include "ZonaiMath.h"

namespace Zonai
{
	class Transform
	{
	private:
		Transform* parent_;
		Zonai::Math::Vector3D position_;
		Zonai::Math::Quaternion rotation_;
		Zonai::Math::Vector3D scale_;
	
	public:
#pragma region Property
		__declspec(property(put = SetParent, get = GetParent)) Transform* parent;

		/// <summary>
		/// 월드 스페이스 트랜스폼 정보
		/// </summary>
		__declspec(property(put = SetWorldPosition, get = GetWorldPosition)) Zonai::Math::Vector3D position;
		__declspec(property(put = SetWorldRotation, get = GetWorldRotation)) Zonai::Math::Quaternion rotation;
		__declspec(property(put = SetWorldEulerAngles, get = GetWorldEulerAngles)) Zonai::Math::Vector3D eulerAngles;
		__declspec(property(put = SetWorldScale, get = GetWorldScale)) Zonai::Math::Vector3D scale;

		/// <summary>
		/// 로컬 스페이스 트랜스폼 정보
		/// </summary>
		__declspec(property(put = SetLocalPosition, get = GetLocalPosition)) Zonai::Math::Vector3D localPosition;
		__declspec(property(put = SetLocalRotation, get = GetLocalRotation)) Zonai::Math::Quaternion localRotation;
		__declspec(property(put = SetLocalEulerAngles, get = GetLocalEulerAngles)) Zonai::Math::Vector3D localEulerAngles;
		__declspec(property(put = SetLocalScale, get = GetLocalScale)) Zonai::Math::Vector3D localScale;

		/// <summary>
		/// 월드 스페이스 정보
		/// </summary>
		__declspec(property(put = SetRight, get = GetRight)) Zonai::Math::Vector3D right;			// x
		__declspec(property(put = SetUp, get = GetUp)) Zonai::Math::Vector3D up;					// y
		__declspec(property(put = SetForward, get = GetForward)) Zonai::Math::Vector3D forward;	// z

		__declspec(property(get = GetLocalTransform)) Zonai::Math::Matrix4x4 localTransform;
		__declspec(property(get = GetWorldTransform)) Zonai::Math::Matrix4x4 worldTransform;
#pragma endregion Property

#pragma region Get
		Transform* GetParent() noexcept;

		const Zonai::Math::Vector3D& GetLocalPosition() noexcept;
		const Zonai::Math::Quaternion& GetLocalRotation() noexcept;
		const Zonai::Math::Vector3D GetLocalEulerAngles() noexcept;
		const Zonai::Math::Vector3D& GetLocalScale() noexcept;

		const Zonai::Math::Vector3D GetWorldPosition() noexcept;
		const Zonai::Math::Quaternion GetWorldRotation() noexcept;
		const Zonai::Math::Vector3D GetWorldEulerAngles() noexcept;
		const Zonai::Math::Vector3D GetWorldScale() noexcept;

		const Zonai::Math::Vector3D GetRight() noexcept;
		const Zonai::Math::Vector3D GetUp() noexcept;
		const Zonai::Math::Vector3D GetForward() noexcept;

		const Zonai::Math::Matrix4x4 GetLocalTransform() noexcept;
		const Zonai::Math::Matrix4x4 GetWorldTransform() noexcept;
#pragma endregion Get

#pragma region Set
		void SetParent(Transform*) noexcept;

		void SetLocalPosition(const Zonai::Math::Vector3D&) noexcept;
		void SetLocalRotation(const Zonai::Math::Quaternion&) noexcept;
		void SetLocalEulerAngles(const Zonai::Math::Vector3D&) noexcept;
		void SetLocalScale(const Zonai::Math::Vector3D&) noexcept;

		void SetWorldPosition(const Zonai::Math::Vector3D&) noexcept;
		void SetWorldRotation(const Zonai::Math::Quaternion&) noexcept;
		void SetWorldEulerAngles(const Zonai::Math::Vector3D&) noexcept;
		void SetWorldScale(const Zonai::Math::Vector3D&) noexcept;

		void SetRight(const Zonai::Math::Vector3D&) noexcept;
		void SetUp(const Zonai::Math::Vector3D&) noexcept;
		void SetForward(const Zonai::Math::Vector3D&) noexcept;
#pragma endregion Set
	};
}

