#include <SDL2/SDL_render.h>
#include <iostream>
#include "chipeu.h"
#include <SDL2/SDL.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;
const int SCALE = 10;
// Global SDL variables
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
// A single pixel
SDL_Rect pixel{};

// Function prototypes
bool init();
void close();

int main(int argc, char* args[]) {
    chipeu chip8;
    chip8.loadRom(args[1]);
    if (init()){
        bool quit = false;
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);
        while(!quit){
            chip8.emulateCycle();
            if(chip8.getDraw()){
                std::cout << "Draw flag is true, trying to draw" << std::endl;
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                SDL_RenderClear(gRenderer);
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                const unsigned char* gfx  = chip8.getGfx();
                for(int y = 0; y < 32; ++y){
                    for(int x = 0; x < 64; ++x){
                        int index = (y * 64) + x;
                        if(gfx[index]){
                            pixel.x = x*SCALE;
                            pixel.y = y*SCALE;
                            pixel.w = SCALE;
                            pixel.h = SCALE;
                            SDL_RenderFillRect(gRenderer, &pixel);
                        }
                    }
                }
                SDL_RenderPresent(gRenderer);
                chip8.setDraw(false);
            }
        }
    }
    close();
    return 0;
}

bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("chipeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    // Destroy renderer and window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}
