#include "Engine.h"
#include "SpaceGame/Player.h"
#include "SpaceGame/Enemy.h"
#include "SpaceGame/Assets.h"
#include "SpaceGame/Bullet.h"
#include "SpaceGame/SpaceGame.h"
#include "SpriteGame/SpriteGame.h"

#include <fmod.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include <fstream>

using namespace nu;

int main()
{
    SetWorkingDirectory("Assets");

    // INITILALIZATION
    Engine::Get().Initialize();

    std::unique_ptr game = std::make_unique<SpriteGame>();
    game->Initialize();

    // MAIN LOOP
    bool quit = false;
    while (!quit) 
    {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
			}
        }


        // ENGINE
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

        // GAME
        game->Update(dt);
		

        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
		Engine::Get().GetRenderer().Clear();

        game->Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

	    Engine::Get().GetRenderer().Present();
    }

    // DELETE GAME
    game.reset();

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}