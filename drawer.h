#pragma once
#include <SDL.h>

class Drawer
{
public:
    static Drawer* Create(SDL_Window* window, SDL_Renderer* renderer);

    void DrawImage(const char* imagePath, int posX = 0, int posY = 0);
    void DrawText(const char* font, const char* text, float size, int posX, int posY);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};
