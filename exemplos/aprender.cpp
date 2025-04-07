#include <SDL2/SDL.h>
#include <iostream>

int main() {
  int altura = 800;
  int largura = 600;

  // Inicializar a SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
    return -1;
  }

  // Criar a janela
  SDL_Window *window = SDL_CreateWindow("Test SDL", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, largura,altura, SDL_WINDOW_SHOWN);

  if (!window) 
  {
    std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return -1;
  }

  // Criar o renderizador
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) 
  {
    std::cerr << "Erro ao criar o renderizador: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  bool running = true;
  SDL_Event event;

  // Loop principal
  while (running) 
  {
    // Processar os eventos
    while (SDL_PollEvent(&event) != 0) 
    {
      if (event.type == SDL_QUIT) 
      {
        running = false;
      }
    }

    // Limpar a tela com a cor preta
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Cor preta
    SDL_RenderClear(renderer);

    // Atualizar a tela
    SDL_RenderPresent(renderer);
  }

  // Limpeza
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
