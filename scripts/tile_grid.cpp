#include <iostream>
#include <raylib.h>
#include "../constants.h"
#include "classes.h"

TileGrid::TileGrid() {
  this->grid_texture = setupGridTexture();
}

TileGrid::~TileGrid() {
  std::cout << "Unloading grid texture..." << "\n";
  UnloadTexture(grid_texture);
}

Texture2D TileGrid::setupGridTexture() {
  /* For creating and returning a basic grid texture. This is done by 
   * first generating an image, and drawing some squares on it. That
   * image will then be converted into a texture.*/
  std::cout << "Creating image to draw the grid on..." << "\n";
  Image grid_img = GenImageColor(window::WIDTH, window::HEIGHT, DARKGRAY);

  Vector2 drawn_size = {tile::SIZE - 1, tile::SIZE - 1};
  Vector2 next_position;

  for (int y = 0; y < tile::ROWS; y++) 
  {
    for (int x = 0; x < tile::COLUMNS; x++) 
    {
      next_position.x = x * tile::SIZE;
      next_position.y = y * tile::SIZE;

      ImageDrawRectangleV(&grid_img, next_position, drawn_size, BLACK);
    }
  }

  std::cout << "Creating texture from said image..." << "\n";
  Texture2D final_texture = LoadTextureFromImage(grid_img);
  UnloadImage(grid_img);

  return final_texture;
}

void TileGrid::draw() {
  DrawTexture(grid_texture, 0, 0, WHITE);
}
