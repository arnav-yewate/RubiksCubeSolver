
#ifndef IDAstarSolver_H
#define IDAstarSolver_H

#include <bits/stdc++.h>
#include "../Model/RCube.h"
#include "../PatternDatabases/CornerPattern.h"
#include "../PatternDatabases/Edge1DB.h"
#include "../PatternDatabases/Edge2DB.h"
// t type
template <typename T>
class IDAstarSolver
{
private:
    CornerPattern cornerDB;
    EdgePatternDatabase1 edge1DB;
    EdgePatternDatabase2 edge2DB;
    vector<RubiksCube::MOVE> moves;

    int dfs(int depth, int bound)
    {
        // 1. Calculate the true maximum heuristic first
        int edge1_h = edge1DB.getNumMoves(cube);
        int edge2_h = edge2DB.getNumMoves(cube);
        int corner_h = cornerDB.getNumMoves(cube);

        int heuristic = max({edge1_h, edge2_h, corner_h});

        // 2. Check the bound using the maximum heuristic
        if (depth + heuristic > bound)
        {
            return depth + heuristic;
        }

        // 3. Did we solve it?
        if (heuristic == 0)
            return -1;

        
        int min_next_bound = 1e9;

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

            cube.move(curr_move);
            moves.push_back(curr_move);

            int t = dfs(depth + 1, bound);

            if (t == -1)
                return -1;
            if (t < min_next_bound)
                min_next_bound = t;

            // 3. Backtrack (Undo the move to explore the next branch)
            moves.pop_back();
            cube.invert(curr_move);
        }

        return min_next_bound; // Tell the main loop how deep to go next time
    }

public:
    T cube;

    IDAstarSolver(T rcube)
    {
        cube = rcube;
        cornerDB.fromFile("corners.bin");
        edge1DB.loadDatabase("edge1.bin");
        edge2DB.loadDatabase("edge2.bin");
    }

    vector<RubiksCube::MOVE> solve()
    {
        int bound = max({cornerDB.getNumMoves(cube), edge1DB.getNumMoves(cube), edge2DB.getNumMoves(cube)});
        moves.clear();

        while (true)
        {
            cout << "Currently searching bound: " << bound << "..." << endl;
            // Call the recursive DFS search
            int next_bound = dfs(0, bound);

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