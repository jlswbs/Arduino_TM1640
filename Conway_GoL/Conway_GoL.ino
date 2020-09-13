// Conway's Game of Life //

#include <TM1640.h>
#include <TM16xxMatrix.h>

#define WIDTH  16
#define HEIGHT 8
TM1640 module(3, 2);
TM16xxMatrix matrix(&module, WIDTH, HEIGHT);

  bool grid[2][WIDTH][HEIGHT];
  int current;

void setup()
{

  srand(analogRead(0));

  module.clearDisplay();

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) grid[0][x][y] = rand()%2;
  }

}

void loop()
{

  DrawGrid();
  RunGrid();

}

void RunGrid(){
  
  int x, y;
  int count;
  int value = 0;
  int new_grid;

  new_grid = 1 - current;
  
  for (y = 0; y < HEIGHT; y++) {
  
    for (x = 0; x < WIDTH; x++) {
      
      count = Neighbours(x, y);
      
      if (count < 2 || count > 3) { value = 0; }
      else if (count == 3) { value = 3; }
      else { value = grid[current][x][y]; }
    
      grid[new_grid][x][y] = value;
    
    }
  }
  
  current = new_grid;
}

int Neighbours(int x, int y){
  
  int i, j;
  int result = 0;

  x--;
  y--;
  
  for (i = 0; i < 3; i++) {
  
    if (y < 0 || y > (HEIGHT - 1)) continue;

    for (j = 0; j < 3; j++) {
      if (x < 0 || x > (WIDTH - 1)) continue;
      if (i==1 && j == 1) { x++; continue; }
      if (grid[current][x][y]) result++;
      x++;
    }
    y++;
    x -= 3;
  }
  
  return result;
}

void DrawGrid()
{
  int  x,  y;
  bool coll;
  
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
        if(grid[current][x][y]) coll = true;
        else coll = false;
        matrix.setPixel(x, y, coll);
    }
  }
}
