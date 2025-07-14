#include "algorithm.h"
#include <iostream>
// #include <cassert>

// extern uint8_t floodarr[8][8];
// extern uint8_t walls[8][8]; //last 4 bits represent walls in the north, south, east and west directions respectively
//0000NSEW



// extern uint8_t goal[2];

// void flood()
// {
//     floodarr[goal[0]][goal[1]] = 0;
//     for(int i=0; i<8; i++)
//     {
//         for(int j=0; j<8; j++)
//         {
//             if(floodarr[i][j] == 0)
//             {
//                 if(i>0 && floodarr[i-1][j] == 255 && !(walls[i][j] & 1<<0))
//                 {
//                     floodarr[i-1][j] = floodarr[i][j] + 1;
//                 }
//                 if(i<7 && floodarr[i+1][j] == 255 && !(walls[i][j] & 1<<1))
//                 {
//                     floodarr[i+1][j] = floodarr[i][j] + 1;
//                 }
//                 if(j>0 && floodarr[i][j-1] == 255 && !(walls[i][j] & 1<<2))
//                 {
//                     floodarr[i][j-1] = floodarr[i][j] + 1;
//                 }
//                 if(j<7 && floodarr[i][j+1] == 255 && !(walls[i][j] & 1<<3))
//                 {
//                     floodarr[i][j+1] = floodarr[i][j] + 1;
//                 }
//             }
//         }
//     }
// }

// int init()
// {
//     // Initialize floodarr with maximum values (e.g., 255) to represent unvisited cells
//     for (int i = 0; i < 8; ++i) {
//         for (int j = 0; j < 8; ++j) {
//             floodarr[i][j] = 255;
//         }
//     }

//     // Initialize walls with 0 to represent no walls initially
//     for (int i = 0; i < 8; ++i) {
//         for (int j = 0; j < 8; ++j) {
//             walls[i][j] = 0;
//         }
//     }

//     for(int i=0; i<8; i++)
//     {
//         walls[0][i] |= 1<<3;
//         walls[7][i] |= 1<<2;
//         walls[i][0] |= 1<<0;
//         walls[i][7] |= 1<<1;
//     }

//     flood();
//     std::cout << "Flood array:" << std::endl;
//     for (int i = 0; i < 8; ++i) {
//         for (int j = 0; j < 8; ++j) {
//             std::cout << (int)floodarr[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }

// int main()
// {
//     Maze maze = new_Maze();
//     uint8_t goal[2] = {7,7};
//     flood(maze, goal);
//     assert(maze.nodes[7][7]->val == 0);
//     assert(maze.nodes[6][7]->val == 1);
//     assert(maze.nodes[7][6]->val == 1);
//     std::cout << "Test 2 passed: Flood fill assigns correct values.\n";

//     addWall(maze, 0, 0, dir::EAST);
//     assert(maze.nodes[0][0]->east == nullptr);
//     std::cout << "Test 3 passed: Wall added correctly.\n";

//     flood(maze, goal);
//     dir d = getDir(maze, 0, 0);
//     assert(d == dir::EAST); // Should point to (7,7)
//     std::cout << "Test 4 passed: getDir returns correct direction.\n";

//     // Test 5: Print shortest path from (0,0) to (7,7)
//     // std::cout << "Test 5: Shortest path from (0,0) to (7,7):\n";
//     // shortestPath(maze, goal);

//     std::cout << "All tests passed.\n";
// }



Maze new_Maze()
{
    Maze *maze = new Maze;

    for(uint8_t i=0; i<8; i++)
    {
        for(uint8_t j=0; j<8; j++)
        {
            maze->nodes[i][j] = new Node;
            maze->nodes[i][j]->x = i;
            maze->nodes[i][j]->y = j;
            maze->nodes[i][j]->smallestNeighbor = dir::NORTH;
            maze->nodes[i][j]->val = 255;
        }
    }

    for(uint8_t i=0; i<8; i++)
    {
        for(uint8_t j=0; j<8; j++)
        {
            if(i<7)
                maze->nodes[i][j]->north = maze->nodes[i+1][j];
            else
                maze->nodes[i][j]->north = nullptr;

            if(i>0)
                maze->nodes[i][j]->south = maze->nodes[i-1][j];
            else
                maze->nodes[i][j]->south = nullptr;

            if(j<7)
                maze->nodes[i][j]->east = maze->nodes[i][j+1];
            else
                maze->nodes[i][j]->east = nullptr;

            if(j>0)
                maze->nodes[i][j]->west = maze->nodes[i][j-1];
            else
                maze->nodes[i][j]->west = nullptr;
        }
    }
    return *maze;
}


void updateVal(Node &node, uint8_t val)
{
    node.val = val;
    if(node.north != nullptr && node.north->val > val+1)
    {
        node.north->smallestNeighbor = dir::SOUTH;
        updateVal(*node.north, val+1);
    }
    if(node.south != nullptr && node.south->val > val+1)
    {
        node.south->smallestNeighbor = dir::NORTH;
        updateVal(*node.south, val+1);
    }
    if(node.east != nullptr && node.east->val > val+1)
    {
        node.east->smallestNeighbor = dir::WEST;
        updateVal(*node.east, val+1);
    }
    if(node.west != nullptr && node.west->val > val+1)
    {
        node.west->smallestNeighbor = dir::EAST;
        updateVal(*node.west, val+1);
    }
}

void flood(Maze &maze, uint8_t goal[2])
{
    for(uint8_t i=0; i<8; i++)
    {
        for(uint8_t j=0; j<8; j++)
        {
            maze.nodes[i][j]->val = 255;
        }
    }
    updateVal(*maze.nodes[goal[0]][goal[1]], 0);
}


// void shortestPath(Maze &maze, uint8_t goal[2])
// {
//     Node *cur = maze.nodes[0][0];
//     int i = 0;
//     while (cur->x != goal[0] || cur->y != goal[1])
//     {
//         std::cout << (int) cur->x << ' ' << (int) cur->y;
//         if(cur->smallestNeighbor == dir::EAST)
//             cur = cur->east;
//         else if(cur->smallestNeighbor == dir::WEST)
//             cur = cur->west;
//         else if(cur->smallestNeighbor == dir::NORTH)
//             cur = cur->north;
//         else if(cur->smallestNeighbor == dir::SOUTH)
//             cur = cur->south;

//         std::cout << " -> ";
//     }
//     std::cout << (int) cur->x << ' ' << (int) cur->y << std::endl;
// }

void addWall(Node &node, dir direction)
{
    if(direction == dir::NORTH)
    {
        node.north = nullptr;
    }
    else if(direction == dir::SOUTH)
    {
        node.south = nullptr;
    }
    else if(direction == dir::EAST)
    {
        node.east = nullptr;
    }
    else if(direction == dir::WEST)
    {
        node.west = nullptr;
    }
}

void addWall(Maze &maze, uint8_t x, uint8_t y, dir direction)
{
    if(direction == dir::NORTH)
    {
        if (maze.nodes[x][y]->north != nullptr){
            maze.nodes[x][y]->north = nullptr;
            maze.nodes[x+1][y]->south = nullptr;
        } 
    }
    else if(direction == dir::SOUTH)
    {
        if (maze.nodes[x][y]->south != nullptr){
            maze.nodes[x][y]->south = nullptr;
            maze.nodes[x-1][y]->north = nullptr;
        }
    }
    else if(direction == dir::EAST)
    {
        if (maze.nodes[x][y]->east != nullptr){
            maze.nodes[x][y]->east = nullptr;
            maze.nodes[x][y+1]->west = nullptr;
        }
    }
    else if(direction == dir::WEST)
    {
        if (maze.nodes[x][y]->west != nullptr){
            maze.nodes[x][y]->west = nullptr;
            maze.nodes[x][y-1]->east = nullptr;
        }
    }
}

dir getDir(Maze &maze, uint8_t x, uint8_t y)
{
    return maze.nodes[x][y]->smallestNeighbor;
}