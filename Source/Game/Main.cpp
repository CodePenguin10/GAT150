#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "Bullet.h"
#include "SpaceGame.h"

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
    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("assets/data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("assets/data/data.json", document))
        {
            std::string name;
            int age;
            float speed;
            bool isAwake;
            Vector2 position;
            Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

        }
    }

    // read/show the data from the json file

    //--------------------------------------------------------------------------------------------------------

    //// Register the actor, adding it to the m_registry map
    //Factory::Instance().Register<Actor>("Actor");

    //// Create the acotr, giving it a name that can be used to call the actor's functions
    //auto actor = Factory::Instance().Create<Actor>("Actor");
    //std::cout << actor->IsActive() << std::endl;
    //std::cout << actor->GetRadius() << std::endl;

    return 0;

    // INITILALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

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
        game.Update(dt);
		

        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
		Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

	    Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}