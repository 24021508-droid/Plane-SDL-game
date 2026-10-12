
#ifndef BULLET_H
#define BULLET_H

#include"CommonFunc.h"

class Bullet {
public:
    Bullet(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h, int dmg );


    void render(SDL_Renderer* renderer);
    void move(int dx, int dy);
    SDL_Rect getRect() const;
    bool isOutOfScreen(int screenHeight) const ;
    int getDamage() const { return damage; }
private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int damage;
};

#endif // BULLET_H
