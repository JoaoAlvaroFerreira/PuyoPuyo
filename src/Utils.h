#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

static std::string filename = "scores.txt";

std::vector<int> read_scores();
int write_scores(std::vector<int> scores);

#endif