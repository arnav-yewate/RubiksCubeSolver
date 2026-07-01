High-Performance C++ Rubik’s Cube Solver
-  An optimal, IDA*-based engine designed to solve the Rubik’s Cube at near-instant speeds.
- Optimized State Representation: Compressed cube states into a 64-bit Bitboard model, enabling O(1) memory lookups and ultra-fast bitwise move execution.
- Intelligent Heuristics: Implemented an IDA* solver utilizing 165MB of pre-computed pattern databases (Corners & Edges).
- Search Pruning: Engineered heuristic pruning to minimize graph traversal, avoiding redundant calculations in deep-node searches.Benchmark
- Performance:
-  13-Move Scrambles: <800 milliseconds.
- 14-Move Scrambles: ~19.2 seconds.


