
#ifndef IDAstarSolver_H
#define IDAstarSolver_H

#include <bits/stdc++.h>
#include "../Model/RCube.h"
#include "../PatternDatabases/CornerPattern.h"

// t type and h hash function
template <typename T, typename H>
class IDAstarSolver
{
private:
    CornerPattern cornerDB;
    vector<RubiksCube::MOVE> moves;

    int dfs(T current_cube, int depth, int bound)
    {
        int heuristic = cornerDB.getNumMoves(current_cube);
        int f = depth + heuristic; // Actual distance + estimated distance

        // Base Case 1: We exceeded our bound limit. Prune this branch!
        if (f > bound)
            return f;

        // Base Case 2: The cube is solved!
        if (current_cube.isSolved())
            return -1;

        int min_next_bound = 1e9; // Infinity

        // Explore all 18 moves
        for (int i = 0; i < 18; i++)
        {
            auto curr_move = static_cast<RubiksCube::MOVE>(i);

            if (!moves.empty())
            {
                auto last_move = moves.back();

                // If the current move is on the exact same face as the last move, skip it!
                if (static_cast<int>(curr_move) / 3 == static_cast<int>(last_move) / 3)
                {
                    continue;
                }
            }

            // 1. Make the move and add to stack
            current_cube.move(curr_move);
            moves.push_back(curr_move);

            // 2. Recurse deeper!
            int t = dfs(current_cube, depth + 1, bound);

            if (t == -1)
                return -1;
            if (t < min_next_bound)
                min_next_bound = t;

            // 3. Backtrack (Undo the move to explore the next branch)
            moves.pop_back();
            current_cube.invert(curr_move);
        }

        return min_next_bound; // Tell the main loop how deep to go next time
    }

    // returns {solved cube, bound}: if the cube was solved
    // returns {rubiksCube, next_bound}, if the cube was not solved

public:
    T cube;

    IDAstarSolver(T rcube, string fileName)
    {
        cube = rcube;
        cornerDB.fromFile(fileName);
    }

    vector<RubiksCube::MOVE> solve()
    {
        int bound = cornerDB.getNumMoves(cube); // Initial heuristic
        moves.clear();                          // This vector will act as our stack

        while (true)
        {
            // Call the recursive DFS search
            int next_bound = dfs(cube, 0, bound);

            // If search returns -1, it means we found the solution!
            if (next_bound == -1)
            {
                return moves;
            }

            // Otherwise, update the bound and search deeper
            bound = next_bound;
        }
    }
};

#endif