#include"CommonFunc.h"
#include "Boss.h"

Boss::Boss(SDL_Renderer* renderer, const std::string& path, int x, int y, int w, int h) {
    texture_ = IMG_LoadTexture(renderer, path.c_str());
    rect_ = {x, y, w, h};
    health_ = 30;  // Máu boss nhiều hơn enemy thường
    speed_ = 2;
    direction_ = 1; // Di chuyển ban đầu sang phải
}

SDL_Rect Boss::getRect() {
    return rect_;  // Trả về rect_ chứa thông tin vị trí của boss
}

void Boss::move(const SDL_Rect& playerRect) {
    // Boss di chuyển ngang qua lại trong màn hình
    rect_.x += speed_ * direction_;

    if (rect_.x <= 0 || rect_.x + rect_.w >= SCREEN_WIDTH) {
        direction_ *= -1; // Đổi hướng khi chạm biên
    }
}

void Boss::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}

void Boss::shootSpecial(SDL_Renderer* renderer, std::vector<Bullet>& bossBullets) {
    // Bắn 3 viên đạn cùng lúc theo hình nón
    int bulletW = 12;
    int bulletH = 20;
    int bulletX = rect_.x + rect_.w / 2 - bulletW / 2;
    int bulletY = rect_.y + rect_.h;

    bossBullets.push_back(Bullet(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\bullet3.png", bulletX, bulletY, bulletW, bulletH, 10)); // Thẳng
    bossBullets.push_back(Bullet(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\bullet2.png", bulletX - 50, bulletY, bulletW, bulletH, 5)); // Lệch trái
    bossBullets.push_back(Bullet(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\bullet2.png", bulletX + 50, bulletY, bulletW, bulletH, 5)); // Lệch phải
}

bool Boss::checkCollision(const SDL_Rect& other) {
    return SDL_HasIntersection(&rect_, &other);
}

void Boss::takeDamage(int amount) {
    health_ -= amount;
}


bool Boss::isDestroyed() const {
    return health_ <= 0;
}
