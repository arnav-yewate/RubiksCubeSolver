#include "CornerPattern.h"
#include <fstream>
#include <iostream>
#include <array>

using namespace std;

CornerPattern::CornerPattern()
{
    size = 88179840;
    database.assign(size, 255);

}

void CornerPattern::setNumMoves(uint32_t index, uint8_t numMoves) 
{
    database[index] = numMoves;
}

void CornerPattern::setNumMoves(const RubiksCube& cube, uint8_t numMoves) 
{
    database[getDatabaseIndex(cube)] = numMoves;
}

uint8_t CornerPattern::getNumMoves(uint32_t index) const 
{
    return database[index];
}

uint8_t CornerPattern::getNumMoves(const RubiksCube& cube) const 
{
    return database[getDatabaseIndex(cube)];
}


bool CornerPattern::toFile(const string& filePath) const 
{
    // Open file in binary write mode
    ofstream writer(filePath, ios::out | ios::binary);
    if (!writer) return false;
    
    // Write the entire vector to the hard drive in one massive block
    writer.write(reinterpret_cast<const char*>(database.data()), database.size());
    writer.close();
    
    return true;
}


bool CornerPattern::fromFile(const string& filePath) 
{
    // Open file in binary read mode
    ifstream reader(filePath, ios::in | ios::binary);
    if (!reader) return false;
    
    // Load the entire file from the hard drive directly into RAM
    reader.read(reinterpret_cast<char*>(database.data()), database.size());
    reader.close();
    
    return true;
}


uint32_t CornerPattern::getDatabaseIndex(const RubiksCube& cube) const 
{
    uint32_t rank = 0;
    array<int, 8> cornerPerm;
    
    // 1. Calculate the Permutation (Position of the 8 corners)
    // We extract the index of each corner (0 through 7)
    for (int i = 0; i < 8; i++)
    {
        cornerPerm[i] = cube.getCornerIndex(i);
    }
    
    // We use a mathematical trick called the "Lehmer Code" to turn 
    // the permutation into a single integer from 0 to 40,319 (8! - 1)
    for (int i = 0; i < 7; i++)
    {
        int count = 0;
        for (int j = i + 1; j < 8; j++) {
            if (cornerPerm[i] > cornerPerm[j]) {
                count++;
            }
        }
        rank = (rank + count) * (7 - i);
    }

    // 2. Calculate the Orientation (Twist of the corners)
    // We only need to check the first 7 corners (the 8th is mathematically forced)
    // We treat the orientations as a Base-3 number and convert it to Base-10
    uint32_t orientation = 0;
    for (int i = 0; i < 7; i++) 
    {
        orientation = orientation * 3 + cube.getCornerOrientation(i);
    }

    // 3. Combine Permutation and Orientation into a single unique master index!
    // 2187 is 3^7 (the total number of possible orientations)
    return (rank * 2187) + orientation;
}