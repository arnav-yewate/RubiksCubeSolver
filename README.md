Optimal Rubik's Cube Engine (C++)
A high-performance Rubik's Cube solver engineered in C++. This project demonstrates a complete architectural evolution, starting from basic data structures and brute-force search, and culminating in a mathematically optimal IDA* engine utilizing bitwise manipulation and large-scale heuristic databases.

🏗️ Architecture & State Representation
The cube model evolved through three distinct phases to maximize Nodes Per Second (NPS):

1D Array Model: A foundational flat-array representation for logic verification.

3D Matrix Model: A spatial representation mapping exactly to the physical cube faces.

64-bit Bitboard Model (Final): Compresses the entire cube state into 64-bit integers, enabling O(1) memory lookups and ultra-fast bitwise move execution.

🧠 Solvers & Algorithms
To benchmark time complexity and graph traversal, multiple solvers were implemented:

BFS (Breadth-First Search): Guaranteed optimal, but highly memory-bound.

DFS (Depth-First Search): Memory efficient, but produces non-optimal solutions.

IDDFS (Iterative Deepening DFS): Balances memory and optimality, but suffers from massive re-computations on deep nodes.

IDA (Iterative Deepening A): The final production solver. Uses heuristic pruning to find the absolute shortest path instantly.

🗄️ Pattern Databases (165MB)
To power the IDA* heuristic, the engine pre-computes and stores the exact distance to the solved state for 85 million unique permutations.

Databases: Corners, Edge-1, and Edge-2.

Indexing: Utilizes Lehmer Codes to perfectly compress permutations into dense 1D arrays.

Optimization: Implements Lazy Heuristic Evaluation to short-circuit RAM lookups, aggressively bypassing L3 cache misses.

🚀 Performance
13-Move Scrambles: Solved in < 100 milliseconds

14-Move Scrambles: Solved in < 10.2 seconds
