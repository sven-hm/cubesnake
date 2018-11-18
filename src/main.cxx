#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include "brick.h"
#include "area.h"
#include "tree.h"
#include "file_reader.h"

using namespace cubesnake;

int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3)
    {
    }

    int number_of_threads = 1;
    if (argc == 3)
    {
        number_of_threads = std::stoi(argv[2]);
    }
    else if (argc != 2)
    {
        std::cout << "Usage: cubesnake infile.txt [number_of_threads]" << std::endl;
        return 1;
    }

    FileReader fr(argv[1], number_of_threads);

    fr.solution_tree.Solve();

    fr.solution_tree.DumpSolutions();
}
