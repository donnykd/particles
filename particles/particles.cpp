#include <iostream>
#include <raylib.h>

#define CELL_ROWS 300
#define CELL_COLUMNS 300

struct Cell {
	int width;
	int height;
	bool active;
	Color colour;
};


struct Sand {
	Vector2 position;
	Color colour = YELLOW;
};

struct Water {
	Vector2 position;
	Color colour = BLUE;
};

void updateSand(Sand* sandparticles, int sandCount, Water* waterparticles, int waterCount, Cell** cells) {
	for (int k = 0; k < sandCount; k++) {
		int i = (int)sandparticles[k].position.y;
		int j = (int)sandparticles[k].position.x;
		if (i + 1 < CELL_ROWS && !cells[i + 1][j].active) {
			cells[i][j].active = false;
			cells[i + 1][j].active = true;
			sandparticles[k].position.y += 1;
		}
		else if (i + 1 < CELL_ROWS && j - 1 >= 0 && !cells[i + 1][j - 1].active) {
			cells[i][j].active = false;
			cells[i + 1][j - 1].active = true;
			sandparticles[k].position.y += 1;
			sandparticles[k].position.x -= 1;
		}
		else if (i + 1 < CELL_ROWS && j + 1 < CELL_COLUMNS && !cells[i + 1][j + 1].active) {
			cells[i][j].active = false;
			cells[i + 1][j + 1].active = true;
			sandparticles[k].position.y += 1;
			sandparticles[k].position.x += 1;
		}
	}
}

void updateWater(Water* waterparticles, int waterCount, Cell** cells) {
	for (int k = 0; k < waterCount; k++) {
		int i = (int)waterparticles[k].position.y;
		int j = (int)waterparticles[k].position.x;
		if (i + 1 < CELL_ROWS && !cells[i + 1][j].active) {
			cells[i][j].active = false;
			cells[i + 1][j].active = true;
			waterparticles[k].position.y += 1;
		}
		else if (j - 1 >= 0 && !cells[i][j - 1].active) {
			cells[i][j].active = false;
			cells[i][j - 1].active = true;
			waterparticles[k].position.x -= 1;
		}
		else if (j + 1 >= 0 && !cells[i][j + 1].active) {
			cells[i][j].active = false;
			cells[i][j + 1].active = true;
			waterparticles[k].position.x += 1;
		}
	}
}

const int screenWidth = 900;
const int screenHeight = 900;

int main(void)
{
	// Initialisation

	Cell** cells = new Cell*[CELL_ROWS];
	for (int i = 0; i < CELL_ROWS; i++) {
		cells[i] = new Cell[CELL_COLUMNS];
		for (int j = 0; j < CELL_COLUMNS; j++) {
			cells[i][j].width = screenWidth / CELL_ROWS;
			cells[i][j].height = screenHeight / CELL_COLUMNS;
			cells[i][j].active = false;
			cells[i][j].colour = RAYWHITE;
		}
	}

	Sand* sandparticles = new Sand[CELL_ROWS * CELL_COLUMNS];
	Water* waterparticles = new Water[CELL_ROWS * CELL_COLUMNS];
	int sandCount = 0;
	int waterCount = 0;

	InitWindow(screenWidth, screenHeight, "display");
	SetTargetFPS(60);

	// Main Game loop
	while (!WindowShouldClose()) {
		// Update

		updateSand(sandparticles, sandCount, waterparticles, waterCount, cells);
		updateWater(waterparticles, waterCount, cells);

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawFPS(30, 30);

		for (int i = 0; i < CELL_ROWS; i++) {
			for (int j = 0; j < CELL_COLUMNS; j++) {
				int x = j * cells[i][j].width;
				int y = i * cells[i][j].height;
				if (CheckCollisionPointRec(GetMousePosition(), { (float)x, (float)y, (float)cells[i][j].width, (float)cells[i][j].height }) && !cells[i][j].active) {
					if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && waterCount < CELL_ROWS * CELL_COLUMNS) {
						cells[i][j].active = true;
						waterparticles[waterCount++].position = { (float)j,(float)i };
					}
					else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && sandCount < CELL_ROWS * CELL_COLUMNS) {
						cells[i][j].active = true;
						sandparticles[sandCount++].position = { (float)j,(float)i };
					}
				}

				DrawRectangle(x, y, cells[i][j].width, cells[i][j].height, cells[i][j].colour);
			}
		}

		// Draw Sand

		for (int k = 0; k < sandCount; k++) {
			int x = (int) sandparticles[k].position.x * (screenHeight / CELL_COLUMNS);
			int y = (int) sandparticles[k].position.y * (screenWidth / CELL_ROWS);
			DrawRectangle(x, y, screenWidth / CELL_ROWS, screenHeight / CELL_COLUMNS, sandparticles[k].colour);
		}

		// Draw Water
		for (int k = 0; k < waterCount; k++) {
			int x = (int) waterparticles[k].position.x * (screenHeight / CELL_COLUMNS);
			int y = (int) waterparticles[k].position.y * (screenWidth / CELL_ROWS);
			DrawRectangle(x, y, screenWidth / CELL_ROWS, screenHeight / CELL_COLUMNS, waterparticles[k].colour);
		}

		EndDrawing();
	}
	for (int i = 0; i < CELL_ROWS; i++) {
		delete[] cells[i];
	}

	delete[] cells;
	delete[] sandparticles;

	// De-Initialisation
	CloseWindow();
}