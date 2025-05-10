#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>

const int WindowWidth = 800, WindowHeight = 500;
const int BlockWidth = 8;
const int offset = 2;

void WaitTime(double seconds) {
	std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

std::vector<int> GetRandomVector(int size) {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	std::vector<int> vec;
	for (int i = 0; i < size; ++i) {
		vec.push_back(std::rand() % 400 + 10);
		std::cout << vec[i] << " ";
	}

	return vec;
}

void DisplayVector(std::vector<int> vec) {
	std::cout << "\n\n\nVector:\n";
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
}

class Block {
private:
	float x, y;
	float height, width;
public:
	Block() : x(0), y(0), height(0), width(0) {}
	Block(float x, float y, float height)
		:x(x), y(y), height(height), width(BlockWidth) {}

	void Draw(Color color) const {
		Rectangle rec = Rectangle{ x + offset, y, width, height };
		DrawRectangleRounded(rec, 0.2, 0, color);
	}
};


class VectorBlocks {
private:
	size_t size;
	std::vector<Block> blocks;
public:
	VectorBlocks(std::vector<int> arr) : size(arr.size()){
		blocks.resize(size);
		FillVectorBlocks(arr);
	}

	size_t GetSize() const { return size; }
	std::vector<Block>& GetBlocksRef() { return blocks; }

	void SetHeight(int index, float height) {
		float x = index * (BlockWidth + offset);
		float y = WindowHeight - height;
		blocks[index] = Block(x, y, height);
	}

	void FillVectorBlocks(std::vector<int> arr) {
		for (int i = 0; i < size; i++) {
			Block block = Block(i * (BlockWidth + offset), WindowHeight - arr[i], arr[i]);
			blocks[i] = block;
		}
	}

	void DrawBlocks() {
		for (int i = 0; i < size; i++) {
			blocks[i].Draw(WHITE);
		}
	}

}; 

void VisualSwap(VectorBlocks& blocks, std::vector<int>& arr, int i, int j) {
	std::swap(arr[i], arr[j]);
	blocks.SetHeight(i, arr[i]);
	blocks.SetHeight(j, arr[j]);

	BeginDrawing();
	ClearBackground(BLACK);
	blocks.DrawBlocks();
	EndDrawing();

	WaitTime(0.02);
}

int Partition(std::vector<int>& arr, int low, int high, VectorBlocks& blocks) {
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j < high; ++j) {
		if (arr[j] < pivot) {
			i++;
			VisualSwap(blocks, arr, i, j);
		}
	}
	VisualSwap(blocks, arr, i + 1, high);
	return i + 1;
}

void QuickSort(std::vector<int>& arr, int low, int high, VectorBlocks& blocks) {
	if (low < high) {
		int pi = Partition(arr, low, high, blocks);
		QuickSort(arr, low, pi - 1, blocks);
		QuickSort(arr, pi + 1, high, blocks);
	}
}


void startGame() {
	InitWindow(WindowWidth, WindowHeight, "Quicksort");
	SetTargetFPS(144);

	std::vector<int> array = GetRandomVector(80);
	VectorBlocks blocks = VectorBlocks(array);

	BeginDrawing();
	ClearBackground(BLACK);
	blocks.DrawBlocks();
	EndDrawing();
	WaitTime(1.0);

	QuickSort(array, 0, array.size() - 1, blocks);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		blocks.DrawBlocks();
		EndDrawing();
	}

	CloseWindow();
}

int main() {
	startGame();
	return 0;
}
