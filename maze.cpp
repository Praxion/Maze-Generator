#include "maze.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

// Constructor to initialize the maze with given rows and columns
Maze::Maze(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<Cell>(cols)) {}

// Function to generate the maze using given seed for the random number generator
void Maze::generateMaze(unsigned int seed){
    std::srand(seed);
    std::vector<std::pair<int, int>> stack; // Stack to manage the cells while generating the maze
    grid[0][0].visited = true; //Start from point (0,0)
    stack.push_back({0, 0});

    while(!stack.empty()) {

        // Get the current cell from the top of the stack
        std::pair<int, int> current = stack.back();
        int currentRow = current.first;
        int currentCol = current.second;

        // Get the unvisited neighbors of the current cell
        auto neighbors = getUnvisitedNeighbors(currentRow, currentCol);
        
        if(!neighbors.empty()) {
            // Pick a random neighbor
            int idx = std::rand() % neighbors.size();
            std::pair<int, int> next = neighbors[idx];
            int nextRow = next.first;
            int nextCol = next.second;
            // Remove wall between the current cell and the chosen neighbor
            if (nextRow < currentRow) {//Next cell is to the north
                removeWall(grid[currentRow][currentCol], grid[nextRow][nextCol], 3); // Remove north wall
            } else if (nextRow > currentRow) { // Next cell is to the south
                removeWall(grid[currentRow][currentCol], grid[nextRow][nextCol], 2); // Remove south wall
            } else if (nextCol < currentCol) { // Next cell is to the west
                removeWall(grid[currentRow][currentCol], grid[nextRow][nextCol], 0); // Remove west wall
            } else if (nextCol > currentCol) { // Next cell is to the east
                removeWall(grid[currentRow][currentCol], grid[nextRow][nextCol], 1); // Remove east wall
            }
            
            grid[nextRow][nextCol].visited = true;
            // Push the neighbor onto the stack
            stack.push_back({nextRow, nextCol});
        } else {
            // Backtrack by popping the current cell in the stack
            stack.pop_back();
        }
    }
    // Make an opening in the starting cell - opens in the north
    grid[0][0].north = false;

    // Make an opening in the ending cell - opens in the south
    grid[rows - 1][cols - 1].south = false;
}

//Get all unvisited neighbors
std::vector<std::pair<int, int>> Maze::getUnvisitedNeighbors(int row, int col) const{
    std::vector<std::pair<int, int>> neighbors;
    // Top neighbor
    if (row > 0 && !grid[row - 1][col].visited) neighbors.push_back({row - 1, col});
    // Bottom neighbor
    if (row < rows - 1 && !grid[row + 1][col].visited) neighbors.push_back({row + 1, col}); 
    // West neighbor
    if (col > 0 && !grid[row][col -1].visited) neighbors.push_back({row, col - 1}); 
    // East neighbor
    if (col < cols - 1 && !grid[row][col + 1].visited) neighbors.push_back({row, col + 1}); 
    return neighbors;
}

// Remove common walls between current and neighboring cells
void Maze::removeWall(Cell & current, Cell & neighbor, int direction) {
    if (direction == 0) { // West
        current.west = false;
        neighbor.east = false;
    } else if (direction == 1) { // East
        current.east = false;
        neighbor.west = false;
    } else if (direction == 2) { // South
        current.south = false;
        neighbor.north = false;
    } else if (direction == 3) { // North
        current.north = false;
        neighbor.south = false;   
    }
}

// Setting the value of each Cell in the maze
int Maze::Cell::toInt() const {
    int value = 0;
    if (west) value += 1; // 0001 west
    if (east) value += 2; // 0010 east
    if (south) value += 4; // 0100 south
    if (north) value += 8; // 1000 north
    return value;
}

// Saving a File as .txt
void Maze::saveToFile(const std::string & filename) const {
    std::ofstream outFile(filename);
    for (const auto & row : grid) {
        for (const auto & cell : row) {
            outFile << cell.toInt() << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}
