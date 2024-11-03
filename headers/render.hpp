#pragma once
#include <SDL.h>
#include <vector>

extern const int CELL_SIZE;
extern const int MATRIX_HEIGHT;
extern const int MATRIX_WIDTH;
extern SDL_Renderer *gRenderer;


void render();
void renderMatrix(const std::vector<std::vector<int>> &matrix );


