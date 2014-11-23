#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <utility>
#include "board.h"

int findBestDirection( int a, int b, int c, int d,
                       int e, int f, int g, int h,
                       int i, int j, int k, int l,
                       int m, int n, int o, int p,
                       int depth);

// finds expected average over a board state
double aiSolverMove(const Board& board, int depth);

double bestPossibleMove(const Board& board, int depth);

int bestDirection(const Board& board, int depth);


