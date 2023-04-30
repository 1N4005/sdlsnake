#include "snake.hpp"
#include <list>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <iterator>

inline bool Contains(std::list<int> list, int x, int &index) {
    int i = 0;
    for(auto iter = list.begin(); iter != list.end(); iter++) {
        if(*iter == x) {
            index = i;
            return true;
        }
        i++;
    }
    index = -1;
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

    int x;
    int y;
    if(Contains(snake.body_x, snake.x, x) && Contains(snake.body_y, snake.y, y)) {
        if(x == y) {
            return true;
        } 
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
