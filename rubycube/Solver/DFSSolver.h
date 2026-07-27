#ifndef PROJECTS_RUBYCUBE_SOLVER_DFSSOLVER_H
#define PROJECTS_RUBYCUBE_SOLVER_DFSSOLVER_H


#include<bits/stdc++.h>
#include "../Model/RCube.h"


//t type and h hash function
template<typename T,typename H>
class DFSSolver
{
    private:


    T rcube;
    int max_depth;
    vector<RubiksCube::MOVE> ans;
    bool dfs(int dep)
    {
        if(rcube.isSolved())return true;
        if(dep>max_depth) return false;
        for(int i=0;i<18;i++)
        {
            auto cur_move = RubiksCube::MOVE(i);
            rcube.move(cur_move);
            ans.push_back(cur_move);
            if(dfs(dep+1)) return true;
            ans.pop_back();
            rcube.invert(cur_move);
        }
        return false;
    }


    public:


    DFSSolver(T cube,int maxdep)
    {
        rcube= cube;
        if(maxdep>8)max_depth = 8;
        else max_depth = maxdep;
    }

    vector<RubiksCube::MOVE> solve()
    {
        ans.clear();
        dfs(max_depth);
        return ans;
    }

    
};


    #endif 