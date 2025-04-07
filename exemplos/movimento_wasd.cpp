#include <SDL2/SDL.h>
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Game {
public:
    Game() : window(nullptr), renderer(nullptr), x(SCREEN_WIDTH / 2), y(SCREEN_HEIGHT / 2), speed(5), quit(false) {}

    bool init() {
        // Inicializa a SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        {
            std::cerr << "SDL não pôde ser inicializada! Erro: " << SDL_GetError() << std::endl;
            return false;
        }

        // Cria a janela
        window = SDL_CreateWindow("Movimento com WASD",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (!window) 
        {
            std::cerr << "Janela não pôde ser criada! Erro: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        // Cria o renderizador
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer) 
        {
            std::cerr << "Renderizador não pôde ser criado! Erro: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        return true;
    }

    void handleEvents() 
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) 
        {
            if (e.type == SDL_QUIT) 
            {
                quit = true;
            }
        }

        // Verifica as teclas pressionadas
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) 
        {
            y -= speed;  // Mover para cima
        }
        if (currentKeyStates[SDL_SCANCODE_S]) 
        {
            y += speed;  // Mover para baixo
        }
        if (currentKeyStates[SDL_SCANCODE_A]) 
        {
            x -= speed;  // Mover para a esquerda
        }
        if (currentKeyStates[SDL_SCANCODE_D]) 
        {
            x += speed;  // Mover para a direita
        }
    }

    void update() 
    {
        // Limita os movimentos para dentro da tela
        if (x < 0) x = 0;
        if (x > SCREEN_WIDTH - 50) x = SCREEN_WIDTH - 50;
        if (y < 0) y = 0;
        if (y > SCREEN_HEIGHT - 50) y = SCREEN_HEIGHT - 50;
    }

    void render() 
    {
        // Limpa a tela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Cor preta
        SDL_RenderClear(renderer);

        // Desenha o quadrado (50x50 pixels)
        SDL_Rect fillRect = { x, y, 50, 50 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Cor vermelha
        SDL_RenderFillRect(renderer, &fillRect);

        // Atualiza a tela
        SDL_RenderPresent(renderer);
    }

    bool isQuit() const 
    {
        return quit;
    }

    ~Game() 
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int x, y, speed;
    bool quit;
};

int main() 
{
    Game game;

    if (!game.init()) 
    {
        return 1; // Erro na inicialização
    }

    while (!game.isQuit()) 
    {
        game.handleEvents();
        game.update();
        game.render();
    }

    return 0;
}
