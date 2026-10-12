#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "bullet.h"

#define CHARGE_DISTANCE 300

#define WAVE_INTERVAL 6000

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h, bool fast);
    void render(SDL_Renderer* renderer);
    void move(const SDL_Rect& playerRect);

    void update(const SDL_Rect& playerRect);
    void shoot(SDL_Renderer* renderer, std::vector<Bullet>& enemyBullets);
    bool checkCollision(const SDL_Rect& otherRect) const;
    bool isDestroyed() const;
    void takeDamage(int amount);
    void setIsFast(bool value) { isFast = value; }

    static void spawnWave(std::vector<Enemy>& enemies, SDL_Renderer* renderer);
    void updateHitbox();
    SDL_Rect getHitboxVertical() const;
    SDL_Rect getHitboxHorizontal() const;

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int health;
    bool destroyed;
    int speedX, speedY;
    bool trackingPlayer;
    int playerX, playerY;
    bool isFast;
    SDL_Rect hitboxVertical;
    SDL_Rect hitboxHorizontal;
     // 3 giây delay giữa các wave

};
#endif
