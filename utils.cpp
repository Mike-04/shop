//
// Created by White Fox on 4/10/2024.
//

#include "utils.h"
int readInt() {
    std::string number = readString();
    try {
        return std::stoi(number);
    }
    catch (std::exception &e) {
        std::cout << "Could not be parsed as an integer!\n";
        return -1;
    }
}

float readFloat() {
    std::string number = readString();
    try {
        return std::stof(number);
    }
    catch (std::exception &e) {
        std::cout << "Could not be parsed as a float!\n";
        return -1;
    }
}

std::string readString() {
    std::string str;
    std::getline(std::cin, str);
    return str;
}

double readDouble() {
    std::string number = readString();
    try {
        return std::stod(number);
    }
    catch (std::exception &e) {
        std::cout << "Could not be parsed as a double!\n";
        return -1;
    }
}

