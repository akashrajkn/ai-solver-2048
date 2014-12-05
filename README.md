ai-solver-2048
==============

Solver for 2048 game based on expectiminimax-algorithm. Interface is implemented in OpenGL and C++. 


The organiZation of the codebase is as follows:

main1.cpp is the driver program which initializes the OpenGL environment and also repaints the window after each move.(main.cpp contains the driver code and the output is in 'standard output')

expectimax.cpp and expectimax.h implement the expectiminimax algorithm. It finds the bestPossibleMove - best direction (to increase the chances of winning) for a given game state and depth value.

board.cpp and board.h implements the boardState as a 1-d 16x1 array which records the current board state and also a heuristic function as a bias.






