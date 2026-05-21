#include <iostream>
#include <queue>
#include "../Model/Cube3D.cpp" // Or whatever your main Rubik's Cube file is named
#include "CornerPattern.h"

using namespace std;

int main() 
{
    cout << "Starting Corner Database Generation..." << endl;
    
  
    CornerPattern cornerDB;
    
    
    Cube3D solved_cube;
    
    
    queue<Cube3D> q;
    q.push(solved_cube);
    
   
    cornerDB.setNumMoves(solved_cube, 0); 
    
    int nodes_generated = 1;
    int current_depth = 0;
    
    cout << "Running BFS... This will take 15 to 60 seconds." << endl;

    
    while (!q.empty()) 
    {
        Cube3D curr = q.front();
        q.pop();
        
        uint8_t depth = cornerDB.getNumMoves(curr);
        
        
        if (depth > current_depth) 
        {
            current_depth = depth;
            cout << "Reached Depth: " << current_depth << " | Nodes Found: " << nodes_generated << endl;
        }
        
       
        for (int i = 0; i < 18; i++) 
        {
            auto move = static_cast<RubiksCube::MOVE>(i);
            curr.move(move);
            
            // If the database has '255', it means we haven't visited this state yet
            if (cornerDB.getNumMoves(curr) == 255) 
            {
                // Record the shortest path to this state
                cornerDB.setNumMoves(curr, depth + 1);
                q.push(curr);
                nodes_generated++;
            }
            
            curr.invert(move);
        }
    }
    
    cout << "Generation Complete! Total Nodes: " << nodes_generated << endl;
    cout << "Saving to corners.bin..." << endl;
    
    
    cornerDB.toFile("corners.bin");
    
    cout << "Saved successfully! You never have to run this file again." << endl;
    
    return 0;
}