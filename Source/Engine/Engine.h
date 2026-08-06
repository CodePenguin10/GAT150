#pragma once
//Creation
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathUtility.h"
#include "Transform.h"
#include "Mesh.h"
#include "Model.h"
#include "Text.h"
#include "Texture.h"

//Systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Scene.h"
#include "Actor.h"
#include "Game.h"
#include "File.h"
#include "Audio.h"
#include "ParticleSystem.h"

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