#include <iostream>
#include <fstream>
#include <memory>

#include "brick.h"
#include "area.h"
#include "tree.h"
#include "file_reader.h"

using namespace cubesnake;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: cubesnake infile.txt" << std::endl;
        return 1;
    }

    FileReader fr(argv[1]);

    fr.solution_tree.Solve();

    fr.solution_tree.DumpSolutions();
}
