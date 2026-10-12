#ifndef MENU_H_
#define MENU_H_

#include "CommonFunc.h"


class Button {
public:
    Button();

    bool LoadButton(SDL_Renderer* renderer, const std::string& path, int x, int y, int w, int h);
    void Render();
    bool IsClicked(int x, int y);
    void Free();

private:
    SDL_Rect rect_;
    SDL_Texture* texture_;
};
class Menu {
public:
    Menu();

    bool LoadMenu();
    int ShowMenu();
    void Free(); // Giải phóng tài nguyên
private:
    SDL_Texture* background_;
    Button startButton_;
    Button quitButton_;
};


#endif // MENU_H_
