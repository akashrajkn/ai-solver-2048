#include "expectimax.h"

const int randomNumAdded[2] = {2, 4}; // numbers added at random
const double prob[2] = {1.0, 0.0}; // prob(adding 2) = prob(0) 

int bestDirection(const Board& board, int depth)
{
  double maxScore = 0;
  int best_dir = -1;

  for(int direction = 0; direction < 4; direction++)
  {
    Board aiBoard = board;
    move(aiBoard, direction);
    
    if (aiBoard == board) // if both are same, no change
    {
      continue;
    }
    
    double aiScore = aiSolverMove(aiBoard, 2 * depth - 1);
        
    if (aiScore >= maxScore)
    { 
      maxScore = aiScore;
      best_dir = direction;
    }
  }

  return best_dir;
}




int findBestDirection( int a, int b, int c, int d,
                       int e, int f, int g, int h,
                       int i, int j, int k, int l,
                       int m, int n, int o, int p,
                       int depth)
{
  Board board;
  board.cells[getIndex(0, 0)] = a;
  board.cells[getIndex(0, 1)] = b;
  board.cells[getIndex(0, 2)] = c;
  board.cells[getIndex(0, 3)] = d;
  board.cells[getIndex(1, 0)] = e;
  board.cells[getIndex(1, 1)] = f;
  board.cells[getIndex(1, 2)] = g;
  board.cells[getIndex(1, 3)] = h;
  board.cells[getIndex(2, 0)] = i;
  board.cells[getIndex(2, 1)] = j;
  board.cells[getIndex(2, 2)] = k;
  board.cells[getIndex(2, 3)] = l;
  board.cells[getIndex(3, 0)] = m;
  board.cells[getIndex(3, 1)] = n;
  board.cells[getIndex(3, 2)] = o;
  board.cells[getIndex(3, 3)] = p;
  
  return bestDirection(board, depth);
}



//finds the move which results in best avg score for a given grid
double bestPossibleMove(const Board& board, int depth)
{
  if (depth == 0)
  {   
    return hasMove(board) ? findHeuristic(board) : 0;
  }

  double maxScore = 0;

  for(int direction = 0; direction < 4; direction++)
  {
    Board aiBoard = board;
    move(aiBoard, direction);

    // if before and after moves are same
    if (aiBoard == board)  
    {
      continue;
    }
    
    double aiScore = 0;

    aiScore = aiSolverMove(aiBoard, depth - 1);

    if (aiScore > maxScore)
    {
      maxScore = aiScore;
    }
  }
    
  return maxScore;
}

double aiSolverMove(const Board& board, int depth)
{
  double totalScore = 0;
  double totalWt =0;
  
  for(int r=0; r < 4; r++)
  {
    for(int c = 0; c < 4; c++)
    {
      if (board.cells[getIndex(r, c)] == 0)
      {
        for(int i = 0; i<2; i++) //fora adding 2 and 4
        {
          Board player_board = board;
          player_board.cells[getIndex(r, c)] = randomNumAdded[i];

          double score = bestPossibleMove(player_board, depth - 1);

          totalScore += prob[i] * score;
          totalWt += prob[i]; // weigbhted avg
        }
      }
    }
  }

  if(totalWt==0)
    return 0;
  else
  {
    return totalScore/totalWt;
  }
}