#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

//Class Declaration
class Maze {
    public:
        // Constructor to initialize the maze with given rows and columns
        Maze(int rows, int cols);

        // Function to generate the maze using a given seed for the random number generator
        void generateMaze(unsigned int seed);

        // Function to save the generated maze to a file
        void saveToFile(const std :: string & filename) const;

    private:
        // Structure to represent each cell in the maze
        struct Cell {
            bool north, south, east, west;  // Walls
            bool visited;                   // Flag to check if the cell has been visited

            // Constructor to inititialize all walls as closed and the cell as unvisited
            Cell() : north(true), south(true), east(true), west(true), visited(false) {}

            // Function to convert the cell's wall configuration to an integer
            int toInt() const;
    };

    int rows; // number of rows in the maze
    int cols; // number of columns in the maze
    std :: vector<std::vector<Cell>> grid; // 2D vector to represent the maze grid

    // Function to remove the wall between the current cell and a neighboring cell
    void removeWall(Cell & current, Cell & neighbor, int direction);

    // Function to get all unvisited neighbors of a cell
    std :: vector<std::pair<int, int>> getUnvisitedNeighbors(int row, int col) const;
};

#endif //MAZE_H
