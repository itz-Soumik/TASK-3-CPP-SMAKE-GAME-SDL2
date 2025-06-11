#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WIDTH = 800, HEIGHT = 600;
const int BLOCK_SIZE = 20;
const int INITIAL_SPEED = 150;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

class SnakeGame {
public:
    SnakeGame();
    ~SnakeGame();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Mix_Chunk* eatSound;
    Mix_Chunk* gameOverSound;

    bool running;
    Direction dir;
    std::vector<Point> snake;
    Point food;
    int speed;
    int score;
    Uint32 lastMove;

    void handleEvents();
    void update();
    void render();
    void spawnFood();
    void playSound(Mix_Chunk* sound);
    bool checkCollision();
};

SnakeGame::SnakeGame() : running(true), dir(RIGHT), speed(INITIAL_SPEED), score(0) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont("assets/font.ttf", 24);
    eatSound = Mix_LoadWAV("assets/eat.wav");
    gameOverSound = Mix_LoadWAV("assets/game_over.wav");

    snake.push_back({ WIDTH / 2, HEIGHT / 2 });
    spawnFood();
    lastMove = SDL_GetTicks();
}

SnakeGame::~SnakeGame() {
    Mix_FreeChunk(eatSound);
    Mix_FreeChunk(gameOverSound);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void SnakeGame::playSound(Mix_Chunk* sound) {
    Mix_PlayChannel(-1, sound, 0);
}

void SnakeGame::spawnFood() {
    srand(time(nullptr));
    food.x = (rand() % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
    food.y = (rand() % (HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;
}

void SnakeGame::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: if (dir != DOWN) dir = UP; break;
                case SDLK_DOWN: if (dir != UP) dir = DOWN; break;
                case SDLK_LEFT: if (dir != RIGHT) dir = LEFT; break;
                case SDLK_RIGHT: if (dir != LEFT) dir = RIGHT; break;
            }
        }
    }
}

bool SnakeGame::checkCollision() {
    for (size_t i = 1; i < snake.size(); ++i)
        if (snake[0] == snake[i])
            return true;
    return false;
}

void SnakeGame::update() {
    Uint32 now = SDL_GetTicks();
    if (now - lastMove < speed) return;
    lastMove = now;

    Point newHead = snake[0];
    switch (dir) {
        case UP: newHead.y -= BLOCK_SIZE; break;
        case DOWN: newHead.y += BLOCK_SIZE; break;
        case LEFT: newHead.x -= BLOCK_SIZE; break;
        case RIGHT: newHead.x += BLOCK_SIZE; break;
    }

    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT || checkCollision()) {
        playSound(gameOverSound);
        SDL_Delay(1000);
        running = false;
        return;
    }

    snake.insert(snake.begin(), newHead);

    if (newHead == food) {
        score += 10;
        playSound(eatSound);
        speed = std::max(50, speed - 5);  // Increase difficulty
        spawnFood();
    } else {
        snake.pop_back();
    }
}

void SnakeGame::render() {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    // Draw food
    SDL_Rect foodRect = { food.x, food.y, BLOCK_SIZE, BLOCK_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &foodRect);

    // Draw snake
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (auto& p : snake) {
        SDL_Rect r = { p.x, p.y, BLOCK_SIZE, BLOCK_SIZE };
        SDL_RenderFillRect(renderer, &r);
    }

    // Draw score
    SDL_Color white = { 255, 255, 255 };
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { 10, 10, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);
}

void SnakeGame::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(10);
    }
}
 
int main(int argc, char* argv[]) {
    SnakeGame game;
    game.run();
    return 0;
}
