#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <time.h>
#include "expectimax.h"  //expectimax.h includes board.h, otherwise use #pragma once in header files

using namespace std;

Board br;
int rnum;
void printBoard();
void generateRNum();

int main()
{
  int temp, direction;
  bool gameSolved = false;
  srand(time(NULL));

  //intitalize
  rnum = rand()%16;
  temp =rnum;

  br.cells[rnum] = 2;

  generateRNum();
  printBoard();

  while(hasMove(br))
  {
    for(int i=0; i<16; ++i)
    {
      if(br.cells[i]==2048)
      {
        gameSolved = true;
        break;
      }
    }

    if(gameSolved)
    {
      break;
    }

    direction = findBestDirection( br.cells[0], br.cells[1], br.cells[2], br.cells[3],
                                  br.cells[4], br.cells[5], br.cells[6], br.cells[7],
                                  br.cells[8], br.cells[9], br.cells[10],br.cells[11],
                                  br.cells[12],br.cells[13],br.cells[14],br.cells[15],
                                  3 );

    cout<<"direction=="<<direction<<"\n";

    move(br, direction);

    generateRNum();
    printBoard();
  }

  if(gameSolved)
    cout<<"ai solved it\n";
  else
    cout<<"ai didnt solve it\n";

  return 0;
}


void printBoard()
{
  cout<<"\n";
  for(int i=0; i<16; ++i)
  {
    cout<<br.cells[i]<<" ";

    if(i%4==3)
    {
      cout<<"\n";
    }
  }
  cout<<"\n";
}


void generateRNum()
{
  rnum = rand()%16;

  while(br.cells[rnum]!=0)
  {
    rnum = rand()%16;
  }

  br.cells[rnum] = 2;
}
