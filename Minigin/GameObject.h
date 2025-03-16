#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Transform.h"
namespace dae
{
	class Command;
	class BaseComponent;
	class Subject;

	class GameObject final 
	{
	public:
		GameObject();

		// Can optionally take ownership when used with std::move
		GameObject(Transform transform);

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// Parent can be null (meaning the scene is the parent, 'tis a root game object)
		// Don't keep world position by default 
		void SetParent(GameObject* pParent, bool keepWorldTransform = false);
		GameObject* GetParent();

		void FixedUpdate();
		void Update(float deltaTime);
		void Render() const;

		void SetLocalTransform(const Transform& transform);
		const Transform& GetLocalTransform() const;
		const Transform& GetWorldTransform();

		bool IsChild(GameObject* pObj) const;

		void AddCommandReference(Command* m_Command);

		std::vector<GameObject*>& GetChildren();

		// Used for subscribing observers
		Subject* GetSubject() const;

		// The component returned is owned by the GameObject, there is no need to free the pointer.
		// However, you do have to check if the component has been removed in PostUpdate.
		template<typename ComponentType>
		requires std::derived_from<ComponentType, BaseComponent>
		[[nodiscard]] ComponentType* GetComponent() const {
			ComponentType* resultComponent{};
			std::ignore = std::ranges::find_if(m_components, [&resultComponent](auto& basecomponent) {
				resultComponent = dynamic_cast<ComponentType*>(basecomponent.get());
				return resultComponent != nullptr;
			});

			return resultComponent;
		}

		// Creates a component, similar to std::make_unique
		template<typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, BaseComponent>
		ComponentType* AddComponent(Args&&... args) {
			std::unique_ptr<ComponentType> component{ std::make_unique<ComponentType>(*this, std::forward<Args>(args)...) };
			ComponentType* rComponent{ component.get() }; // Get a non-owning pointer
			m_components.push_back(std::move(component));
			return rComponent; // Return a pointer to the component that was created
		}

		template<typename ComponentType>
		requires std::derived_from<ComponentType, BaseComponent>
		[[nodiscard]] bool HasComponent() const {
			auto it = std::ranges::find_if(m_components, [](const auto& basecomponent) {
				return dynamic_cast<ComponentType*>(basecomponent.get()) != nullptr;
			});

			return it != m_components.end();
		}
	private:
		void MarkTransformDirty();
		void UpdateWorldTransform();
		void RemoveDestroyedComponents();

		// The transform for this game object
		Transform m_localTransform{};
		Transform m_worldTransform{};
		bool m_transformDirty{ true };

		// GameObjects won't have that many components, thus having a single vector of BaseComponents is fine.
		std::vector<std::unique_ptr<BaseComponent>> m_components;

		// Objects are not owned by GameObject, they're just references
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren;

		// Game objects may receive ActorCommandsd that refer to them
		// However, these commands need to be notified when their object has been removed
		// such that they can be unbound. Thus they are kept over here.
		std::vector<Command*> m_boundCommands;

		// Subjects can be used for all events, given events are keyed with strings
		std::unique_ptr<Subject> m_subject;
	};
}
