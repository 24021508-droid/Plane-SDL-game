
#ifndef PLAYER_H
#define PLAYER_H
#include"CommonFunc.h"

class Player {
public:
    Player(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h);


    void render(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& event);
    void takeDamage();

    void move();
    SDL_Rect getRect() const;
    int getHealth() const;
    int getMaxHealth() const { return 60; }

    void updateHitbox();
    SDL_Rect getHitboxVertical() const;
    SDL_Rect getHitboxHorizontal() const;
    void addEnergy(int amount);
    void activateSpecialBullet();  // Khi nhấn phím 1
    void updateSpecialState();     // Gọi mỗi frame
    bool isUsingSpecialBullet() const;
    int getEnergy() const;


private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int health;
    bool moveLeft, moveRight, moveUp, moveDown;
    SDL_Rect hitboxVertical;
    SDL_Rect hitboxHorizontal;
    int energy = 0;
    bool usingSpecialBullet = false;
    Uint32 specialStartTime = 0;
    const int maxEnergy = 60;


};
#endif // PLAYER_H
