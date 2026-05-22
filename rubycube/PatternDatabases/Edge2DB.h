#ifndef EDGE_PATTERN_DATABASE_2_H
#define EDGE_PATTERN_DATABASE_2_H

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../Model/CubeBitboard.cpp" 

using namespace std;

class EdgePatternDatabase2 
{
private:
    vector<uint8_t> database;
   
    const uint32_t pick_weights[6] = {55440, 5040, 504, 56, 7, 1};

public:
    
    EdgePatternDatabase2() {}

    // Loads the .bin file into RAM (used in your main solver)
    bool loadDatabase(const string& filePath) 
    {
        ifstream infile(filePath, ios::binary | ios::ate);
        if (!infile) 
        {
            cout << "Could not open " << filePath << endl;
            return false;
        }
        streamsize size = infile.tellg();
        infile.seekg(0, ios::beg);
        
        
        database.resize(size);
        
        
        if (infile.read((char*)database.data(), size)) 
        {
            cout << "Loaded " << filePath << " successfully! (" << size << " bytes)" << endl;
            return true;
        }
        return false;
    }

   
    uint8_t getNumMoves(const CubeBitB& cube) const 
    {
        uint32_t idx = getDatabaseIndex(cube);
        uint8_t moves = database[idx];
        
        // If it's unvisited (255), we know it takes at least 11 moves
        if (moves == 255) 
        {
            return 11;
        }
        return moves;
    }

    // Calculates the unique 1D index using Lehmer codes
    uint32_t getDatabaseIndex(const CubeBitB& cube) const 
    {
        int targetEdges[6] = {6, 7, 8, 9, 10, 11}; 
        int currentPositions[6];
        int orientations[6];

        // 1. Bitboard Extraction using your new getEdge() method
        for (int i = 0; i < 6; i++) 
        {
            for (int j = 0; j < 12; j++) 
            {
                CubeBitB::EdgePiece edge = cube.getEdge(j);
                if (edge.id == targetEdges[i]) 
                {
                    currentPositions[i] = j;
                    orientations[i] = edge.orientation;
                    break;
                }
            }
        }

        // 2. Calculate the Orientation Index
        uint32_t orientationIndex = 0;
        for (int i = 0; i < 6; i++) 
        {
            orientationIndex <<= 1;
            orientationIndex |= orientations[i];
        }

        // 3. Calculate the Permutation Index using the lookup table
       uint32_t permutationIndex = 0;
        for (int i = 0; i < 6; i++) 
        {
            int less = currentPositions[i];
            for (int j = 0; j < i; j++) 
            {
                // Subtract 1 for any previously placed edge that takes up a lower slot
                if (currentPositions[j] < currentPositions[i]) 
                {
                    less--;
                }
            }
            permutationIndex += less * pick_weights[i]; 
        }

        // 4. Combine them into a single unique index
        return (permutationIndex * 64) + orientationIndex;
    }
};

#endif