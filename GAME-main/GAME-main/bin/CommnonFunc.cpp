#include "CommonFunc.h"

// Định nghĩa các biến toàn cục
SDL_Window* g_window = nullptr;
SDL_Renderer* g_screen = nullptr;
SDL_Event g_event;
TTF_Font* g_font = nullptr;

// Khởi tạo SDL
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_window = SDL_CreateWindow("Plane Battle!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == nullptr) {
        std::cout<< "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_screen == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
   return true;
}
bool InitFont() {
    if (TTF_Init() == -1) {
        std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
        return false;
    }

    g_font = TTF_OpenFont("D:\\gamestart_1\\game start 1\\Game_2\\font\\arial.ttf", 24);
    if (!g_font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}



// Đóng SDL và giải phóng tài nguyên
 void CloseFont() {
    if (g_font != nullptr) {
        TTF_CloseFont(g_font);
        g_font = nullptr;
    }
    }
void closeSDL() {
    if (g_screen != nullptr) {
        SDL_DestroyRenderer(g_screen);
        g_screen = nullptr;
    }

    if (g_window != nullptr) {
        SDL_DestroyWindow(g_window);
        g_window = nullptr;
    }



    SDL_Quit();
}
