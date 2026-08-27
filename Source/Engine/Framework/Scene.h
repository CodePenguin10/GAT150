#pragma once
#include "Actor.h"
#include <vector>
#include <string>
#include <memory>

namespace nu 
{
	class Scene
	{
	public:
		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		void Update(float dt);
		bool Load(const std::string& sceneName);

		void Draw(const class Renderer& renderer);

		template<typename T>
		T* GetActorByName(const std::string& name);

		void SetGame(class Game* game) { m_game = game; }
		class Game* GetGame() { return m_game; }

	private:
		std::vector<std::unique_ptr<Actor>> m_actors;
		std::vector<std::unique_ptr<Actor>> m_pendingActors;

		class Game* m_game;

		void UpdateCollisions();
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			T* actorT = dynamic_cast<T*>(actor.get());
			if (actorT && actor->m_name == name)
			{
				return actorT;
			}
		}

		return nullptr;
	}
}
