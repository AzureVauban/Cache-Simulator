# Cache Simulator with Address Generator
# Made by Michael Elder
# CS 3339.002 - 12/3/2024
This project includes:
1. A **Python script** to generate a `.txt` file with random hexadecimal memory addresses.
2. A **C++ program** that simulates a cache, reading the addresses from the generated `.txt` file.

## Requirements

### Python Script
- Python 3.x installed on your system.

### C++ Program
- A C++ compiler such as `g++`.

---

## How to Use

### 1. Run the Python Address Generator

The Python script (`generate_addresses.py`) generates a `.txt` file containing random hexadecimal addresses.

#### Steps:
1. Open a terminal or command prompt.
2. Run the script:
```bash
python generate_addresses.py
```

### 2. Compile and Run the C++ Cache Simulator
1. Open a terminal or command prompt.
2. Compile the program using g++
```bash
g++ -o cache_simulator main.cpp
```
3. Execute the program
```
./cache_simulator
```



