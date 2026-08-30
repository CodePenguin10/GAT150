#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureFrames.h"
#include "Engine.h"

namespace nu
{
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Update(float dt)
	{
		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSecond;
		if (m_frameTimer >= frameTime)
		{
			m_frameTimer = 0.0f;

			m_frame++;
			m_frame = m_frame % m_textureFrames->GetTotalFrames();
		}
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer)
	{
		if (!m_textureFrames)
		{
			return;
		}

		auto transform = GetOwner()->GetTransform();

		renderer.DrawTexture(*m_textureFrames->GetTexture(), m_textureFrames->GetFrameRect(m_frame), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME(value, "frames_per_second", m_framesPerSecond);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;
		JSON_READ(value, texture_frames);

		if (!texture_frames.empty())
		{
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
		}

	}
}