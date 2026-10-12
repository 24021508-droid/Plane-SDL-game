#include"CommonFunc.h"
#include"Bullet.h"
class Boss {
public:
    Boss(SDL_Renderer* renderer, const std::string& path, int x, int y, int w, int h);
    void move(const SDL_Rect& playerRect); // Boss di chuyển
    void render(SDL_Renderer* renderer);   // Vẽ boss
    void shootSpecial(SDL_Renderer* renderer, std::vector<Bullet>& bossBullets); // Boss bắn đạn đặc biệt
    bool checkCollision(const SDL_Rect& other); // Kiểm tra va chạm
    void takeDamage(int amount); // Boss bị trúng đạn
    bool isDestroyed() const; // Boss chết chưa
    SDL_Rect getRect(); // Loại bỏ const
private:
    SDL_Texture* texture_;  // Hình ảnh boss
    SDL_Rect rect_;         // Vị trí boss trên màn hình
    int health_;            // Máu của boss
    int speed_;             // Tốc độ di chuyển
    int direction_;         // Hướng di chuyển (1: sang phải, -1: sang trái)
};
