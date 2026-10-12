
#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h, int dmg) : damage(dmg) {
    texture = IMG_LoadTexture(renderer, imagePath);
    if (!texture) {
        std::cout << "Failed to load bullet texture: " << IMG_GetError() << std::endl;
    }
    rect = {x, y, w, h};
}


void Bullet::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Bullet::move(int dx, int dy) {
    rect.x += dx;
    rect.y += dy;
    // Giữ đạn trong màn hình
    if (rect.y + rect.h < 0) rect.y = -rect.h;
    if (rect.y > SCREEN_HEIGHT) rect.y = SCREEN_HEIGHT;
}
// Kiểm tra đạn có vượt ra khỏi màn hình không
bool Bullet::isOutOfScreen(int screenHeight) const {
    return (rect.y + rect.h < 0 || rect.y > screenHeight);
}
SDL_Rect Bullet::getRect() const {
    return rect;
}
