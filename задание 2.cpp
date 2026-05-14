#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iterator>


std::list<int> readListFromKeyboard() {
    std::list<int> L;
    std::string line;
    
    std::cout << "Введите элементы списка (целые числа через пробел): ";
    if (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        int val;
        while (iss >> val) {
            L.push_back(val);
        }
    }
    return L;
}

void printList(const std::list<int>& L, const std::string& label = "") {
    std::cout << label;
    for (int x : L) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    std::list<int> L = readListFromKeyboard();

    if (L.empty()) {
        std::cerr << "Ошибка: список пуст. Завершение работы.\n";
        return EXIT_FAILURE;
    }

    printList(L, "Исходный список: ");

    size_t half_size = L.size() / 2;
    auto r = L.rbegin();
    std::advance(r, half_size);

    for (size_t i = 0; i < half_size; ++i) {
        auto fwd_it = L.insert(r.base(), -1);
        r = std::list<int>::reverse_iterator(fwd_it);  
        ++r;
    }

    printList(L, "Изменённый список: ");

    return 0;
}
