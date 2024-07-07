#include <iostream>
#include <raylib.h>

#define CELL_ROWS 80
#define CELL_COLUMNS 80

typedef struct Cell {
	int width;
	int height;
	bool active;
	Color colour;
} Cell;

typedef struct Sand {
	Vector2 position;
	Color colour = YELLOW;
} Sand;

void updateSand(Sand sandparticles[], int sandCount, Cell cells[CELL_ROWS][CELL_COLUMNS]) {
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

const int screenWidth = 800;
const int screenHeight = 800;

int main(void)
{
	// Initialisation

	Cell cells[CELL_ROWS][CELL_COLUMNS];
	for (int i = 0; i < CELL_ROWS; i++) {
		for (int j = 0; j < CELL_COLUMNS; j++) {
			cells[i][j].width = screenWidth / CELL_ROWS;
			cells[i][j].height = screenHeight / CELL_COLUMNS;
			cells[i][j].active = false;
			cells[i][j].colour = RAYWHITE;
		}
	}

	Sand sandparticles[CELL_ROWS * CELL_COLUMNS];
	int sandCount = 0;

	InitWindow(screenWidth, screenHeight, "display");
	SetTargetFPS(60);

	// Main Game loop
	while (!WindowShouldClose()) {
		// Update
		updateSand(sandparticles, sandCount, cells);

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawFPS(30, 30);

		for (int i = 0; i < CELL_ROWS; i++) {
			for (int j = 0; j < CELL_COLUMNS; j++) {
				int x = j * cells[i][j].width;
				int y = i * cells[i][j].height;
				if (CheckCollisionPointRec(GetMousePosition(), { (float)x, (float)y, (float)cells[i][j].width, (float)cells[i][j].height }) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !cells[i][j].active) {
					if (sandCount < CELL_ROWS * CELL_COLUMNS) {
						cells[i][j].active = true;
						sandparticles[sandCount++].position = { (float)j,(float)i };
					}
				}

				DrawRectangle(x, y, cells[i][j].width, cells[i][j].height, cells[i][j].colour);
			}
		}

		// Draw Sand

		for (int k = 0; k < sandCount; k++) {
			int x = sandparticles[k].position.x * (screenHeight / CELL_COLUMNS);
			int y = sandparticles[k].position.y * (screenWidth / CELL_ROWS);
			DrawRectangle(x, y, screenWidth / CELL_ROWS, screenHeight / CELL_COLUMNS, sandparticles[k].colour);
		}

		EndDrawing();
	}

	// De-Initialisation
	CloseWindow();
}