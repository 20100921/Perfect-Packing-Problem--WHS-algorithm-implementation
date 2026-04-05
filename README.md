# WHS Limit Performance Test (1D / 2D / 3D)

This code tests the **maximum solvable instance size** of the WHS exact algorithm under strict time limits.

## Algorithm
- WHS: A Labeling-based Exact Algorithm for Perfect Packing

## Time Limits
- 1D: 60 seconds
- 2D: 3600 seconds (1 hour)
- 3D: 36000 seconds (10 hours)

## Hardware
- CPU: Intel i7-12700K
- Compiler: GCC 12.2
- Optimization: -O2

## Reproducible Results
| Dimension | Max Solvable Size |
|-----------|-------------------|
| 1D        | 9300              |
| 2D        | 64×64             |
| 3D        | 17×17×17          |

## File
- WHS极限.cpp

## Compile & Run
```bash
g++ WHS极限.cpp -O2 -o limit
./limit
