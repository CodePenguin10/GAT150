#include "Assets.h"

using namespace nu;

namespace assets
{
    Mesh playerMesh{ { { 2, 0 }, { 1, -1 }, { -2, -1 }, { -2, 1 }, { 1, 1 }, { 2, 0 } }, Color{ 1.0f, 1.0f, 1.0f} };
    Mesh playerMesh2{ { { -1, -1 }, { -2, -2 }, { -2, -1 } }, Color { 1.0f, 1.0f, 1.0f} };
    Mesh playerMesh3{ { { -1, 1 }, { -2, 2 }, { -2, 1 }, }, Color { 1.0f, 1.0f, 1.0f} };

    std::shared_ptr<Model> playerModel = std::make_shared<Model>(std::vector<Mesh>{ playerMesh, playerMesh2, playerMesh3 });

    Mesh enemyMesh{ { { 2, 0 }, { 1, -1 }, { -2, -1 }, { -2, 1 }, { 1, 1 }, { 2, 0 } }, Color{ 1.0f, 1.0f, 1.0f} };
    Mesh enemyMesh2{ { { -1, -1 }, { -2, -2 }, { -2, -1 } }, Color { 1.0f, 0.0f, 0.0f} };
    Mesh enemyMesh3{ { { -1, 1 }, { -2, 2 }, { -2, 1 }, }, Color { 1.0f, 0.0f, 0.0f} };

    std::shared_ptr<Model> enemyModel = std::make_shared<Model>(std::vector<Mesh>{ enemyMesh, enemyMesh2, enemyMesh3 });

    Mesh enemyMesh4{ { { -1, -1 }, { -2, -2 }, { -2, -1 } }, Color { 0.0f, 1.0f, 0.0f} };
    Mesh enemyMesh5{ { { -1, 1 }, { -2, 2 }, { -2, 1 }, }, Color { 0.0f, 1.0f, 0.0f} };

    std::shared_ptr<Model> enemyModel2 = std::make_shared<Model>(std::vector<Mesh>{ enemyMesh, enemyMesh4, enemyMesh5 });


    Mesh enemyMesh6{ { { -1, -1 }, { -2, -2 }, { -2, -1 } }, Color { 0.0f, 0.0f, 1.0f} };
    Mesh enemyMesh7{ { { -1, 1 }, { -2, 2 }, { -2, 1 }, }, Color { 0.0f, 0.0f, 1.0f} };

    std::shared_ptr<Model> enemyModel3 = std::make_shared<Model>(std::vector<Mesh>{ enemyMesh, enemyMesh6, enemyMesh7 });

    Mesh bulletMesh{ { Vector2{ -1, -1 }, Vector2{ 1, 0 }, Vector2{ -1, 1 }, Vector2{ -1, -1 }, }, Color{ 1.0f, 0.0f, 0.0f }
    };
    std::shared_ptr<Model> bulletModel = std::make_shared<Model>( std::vector<Mesh>{ bulletMesh });
}