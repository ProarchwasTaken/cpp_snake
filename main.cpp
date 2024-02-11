#include <cstddef>
#include <iostream>
#include <raylib.h>
#include "constants.h"
#include "scripts/classes.h"


/* Very important structure, as it's needed to setup the game's elements,
 * and delete them when they are not needed anymore. It also has a
 * boolean for whether the game should start or not. I had fun writing
 * this to be honest.*/
struct Game {
  bool started = false;
  Snake *player = NULL;
  Apple *apple = NULL;

  /* For setting up the game's elements and starting the game when the
   * player presses the enter key in the start screen. This is done 
   * through dynamic memory allocation.*/
  void setup() { 
    std::cout << "Starting the game.." << "\n";

    std::cout << "Allocating memory for the player instance." << "\n";
    player = new Snake(20, 20, 4, 0.1);

    std::cout << "Allocating memory for the apple instance." << "\n";
    apple = new Apple(*player);
    
    started = true;
  }

  /* For resetting the game when the player loses. Deletes all important
   * game elements from memory and takes the player back to the start
   * screen.*/
  void reset() {
    std::cout << "Resetting the game.." << "\n";

    std::cout << "Deleting the player from memory.." << "\n";
    delete player;
    player = NULL;

    std::cout << "Deleting the apple from memory.." << "\n";
    delete apple;
    apple = NULL;

    started = false;
  }

  /* For cleaning up any leftover stuff when the program is about to end.
   * This is to ensure that no memory.*/
  void cleanup() {
    std::cout << "Cleaning up..." << "\n";
    if (player != NULL) {
      std::cout << "Deleting the player from memory.." << "\n";
      delete player;
    }
    if (apple != NULL) {
      std::cout << "Deleting the apple from memory.." << "\n"; 
      delete apple;
    }
  }
};


/* This is a basic snake game I made to learn about raylib, dynamic memory
 * allocation, and making multiple file projects in C++. I had fun making
 * this.*/
int main() {
  InitWindow(window::WIDTH, window::HEIGHT, "Snake");
  SetTargetFPS(60);

  TileGrid grid = TileGrid();
  Game game;

  Snake* &player = game.player;
  Apple* &apple = game.apple;
  
  std::cout << "Everything seems to be good to go!" << "\n";
  while (WindowShouldClose() == false) 
  {
    if (game.started == false) 
    {
      if (IsKeyPressed(KEY_ENTER)) 
      {
        game.setup();
      }
    } 
    else {
      player->keyPressed();

      player->update();
      apple->update();

      if (player->game_over) {
        game.reset();
      }
    }
    
    BeginDrawing();
    if (game.started == false) 
    {
      ClearBackground(BLACK);
      DrawText("Press Enter to start the game.", 150, 284, 32, WHITE);
    } 
    else {
      grid.draw();
      apple->draw();
      player->draw();
    }
    EndDrawing();
  }

  game.cleanup();

  std::cout << "Thanks for playing!" << "\n";
  return 0;
}
