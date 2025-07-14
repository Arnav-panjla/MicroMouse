#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstdint>

// Direction enumeration
enum dir {NORTH, SOUTH, EAST, WEST};

// Node structure for maze representation
struct Node {
    uint8_t x, y;
    Node* north;
    Node* south;
    Node* east;
    Node* west;
    dir smallestNeighbor;
    uint8_t val;
};

// Maze structure containing nodes
struct Maze {
    Node* nodes[8][8];
    Node* goal;
};

// Creates a new maze with interconnected nodes
Maze new_Maze();

// Updates node values recursively for flood fill algorithm
void updateVal(Node &node, uint8_t val);

// Performs flood fill on the maze from the goal
void flood(Maze &maze, uint8_t goal[2]);

// Calculates and returns the shortest path from (0,0) to goal
// void shortestPath(Maze &maze, uint8_t goal[2]);

// Add a wall in a specific direction from a node
void addWall(Node &node, dir direction);

// Add a wall in a specific direction from a node at coordinates (x,y)
void addWall(Maze &maze, uint8_t x, uint8_t y, dir direction);

// Get the direction of the smallest neighbor from a node at coordinates (x,y)
dir getDir(Maze &maze, uint8_t x, uint8_t y);

#endif