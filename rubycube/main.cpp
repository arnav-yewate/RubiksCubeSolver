#include <bits/stdc++.h>
#include <chrono>
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
    Cube1D dd;
    dd.randomshuffle(12);
    IDAstarSolver<Cube1D> g(dd,"corners.bin");
    auto start_time = chrono::high_resolution_clock::now();
    vector<RubiksCube::MOVE> h= g.solve();

    auto end_time = chrono::high_resolution_clock::now();
    // dd.print();
    for(int i=0;i<h.size();i++)
    {
        cout<<RubiksCube::getMove(h[i])<<endl;
        // dd.move(h[i]);
    }
    cout<<endl;
    // dd.print();
    
    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    double duration_seconds = duration_ms / 1000.0;

    // Print the results
    cout << "\nSolution Found! Total Moves: " << h.size() << endl;
    cout << "Time Taken: " << duration_ms << " ms (" << duration_seconds << " seconds)" << endl;
    










    return 0;

}