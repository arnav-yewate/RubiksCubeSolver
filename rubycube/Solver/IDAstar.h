
#ifndef IDAstarSolver_H
#define IDAstarSolver_H

#include <bits/stdc++.h>
#include "../Model/RCube.h"
#include "../PatternDatabases/CornerPattern.h"

// t type 
template <typename T>
class IDAstarSolver
{
private:
    CornerPattern cornerDB;
    vector<RubiksCube::MOVE> moves;

    int dfs(int depth, int bound)
    {
        int heuristic = cornerDB.getNumMoves(cube);
        int f = depth + heuristic; 

        
        if (f > bound)
            return f;

       
        if (cube.isSolved())
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

            
            int t = dfs( depth + 1, bound);

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

    IDAstarSolver(T rcube, string fileName)
    {
        cube = rcube;
        cornerDB.fromFile(fileName);
    }

    vector<RubiksCube::MOVE> solve()
    {
        int bound = cornerDB.getNumMoves(cube); 
        moves.clear();                          

        while (true)
        {
            // Call the recursive DFS search
            int next_bound = dfs( 0, bound);

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