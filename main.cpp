#include <iostream>
#include <fstream>


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::ofstream writer("output.txt");
    writer << "Hello World!" << std::endl;
    return 0;
}
