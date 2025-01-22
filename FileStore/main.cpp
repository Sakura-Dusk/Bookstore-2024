#include<fstream>
#include<iostream>
#include<cstring>
#include<string>
#include "filestore.h"

// int main() {
//     std::ofstream inp;
//     inp.open("read.txt", std::ios::out);
//     if (!inp.is_open()) {
//         std::ofstream inp;
//         inp.open("read.txt", std::ios::out);
//     }
//     int n;
//     std::cin >> n;
//     inp << n;
//     std::string line;
//     while (getline(std::cin, line)) {
//         inp << line << std::endl;
//     }
//     inp.close();
// }

int main() {
    Init();
    int n; std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string op; std::cin >> op;
        if (op == "insert") {
            std::string index; int value; std::cin >> index >> value;
            data_inert(index, value);
            continue;
        }
        if (op == "delete") {
            std::string index; int value; std::cin >> index >> value;
            data_delete(index, value);
            continue;
        }
        if (op == "find") {
            std::string index; std::cin >> index;
            if (!data_find(index)) cout << "null";
            cout << endl;
        }
    }
}