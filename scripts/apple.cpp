#include <iostream>
#include <list>
#include <array>
#include <raylib.h>
#include "../constants.h"
#include "classes.h"

using std::list, std::array;


Apple::Apple(Snake &player) {
  this->player = &player;
  this->rect = {0, 0, tile::SIZE, tile::SIZE};

  repositionApple();
}

/* Called once every frame. Just checks if the head of the snake has
 * collided with it.*/
void Apple::update() {
  if (CheckCollisionRecs(player->head_rect, rect)) {
    std::cout << "The snake's head has collided with the apple." << "\n";
    player->length++;
    player->incrementScore(10);

    repositionApple();
  }
}

/* Returns true if the specified tile is occupied by the snake's head or
 * body. Otherwise, it will return false.*/
bool Apple::tileOccupied(int tileX, int tileY, list<array<int, 2>> &occupied) {
  list<array<int, 2>>::iterator occupied_tile;
  array<int, 2> tile_toBeChecked = {tileX, tileY};

  for (occupied_tile = occupied.begin(); occupied_tile != occupied.end(); occupied_tile++) {
    if (tile_toBeChecked == *occupied_tile) {
      return true;
    }
  }

  return false;
}

/* Returns an vector container that consists of arrays that represent 
 * every available tile that the apple can move to once it's been eaten 
 * by the snake.*/
vector<array<int, 2>> Apple::getAvailableTiles() {
  list<array<int, 2>> occupied_tiles = player->getOccupiedTiles();
  vector<array<int, 2>> available_tiles;

  std::cout << "Getting a vector of avaliable tiles." << "\n";
  for (int y = 0; y < tile::ROWS; y++)
  {
    for (int x = 0; x < tile::COLUMNS; x++)
    {
      if (tileOccupied(x, y, occupied_tiles) == false) {
        array<int, 2> avail_tile = {x, y};
        available_tiles.push_back(avail_tile);
      }
    }
  }

  return available_tiles;
}

/* For repositioning the apple to an random availiable tile when the snake
 * eats it. The game will end if there are no availiable tiles left.*/
void Apple::repositionApple() {
  std::cout << "Attempting to reposition the apple to a random available"
    << " tile on the grid." << "\n";
  vector<array<int, 2>> available_tiles = getAvailableTiles();
  int vector_size = available_tiles.size();

  if (vector_size == 0) {
    player->prepareGameOver("Ran out of availiable space.");
    return;
  }

  int random_value = GetRandomValue(0, vector_size - 1);
  array<int, 2> chosen_tile = available_tiles.at(random_value);

  rect.x = chosen_tile[0] * tile::SIZE;
  rect.y = chosen_tile[1] * tile::SIZE;
  std::cout << "Successfully repositioned the apple!" << "\n";
}

void Apple::draw() {
  DrawRectangleRec(rect, RED);
}
