#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <tuple>

const int GAME_WIDTH = 60;
const int GAME_HEIGHT = 60;

enum Direction {
    Up,
    Down,
    Left,
    Right
};

class Snake {
    public:
    int x;
    int y;
    std::list<int> body_x;
    std::list<int> body_y;
    Direction direction;

    Snake();
    
    void tick();
};

class SnakeGame {
    public:
    Snake snake;

    int apple_x;
    int apple_y;

    SnakeGame();

    bool tick(int& score);
    private:
    void place_apple();
};

#endif