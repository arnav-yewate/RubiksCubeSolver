#include <bits/stdc++.h>

#include "Model/Cube1D.cpp"
#include "Model/Cube3D.cpp"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"


using namespace std;

int main()
{
    Cube1D dd;

    vector<RubiksCube::MOVE> g = dd.randomshuffle(6),h;
    reverse(g.begin(),g.end());

    IDDFSSolver<Cube1D, Cube1D:: Hash1d> bfs(dd,6);
    h = bfs.solve();

    
    dd.print();
    cout<<h.size()<<endl;
    for(int i=0;i<h.size();i++)
    {
        dd.move(h[i]);
    }
    dd.print();














    return 0;

}