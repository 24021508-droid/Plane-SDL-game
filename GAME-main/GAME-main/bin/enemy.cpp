#include "enemy.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Enemy::Enemy(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h, bool fast)
    : isFast(fast) { // Gán trực tiếp giá trị cho isFast
    texture = IMG_LoadTexture(renderer, imagePath);
    if (!texture) {
        std::cout << "Failed to load enemy texture: " << IMG_GetError() << std::endl;
    }
    rect = {x, y, w, h};
    health = 2;
    destroyed = false;

    trackingPlayer = false;
    playerX = 0;
    playerY = 0;

    // Thiết lập tốc độ cố định
    if (isFast) {
        speedX = 2; // Enemy đặc biệt có tốc độ gấp đôi
        speedY = 2;
    } else {
        speedX = 1; // Enemy thường có tốc độ cố định
        speedY = 1;
    }
}


void Enemy::render(SDL_Renderer* renderer) {
    if (!destroyed) {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void Enemy::move(const SDL_Rect& playerRect) {
    if (destroyed) return;
    updateHitbox();
    // Tính toán khoảng cách đến người chơi
    int deltaX = playerRect.x - rect.x;
    int deltaY = playerRect.y - rect.y;
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance < CHARGE_DISTANCE) {
        trackingPlayer = true;
    } else {
        trackingPlayer = false;
    }

    // Nếu enemy đang tracking player
    if (trackingPlayer) {
        if (distance > 0) { // Đảm bảo tránh chia cho 0
            rect.x += (deltaX / distance) * speedX;
            rect.y += (deltaY / distance) * speedY;
        }
    } else {
        // Di chuyển theo quỹ đạo ziczac nếu không tracking player
        rect.x += speedX;
        if (rect.x <= 0 || rect.x + rect.w >= SCREEN_WIDTH) {
            speedX = -speedX; // Đảo hướng nếu chạm mép màn hình
        }
        rect.y += speedY;
        if (rect.y <= 0 || rect.y + rect.h >= SCREEN_HEIGHT) {
            speedY = -speedY; // Đảo hướng nếu chạm mép trên/dưới
        }
    }
}
void Enemy::updateHitbox() {
    hitboxVertical.x = rect.x + rect.w * 0.3;
    hitboxVertical.y = rect.y;
    hitboxVertical.w = rect.w * 0.4;
    hitboxVertical.h = rect.h;

    hitboxHorizontal.x = rect.x;
    hitboxHorizontal.y = rect.y + rect.h * 0.3;
    hitboxHorizontal.w = rect.w;
    hitboxHorizontal.h = rect.h * 0.4;
}

SDL_Rect Enemy::getHitboxVertical() const {
    return hitboxVertical;
}

SDL_Rect Enemy::getHitboxHorizontal() const {
    return hitboxHorizontal;
}


void Enemy::update(const SDL_Rect& playerRect) {
    playerX = playerRect.x;
    playerY = playerRect.y;
    move(playerRect);
}

void Enemy::shoot(SDL_Renderer* renderer, std::vector<Bullet>& enemyBullets) {
    if (!destroyed) {
        enemyBullets.push_back(Bullet(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\enemybullet.png", rect.x + rect.w / 2, rect.y + rect.h, 50, 40, 1));
    }
}


bool Enemy::checkCollision(const SDL_Rect& otherRect) const {
    return SDL_HasIntersection(&hitboxVertical, &otherRect) ||
           SDL_HasIntersection(&hitboxHorizontal, &otherRect);
}

bool Enemy::isDestroyed() const {
    return destroyed;
}

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) destroyed = true;
}


void Enemy::spawnWave(std::vector<Enemy>& enemies, SDL_Renderer* renderer) {
   static Uint32 lastWaveTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastWaveTime > WAVE_INTERVAL) {
        int numEnemies = 2 + (currentTime / 20000); // Tăng số lượng theo thời gian

        for (int i = 0; i < numEnemies; ++i) {
            int spawnSide = rand() % 3;
            int x, y = 0;

            // Chọn vị trí xuất hiện dựa trên spawnSide
            if (spawnSide == 0) { // Trái
                x = rand() % 100; // Giới hạn x trong khoảng an toàn
            } else if (spawnSide == 1) { // Phải
                x = SCREEN_WIDTH - 50 - (rand() % 100);
            } else { // Giữa
                x = SCREEN_WIDTH / 2 - 25;
            }

            // Đảm bảo enemy không spawn quá sát viền màn hình
            if (x < 10) x = 10;
            if (x > SCREEN_WIDTH - 60) x = SCREEN_WIDTH - 60;

            // Thêm enemy vào danh sách
            bool isFast = (rand() % 5 == 0); // Xác suất enemy đặc biệt
            enemies.emplace_back(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\enemy.png", x, y, 50, 70, isFast);
        }

        lastWaveTime = currentTime;
    }
}


