#include <iostream>
#include <fstream>

#include <string>
using std::cin, std::cout, std::endl;
using std::string;

int main() {
    string firstName {};
    string lastName {};

    cout << "Enter your first and last name: ";
    cin >> firstName >> lastName;

    cout << "Hello " << firstName
         << ". Github gives you a Githug!" << endl;
}
