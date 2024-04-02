#pragma once


namespace Zonai
{
	class Transform;
	class Entity;
	class Collider;
	class Collision;

	class Component abstract
	{
	public:
		Component() noexcept = default;
		virtual ~Component() noexcept = default;

	public:
		Entity* entity;
		Transform* transform;

	public:
		virtual void Awake() noexcept;
		virtual void OnEnable() noexcept;

		virtual void Start() noexcept;

		virtual void FixedUpdate() noexcept;
		virtual void Update() noexcept;
		virtual void LateUpdate() noexcept;

		virtual void OnTriggerEnter(Collider*) noexcept;
		virtual void OnTriggerStay(Collider*) noexcept;
		virtual void OnTriggerExit(Collider*) noexcept;

		virtual void OnCollisionEnter(Collision*) noexcept;
		virtual void OnCollisionStay(Collision*) noexcept;
		virtual void OnCollisionExit(Collision*) noexcept;

		virtual void OnDisable() noexcept;
		virtual void OnDestroy() noexcept;
	};
}

/*
���� ���ο� �ִ� ������Ʈ�� ���� �����ϴ� ������� �ϸ� ���� �� ����.
*/