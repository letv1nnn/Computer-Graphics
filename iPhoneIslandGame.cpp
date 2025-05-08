#include "raylib.h"

const int WindowWidth = 400;
const int WindowHeight = 800;

int playerCounter = 0;

struct Block {
    float x, y, width, height;

    void Draw() {
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, BLACK);
    }
};

struct Paddle : Block {
    int speedX;

    void Update() {
        if (IsKeyDown(KEY_LEFT)) x -= speedX;
        else if (IsKeyDown(KEY_RIGHT)) x += speedX;

        if (x <= 0) x = 0;
        if (x >= GetScreenWidth() - width) x = GetScreenWidth() - width;
    }
};

struct Ball {
    float x, y, radius;
    int speedX, speedY;

    void Draw() const {
        DrawCircle((int)x, (int)y, radius, BLACK);
    }

    void Update() {
        x += speedX;
        y += speedY;

        if (x <= radius) speedX *= -1;
        if (x >= GetScreenWidth() - radius) speedX *= -1;

        if (y <= radius) speedY *= -1;
        if (y >= GetScreenHeight() - radius) {
            over = 1;
        }
    }
};

void test() {
    InitWindow(WindowWidth, WindowHeight, "iPhone Island Game");

    SetTargetFPS(60);

    Block block{};
    block.x = WindowWidth / 2 - 60;
    block.y = -20;
    block.width = 150;
    block.height = 55;

    Paddle paddle{};
    paddle.x = WindowWidth / 2 - 60;
    paddle.y = WindowHeight - 10 - 40;
    paddle.width = 120;
    paddle.height = 40;
    paddle.speedX = 5;

    Ball ball{};
    ball.x = WindowWidth / 2;
    ball.y = WindowHeight / 2;
    ball.radius = 15;
    ball.speedX = 7;
    ball.speedY = 7;

    while (!WindowShouldClose()) {
        BeginDrawing();
        paddle.Update();
        ball.Update();

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{paddle.x, paddle.y, paddle.width, paddle.height})) {
            ball.speedY *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{block.x, block.y, block.width, block.height})) {
            ball.speedY *= -1;
            playerCounter++;
        }

        ClearBackground(WHITE);
        ball.Draw();
        block.Draw();
        paddle.Draw();
        if (over == 1) {
            DrawText(TextFormat("Game Over"), WindowWidth / 2 - 40, WindowHeight / 2, 20, BLACK);
            break;
        } else {
            DrawText(TextFormat("%i", playerCounter), WindowWidth / 2 - 40, WindowHeight / 2, 80, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
}

int main() {
    test();
    return 0;
}
