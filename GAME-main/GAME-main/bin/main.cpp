#include "CommonFunc.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "button.h"
#include"boss.h"
enum EndGameType {
    GAME_OVER,
    GAME_WIN
};

bool ShowEndGameScreen(SDL_Renderer* renderer, EndGameType type) {
    SDL_Texture* end_texture = nullptr;
    if (type == GAME_OVER) {
        end_texture = IMG_LoadTexture(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\Game_over.png");
    } else {
        end_texture = IMG_LoadTexture(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\you_win.png");
    }

    if (!end_texture) {
        std::cout << "Failed to load end game image!\n";
        return false;
    }

    Button yes_button, no_button;
    yes_button.LoadButton(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\yes.png", 440, 650, 125, 60);
    no_button.LoadButton(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\no.png", 690, 650, 125, 60);

    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                return false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (yes_button.IsClicked(x, y)) {
                    yes_button.Free();
                    no_button.Free();
                    SDL_DestroyTexture(end_texture);
                    return true;
                }
                if (no_button.IsClicked(x, y)) {
                    yes_button.Free();
                    no_button.Free();
                    SDL_DestroyTexture(end_texture);
                    return false;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, end_texture, nullptr, nullptr);
        yes_button.Render();
        no_button.Render();
        SDL_RenderPresent(renderer);
    }
}

    // biến cục bộ
    int waveCount = 0;
    bool waveReady = true;
int main(int argc, char* argv[]) {

enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_EXIT
};



if (!initSDL() || !InitFont()) {
    std::cout << "Failed to initialize SDL or font!" << std::endl;
    return 1;
}

 Menu menu;
   if (!menu.LoadMenu()) {
        std::cout << "Failed to load menu!" << std::endl;
        closeSDL();
        return 1;
   }

   GameState currentState = STATE_MENU;

   while (currentState != STATE_EXIT) {
    while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT ) {
                menu.Free();
                CloseFont();
                closeSDL();
                return 0;
            }
        }
       if (currentState == STATE_MENU) {
           int choice = menu.ShowMenu();
           if (choice == 1) {
               currentState = STATE_PLAYING;
           }
           else {
               currentState = STATE_EXIT;
           }
       }
       else if (currentState == STATE_PLAYING) {

SDL_Texture* g_background = nullptr;
    g_background = IMG_LoadTexture(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\background.png");
if (g_background == nullptr) {
    std::cout << "Failed to load background: " << IMG_GetError() << std::endl;
}


    Player player(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\khongphut.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 96, 80);

    std::vector<Bullet> bullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Bullet> bossBullets;
    std::vector<Enemy> enemies;
    std::vector<Boss> bosses;

    waveCount = 0;
    waveReady = true;

    bool running = true;
    bool gameOver = false;

    while (running && !gameOver) {
        while (SDL_PollEvent(&g_event)) {

            if (g_event.type == SDL_QUIT ) {
                menu.Free();
                CloseFont();
                closeSDL();
                return 0;
            }
       if (player.getHealth() <= 0) {
    bool replay = ShowEndGameScreen(g_screen, GAME_OVER);
    if (replay) {
        currentState = STATE_PLAYING;
    } else {
        currentState = STATE_MENU;
    }
    running = false;
    break;
}

            player.handleEvent(g_event);
            if (g_event.type == SDL_KEYDOWN) {
                    if (g_event.type == SDL_KEYDOWN) {

    if (g_event.key.keysym.sym == SDLK_p) {
        running = false;
        currentState = STATE_MENU;
    }
}
if (currentState != STATE_PLAYING) {
        break;
    }

    if (g_event.key.keysym.sym == SDLK_SPACE) {
    int bulletX = player.getRect().x + player.getRect().w / 2 - 10;
    int bulletY = player.getRect().y - 20;
    if (player.isUsingSpecialBullet()) {
        bullets.push_back(Bullet(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\triple_bullet.png", bulletX, bulletY, 40, 50, 3));
    } else {
        bullets.push_back(Bullet(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\onebullet.png", bulletX, bulletY, 20, 25, 1));
    }
}

    if (g_event.key.keysym.sym == SDLK_1) {
    player.activateSpecialBullet();
}
}
        }
        player.move();
        player.updateSpecialState();
        // Di chuyển Bullet
        for (auto& bullet : bullets) {

            bullet.render(g_screen);
            bullet.move(0, -7);
        }
  for (auto& boss : bosses) {
    boss.move(player.getRect());
    boss.render(g_screen);
    if (rand() % 100 < 2) {
        boss.shootSpecial(g_screen, enemyBullets);
    }
}


        // Di chuyển Enemy và bắn đạn
        for (auto& enemy : enemies) {

           enemy.move(player.getRect());
            if (rand() % 100 < 1) { // Xác suất bắn đạn
                enemy.shoot(g_screen, enemyBullets);
            }
        }

        // Di chuyển đạn của kẻ địch
        for (auto& bullet : enemyBullets) {
            bullet.move(0, 3);
        }

        // Kiểm tra va chạm giữa đạn của người chơi và Enemy || người chơi và boss
        for (auto& bullet : bullets) {
            for (auto& enemy : enemies) {
                if (enemy.checkCollision(bullet.getRect())) {
                    enemy.takeDamage(bullet.getDamage());
                    player.addEnergy(5);
                    bullet = bullets.back(); // Xóa đạn bằng cách gán nó vào phần tử cuối
                    bullets.pop_back();     // Xóa phần tử cuối
                    break;
                }
            }
            }
for (auto& boss : bosses) {
    boss.move(player.getRect());
    boss.render(g_screen);
    if (rand() % 100 < 2) {
        boss.shootSpecial(g_screen, enemyBullets);
    }
}


        // Kiểm tra va chạm giữa đạn của kẻ địch và người chơi
       for (auto& bullet : enemyBullets) {
    SDL_Rect bulletRect = bullet.getRect();
    SDL_Rect playerRect = player.getRect();

    if (SDL_HasIntersection(&bulletRect, &playerRect)) {
        player.takeDamage();

        bullet = enemyBullets.back();
        enemyBullets.pop_back();

    }
}for (auto& bullet : bullets) {
    SDL_Rect bulletRect = bullet.getRect();

    for (auto& boss : bosses) {
        SDL_Rect bossRect = boss.getRect();

        if (SDL_HasIntersection(&bulletRect, &bossRect)) {
            boss.takeDamage(bullet.getDamage());
            player.addEnergy(10);
            bullet = bullets.back();
            bullets.pop_back();
            break;
        }
    }
}


      for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
   SDL_Rect playerHitboxV = player.getHitboxVertical();
SDL_Rect playerHitboxH = player.getHitboxHorizontal();

SDL_Rect enemyHitboxV = enemyIt->getHitboxVertical();
SDL_Rect enemyHitboxH = enemyIt->getHitboxHorizontal();

if (SDL_HasIntersection(&playerHitboxV, &enemyHitboxV) ||
    SDL_HasIntersection(&playerHitboxV, &enemyHitboxH) ||
    SDL_HasIntersection(&playerHitboxH, &enemyHitboxV) ||
    SDL_HasIntersection(&playerHitboxH, &enemyHitboxH)) {
        player.takeDamage();

        // Xóa enemy ngay lập tức sau khi va chạm
        enemyIt = enemies.erase(enemyIt);

        // Kiểm tra nếu Player hết máu, thoát vòng lặp ngay
        if (player.getHealth() <= 0) {
            bool replay = ShowEndGameScreen(g_screen, GAME_OVER);
            currentState = replay ? STATE_PLAYING : STATE_MENU;
            running = false;
            break;
        }
    } else {
        ++enemyIt;  // Nếu không có va chạm, tiếp tục duyệt
    }
}
// Kiểm tra va chạm giữa người chơi và boss
for (auto bossIt = bosses.begin(); bossIt != bosses.end();) {
    SDL_Rect bossRect = bossIt->getRect();
    SDL_Rect playerHitboxV = player.getHitboxVertical();
    SDL_Rect playerHitboxH = player.getHitboxHorizontal();

    if (SDL_HasIntersection(&playerHitboxV, &bossRect) ||
        SDL_HasIntersection(&playerHitboxH, &bossRect)) {

        player.takeDamage();


        // Kiểm tra nếu người chơi chết
        if (player.getHealth() <= 0) {
            bool replay = ShowEndGameScreen(g_screen, GAME_OVER);
            currentState = replay ? STATE_PLAYING : STATE_MENU;
            running = false;
            break;
        }
    }

    ++bossIt;  // Nếu không va chạm hoặc vẫn tiếp tục
}


for (auto it = bosses.begin(); it != bosses.end();) {
    if (it->isDestroyed()) {
        it = bosses.erase(it);  // Xóa boss khỏi danh sách và cập nhật iterator
    } else {
        ++it;  // Tiếp tục nếu boss chưa bị tiêu diệt
    }
}

        // Xóa các Enemy đã bị tiêu diệt
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
            return enemy.isDestroyed();
        }), enemies.end());
        // Xóa đạn của người chơi nếu ra khỏi màn hình
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
            return b.isOutOfScreen(SCREEN_HEIGHT);
            }), bullets.end());

        // Xóa đạn của kẻ địch nếu ra khỏi màn hình
        enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](const Bullet& b) {
            return b.isOutOfScreen(SCREEN_HEIGHT);
            }), enemyBullets.end());


            // Nếu không còn enemy và boss -> bắt đầu đếm thời gian chuẩn bị wave mới
       if (enemies.empty() && bosses.empty() && waveReady) {
    waveCount++;
    waveReady = false;
    if (waveCount > 8 && bosses.empty()) {
    bool replay = ShowEndGameScreen(g_screen, GAME_WIN);
    if (replay) {
        currentState = STATE_PLAYING;
    } else {
        currentState = STATE_MENU;
    }
    running = false;
    break;
}

  if (waveCount == 1 && enemies.empty()) {
    Enemy enemy1(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\enemy.png", 200, 100, 60, 60, 0);
    Enemy enemy2(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\enemy.png", 900, 150, 60, 60, 0);
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
}
    // Tạo boss nếu đến wave có boss
    if (waveCount == 3 || waveCount == 6 || waveCount == 8) {
        std::string bossImg;
        if (waveCount == 3) bossImg = "D:\\gamestart_1\\game start 1\\Game_2\\picture\\boss_1.png";
        if (waveCount == 6) bossImg = "D:\\gamestart_1\\game start 1\\Game_2\\picture\\boss_2.png";
        if (waveCount == 8) bossImg = "D:\\gamestart_1\\game start 1\\Game_2\\picture\\boss_3.png";

        Boss newBoss(g_screen, bossImg, SCREEN_WIDTH / 2 - 100, 60, 200, 150);
        bosses.push_back(newBoss);
    }else{
    Enemy::spawnWave(enemies, g_screen);
    }
    waveReady = true;
}
        // Vẽ lại màn hình
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);
        SDL_RenderCopy(g_screen, g_background, NULL, NULL);
        player.render(g_screen);
        std::string waveText = "Wave: " + std::to_string(waveCount);
        SDL_Color color = { 0, 0, 0 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, waveText.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_screen, textSurface);
        SDL_Rect textRect = { 1050, 20, textSurface->w, textSurface->h };

        SDL_RenderCopy(g_screen, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);


        for (auto& boss : bosses) {
            boss.render(g_screen);
        }
        for (auto& bullet : bullets) {
            bullet.render(g_screen);
        }
        for (auto& enemy : enemies) {
            enemy.render(g_screen);
        }
        for (auto& bullet : enemyBullets) {
            bullet.render(g_screen);
        }
        for (auto& boss : bosses) {
            boss.render(g_screen);
        }
        waveReady = true;
        //Thanh năng lượng
        SDL_Rect bg = { 20, 20, 240, 20 };
        SDL_Rect bar = { 20, 20, player.getEnergy() * 4, 20 };

        SDL_SetRenderDrawColor(g_screen, 100, 100, 100, 255); // khung nền
        SDL_RenderFillRect(g_screen, &bg);

        if (player.isUsingSpecialBullet()){
            SDL_SetRenderDrawColor(g_screen, 255, 100, 0, 255);} // cam
        else{
            SDL_SetRenderDrawColor(g_screen, 0, 255, 0, 255); }  // xanh
             SDL_RenderFillRect(g_screen, &bar);

        // --- VẼ THANH MÁU ---
        int hpBarWidth = 240;
        int hpBarHeight = 20;

        // Vị trí: bên dưới thanh năng lượng
        int hpBarX = 20;
        int hpBarY = 20 + 20 + 10;

        // Viền tổng thể
        SDL_Rect hpOutline = { hpBarX, hpBarY, hpBarWidth, hpBarHeight };

        // Nền xám
        SDL_SetRenderDrawColor(g_screen, 100, 100, 100, 255);
        SDL_RenderFillRect(g_screen, &hpOutline);

        // Phần máu còn lại
        int currentHP = std::max(0, player.getHealth());
        int maxHP = std::max(1, player.getMaxHealth());
        int hpWidth = std::max(0, (hpBarWidth * currentHP) / maxHP);

        SDL_Rect hpFill = { hpBarX, hpBarY, hpWidth, hpBarHeight };
        SDL_SetRenderDrawColor(g_screen, 255, 0, 0, 255); // đỏ
        SDL_RenderFillRect(g_screen, &hpFill);

        // Viền trắng
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderDrawRect(g_screen, &hpOutline);



        SDL_RenderPresent(g_screen);
        SDL_Delay(16);
    }

     if (g_background != nullptr) {
        SDL_DestroyTexture(g_background);
        g_background = nullptr;
    }
       }

 }
    menu.Free();

    CloseFont();
    closeSDL();

    return 0;
}
