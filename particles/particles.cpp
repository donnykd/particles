#include <iostream>
#include <raylib.h>

typedef struct Cell {
	int width;
	int height;
	bool active;
	Color colour;
} Cell;

const int screenWidth = 1280;
const int screenHeight = 720;

int main(void)
{
	// Initialisation

	Cell cells[5][5];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cells[i][j].width = screenWidth / 5;
			cells[i][j].height = screenHeight / 5;
			cells[i][j].active = false;
			cells[i][j].colour = RAYWHITE;
		}
	}

	InitWindow(screenWidth, screenHeight, "display");
	SetTargetFPS(60);

	// Main Game loop
	while (!WindowShouldClose()) {
		// Update

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawFPS(30, 30);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				int x = j * cells[i][j].width;
				int y = i * cells[i][j].height;
				if (CheckCollisionPointRec(GetMousePosition(), { (float)x, (float)y, (float)cells[i][j].width, (float)cells[i][j].height }) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
					cells[i][j].colour = RED;
					cells[i][j].active = true;
				}
				else
				{
					cells[i][j].colour = RAYWHITE;
					cells[i][j].active = false;
				}
				DrawRectangle(x, y, cells[i][j].width, cells[i][j].height, cells[i][j].colour);
				DrawRectangleLines(x, y, cells[i][j].width, cells[i][j].height, BLACK);
			}
		}

		EndDrawing();
	}


	// De-Initialisation
	CloseWindow();

}