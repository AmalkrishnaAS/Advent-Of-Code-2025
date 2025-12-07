# 🎄 Advent of Code 2025 🎄

<div align="center">

![Language](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Event](https://img.shields.io/badge/Event-Advent%20of%20Code%202025-FFD700?style=for-the-badge&logo=adventofcode&logoColor=black)

![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**My solutions for [Advent of Code 2025](https://adventofcode.com/2025) implemented in C++.**

[About](#-about) • [Progress](#-progress) • [Structure](#-structure) • [Usage](#-usage)

</div>

---

##  About

Advent of Code is an annual set of Christmas-themed computer programming challenges that follow an Advent calendar. It has been running since 2015. The puzzles unlock daily at midnight EST/UTC-5 from December 1st to December 12th.

This repository contains my personal solutions, written in **C++**, focusing on efficiency and clean code.

## 📅 Progress

| Day | Challenge | Solution |
|:---:|:----------|:--------:|
| 01 | [Secret Entrance](https://adventofcode.com/2025/day/1) | [Solution](01/) |
| 02 | [Gift Shop](https://adventofcode.com/2025/day/2) | [Solution](02/) |
| 03 | [Lobby](https://adventofcode.com/2025/day/3) | [Solution](03/) |
| 04 | [Printing Department](https://adventofcode.com/2025/day/4) | [Solution](04/) |
| 05 | [Cafeteria](https://adventofcode.com/2025/day/5) | [Solution](05/) |
| 06 | [Trash Compactor](https://adventofcode.com/2025/day/6) | [Solution](06/) |
| 07 | [Laboratories](https://adventofcode.com/2025/day/7) | [Solution](07/) |

## 📂 Structure

The repository is organized by day. Each directory contains the solution source code, input files, and the compiled binary.

For days where the solution for Part 2 requires a different approach or significant changes, the directory is split into `part1` and `part2`.

```text
📦 adventofcode-2025
 ┣ 📂 01
 ┃ ┣ 📜 input.txt
 ┃ ┣ 📜 sample.txt
 ┃ ┗ 📜 solution.cpp
 ┣ 📂 06
 ┃ ┣ 📂 part1
 ┃ ┃ ┗ 📜 solution.cpp
 ┃ ┗ 📂 part2
 ┃   ┗ 📜 solution.cpp
 ┗ 📜 README.md
```

## 🛠️ Usage

### Prerequisites

- A C++ compiler (e.g., `g++`, `clang++`) supporting C++17 or later.

### Running a Solution

Navigate to the specific day's directory and compile the solution.

```bash
# Navigate to the day's folder (e.g., Day 1)
cd 01
# If the day is split into parts, navigate to the specific part
# cd part1

# Compile the solution
g++ -std=c++17 solution.cpp -o solution

# Run the solution
./solution
```

> **Note**: The solutions are designed to read from `input.txt` located in the same directory. Ensure the file exists before running.

## 📜 License

This project is licensed under the MIT License.
Advent of Code puzzles and inputs are property of [Advent of Code](https://adventofcode.com).
