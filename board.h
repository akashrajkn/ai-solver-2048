#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

struct Board
{
  int cells[16];

  Board()
  {
    for(int i = 0; i < 16; cells[i] = 0, i++);
  }

  inline bool operator ==(const Board& board) const //operator overloading
  {
    bool equal = true;
    for(int i=0; i<16; ++i)
    {
      if(cells[i]!=board.cells[i])
      {
        equal = false;
        break;
      }
    }
    return equal;
  }
};


inline int getIndex(int r, int c)
{
  return 4*r+c;
}


// Heuristic fucntion function
int findHeuristic(const Board& board);

// Checks for dead end
bool hasMove(const Board& board);

// Gets the maxCell tile in the board
int maxCell(const Board& board);

//row col move
void move1(int cells[4]);

void moveUP(Board& board);

void moveDOWN(Board& board);

void moveLEFT(Board& board);

void moveRIGHT(Board& board);

void move(Board& board, int direction);

