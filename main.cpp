#include <iostream>
#include <cstdlib>
#include "maze.h"

int main(int argc, char * argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <seed> <N> <M> <fname>\n";
        return 1;
    }
    // Parse command line arguments
    unsigned int seed = std::stoi(argv[1]);
    int rows = std::stoi(argv[2]);
    int cols = std::stoi(argv[3]);
    std::string filename = argv[4];

    // Check for valid number of rows and columns
    if (rows <= 0 || cols <= 0) {
        std::cerr << "Number of rows and columns must be greater than 0.\n";
        return 1;
    }

    // Create a Maze object
    Maze maze(rows, cols);

    // Generate the maze with the given seed
    maze.generateMaze(seed);

    // Save the generated maze to the specified file
    maze.saveToFile(filename);

    return 0;
}
