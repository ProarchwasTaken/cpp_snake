#include <string>
#include <list>
#include <array>
#include <vector>
#include <raylib.h>
#include "../constants.h"

using std::string, std::array, std::list, std::vector;

/* The game's grid, this is here because I couldn't draw a grid on the
 * screen without setting up a camera and using 2D Move. So I opted to
 * set it up from scratch.
 *
 * The instance of this class will draw a texture to the screen. This 
 * texture is actually created within the program itself rather than
 * loading up a separate file.*/
class TileGrid {
private:
  Texture2D grid_texture;

public:
  TileGrid();
  ~TileGrid();

  Texture2D setupGridTexture();
  void draw();
};

class SnakeBody;


/* The snake is the main element of the game as they are controlled by
 * the player.*/
class Snake {
private:
  int score = 0;

  list<SnakeBody> body_list;
  list<SnakeBody>::iterator body;

  int next_direction = 0;
  int invalid_direction = 2;

  float move_delay;
  double move_timestamp;

public:
  Snake(int tileX, int tileY, int length, float move_delay);
  ~Snake();
  bool game_over = false;
  int length;

  Rectangle head_rect;

  void keyPressed();
  void update();

  bool outsideScreen();
  bool bodyCollision();
  list<array<int, 2>> getOccupiedTiles();

  void incrementScore(int magnitude);
  void prepareGameOver(string reason);
  
  void bodyTick();
  void move();

  void draw();
};


/* The body tiles of the snake. Each instance of the SnakeBody will be
 * apart of a list created by the Snake class itself. They will also have
 * a counter that will tick down whenever the snake moves. When that
 * counter hits 0, the instance will be removed from the list and be 
 * deleted.*/
class SnakeBody {
private:
  int counter;

public:
  SnakeBody(float spawn_x, float spawn_y, int start_count);
  Rectangle rect;

  void tickCounter();
  bool counterIsZero();
  void draw();
};


/* The apple. When the head of the snake collides with it, it's length
 * will increase and the apply will be positioned to a random available
 * tile. If there are no available tiles left, the game will end.*/
class Apple {
private:
  Snake *player;
  Rectangle rect;

public:
  Apple(Snake &player);
  void update();

  // TODO: Write this method after fining the getOccupiedTiles() method.
  bool tileOccupied(int tileX, int tileY, list<array<int, 2>> &occupied);
  vector<array<int, 2>> getAvailableTiles();
  void repositionApple();
  
  void draw();
};
