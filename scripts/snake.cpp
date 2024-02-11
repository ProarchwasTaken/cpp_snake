#include <iostream>
#include <list>
#include <array>
#include <raylib.h>
#include "../constants.h"
#include "classes.h"

using std::array, std::list;


// Snake Class
Snake::Snake(int tileX, int tileY, int length, float move_delay) {
  head_rect.x = tileX * tile::SIZE;
  head_rect.y = tileY * tile::SIZE;
  head_rect.width = tile::SIZE;
  head_rect.height = tile::SIZE;

  this->length = length;
  this->move_delay = move_delay;

  move_timestamp = GetTime();
}

Snake::~Snake() {
  body_list.clear();
}

/* Is called once per frame. Most of the important stuff runs on a delay 
 * instead of every frame.*/
void Snake::update() {
  bool delay_over = GetTime() - move_timestamp >= move_delay;

  if (delay_over) {
    bodyTick();
    move();

    move_timestamp = GetTime();
  }
}

/* For checking if the head of the snake is outside of the screen.
 * In such a scenario, the game will reset. Is called when the move
 * method is called.*/
bool Snake::outsideScreen() {
  int right_x = head_rect.x + head_rect.width;
  int bottom_y = head_rect.y + head_rect.height;

  if (head_rect.x >= window::WIDTH || head_rect.y >= window::HEIGHT) {
    return true;
  }
  else if (right_x <= 0 || bottom_y <= 0) {
    return true;
  }
  else {
    return false;
  }
}

/* Returns true if the head of the snake colides with it's body. In such a
 * scenario, the game will reset. Is called each time the snake moves.
 * Returns false if no collisions are detected.*/
bool Snake::bodyCollision() {
  for (body = body_list.begin(); body != body_list.end(); body++)
  {
    if (CheckCollisionRecs(head_rect, body->rect)) {
      return true;
    }
  }

  return false;
}

/* Returns a list of arrays that consist of the tile positions of the
 * snake's head and body. This is used by the apple class.*/
list<array<int, 2>> Snake::getOccupiedTiles() {
  std::cout << "Getting a list of every tile the snake is currently" <<
    " occupying." << "\n";
  list<array<int, 2>> occupied_tiles;

  array<int, 2> head_tile_position;

  head_tile_position[0] = head_rect.x / tile::SIZE;
  head_tile_position[1] = head_rect.y / tile::SIZE;

  occupied_tiles.push_front(head_tile_position);

  for (body = body_list.begin(); body != body_list.end(); body++) {
    array<int, 2> tile_position;

    tile_position[0] = body->rect.x / tile::SIZE;
    tile_position[1] = body->rect.y / tile::SIZE;

    occupied_tiles.push_front(tile_position);
  }

  return occupied_tiles;
}

/* For adding a new SnakeBody instance to the list, and ticking down the 
 * counters of all existing instances in the list.*/
void Snake::bodyTick() {
  body_list.push_front(SnakeBody(head_rect.x, head_rect.y, length));

  for (body = body_list.begin(); body != body_list.end(); body++) 
  {
    body->tickCounter();
    if (body->counterIsZero()) {
      body_list.pop_back();
    }
  }
}

/* Moves the snake in a certain direction when called. After that's done,
 * the game checks if the head of the snake is out of bounds, or has
 * collided with it's body.*/
void Snake::move() {
  switch (next_direction)
  {
    case RIGHT:
      head_rect.x += tile::SIZE;
      invalid_direction = LEFT;
      break;
    case DOWN:
      head_rect.y += tile::SIZE;
      invalid_direction = UP;
      break;
    case LEFT:
      head_rect.x -= tile::SIZE;
      invalid_direction = RIGHT;
      break;
    case UP:
      head_rect.y -= tile::SIZE;
      invalid_direction = DOWN;
      break;
  }

  if (outsideScreen()) {
    prepareGameOver("Out of bounds");
  }
  if (bodyCollision()) {
    prepareGameOver("Collided with body");
  }
}

/* Since score is a private variable. This method is written to increment
 * the value when needed.*/
void Snake::incrementScore(int magnitude) {
  score += magnitude;
}

/* Called when the head of the snake reaches out of bounds or collides
 * with it's own tail.*/
void Snake::prepareGameOver(string reason) {
  std::cout << "==================================" << "\n";
  std::cout << "GAME OVER: " << reason << "\n";
  std::cout << "Score: " << score << "\n";
  std::cout << "==================================" << "\n";

  game_over = true;
}

/* For checking for player input and changing the player's next_direction
 * as long as it isn't invalid.*/
void Snake::keyPressed() {
  if (IsKeyPressed(KEY_RIGHT) && invalid_direction != RIGHT) {
    next_direction = RIGHT;
  }
  if (IsKeyPressed(KEY_DOWN) && invalid_direction != DOWN) {
    next_direction = DOWN;
  }
  if (IsKeyPressed(KEY_LEFT) && invalid_direction != LEFT) {
    next_direction = LEFT;
  }
  if (IsKeyPressed(KEY_UP) && invalid_direction != UP) {
    next_direction = UP;
  }
}

void Snake::draw() {
  DrawRectangleRec(head_rect, GREEN);

  for (body = body_list.begin(); body != body_list.end(); body++) {
    body->draw();
  }
}


// SnakeBody Class
SnakeBody::SnakeBody(float spawn_x, float spawn_y, int start_count) {
  rect = {spawn_x, spawn_y, tile::SIZE, tile::SIZE};
  counter = start_count;
}

/* Decrements the counter by one when called. The counter's start value
 * upon initialization is equal to the length of the snake at the time.*/
void SnakeBody::tickCounter() {
  counter -= 1;
}

/* Returns true if the counter is 0. Is called after the tickCounter
 * method is called. In the occasion of the counter hitting 0, the 
 * SnakeBody instance will be deleted.*/
bool SnakeBody::counterIsZero() {
  return counter == 0;
}

void SnakeBody::draw() {
  DrawRectangleRec(rect, GREEN);
}
