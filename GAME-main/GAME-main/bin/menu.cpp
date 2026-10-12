#include "button.h"
// ========== Button ==========

Button::Button() {
    texture_ = nullptr;
    rect_ = {0, 0, 0, 0};
}

bool Button::LoadButton(SDL_Renderer* renderer, const std::string& path, int x, int y, int w, int h) {
    texture_ = IMG_LoadTexture(renderer, path.c_str());
    if (texture_ == nullptr) {
        return false;
    }
    rect_ = {x, y, w, h};
    return true;
}

void Button::Render() {
    SDL_RenderCopy(g_screen, texture_, NULL, &rect_);
}

bool Button::IsClicked(int x, int y) {
    return (x >= rect_.x && x <= rect_.x + rect_.w &&
            y >= rect_.y && y <= rect_.y + rect_.h);
}

void Button::Free() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

// ========== Menu ==========

Menu::Menu() {
    background_ = nullptr;
}

bool Menu::LoadMenu() {
    background_ = IMG_LoadTexture(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\menu.png");
    if (background_ == nullptr) return false;

    if (!startButton_.LoadButton(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\StartButton.png", 515, 300, 250, 80)) {
        return false;
    }
    if (!quitButton_.LoadButton(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\QuitButton.png", 515, 420, 250, 80)) {
        return false;
    }

    return true;
}

int Menu::ShowMenu() {
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                return 0; // Thoát game
            }

            if (g_event.type == SDL_MOUSEBUTTONDOWN) {
                int x = g_event.button.x;
                int y = g_event.button.y;

                if (startButton_.IsClicked(x, y)) {
                    return 1; // Bắt đầu game
                }
                if (quitButton_.IsClicked(x, y)) {
                    return 0; // Thoát game
                }
            }
        }

        SDL_RenderClear(g_screen);
        SDL_RenderCopy(g_screen, background_, NULL, NULL);
        startButton_.Render();
        quitButton_.Render();
        SDL_RenderPresent(g_screen);
    }
    return 0;
}

void Menu::Free() {
    if (background_ != nullptr) {
        SDL_DestroyTexture(background_);
        background_ = nullptr;
    }

    startButton_.Free();
    quitButton_.Free();
}
