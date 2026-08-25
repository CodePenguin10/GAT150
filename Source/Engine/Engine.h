#pragma once
//Creation
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/MathUtility.h"
#include "Math/Transform.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Core/StringUtility.h"
#include "Serialization/Json.h"

#include "Renderer/Text.h"
#include "Renderer/Texture.h"

#include "Core/Factory.h"

//Systems
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Core/GameTime.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"
#include "Framework/Game.h"
#include "Core/File.h"
#include "Audio/Audio.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourceManager.h"

namespace nu
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particleSystem; }
		Audio& GetAudio() { return m_audio; }

		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;

	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;
		ParticleSystem m_particleSystem;
		Audio m_audio;

		Time m_time;
	};
}