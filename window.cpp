#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>

void window()
{   
    //altura
    int height = 800;

    //largura
    int width = 600;

    SDL_Window* window;
    if(window == nullptr)
    {
        std::cout << "Erro creating window\n\n";
    }

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, height, width, SDL_WINDOW_SHOWN);

        SDL_Delay(5000);
        SDL_DestroyWindow(window);
        SDL_Quit();
}

int main(int argc, char* argv[])
{
    window();

    return 0;
}