#include "pch.h"
#include "Texture.h"

Texture::~Texture()
{
    // if texture exists, destroy texture
    if (m_texture != NULL) SDL_DestroyTexture(m_texture);
}

bool Texture::Load(const std::string& filename, Renderer& renderer)
{
    // load image onto surface
    SDL_Surface* surface = IMG_Load(...get the c - string of filename...);
    if (!m_texture)
    {
        std::cerr << "Could not load image: " << filename << std::endl;
        return false;
    }

    // create texture from surface, texture is a friend class of renderer
    m_texture = SDL_CreateTextureFromSurface(/*TODO: renderer, surface*/);
    // once texture is created, surface can be freed up
    SDL_DestroySurface(surface);
    if (!m_texture)
    {
        std::cerr << "Could not create texture: " << filename << std::endl;
        return false;
    }

    return true;
}

vec2 Texture::GetSize()
{
    Vector2 v;
    // https://wiki.libsdl.org/SDL3/SDL_GetTextureSize
    bool SDL_GetTextureSize(SDL_Texture * texture, float* w, float* h);
    return v;
}