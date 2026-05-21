
#ifndef IDAstarSolver_H
#define IDAstarSolver_H


#include<bits/stdc++.h>
#include "../Model/RCube.h"
#include "../PatternDatabases/CornerPattern.h"

//t type and h hash function
template<typename T,typename H>
class IDAstarSolver
{
private:
    CornerPattern cornerDB;
    vector<RubiksCube::MOVE> moves;
    unordered_map<T, RubiksCube::MOVE, H> move_done;
    unordered_map<T, bool, H> vis;

    struct Node 
    {
        T cube;
        int depth;
        int estimate;
        // 1step faster than  2 step assignment
        Node(T _cube, int _depth, int _estimate) : cube(_cube), depth(_depth), estimate(_estimate) {};
    };

    struct comparecube 
    {
        // cuz needed min heap bigger are thrown to the left and smaller to the right , rightmost is the top
        bool operator()(pair<Node, int> const &p1, pair<Node, int> const &p2) 
        {
            auto n1 = p1.first, n2 = p2.first;
            if (n1.depth + n1.estimate == n2.depth + n2.estimate) 
            {
                return n1.estimate > n2.estimate;
            } 
            else return n1.depth + n1.estimate > n2.depth + n2.estimate;
        }
    };

    void resetstruct() 
    {
        moves.clear();
        move_done.clear();
        vis.clear();
    }

    // returns {solved cube, bound}: if the cube was solved
    // returns {rubiksCube, next_bound}, if the cube was not solved
    pair<T, int> IDAstar(int bound) 
    {
        //pair(Node, move  to reach )
        priority_queue<pair<Node, int>, vector<pair<Node, int>>, comparecube> pq;
        Node start = Node(cube, 0, cornerDB.getNumMoves(cube));
        pq.push(make_pair(start, 0));
        int next_bound = 100;
        while (!pq.empty()) 
        {
            auto p = pq.top();
            Node node = p.first;
            pq.pop();

            if (vis[node.cube]) continue;

            vis[node.cube] = true;
            move_done[node.cube] = RubiksCube::MOVE(p.second);

            if (node.cube.isSolved()) return make_pair(node.cube, bound);
            node.depth++;
            for (int i = 0; i < 18; i++) 
            {
                auto curr_move = RubiksCube::MOVE(i);
                node.cube.move(curr_move);
                if (!vis[node.cube]) 
                {
                    node.estimate = cornerDB.getNumMoves(node.cube);
                    if (node.estimate + node.depth > bound) 
                    {
                        next_bound = min(next_bound, node.estimate + node.depth);
                    }
                    else
                    {
                        pq.push(make_pair(node, i));
                    }
                }
                node.cube.invert(curr_move);
            }

        }
        return make_pair(cube, next_bound);
    }

public:
    T cube;

    IDAstarSolver(T rcube  , string fileName)
    {
        cube = rcube;
        cornerDB.fromFile(fileName);
    }

    vector<RubiksCube::MOVE> solve() 
    {
        int bound = 1;
        auto p = IDAstar(bound);
        while (p.second != bound) 
        {
            resetstruct();
            bound = p.second;
            p = IDAstar(bound);
        }
        T solved_cube = p.first;
        assert(solved_cube.isSolved());
        T curr_cube = solved_cube;
        while (!(curr_cube == cube)) 
        {
            RubiksCube::MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        cube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};


    #endif 