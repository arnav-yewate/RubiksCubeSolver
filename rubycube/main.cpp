#include <bits/stdc++.h>
// #include <chrono>
#include "Model/Cube1D.cpp"
#include "Model/Cube3D.cpp"
#include "Model/CubeBitboard.cpp"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAstar.h"
#include "PatternDatabases/CornerPattern.h"
#include "PatternDatabases/Edge1DB.h"
#include "PatternDatabases/Edge2DB.h"
// g++ main.cpp Model/RCube.cpp PatternDatabases/CornerPattern.cpp -O3 
using namespace std;

int main()
{
    CubeBitB dd;
    dd.randomshuffle(15);
    IDAstarSolver<CubeBitB> g(dd);
    auto start_time = chrono::high_resolution_clock::now();

    cout<<"Solving....."<<endl;
    vector<RubiksCube::MOVE> h= g.solve();
    cout<<"Solved!!"<<endl;
    auto end_time = chrono::high_resolution_clock::now();
    dd.print();
    for(int i=0;i<h.size();i++)
    {
        cout<<RubiksCube::getMove(h[i])<<" ";
        dd.move(h[i]);
    }
    cout<<endl;
    dd.print();
    
    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    double duration_seconds = duration_ms / 1000.0;

   
   
    cout << "Time Taken: " << duration_ms << " ms (" << duration_seconds << " seconds)" << endl;
    










    return 0;

}