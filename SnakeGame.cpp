#include "raylib.h"
#include <iostream>
#include <deque>
#include "raymath.h"

Color greenLight = { 173, 204, 96, 255 };
Color greenDark = { 43, 51, 24, 255 };

const int cellSize = 30;
const int cellCount = 25;
const int offset = 75;

int score = 0;
const double currentSpeed = 0.1;

double lastUpdateTime = 0.0;

bool elementInDeque(Vector2 element, std::deque<Vector2> deque) {
	for (unsigned int i = 0; i < deque.size(); i++) {
		if (Vector2Equals(deque[i], element)) {
			return true;
		}
	}
	return false;
}

bool eventTriggered(double interval) {
	double curr = GetTime();
	if (curr - lastUpdateTime >= interval) {
		lastUpdateTime = curr;
		return true;
	}
	return false;
}

class Food {
private:
	Vector2 pos;
	Texture2D texture;
public:
	Food(std::deque<Vector2> body) {
		Image img = LoadImage("apple.jpg");
		texture = LoadTextureFromImage(img);
		UnloadImage(img);
		pos = RandomPos(body);
	}
	~Food() {
		UnloadTexture(texture);
	}

	void setPos(Vector2 newPos) { pos = newPos; }
	Vector2 getPos() { return pos; }

	void Draw() {
		DrawTexture(texture, offset + pos.x * cellSize, offset + pos.y * cellSize, WHITE);
	}

	Vector2 randomCell() {
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);
		return Vector2{ x, y };
	}

	Vector2 RandomPos(std::deque<Vector2> body) {
		Vector2 position = randomCell();
		while (elementInDeque(position, body)) {
			position = randomCell();
		}

		return position;
	}
};

class Snake {
private:
	std::deque<Vector2> body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
	const Vector2 directionRight = { 1, 0 };
	const Vector2 directionLeft = { -1, 0 };
	const Vector2 directionUp = { 0, -1 };
	const Vector2 directionDown = { 0, 1 };
	Vector2 prevDirection = directionRight;
	bool addSegment = false;
public:

	std::deque<Vector2> getBody() { return body; }
	bool getSegmentState() { return addSegment; }
	Vector2 getPrevDirection() { return prevDirection; }

	void setSegmentState(bool val) { addSegment = val; }

	void Draw() {
		for (unsigned int i = 0; i < body.size(); ++i) {
			Rectangle rec = { offset + body[i].x * cellSize, offset + body[i].y * cellSize, cellSize, cellSize };
			DrawRectangleRounded(rec, 0.4, 0, greenDark);
		}
	}

	void changeDirection(Vector2 direction) {
		body.pop_back();
		body.push_front(Vector2Add(body[0], direction));
		prevDirection = direction;
	}

	void Update() {
		if (addSegment) {
			Vector2 direction;
			if (prevDirection == directionLeft) direction = directionLeft;
			else if (prevDirection == directionRight) direction = directionRight;
			else if (prevDirection == directionUp) direction = directionUp;
			else direction = directionDown;
			body.push_front(Vector2Add(body[0], direction));
			addSegment = false;
		}
		else {
			if (IsKeyDown(KEY_RIGHT) && prevDirection != directionLeft){
				changeDirection(directionRight);
			}
			else if (IsKeyDown(KEY_LEFT) && prevDirection != directionRight)
				changeDirection(directionLeft);
			else if (IsKeyDown(KEY_UP) && prevDirection != directionDown)
				changeDirection(directionUp);
			else if (IsKeyDown(KEY_DOWN) && prevDirection != directionUp)
				changeDirection(directionDown);
			else changeDirection(prevDirection);
		}
	}

	void ResetSnake() {
		body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
		prevDirection = directionRight;
	}
};

class Game {
public:
	Snake rot;
	Food apple = Food(rot.getBody());
	bool running = true;

	void Draw() {
		apple.Draw();
		rot.Draw();
	}

	void Update() {
		if (running) {
			rot.Update();
			CheckCollisionFood();
			CheckCollisionsEdges();
			CheckCollisionTail();
		}
	}

	void CheckCollisionFood() {
		if (Vector2Equals((rot.getBody())[0], apple.getPos())) {
			rot.setSegmentState(true);
			std::cout << "Eating food\n";
			apple.setPos(apple.RandomPos(rot.getBody()));
			score++;
		}
	}

	void CheckCollisionsEdges() {
		if ((rot.getBody())[0].x == cellCount || (rot.getBody())[0].x == -1 ||
			(rot.getBody())[0].y == cellCount || (rot.getBody())[0].y == -1)
			GameOver();
	}

	void GameOver() {
		std::cout << "Game Over\n";
		rot.ResetSnake();
		apple.setPos(apple.RandomPos(rot.getBody()));
		running = false;
		score = 0;
	}

	void CheckCollisionTail() {
		std::deque<Vector2> headLessBody = rot.getBody();
		headLessBody.pop_front();
		if (elementInDeque(rot.getBody()[0], headLessBody)) {
			GameOver();
		}
	}
};

void startGame() {
	std::cout << "Starting the game...\n";
	InitWindow(cellSize * cellCount + offset * 2, cellSize * cellCount + offset * 2, "SNAKE");
	SetTargetFPS(60);

	Game game = Game();

	while (!WindowShouldClose()) {
		BeginDrawing();

		if (eventTriggered(currentSpeed)) {
			game.Update();
			
			if (IsKeyDown(KEY_UP) ||
				IsKeyDown(KEY_DOWN) ||
				IsKeyDown(KEY_RIGHT) ||
				IsKeyDown(KEY_LEFT))
				game.running = true;
		}
		ClearBackground(greenLight);
		game.Draw();
		Rectangle rec = Rectangle{offset - 5, offset - 5, cellSize * cellCount +  10, cellSize * cellCount +  + 10};
		DrawRectangleLinesEx(rec, 5, greenDark);
		DrawText("Retro Snake", offset - 5, 20, 40, greenDark);
		DrawText(TextFormat("Score: %i", score), offset + 550, 20, 40, greenDark);

		EndDrawing();
	}

	CloseWindow();
}

int main() {
	startGame();
	return 0;
}