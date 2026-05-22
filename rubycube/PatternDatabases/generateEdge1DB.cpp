#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

#include "Edge1DB.h" // Your new Edge 1 class

using namespace std;

int main()
{
    cout << "Starting Edge 1 Database Generation (42,577,920 states)..." << endl;

    // We use a flat vector instead of a complex class for the raw generation script
    vector<uint8_t> edge1DB(42577920, 255);
    EdgePatternDatabase1 indexer;
  
    CubeBitB cube; // Start with your perfectly solved bitboard
    queue<CubeBitB> q;

    uint32_t solved_idx = indexer.getDatabaseIndex(cube);
    edge1DB[solved_idx] = 0;
    q.push(cube);

    int current_depth = 0;
    int nodes_generated = 1;

    while (!q.empty())
    {
        int level_size = q.size();
        cout << "Depth: " << current_depth << " | Queue Size: " << level_size << " | Nodes: " << nodes_generated << endl;

        // Hard cutoff at Depth 10.
        // Depths 11 and 12 for edges take hours even with bitboards.
        // A depth 10 edge heuristic combined with a depth 11 corner heuristic is God-tier.
        if (current_depth == 10)
            break;

        for (int i = 0; i < level_size; i++)
        {
            CubeBitB curr = q.front();
            q.pop();

            // Loop through all 18 standard Rubik's Cube moves
            for (int m = 0; m < 18; m++)
            {
                CubeBitB next_node = curr; // Copying a bitboard is virtually instant
                auto curr_move = RubiksCube::MOVE(m);
                next_node.move(curr_move);

                uint32_t idx = indexer.getDatabaseIndex(next_node);

                // If we haven't seen this state before, record its depth and push it
                if (edge1DB[idx] == 255)
                {
                    edge1DB[idx] = current_depth + 1;
                    q.push(next_node);
                    nodes_generated++;
                }
            }
        }
        current_depth++;
    }

    cout << "\nGeneration Complete! Found " << nodes_generated << " unique edge states." << endl;
    cout << "Saving to edge1.bin..." << endl;

    // Write the raw array directly to a binary file
    ofstream outfile("edge1.bin", ios::binary);
    outfile.write((char *)edge1DB.data(), edge1DB.size());
    outfile.close();

    cout << "Saved successfully! You now have the First Edge Database." << endl;
    return 0;
}