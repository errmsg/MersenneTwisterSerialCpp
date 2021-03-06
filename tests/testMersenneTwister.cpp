
#include "../include/mt_serial.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Not enough input arguments!, usage: " << std::endl << "(program name) (initial seed) (number of outputs)" << std::endl;
        exit(1);
    }

    int initalSeed = std::stoi(argv[1]);
    std::cout << "Initial seed is: " << initalSeed << std::endl;
    int numberOfOutptus = std::stoi(argv[2]);

    //unsigned long long init[4]={0x12345ULL, 0x23456ULL, 0x34567ULL, 0x45678ULL}, length=4;
    //init_by_array64(init, length);
    init_genrand64(initalSeed);
    std::cout << numberOfOutptus << " outputs of genrand64_int64()" << std::endl;

    for (int i=0; i<numberOfOutptus; i++) {
        std::cout << genrand64_int64() << std::endl;
    }

    return 0;
}
