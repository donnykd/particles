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
	int width;
	int height;
	Color colour = YELLOW;
} Sand;

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

	Sand sand[CELL_ROWS][CELL_COLUMNS];

	InitWindow(screenWidth, screenHeight, "display");
	SetTargetFPS(60);

	// Main Game loop
	while (!WindowShouldClose()) {
		// Update
		for (int i = CELL_ROWS - 1; i >= 0; i--) {
			for (int j = 0; j < CELL_COLUMNS; j++) {
				if (cells[i][j].active && !cells[i + 1][j].active) {
					int newI = i + 1;
					if (newI < CELL_ROWS) {
						cells[newI][j].colour = sand[i][j].colour;
						cells[newI][j].active = true;
						cells[i][j].colour = RAYWHITE;
						cells[i][j].active = false;
					}
				}
				else if (cells[i][j].active && !cells[i + 1][j - 1].active) {
					int newI = i + 1;
					int newJ = j - 1;
					if (newI < CELL_ROWS && newJ < CELL_COLUMNS) {
						cells[newI][newJ].colour = sand[i][j].colour;
						cells[newI][newJ].active = true;
						cells[i][j].colour = RAYWHITE;
						cells[i][j].active = false;
					}
				}
				else if (cells[i][j].active && !cells[i + 1][j + 1].active) {
					int newI = i + 1;
					int newJ = j + 1;
					if (newI < CELL_ROWS && newJ < CELL_COLUMNS) {
						cells[newI][newJ].colour = sand[i][j].colour;
						cells[newI][newJ].active = true;
						cells[i][j].colour = RAYWHITE;
						cells[i][j].active = false;
					}
				}
			}
		}

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawFPS(30, 30);

		for (int i = 0; i < CELL_ROWS; i++) {
			for (int j = 0; j < CELL_COLUMNS; j++) {
				int x = j * cells[i][j].width;
				int y = i * cells[i][j].height;
				if (CheckCollisionPointRec(GetMousePosition(), { (float)x, (float)y, (float)cells[i][j].width, (float)cells[i][j].height }) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !cells[i][j].active) {
					cells[i][j].colour = sand[i][j].colour;
					cells[i][j].active = true;
				}

				DrawRectangle(x, y, cells[i][j].width, cells[i][j].height, cells[i][j].colour);
				DrawRectangleLines(x, y, cells[i][j].width, cells[i][j].height, RAYWHITE);
			}
		}

		EndDrawing();
	}

	// De-Initialisation
	CloseWindow();
}