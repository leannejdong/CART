//
// Created by leanne on 10/13/20.
//

#ifndef CART_UTILITY_H
#define CART_UTILITY_H

#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>
#include <typeinfo>

template<typename T>
int read_txt_file(std::string_view name, std::vector<std::vector<T>> &data, const char separator, const int rows, const int cols)
{
    if (typeid(float).name() != typeid(T).name()) {
        //  fprintf(stderr, "string convert to number only support float type\n");
        std::cout << " string convert to number only support float type "
                  << " \n";
        return -1;
    }

    std::ifstream fin(std::string(name), std::ios::in);
    if (!fin.is_open()) {
        // fprintf(stderr, "open file fail: %s\n", std::string(name).c_str());
        std::cout << " open file fail: " << std::string(name).c_str() << " \n";
        return -1;
    }

    std::string line, cell;
    int col_count = 0, row_count = 0;
    data.clear();

    while (std::getline(fin, line)) {
        col_count = 0;
        ++row_count;
        std::stringstream line_stream(line);
        std::vector<float> vec;

        while (std::getline(line_stream, cell, separator)) {
            ++col_count;
            vec.emplace_back(std::stof(cell));
        }

        assert(cols == col_count);
        data.emplace_back(vec);
    }

    assert(rows == row_count);

    fin.close();
    return 0;
}
#endif//CART_UTILITY_H
