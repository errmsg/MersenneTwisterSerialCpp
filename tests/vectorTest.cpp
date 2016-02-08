// Very simple program for testing 64 bit ULL operations in vectors

#define LENGTH 10
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{


    std::vector<unsigned long long> stateVector(LENGTH);
    if(argc != 2) {
      stateVector[0] = 125ULL;
      std::cout << "Using default seed value: " << 125ULL << std::endl;
    } else {
      stateVector[0] = (unsigned long long) std::stoi(argv[1]);
    }


    for(int i = 1; i < LENGTH; i++){
      stateVector[i] = (6364136223846793005ULL * (stateVector[i-1] ^ (stateVector[i-1] >> 62)) + i);
      std::cout << stateVector[i] << std::endl;
    }




    return 0;
}
