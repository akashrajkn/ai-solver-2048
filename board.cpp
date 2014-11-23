#include <cstdlib>
#include <vector>
#include "board.h"

using namespace std;

//heuristic
//1- topleft
//2- topright
static int weight_matrices[2][4][4] = 
{
    {{3,2,1,0},
     {2,1,0,-1},
     {1,0,-1,-2},
     {0,-1,-2,-3}},
    {{0,1,2,3},
     {-1,0,1,2},
     {-2,-1,0,1},
     {-3,-2,-1,0}}
};


//for merging(moving) a particular row or column
void move1(int cells[4])
{
  int target = 0;
  for (int i = 1; i < 4; i++)
  {
    int tVal = cells[target];  //tval -> target value
    int cVal = cells[i];  //cval -> current value
    if (cVal != 0){
      if (tVal == 0){
        cells[target] = cVal;
        cells[i] = 0;
      }
      else{
        if (tVal == cVal){
          cells[i] = 0;
          cells[target] <<= 1;
        }
        else{
          cells[i] = 0;
          cells[target + 1] = cVal;
        }
        target++;
      }
    }
  }
}


void moveUP(Board& board)
{
  for (int column = 0; column < 4; column++)
  {
    int cells[4];
    for (int y = 0; y < 4; y++)
    {
      cells[y] = board.cells[getIndex(column, y)];
    }
    move1(cells);
    for (int y = 0; y < 4; y++)
    {
      board.cells[getIndex(column, y)] = cells[y];
    }
  }
}


void moveDOWN(Board& board)
{
  for (int column = 0; column < 4; column++)
  {
    int cells[4];
    for (int y = 0; y < 4; y++)
    {
      cells[y] = board.cells[getIndex(column, 3 - y)];
    }
    move1(cells);
    for (int y = 0; y < 4; y++)
    {
      board.cells[getIndex(column, 3 - y)] = cells[y];
    }
  }
}


void moveLEFT(Board& board)
{
  for (int row = 0; row < 4; row++)
  {
    int cells[4];
    for (int x = 0; x < 4; x++)
    {
      cells[x] = board.cells[getIndex(x, row)];
    }
    move1(cells);
    for (int x = 0; x < 4; x++)
    {
      board.cells[getIndex(x, row)] = cells[x];
    }
  }
}


void moveRIGHT(Board& board)
{
  for (int row = 0; row < 4; row++)
  {
    int cells[4];
    for (int x = 0; x < 4; x++)
    {
      cells[x] = board.cells[getIndex(3 - x, row)];
    }
    move1(cells);
    for (int x = 0; x < 4; x++)
    {
      board.cells[getIndex(3 - x, row)] = cells[x];
    }
  }
}


void move(Board& board, int direction)
{
  if(direction==0)
  {
    moveUP(board);
  }
  else if(direction==1)
  {
    moveRIGHT(board);
  }
  else if(direction==2)
  {
    moveDOWN(board);
  }
  else if(direction==3)
  {
    moveLEFT(board);
  }
}


int findHeuristic(const Board& board)
{
  int best = 0;
  
  for (int i = 0; i < 2; i++)
  {
    int s = 0;
    for (int y = 0; y < 4; y++)
    {
      for (int x = 0; x < 4; x++)
      {
        s += weight_matrices[i][y][x] * (int)board.cells[getIndex(x, y)];
      }
    }
    s = abs(s); //topright = -(bottom left) and topleft= -(bottomright)
    if (s > best)
    {
      best = s;
    }
  }
  return best;
}


bool hasMove(const Board& board)
{
  for (int x = 0; x < 4; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      if (board.cells[getIndex(x, y)] == 0)
        return true;
      if (x < 3 && board.cells[getIndex(x, y)] == board.cells[getIndex(x + 1, y)])
        return true;
      if (y < 3 && board.cells[getIndex(x, y)] == board.cells[getIndex(x, y + 1)])
        return true;
    }
  }
  return false;
}


int maxCell(const Board& board)
{
  int h = 0;
  for (int i = 0; i < 16; i++)
  {
    if (board.cells[i] > h)
    {
      h = board.cells[i];
    }
  }
  return h;
}