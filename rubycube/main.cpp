#include <bits/stdc++.h>

#include "Model/Cube1D.cpp"
#include "Model/Cube3D.cpp"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"


using namespace std;

int main()
{
    Cube3D dd;

    dd.move("D");
    dd.move("F");
    dd.move("R'");
    
    dd.print();
    cout<<endl;
    dd.invert("R'");
    dd.print();
    cout<<endl;
    dd.invert("F");
    dd.print();
    cout<<endl;
    dd.invert("D");
    dd.print();
    cout<<endl;

    














    return 0;

}