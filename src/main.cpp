#include <SDL2/SDL.h>
#include <memory>
#include <chrono>
#include <iterator>
#include <list>
#include <vector>
#include <iostream>

#include "snake.hpp"

const float FPS = 240;
const float FPS_DELAY = 1 / FPS;

const int WIDTH = 600;
const int HEIGHT = 600;
const int GRID_SIZE = 15;

long frame_count = 0;
int score = 0;

struct SDLWindowDeleter {
    inline void operator()(SDL_Window* window) {
        SDL_DestroyWindow(window);
    }
};

struct SDLRendererDelter {
    inline void operator()(SDL_Renderer* renderer) {
        SDL_DestroyRenderer(renderer);
    }
};

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    std::unique_ptr<SDL_Window, SDLWindowDeleter> window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(SDL_CreateWindow("hi", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN));
    std::unique_ptr<SDL_Renderer, SDLRendererDelter> renderer = std::unique_ptr<SDL_Renderer, SDLRendererDelter>(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    
    SnakeGame game;
    SDL_Rect snakeRect;
    SDL_Rect appleRect;

    bool run = true;
    while(run) {
        auto start = std::chrono::high_resolution_clock::now();

        snakeRect.x = game.snake.x * GRID_SIZE;
        snakeRect.y = game.snake.y * GRID_SIZE;
        snakeRect.w = GRID_SIZE;
        snakeRect.h = GRID_SIZE;

        appleRect.x = game.apple_x * GRID_SIZE;
        appleRect.y = game.apple_y * GRID_SIZE;
        appleRect.w = GRID_SIZE;
        appleRect.h = GRID_SIZE;

        std::vector<int> draw_body_x(std::begin(game.snake.body_x), std::end(game.snake.body_x));
        std::vector<int> draw_body_y(std::begin(game.snake.body_y), std::end(game.snake.body_y));

        const Uint8 * keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_DOWN] && game.snake.direction != Up) {
            game.snake.direction = Down;
        } else if (keys[SDL_SCANCODE_UP] && game.snake.direction != Down) {
            game.snake.direction = Up;
        } else if (keys[SDL_SCANCODE_RIGHT] && game.snake.direction != Left) {
            game.snake.direction = Right;
        } else if (keys[SDL_SCANCODE_LEFT] && game.snake.direction != Right) {
            game.snake.direction = Left;
        }

        SDL_Event e;
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                run = false;
            }
        }        
        
        if(frame_count % 20 == 0) {
            SDL_RenderClear(renderer.get());
            SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
            SDL_RenderFillRect(renderer.get(), &appleRect);   
            for (int i=0; i<draw_body_x.size(); i++) {
                if(i % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer.get(), 0, 200, 0, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer.get(), 0, 127, 0, 255);
                }
                snakeRect.x = draw_body_x[i] * GRID_SIZE;
                snakeRect.y = draw_body_y[i] * GRID_SIZE;
                snakeRect.w = GRID_SIZE;
                snakeRect.h = GRID_SIZE;

                SDL_RenderFillRect(renderer.get(), &snakeRect);
            }
            SDL_SetRenderDrawColor(renderer.get(), 0, 255, 0, 255);
            SDL_RenderFillRect(renderer.get(), &snakeRect);
            SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
            SDL_RenderPresent(renderer.get());

            if (game.tick(score)) {
                SDL_Delay(1000);
                run = false;
            }

            if (game.snake.x < 0 || game.snake.x > WIDTH / GRID_SIZE - 1 || game.snake.y < 0 || game.snake.y > HEIGHT / GRID_SIZE - 1) {
                SDL_Delay(1000);
                run = false;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        if((duration < FPS_DELAY * 1000000)) {
            SDL_Delay(FPS_DELAY * 1000 - duration / 1000);
        }
        frame_count++;
    }
    SDL_Quit();
    std::cout << "SCORE: " << score << "\n";
}

