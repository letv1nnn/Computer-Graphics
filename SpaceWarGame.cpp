#include <iostream>
#include "raylib.h"
#include <vector>
#include <string>
#include <algorithm>

const int WindowWidth = 1280, WindowHeight = 900;
const int SpaceShipWidth = 85, SpaceShipHeight = 48;

const std::vector<std::string> asteroids = {
    "pinkAsteroids.png", "bluePinkAsteroid.png",
    "greyAsteroidPinkLines.png", "greyAsteroid.png"
};

int playerScore = 0, enemyScore = 0;

Vector2 EdgesCollisions(Vector2 pos) {
    if (pos.x <= 0) pos.x = 0;
    if (pos.x >= WindowWidth - SpaceShipWidth) pos.x = WindowWidth - SpaceShipWidth;
    if (pos.y <= 0) pos.y = 0;
    if (pos.y >= WindowHeight - SpaceShipHeight) pos.y = WindowHeight - SpaceShipHeight;
    return pos;
}

class Bullet {
public:
    Vector2 pos;
    int speed = 10;

    Bullet(Vector2 p) : pos(p) {}

    void Update() {
        pos.y -= speed;
    }

    void Draw() const {
        DrawRectangle((int)pos.x, (int)pos.y, 5, 15, PINK);
    }

    bool isOffScreen() const {
        return pos.y < 0;
    }
};

class SpaceShip {
private:
    Vector2 pos;
    Texture2D texture;
    const int speed = 7;
    std::vector<Bullet> bullets;
    bool canShoot = true;

public:
    SpaceShip() {
        Image img = LoadImage("spaceShip.png");
        texture = LoadTextureFromImage(img);
        UnloadImage(img);
        pos = getRandomPosition();
    }

    ~SpaceShip() {
        UnloadTexture(texture);
    }

    Vector2 getRandomPosition() {
        float x = GetRandomValue(100, WindowWidth - 100);
        float y = GetRandomValue(WindowHeight - 300, WindowHeight);
        return Vector2{ x, y };
    }

    void Draw() const {
        DrawTexture(texture, (int)pos.x, (int)pos.y, WHITE);
        for (const auto& b : bullets) {
            b.Draw();
        }
    }

    void Update() {
        if (IsKeyDown(KEY_W)) pos.y -= speed;
        if (IsKeyDown(KEY_S)) pos.y += speed;
        if (IsKeyDown(KEY_D)) pos.x += speed;
        if (IsKeyDown(KEY_A)) pos.x -= speed;

        pos = EdgesCollisions(pos);

        if (IsKeyDown(KEY_SPACE) && canShoot) {
            canShoot = false;
            bullets.push_back(Bullet({ pos.x + 10, pos.y }));
            bullets.push_back(Bullet({ pos.x + SpaceShipWidth - 15, pos.y }));
        }

        if (IsKeyUp(KEY_SPACE)) {
            canShoot = true;
        }

        for (auto& b : bullets) {
            b.Update();
        }

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [](Bullet& b) { return b.isOffScreen(); }),
            bullets.end()
        );
    }

    std::vector<Bullet>& getBullets() { return bullets; }
};

class Asteroid {
public:
    Vector2 pos;
    int speed;
    Texture2D texture;
    std::string textureName;

    Asteroid() {
        pos = getRandomPosition();
        speed = GetRandomValue(2, 6);
        textureName = getRandomTexture();
        Image img = LoadImage(textureName.c_str());
        texture = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    ~Asteroid() {
        UnloadTexture(texture);
    }

    Vector2 getRandomPosition() {
        return { (float)GetRandomValue(0, WindowWidth - 100), (float)GetRandomValue(-200, -100) };
    }

    std::string getRandomTexture() {
        int index = GetRandomValue(0, asteroids.size() - 1);
        return asteroids[index];
    }

    void Update() {
        pos.y += speed;
        if (pos.y > WindowHeight) {
            pos = getRandomPosition();
            enemyScore++;
        }
    }

    void Draw() const {
        DrawTexture(texture, (int)pos.x, (int)pos.y, WHITE);
        DrawRectangleLines((int)pos.x, (int)pos.y, texture.width, texture.height, RED);
        DrawText(textureName.c_str(), (int)pos.x, (int)pos.y - 20, 20, WHITE);
    }

    Rectangle getBounds() const {
        return { pos.x, pos.y, (float)texture.width, (float)texture.height };
    }
};

class Game {
private:
    SpaceShip spaceship;
    std::vector<Asteroid> asteroids;

public:
    Game() {
        for (int i = 0; i < 5; ++i) {
            asteroids.push_back(Asteroid());
        }
    }

    void Update() {
        spaceship.Update();

        for (auto& asteroid : asteroids) {
            asteroid.Update();
        }

        auto& bullets = spaceship.getBullets();
        for (auto& asteroid : asteroids) {
            Rectangle aRect = asteroid.getBounds();
            for (auto& b : bullets) {
                Rectangle bRect = { b.pos.x, b.pos.y, 5, 15 };
                if (CheckCollisionRecs(aRect, bRect)) {
                    playerScore++;
                    asteroid = Asteroid();
                    b.pos.y = -100;
                }
            }
        }

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return b.isOffScreen(); }),
            bullets.end()
        );
    }

    void Draw() {
        for (const auto& asteroid : asteroids) {
            asteroid.Draw();
        }
        spaceship.Draw();
    }
};

void startGame() {
    InitWindow(WindowWidth, WindowHeight, "Space War");
    SetTargetFPS(60);

    Game game;

    Image img = LoadImage("spacePixelBackground.jpg");
    Texture texture = LoadTextureFromImage(img);
    UnloadImage(img);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        game.Update();

        DrawTexture(texture, 0, 0, WHITE);
        game.Draw();
        DrawText(TextFormat("%i", enemyScore), 10, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), WindowWidth - 100, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
}

int main() {
    startGame();
    return 0;
}
