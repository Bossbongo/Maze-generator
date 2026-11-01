#include <stdio.h>
#include "raylib.h"

//PSUEDO CODE
//Pick a random cell
//Mark the cell as visited

//Add all walls of the cell to a wall list

//While there are walls in the list
     //Pick a random wall from the list
     //If the wall seperates a visited cell and an unvisited cell
        //Remove the wall to create a passage
        //Mark the unvisited cell as visited
        //Add all walls of the newly visited cell to the wall list
    //Remove the wall from the list

//End While


//---


#define GRID_SIZE 10
#define CELL_SIZE 80

typedef struct Cell {
        int x;
        int y;
        bool isvisited;

        //Walls of the cell
        bool NorthWall;
        bool SouthWall;
        bool EastWall;
        bool WestWall;
    } Cell;

typedef struct Wall {
        int fromCell;
        int toX , toY;
    } Wall;

    int getCellIndex(int x, int y) {
        if(x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
            return -1; //Invalid cell index
        }
        return y + (x * GRID_SIZE);
    }

int main() {

    //Initialize window
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 800;

    Cell currentCell;


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Generator");
    SetTargetFPS(60);

    //Sets up grid
    Cell grid[GRID_SIZE * GRID_SIZE];
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            int idx = getCellIndex(x, y);
            grid[idx].x = x;
            grid[idx].y = y;
            grid[idx].isvisited = false;

            //List of walls for the cell
            grid[idx].NorthWall = true;
            grid[idx].SouthWall = true;
            grid[idx].WestWall = true;
            grid[idx].EastWall = true;

        }
    }
    

    Wall wallList[GRID_SIZE * GRID_SIZE * 4]; //Maximum number of walls is 4 per cell
    int wallListCount = 0; //Initialize the count of walls in the list

    //Pick a random starting cell
    currentCell.x = GetRandomValue(0, GRID_SIZE - 1);
    currentCell.y = GetRandomValue(0, GRID_SIZE - 1);
    int startIdx = getCellIndex(currentCell.x, currentCell.y);

    grid[startIdx].isvisited = true;

    int currentX = grid[startIdx].x;
    int currentY = grid[startIdx].y;

    //Directions for moving up, down, left, right
    int dx[] = {0, 0, 1, -1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int nx = currentX + dx[i];
        int ny = currentY + dy[i];

        //if neighbor is within the grid
        if (getCellIndex(nx, ny) != -1) {
            wallList[wallListCount].fromCell = startIdx;
            wallList[wallListCount].toX = nx;
            wallList[wallListCount].toY = ny;
            wallListCount++;
        }
    }

    while (!WindowShouldClose()) {

        if (wallListCount > 0) {

            //Pick a random wall from the list (North, South, East, West)
            int randomWallIdx = GetRandomValue(0, wallListCount - 1);
            Wall chosenWall = wallList[randomWallIdx];

            //Get the index of the target cell based on the chosen wall
            int targetIdx = getCellIndex(chosenWall.toX, chosenWall.toY);
        
        
            if (!grid[targetIdx].isvisited) {

                Cell* from = &grid[chosenWall.fromCell];
                Cell* to = &grid[targetIdx];

                if (to->x == from->x + 1) {
                    from->EastWall = false;
                    to->WestWall = false;
                } else if (to->x == from->x - 1) {
                    from->WestWall = false;
                    to->EastWall = false;
                } else if (to->y == from->y + 1) {
                    from->SouthWall = false;
                    to->NorthWall = false;
                } else if (to->y == from->y - 1) {
                    from->NorthWall = false;
                    to->SouthWall = false;
                }

                grid[targetIdx].isvisited = true;

                //Update the current cell to the target cell
                for(int i = 0; i < 4; i++) {
                    int nx = grid[targetIdx].x + dx[i];
                    int ny = grid[targetIdx].y + dy[i];
                    int nextIdx = getCellIndex(nx, ny);

                    

                    if (nextIdx != -1 && !grid[nextIdx].isvisited) {
                        wallList[wallListCount].fromCell = targetIdx;
                        wallList[wallListCount].toX = nx;
                        wallList[wallListCount].toY = ny;
                        wallListCount++;
                    }
                }
            }
            //Remove the chosen wall from the list by replacing it with the last wall and decrementing the count
            wallList[randomWallIdx] = wallList[wallListCount - 1];
            wallListCount--;
        }

    

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
            int x = grid[i].x * CELL_SIZE;
            int y = grid[i].y * CELL_SIZE;

            //Draw the cell background based on whether it has been visited
            if (grid[i].isvisited) {
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, RAYWHITE);
            } else {
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, BLACK);
            }

            //Draw the walls of the cell
            if (grid[i].NorthWall) {
                DrawLine(x, y, x + CELL_SIZE, y, BLACK);
            }
            if (grid[i].SouthWall) {
                DrawLine(x, y + CELL_SIZE, x + CELL_SIZE, y + CELL_SIZE, BLACK);
            }
            if (grid[i].WestWall) {
                DrawLine(x, y, x, y + CELL_SIZE, BLACK);
            }
            if (grid[i].EastWall) {
                DrawLine(x + CELL_SIZE, y, x + CELL_SIZE, y + CELL_SIZE, BLACK);
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
