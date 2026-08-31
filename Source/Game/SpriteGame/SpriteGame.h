#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Resources/ResourceManager.h"

class SpriteGame : public nu::Game
{
public:
	enum GameState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	SpriteGame() = default;

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

	void OnPlayerDeath();
	void AddPoints(int points) { m_score += points; }

private:
	int m_score{ 0 };
	int m_lives{ 0 };
	float m_stateTimer = 0.0f;
	float m_spawnTimer = 0.0f;

	void SpawnPlayer();
	void SpawnEnemy();

	GameState m_gameState = GameState::Title;

	nu::Text* m_titleText{ nullptr };
	nu::Text* m_gameText{ nullptr };

	nu::Font* m_gameOverFont{ nullptr };
	nu::Text* m_gameOverText{ nullptr };

	nu::Font* m_scoreFont{ nullptr };
	nu::Text* m_scoreText{ nullptr };

	nu::Font* m_livesFont{ nullptr };
	nu::Text* m_livesText{ nullptr };
};
