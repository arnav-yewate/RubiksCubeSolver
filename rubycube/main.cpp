#include <bits/stdc++.h>

#include "Model/Cube1D.cpp"
#include "Model/Cube3D.cpp"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAstar.h"
#include "PatternDatabases/CornerPattern.h"

using namespace std;

int main()
{
    Cube3D dd;
    dd.randomshuffle(15);
    IDAstarSolver<Cube3D,Cube3D::Hash3d> g(dd,"corners.bin");
    vector<RubiksCube::MOVE> h= g.solve();
    dd.print();
    for(int i=0;i<h.size();i++)
    {
        cout<<RubiksCube::getMove(h[i])<<endl;
        dd.move(h[i]);
    }
    
    dd.print();
    

    










    return 0;

}