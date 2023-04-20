#pragma once
#include <SFML/Graphics.hpp>

// global variables
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int TILE_SIZE = 32;

// grid
const int GRID_WIDTH = WINDOW_WIDTH / TILE_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / TILE_SIZE;

// set initial spawn to the middle
const int INITIAL_X = WINDOW_WIDTH / 2 / TILE_SIZE;
const int INITIAL_Y = WINDOW_HEIGHT / 2 / TILE_SIZE + 1;