# Approximation-algorithm-for-tsp
# Traveling Salesman Problem (TSP) Solver

This repository provides a practical solution for the Traveling Salesman Problem (TSP) using deterministic and approximation algorithms. The project features:
1. A **C++ implementation** with modular structure for different algorithms.
2. A **Tkinter-based GUI** in Python for interactive visualization.
3. Support for input data through a text file.

---

## Table of Contents
- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Algorithms Implemented](#algorithms-implemented)
- [Features](#features)
- [Input Format](#input-format)
- [Usage](#usage)
- [Dependencies](#dependencies)
- [Report Highlights](#report-highlights)
- [Contributing](#contributing)

---

## Introduction
The Traveling Salesman Problem (TSP) is a well-known problem in optimization, where the objective is to find the shortest route to visit all cities and return to the starting point. This project implements both **deterministic** and **approximation algorithms** for TSP, alongside a graphical user interface (GUI) for ease of interaction.

---

## Project Structure
```plaintext
📂 project-root/
├── src/
│   ├── main.cpp         # Main program
│   ├── algorithms/      # Header files for Brute Force, DP, and Approximation algorithms
│   └── utils/           # Helper functions
├── gui/
│   └── gui.py           # Python Tkinter GUI script
├── input.txt            # Sample input file
├── report/
│   └── report.pdf       # Detailed explanation of the project
└── README.md            # Project documentation
```

---

## Algorithms Implemented

1. **Exact Algorithms**:
   - **Brute Force (BF):** Computes all permutations of vertices to find the optimal tour.
   - **Dynamic Programming (DP):** Implements Held-Karp’s algorithm to optimize the search.

2. **Approximation Algorithms**:
   - **MST-Based Algorithm:** Converts a Minimum Spanning Tree into a TSP solution.
   - **Enhanced Approximation:** Implements improvements to the basic MST-based approach.(Read:https://www.mdpi.com/2076-3417/11/1/177)

---

## Features
- **Flexible Input Format:** Accepts graph data from a text file.
- **Modular Implementation:** Cleanly separated algorithms for easier understanding and extension.
- **Tkinter GUI:** Simple, intuitive interface to visualize the TSP graph and its solution.

---

## Input Format

The input is a text file (`input.txt`) where each line represents an edge in the graph in the following format:
```plaintext
u v w
```
Here:
- `u`: The starting vertex of the edge.
- `v`: The ending vertex of the edge.
- `w`: The cost (weight) of traveling from `u` to `v`.

Example:
```plaintext
1 2 10
2 3 15
3 1 20
```

---

## Usage

### Running the C++ Implementation
1. Navigate to the `src` directory and compile the program:
   ```bash
   g++ -o tsp_solver main.cpp
   ```
2. Run the executable with the input file:
   ```bash
   ./tsp_solver input.txt
   ```

### Running the Python GUI
1. Navigate to the `gui` directory:
   ```bash
   cd gui
   ```
2. Run the GUI script:
   ```bash
   python gui.py
   ```

---

## Dependencies

- **C++ Compiler**: e.g., g++
- **Python**: Version 3.6 or later
- **Python Libraries**:
  - `Tkinter`

---

## Report Highlights

The project includes a detailed report (`report/report.pdf`) that provides:
- **Algorithm Analysis:** In-depth discussion of the implemented algorithms, including time and space complexity analysis.
- **Comparative Study:** A comparison between the exact and approximation methods in terms of accuracy and performance.
- **Visualization:** Examples of input/output with graphical representation of the TSP solution.
- **Theoretical Insights:** Explanations of the mathematical principles behind each algorithm.

Readers are encouraged to explore the report for a deeper understanding of the project and its underlying algorithms.

---

## Contributing
Contributions are welcome! Feel free to fork this repository and submit a pull request.

---
Hint

If you are solving large datasets, disable the exact algorithms (Brute Force and Dynamic Programming) before compilation to improve performance. These algorithms are suitable only for small to medium-sized inputs due to their high computational complexity.

