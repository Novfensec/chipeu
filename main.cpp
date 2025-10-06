#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include "chipeu.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCALE = 20;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init();
void close();

int main(int argc, char* args[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << args[0] << " <path_to_rom>" << std::endl;
        return 1;
    }

    srand(time(NULL));
    chipeu chip8;
    chip8.loadRom(args[1]);

    if (!init()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return 1;
    }

    const int CPU_HZ = 700;
    const int CPU_INTERVAL = 1000 / CPU_HZ;

    // Timer for the 60Hz updates (delay/sound)
    unsigned int last_timer_update = SDL_GetTicks();
    const int TIMER_INTERVAL = 1000 / 60;

    bool quit = false;
    SDL_Event e;
    SDL_Rect pixel;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                unsigned char key_state = (e.type == SDL_KEYDOWN) ? 1 : 0;
                switch (e.key.keysym.sym) {
                    case SDLK_1: chip8.setKey(0x1, key_state); break;
                    case SDLK_2: chip8.setKey(0x2, key_state); break;
                    case SDLK_3: chip8.setKey(0x3, key_state); break;
                    case SDLK_4: chip8.setKey(0xC, key_state); break;
                    case SDLK_q: chip8.setKey(0x4, key_state); break;
                    case SDLK_w: chip8.setKey(0x5, key_state); break;
                    case SDLK_e: chip8.setKey(0x6, key_state); break;
                    case SDLK_r: chip8.setKey(0xD, key_state); break;
                    case SDLK_a: chip8.setKey(0x7, key_state); break;
                    case SDLK_s: chip8.setKey(0x8, key_state); break;
                    case SDLK_d: chip8.setKey(0x9, key_state); break;
                    case SDLK_f: chip8.setKey(0xE, key_state); break;
                    case SDLK_z: chip8.setKey(0xA, key_state); break;
                    case SDLK_x: chip8.setKey(0x0, key_state); break;
                    case SDLK_c: chip8.setKey(0xB, key_state); break;
                    case SDLK_v: chip8.setKey(0xF, key_state); break;
                }
            }
        }

        for (int i = 0; i < (CPU_HZ / 60); ++i) {
            chip8.emulateCycle();
        }

        unsigned int current_time = SDL_GetTicks();
        if (current_time - last_timer_update >= TIMER_INTERVAL) {
            chip8.updateTimers();
            last_timer_update = current_time;
        }

        if (chip8.getDraw()) {
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

            const unsigned char* gfx = chip8.getGfx();
            for (int y = 0; y < 32; ++y) {
                for (int x = 0; x < 64; ++x) {
                    if (gfx[(y * 64) + x]) {
                        pixel.x = x * SCALE;
                        pixel.y = y * SCALE;
                        pixel.w = SCALE;
                        pixel.h = SCALE;
                        SDL_RenderFillRect(gRenderer, &pixel);
                    }
                }
            }
            SDL_RenderPresent(gRenderer);
            chip8.setDraw(false);
        }
        
        SDL_Delay(TIMER_INTERVAL);
    }

    close();
    return 0;
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("chipeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    SDL_Quit();
}
