#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Kích thước màn hình (16:9)
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32; // Độ sâu màu (32-bit)

// Màu sắc (RGB)
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

// Khai báo các biến toàn cục
extern SDL_Window* g_window;       // Cửa sổ chính
extern SDL_Renderer* g_screen;     // Renderer
extern SDL_Event g_event;          // Sự kiện
extern TTF_Font* g_font;           // Chữ

// Khai báo các hàm
bool initSDL();                    // Khởi tạo SDL
void closeSDL();                    // Đóng SDL và giải phóng tài nguyên
void CloseFont();                   //đóng font
bool InitFont();                    //Khởi tạo font
#endif // COMMONFUNC_H_
