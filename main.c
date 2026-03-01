#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int score = 0;
char title[50];

int main() {
    srand(time(0));
    sprintf(title, "x%d", score);

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Osu!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color fontColor = {255, 255, 255, 255};
    TTF_Font* scoreFont = TTF_OpenFont("fonts/Eitai.ttf", 24);

    SDL_Surface* circleSurface = IMG_Load("images/circle2.png");
    SDL_Texture* circleTexture = SDL_CreateTextureFromSurface(renderer, circleSurface);
    SDL_FreeSurface(circleSurface);

    SDL_Surface* cursorSurface = IMG_Load("images/cursor.png");
    SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, 20, 20);
    SDL_SetCursor(cursor);
    SDL_FreeSurface(cursorSurface);

    SDL_Rect circleRect, fontRect;
    circleRect.w = 70;
    circleRect.h = 70;
    circleRect.x = rand() % (800 - 50);
    circleRect.y = rand() % (600 - 50);

    fontRect.w = 100;
    fontRect.h = 60;
    fontRect.x = 0;
    fontRect.y = 600 - 60;

    SDL_Event event;
    bool running = true;
    int mouseX = 0, mouseY = 0;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
            if(event.type == SDL_MOUSEMOTION) {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT) {
                    if(mouseX >= circleRect.x && mouseX <= circleRect.x + circleRect.w &&
                       mouseY >= circleRect.y && mouseY <= circleRect.y + circleRect.h) {
                        score += 1;
                        circleRect.x = rand() % (800 - 50);
                        circleRect.y = rand() % (600 - 50);
                    }
                    else {
                        score = 0;
                    }
                }
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_z || event.key.keysym.sym == SDLK_x) {
                    if(mouseX >= circleRect.x && mouseX <= circleRect.x + circleRect.w &&
                       mouseY >= circleRect.y && mouseY <= circleRect.y + circleRect.h) {
                        score += 1;
                        circleRect.x = rand() % (800 - 50);
                        circleRect.y = rand() % (600 - 50);
                    }
                    else {
                        score = 0;
                    }
                }
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_FreeCursor(cursor);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(circleTexture);
                    SDL_DestroyRenderer(renderer);
                    TTF_Quit();
                    IMG_Quit();
                    SDL_Quit();
                    return 0;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        sprintf(title, "x%d", score);
        SDL_Surface* fontSurface = TTF_RenderText_Solid(scoreFont, title, fontColor);
        SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
        SDL_FreeSurface(fontSurface);

        SDL_RenderCopy(renderer, circleTexture, NULL, &circleRect);
        SDL_RenderCopy(renderer, fontTexture, NULL, &fontRect);

        SDL_DestroyTexture(fontTexture);

        SDL_RenderPresent(renderer);
        SDL_Delay(8);
    }

    SDL_FreeCursor(cursor);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(circleTexture);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}