# WHS vs DLX Exact Algorithm Comparison

This repository contains the benchmark code for performance comparison between the **WHS** labeling-based exact algorithm and **DLX (Dancing Links)** on 2D perfect packing problems.

## Algorithms
- **WHS**: Proposed exact packing algorithm (labeling-based pruning)
- **DLX**: Classic exact cover algorithm (Knuth, 1972)

## Benchmark Settings
- Problem: 2D perfect square packing
- Test instance: 40×40
- Metric: Average solving time (milliseconds)
- Time limit: None (small instance for speed test)
- Runs: 3 times (averaged result)

## Hardware Environment
- CPU: Intel i7-12700K
- Compiler: GCC 12.2
- Optimization: -O2
- Single-threaded

## Reproducible Results
| Method | 40×40 Speed |
|--------|-------------|
| WHS    | 8.27 ms     |
| DLX    | 89.20 ms    |

## Source File
- `whs_vs_dlx.cpp`

## Compile & Run
```bash
g++ whs_vs_dlx.cpp -O2 -o compare
./compare
