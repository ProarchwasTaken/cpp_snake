#pragma once

namespace window {
  const int WIDTH = 800;
  const int HEIGHT = 600;
}

namespace tile {
  const int SIZE = 20;

  const int ROWS = window::HEIGHT / tile::SIZE;
  const int COLUMNS = window::WIDTH / tile::SIZE;
}

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
