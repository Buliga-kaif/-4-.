#include <iostream>
#include <list>
#include <iterator>

int main() {

    std::list<int> L = { 10, 20, 30, 40, 50, 60 };

    std::cout << "Исходный список: ";
    for (int x : L) std::cout << x << " ";
    std::cout << "\n";


    size_t half_size = L.size() / 2;

    auto r = L.rbegin();
    std::advance(r, half_size);

    for (size_t i = 0; i < half_size; ++i) {

        auto fwd_it = L.insert(r.base(), -1);

        r = std::list<int>::reverse_iterator(fwd_it);  
       
        ++r;
    }

    std::cout << "Изменённый список: ";
    for (int x : L) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
