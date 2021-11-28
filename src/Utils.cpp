#include "Utils.h"

std::vector<int> read_scores()
{
    std::vector<int> scores = {};
    int number;

    std::ifstream input_file(filename);
    if (!input_file.is_open())
    {
        std::cerr << "Could not open the file - '" << std::endl;
        return scores;
    }

    while (input_file >> number)
    {
        scores.push_back(number);
    }
    input_file.close();

    return scores;
}

int write_scores(std::vector<int> scores)
{
    std::ofstream myfile(filename);

    if (myfile.is_open())
    {

        for (int i = 0; i < scores.size(); i++)
            myfile << scores[i] << "\n";

        myfile.close();

        return 1;
    }

    return 0;
}