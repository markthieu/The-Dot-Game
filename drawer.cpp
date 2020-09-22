#include<iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBTTF_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION

#include <stb_image.h>
#include <stbttf.h>

#include <SDL.h>
#include"drawer.h"

static SDL_Surface* CreateImageSurface(const char* img)
{
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    unsigned char* data = stbi_load(img, &width, &height, &orig_format, req_format);
    if (data == nullptr)
    {
        SDL_Log("Loading image %s failed: %s", img, stbi_failure_reason());
        return nullptr;
    }

    int depth, pitch;
    Uint32 pixel_format;
    if (req_format == STBI_rgb_alpha)
    {
        depth = 32;
        pitch = 4 * width;
        pixel_format = SDL_PIXELFORMAT_RGBA32;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)data, width, height,
        depth, pitch, pixel_format);

    if (surface == nullptr)
    {
        SDL_Log("Creating surface failed: %s", SDL_GetError());
        return nullptr;
    }

    return surface;
}

/*static*/ Drawer* Drawer::Create(SDL_Window* window, SDL_Renderer* renderer)
{
    Drawer* newDrawer = new Drawer();
    newDrawer->m_window = window;
    newDrawer->m_renderer = renderer;
    return newDrawer;
}
void Drawer::DrawImage(const char* img, int posX, int posY)
{
    SDL_Surface* surface = CreateImageSurface(img);
    if (surface)
    {
        SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(m_renderer, surface);

        SDL_Rect sizeRect;
        sizeRect.x = 0;
        sizeRect.y = 0;
        sizeRect.w = surface->w;
        sizeRect.h = surface->h;

        SDL_Rect posRect;
        posRect.x = posX;
        posRect.y = posY;
        posRect.w = sizeRect.w;
        posRect.h = sizeRect.h;
        SDL_RenderCopy(m_renderer, optimizedSurface, &sizeRect, &posRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(optimizedSurface);
    }
    else
    {
        SDL_Log("Image not found");
    }


}
void Drawer::DrawText(const char* font, const char* text, float size, int posX, int posY)
{
    STBTTF_Font* stbFont = STBTTF_OpenFont(m_renderer, font, size);
    if (stbFont)
    {
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        STBTTF_RenderText(m_renderer, stbFont, posX, posY, text);
    }
    else
    {
        SDL_Log("Error loading font: %s", font);
    }
}
