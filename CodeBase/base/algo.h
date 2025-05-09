#ifndef ALGO_H
#define ALGO_H

// Direction enum
enum Direction { NORTH, EAST, SOUTH, WEST };

// Robot position
struct Position {
    int x;
    int y;
    Direction dir;
};

// Extern global state
extern Position currentPos;

// Function declarations
void initializeBot();
void simpleNavigate(int frontWall);
void moveForward();
void turnRight();

#endif
