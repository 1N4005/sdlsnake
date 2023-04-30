#include "snake.hpp"
#include <list>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <iterator>
#include <iostream>

inline bool check_collision(std::list<int> list1, std::list<int> list2, int x, int y) {
    auto iter1 = list1.begin();
    auto iter2 = list2.begin();
    for(; iter1 != list1.end() && iter2 != list2.end(); iter1++, iter2++) {
        if (*iter1 == x && *iter2 == y) {
            return true;
        }
    }
	return false;
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

    if(check_collision(snake.body_x, snake.body_y, snake.x, snake.y)) {
        std::cout << "oh no\n";
        return true;
    }

    if (this->snake.x == this->apple_x && this->snake.y == this->apple_y) {
        score++;
        this->place_apple();
    } else {
        this->snake.body_x.pop_front();
        this->snake.body_y.pop_front();
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
