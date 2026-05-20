
#ifndef PROJECTS_RUBYCUBE_SOLVER_BFSSOLVER_H
#define PROJECTS_RUBYCUBE_SOLVER_BFSSOLVER_H


#include<bits/stdc++.h>
#include "../Model/RCube.h"


//t type and h hash function
template<typename T,typename H>
class BFSSolver
{
private:
    T rcube; // current state of the cube

    // list of moves to solve the cube
    unordered_map<T,bool,H> vis;
    unordered_map<T,RubiksCube::MOVE,H> prevmove; // move used to reach this state

    T bfs()
    {
        T node;
        queue<T> q;
        q.push(rcube);
        vis[rcube] = true;

        while(!q.empty())
        {
            node = q.front();
            q.pop();
            if(node.isSolved())
            {
                return node;
            }
            for(int i=0;i<18;i++)
            {
                auto cur_move =  RubiksCube::MOVE(i);
                node.move(cur_move);
                if(!vis[node])
                {
                    vis[node]=true;
                    prevmove[node]=cur_move;
                    q.push(node);

                } 
                node.invert(cur_move);
            }
        }
        // compailar needs a return statement here but this line should never be reached
        return rcube;

    }


    public:


    BFSSolver(T cube)
    {
        rcube = cube;
    }

    vector<RubiksCube::MOVE> solve()
    {
        T node = bfs();
        assert(node.isSolved());
        vector<RubiksCube::MOVE> ans;
        while(node !=rcube)
        {
            auto last_move = prevmove[node];
            ans.push_back(last_move);
            node.invert(last_move);
        }
        reverse(ans.begin(),ans.end());
        return ans;

    }
};


    #endif 