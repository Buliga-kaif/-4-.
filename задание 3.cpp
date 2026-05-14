#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdlib> 

int main() {
    std::vector<int> V;
    std::string line;

    std::cout << "Введите элементы вектора (целые числа через пробел): ";
    if (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        int val;
        while (iss >> val) {
            V.push_back(val);
        }
    }

    if (V.empty()) {
        std::cerr << "Ошибка: вектор пуст. Завершение работы.\n";
        return EXIT_FAILURE;
    }

    std::map<int, std::vector<int>> M;

    for (std::vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        int key = std::abs(*it) % 10;
        M[key].push_back(*it);
    }

    for (std::map<int, std::vector<int>>::const_iterator it_m = M.begin();
         it_m != M.end(); ++it_m) {

        std::cout << "Ключ " << it_m->first << ": ";

        for (std::vector<int>::const_iterator it_v = it_m->second.begin();
             it_v != it_m->second.end(); ++it_v) {
            std::cout << *it_v << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
