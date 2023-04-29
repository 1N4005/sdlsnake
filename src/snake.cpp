#include "snake.hpp"
#include <list>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <vector>
#include <iterator>

inline bool Contains(const std::vector<int> &list, int x) {
	return std::find(list.begin(), list.end(), x) != list.end();
}

Snake::Snake() {
    this->x = 10;
    this->y = 10;
    this->direction = Down;
    this->body_x = std::list<int>();
    this->body_y = std::list<int>();
    body_x.push_back(x);
    body_y.push_back(y);
}

void Snake::tick() {
    switch(this->direction) {
        case Up:
        y--;
        break;
        case Down:
        y++;
        break;
        case Left:
        x--;
        break;
        case Right:
        x++;
        break;
    }
}

SnakeGame::SnakeGame() {
    this->snake = Snake();

    this->place_apple();
}

bool SnakeGame::tick(int &score) {

    this->snake.tick();
    if (this->snake.x == this->apple_x && this->snake.y == this->apple_y) {
        score++;
        this->place_apple();
    } else {
        this->snake.body_x.pop_front();
        this->snake.body_y.pop_front();
    }

    std::vector<int> hit_detect_x(std::begin(snake.body_x), std::end(snake.body_x));
    std::vector<int> hit_detect_y(std::begin(snake.body_y), std::end(snake.body_y));

    if(Contains(hit_detect_x, snake.x) && Contains(hit_detect_y, snake.y)) {
        return true;
    }

    this->snake.body_x.push_back(snake.x);
    this->snake.body_y.push_back(snake.y);
    return false;
}

void SnakeGame::place_apple() {
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
    srand(time.count());
    do {
        this->apple_x = rand() % GAME_WIDTH;
        this->apple_y = rand() % GAME_HEIGHT;
    } while (std::find(this->snake.body_x.begin(), this->snake.body_x.end(), this->apple_x) != this->snake.body_x.end() && std::find(this->snake.body_y.begin(), this->snake.body_y.end(), this->apple_y) != this->snake.body_y.end());
}
