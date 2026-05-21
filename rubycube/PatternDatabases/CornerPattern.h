#ifndef CORNER_PATTERN__H
#define CORNER_PATTERN__H

#include "../Model/RCube.h"
#include <vector>
#include <string>
#include <cstdint> 
using namespace std;

class CornerPattern {
private:
    // 88,179,840 states. We use uint8_t (1 byte) to save massive amounts of RAM!
    vector<uint8_t> database;
    uint32_t size;

public:
    CornerPattern();

    // 1. Store and Retrieve moves
    void setNumMoves(uint32_t index, uint8_t numMoves);
    void setNumMoves(const RubiksCube& cube, uint8_t numMoves);
    
    uint8_t getNumMoves(uint32_t index) const;
    uint8_t getNumMoves(const RubiksCube& cube) const;

    // 2. File I/O (Saving and Loading)
    bool toFile(const string& filePath) const;
    bool fromFile(const string& filePath);

    // 3. The Math (Turning 8 corners into a single index)
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
};

#endif