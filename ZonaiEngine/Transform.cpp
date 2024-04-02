#include "Transform.h"

namespace Zonai
{


#pragma region Get
	Transform* Transform::GetParent() noexcept
	{
		return this->parent_;
	}

	const Zonai::Math::Vector3D& Transform::GetLocalPosition() noexcept
	{
		return this->position_;
	}

	const Zonai::Math::Quaternion& Transform::GetLocalRotation() noexcept
	{
		return this->rotation_;
	}

	const Zonai::Math::Vector3D Transform::GetLocalEulerAngles() noexcept
	{
		return Zonai::Math::ToEuler(this->rotation_);
	}

	const Zonai::Math::Vector3D& Transform::GetLocalScale() noexcept
	{
		return this->scale_;
	}

	const Zonai::Math::Vector3D Transform::GetWorldPosition() noexcept
	{
		if (parent_)
		{
			return this->position_ * this->parent_->GetWorldTransform();
		}
		else
		{
			return this->position_;
		}
	}

	const Zonai::Math::Quaternion Transform::GetWorldRotation() noexcept
	{
		if (parent_)
		{
			return this->rotation_ * this->parent_->GetWorldRotation();
		}
		else
		{
			return this->rotation_;
		}
	}

	const Zonai::Math::Vector3D Transform::GetWorldEulerAngles() noexcept
	{
		return Zonai::Math::ToEuler(this->GetWorldRotation());
	}

	const Zonai::Math::Vector3D Transform::GetWorldScale() noexcept
	{
		if (this->parent_)
		{
			auto& parentScale = this->parent_->GetWorldScale();
			
			return Zonai::Math::Vector3D(
				parentScale.x * this->scale_.x, 
				parentScale.y * this->scale_.y, 
				parentScale.z * this->scale_.z
			);
		}
		else
		{
			return this->scale_;
		}
	}

	const Zonai::Math::Vector3D Transform::GetRight() noexcept
	{
		return this->GetWorldRotation() * Zonai::Math::Vector3D::Right;
	}

	const Zonai::Math::Vector3D Transform::GetUp() noexcept
	{
		return this->GetWorldRotation() * Zonai::Math::Vector3D::Up;
	}

	const Zonai::Math::Vector3D Transform::GetForward() noexcept
	{
		return this->GetWorldRotation() * Zonai::Math::Vector3D::Forward;
	}

	const Zonai::Math::Matrix4x4 Transform::GetLocalTransform() noexcept
	{
		return Zonai::Math::ToTransformMatrix(
			this->position_, 
			this->rotation_, 
			this->scale_
		);
	}

	const Zonai::Math::Matrix4x4 Transform::GetWorldTransform() noexcept
	{
		if (this->parent_)
		{
			return this->GetLocalTransform() * this->parent_->GetWorldTransform();
		}
		else
		{
			return this->GetLocalTransform();
		}
	}
#pragma endregion Get

#pragma region Set
	void Transform::SetParent(Transform* _parent) noexcept
	{
		this->parent_ = _parent;
	}

	void Transform::SetLocalPosition(const Zonai::Math::Vector3D& _pos) noexcept
	{
		this->position_ = _pos;
	}

	void Transform::SetLocalRotation(const Zonai::Math::Quaternion& _rot) noexcept
	{
		this->rotation_ = _rot;
	}

	void Transform::SetLocalEulerAngles(const Zonai::Math::Vector3D& _euler) noexcept
	{
		this->rotation_ = Zonai::Math::ToQuaternion(_euler);
	}

	void Transform::SetLocalScale(const Zonai::Math::Vector3D& _scl) noexcept
	{
		this->scale_ = _scl;
	}

	void Transform::SetWorldPosition(const Zonai::Math::Vector3D& _pos) noexcept
	{
		if (this->parent_)
		{
			this->position_ = _pos * this->parent_->GetWorldTransform().Inverse();
		}
		else
		{
			this->position_ = _pos;
		}
	}

	void Transform::SetWorldRotation(const Zonai::Math::Quaternion& _rot) noexcept
	{
		if (this->parent_)
		{
			this->rotation_ = parent_->GetWorldRotation().Inverse() * _rot;
		}
		else
		{
			this->rotation_ = _rot;
		}
	}

	void Transform::SetWorldEulerAngles(const Zonai::Math::Vector3D& _euler) noexcept
	{
		auto q = Zonai::Math::ToQuaternion(_euler);

		this->SetWorldRotation(q);
	}

	void Transform::SetWorldScale(const Zonai::Math::Vector3D& _scl) noexcept
	{
		if (this->parent_)
		{
			auto s = this->parent_->GetWorldScale();

			this->scale_ = Zonai::Math::Vector3D(
				_scl.x / s.x, 
				_scl.y / s.y, 
				_scl.z / s.z
			);
		}
		else
		{
			this->scale_ = _scl;
		}
	}

	void Transform::SetRight(const Zonai::Math::Vector3D& _right) noexcept
	{
		this->SetWorldRotation(
			Zonai::Math::RotateVectorToVectorQuaternion(
				Zonai::Math::Vector3D::Right, _right
			)
		);
	}

	void Transform::SetUp(const Zonai::Math::Vector3D& _up) noexcept
	{
		this->SetWorldRotation(
			Zonai::Math::RotateVectorToVectorQuaternion(
				Zonai::Math::Vector3D::Up, _up
			)
		);
	}

	void Transform::SetForward(const Zonai::Math::Vector3D& _forward) noexcept
	{
		this->SetWorldRotation(
			Zonai::Math::RotateVectorToVectorQuaternion(
				Zonai::Math::Vector3D::Forward, _forward
			)
		);
	}
#pragma endregion Set
}