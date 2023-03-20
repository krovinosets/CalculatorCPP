#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <sstream>

struct option {
    int opt;
    std::string str;
};

std::string choose(struct option option);

#endif // FUNCTIONS_H
