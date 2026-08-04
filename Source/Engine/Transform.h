#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace nu
{ 
    struct Transform
    {
        Vector2 position;
        float rotation;
        float scale;
    };

    struct Transform3D
    {
        Vector3 position;
        float rotation;
        float scale;
	};
}



