#include "cubesnake.h"

int main(int argc, char* argv[])
{
    if (argc != 2 and argc != 3)
    {
        std::cout << "Usage: cubesnake infile.txt" << std::endl;
        return 1;
    }
    int n_threads = 1;
    if (argc == 3)
    {
        n_threads = atoi(argv[2]);
    }

    // collect data
    std::fstream file(argv[1], std::ios_base::in);

    int length_sequence;
    file >> length_sequence;

    std::vector<int> Sequence;
    int tmp;
    for (int i = 0; i < length_sequence; i++)
    {
        file >> tmp;
        Sequence.push_back(tmp);
    }

    int number_startvalues;
    file >> number_startvalues;
    if (number_startvalues < 2)
    {
        std::cout << "Need at least 2 startvalues :/" << std::endl;
        return 2;
    }
    std::vector<std::vector<int>> startvalues;

    for (int i = 0; i < number_startvalues; i++)
    {
        std::vector<int> pnt;
        for (int j : {0,1,2})
        {
            file >> tmp;
            pnt.push_back(tmp);
        }
        startvalues.push_back(pnt);
    }
 
    int fieldsize[3];
    for (int i = 0; i < 3; i++)
        file >> fieldsize[i];
    Field<bool> field(fieldsize[0], fieldsize[1], fieldsize[2], false);
    
    int number_nonfree_bricks;
    file >> number_nonfree_bricks;
    if (number_nonfree_bricks != 0)
    {
        std::cout << "Non free bricks not implemented yet :/" << std::endl;
        return 2;
    }

    // check data
    int field_size_1 = 1;
    for (auto i : Sequence)
        field_size_1 += i;

    int field_size_2 = fieldsize[0] * fieldsize[1] * fieldsize[2] - number_nonfree_bricks;

    if (field_size_1 != field_size_2)
    {
        std::cout << "Sequence length and field size do not fit together :/" << std::endl;
        return 3;
    }

    //
    std::cout << "== cubesnake (" << CUBESNAKE_VERSION << ") ==" << std::endl;
    std::cout << "File: " << argv[1] << std::endl;
    std::cout << "Field size: " << field_size_1
              << " = " << fieldsize[0] << " x "
                       << fieldsize[1] << " x "
                       << fieldsize[0] << std::endl;

    std::cout << "Sequence: ";
    for (auto i : Sequence)
        std::cout << i << " ";
    std::cout << std::endl;

    for (unsigned int i = 0; i < startvalues.size(); i++)
    {
        std::cout << i << "\t( ";
        for (auto j : startvalues[i])
            std::cout << j << " ";
        std::cout << ")" << std::endl;
    }
    std::cout << std::endl;

    run(startvalues, field, Sequence, n_threads);
}
