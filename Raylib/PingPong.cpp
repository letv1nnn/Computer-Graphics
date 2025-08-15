#include <raylib.h>

int playerScore = 0, robotScore = 0;
Color green = Color{ 38, 185, 154, 255 };
Color greenDark = Color{ 20, 160, 133, 255 };
Color greenLight = Color{ 129, 204, 184, 255 };
Color yellow = Color{ 243, 213, 91, 255 };

class Ball {
public:
    float x, y;
    int speedX, speedY;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, yellow);
    }
    void Update() {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speedY *= -1;
        }
        if (x + radius >= GetScreenWidth()) {
            robotScore++;
            ResetBall();
        }
        if (x - radius <= 0) {
            playerScore++;
            ResetBall();
        }
    }
    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speedChoices[2] = { -1, 1 };
        speedX *= speedChoices[GetRandomValue(0, 1)];
        speedY *= speedChoices[GetRandomValue(0, 1)];
    }
};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) y = 0;
        if (y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        else if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }
        LimitMovement();
    }
};

class CpuPaddle : public Paddle {
public:
    void Update(int ballY) {
        if (y + height / 2 > ballY) y -= speed;
        else y += speed;
        LimitMovement();
    }
};


void game() {
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Ping Pong Game | Press Esc to exit");
    SetTargetFPS(60);

    Ball ball;
    Paddle player;
    CpuPaddle robot;


    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 7;
    ball.speedY = 7;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;

    robot.height = 120;
    robot.width = 25;
    robot.x = 10;
    robot.y = screenHeight / 2 - robot.height / 2;
    robot.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ball.Update();
        player.Update();
        robot.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{player.x, player.y, player.width, player.height}) || 
            CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ robot.x, robot.y, robot.width, robot.height })) {
            ball.speedX *= -1;
        }

        ClearBackground(greenDark);
        DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, green);
        DrawCircle(screenWidth / 2, screenHeight / 2, 150, greenLight);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.Draw();
        player.Draw();
        robot.Draw();

        DrawText(TextFormat("%i", robotScore), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
}

int main(int argc, char **argv) {
    game();
    return 0;
}
