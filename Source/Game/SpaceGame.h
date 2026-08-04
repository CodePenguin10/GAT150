#pragma once
#include "Game.h"
#include "Text.h"

class SpaceGame : public nu::Game
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
	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) : nu::Game{ scene } {}

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
	void SpawnEnemy2();
	void SpawnEnemy3();

	GameState m_gameState = GameState::Title;

	nu::Font* m_titleFont{ nullptr };
	nu::Text* m_titleText{ nullptr };

	nu::Font* m_gameFont{ nullptr };
	nu::Text* m_gameText{ nullptr };

	nu::Font* m_gameOverFont{ nullptr };
	nu::Text* m_gameOverText{ nullptr };

	nu::Font* m_scoreFont{ nullptr };
	nu::Text* m_scoreText{ nullptr };

	nu::Font* m_livesFont{ nullptr };
	nu::Text* m_livesText{ nullptr };
};
