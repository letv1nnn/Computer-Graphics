#include "raylib.h"
#include "vector"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

const int WindowWidth = 800, WindowHeight = 500;
const int BlockWidth = 10;

class Block {
private:
	int x, y, BlockHeight;
public:
	Block() {}
	Block(int height, int x) 
		:BlockHeight(height), x(x), y(WindowHeight - height) {}

	void Draw() const {
		DrawRectangle(x, y, BlockWidth, BlockHeight, WHITE);
	}

	void DrawSpecial() const {
		DrawRectangle(x, y, BlockWidth, BlockHeight, GREEN);
	}

};

class Blocks {
private:
	Block *blocks;
	int size;
public:
	Blocks(std::vector<int> array) {
		blocks = new Block[array.size()];
		if (blocks == NULL) exit(1);
		int spacing = BlockWidth + 2;
		for (int i = 0; i < array.size(); i++) {
			Block block(array[i], i * spacing);
			blocks[i] = block;
		}
		size = array.size();
	}
	~Blocks() {
		delete[] blocks;
		blocks = nullptr;
	}

	void Update(std::vector<int>& array) {
		int spacing = BlockWidth + 2;
		for (int i = 0; i < size; i++) {
			blocks[i] = Block(array[i], i * spacing);
		}
	}

	Block* getBlocks() {
		return blocks;
	}

	void DisplayBlocks(int special = -1) {
		for (int i = 0; i < size; i++)
			if (i == special) blocks[i].DrawSpecial();
			else blocks[i].Draw();
	}

	
};

static void startVisualizing() {
	InitWindow(WindowWidth, WindowHeight, "Sorting Visualizing");
	SetTargetFPS(1);

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	std::vector<int> vec;
	for (int i = 0; i < 67; ++i) {
		vec.push_back(std::rand() % 400);
		std::cout << vec[i] << " ";
	}

	Blocks blocks(vec);
	int i = 0;
	bool sorting = true;


	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);
		if (sorting) {
			if (i < vec.size() - 1) {
				int sm = i;
				for (int j = i + 1; j < vec.size(); j++) {
					if (vec[j] < vec[sm]) sm = j;
				}
				std::swap(vec[i], vec[sm]);

				blocks.Update(vec);
				blocks.DisplayBlocks(sm);

				i += 1;
			}
			else sorting = false;
		}
		else {
			blocks.DisplayBlocks();
		}

		EndDrawing();
	}

	CloseWindow();
}

int main() {
	startVisualizing();
	return 0;
}
