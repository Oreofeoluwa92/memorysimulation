Ademuyiwa Adebunmi

Memory Allocation Simulation
Project Overview
This project simulates dynamic memory allocation using a first-fit strategy. 
It manages memory requests with lease durations and handles memory deallocation when leases expire. 
The simulation demonstrates how to handle free memory fragmentation and merges adjacent free blocks to optimize memory utilization.

Key Features
Random Memory Requests: Generates memory requests with random sizes and lease durations.
First-Fit Allocation: Searches for the first suitable free block for each request.
Lease Management: Frees memory blocks when their lease durations expire.
Block Merging: Merges adjacent free blocks to minimize fragmentation.
Simulation Statistics: Provides a detailed report on memory usage, allocation success, and merges.

Requirements
Compiler: C++11 or higher
IDE: Any C++ compatible IDE

Files:
main.cpp: Contains the main simulation loop and handles statistics.
memory.cpp: Implements memory management functions.
header.h: Declares functions and data structures used in the simulation.

Build and run the project.
Using Command Line (g++):
bash
Copy code
g++ -o memory_simulator main.cpp memory.cpp -std=c++11
./memory_simulator
