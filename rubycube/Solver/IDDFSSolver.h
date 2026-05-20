#ifndef PROJECTS_RUBYCUBE_SOLVER_IDDFSSOLVER_H
#define PROJECTS_RUBYCUBE_SOLVER_IDDFSSOLVER_H


#include<bits/stdc++.h>
#include "../Model/RCube.h"
#include "DFSSolver.h"

//t type and h hash function
template<typename T,typename H>
class IDDFSSolver
{
    private:


    T rcube;
    int max_depth;
    public:


    IDDFSSolver(T cube,int maxdep)
    {
        rcube= cube;
        if(maxdep>8)max_depth = 8;
        else max_depth = maxdep;
    }

    vector<RubiksCube::MOVE> solve()
    {
        vector<RubiksCube::MOVE> ans;
        for(int i=1;i<=max_depth;i++)
        {
            DFSSolver<T,H> dfss(rcube,i);
            ans = dfss.solve();
            if(!ans.empty())
            {
                break;
            }
        }
        return ans;
        
    }

    
};


    #endif 