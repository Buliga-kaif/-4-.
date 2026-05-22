#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

struct point {
    int x, y;
    std::string s;

    bool operator<(const point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

   
    friend std::istream& operator>>(std::istream& is, point& p);
    friend std::ostream& operator<<(std::ostream& os, const point& p);
};

std::istream& operator>>(std::istream& is, point& p) {
    is >> p.x >> p.y >> p.s;
    return is;
}

std::ostream& operator<<(std::ostream& os, const point& p) {
    os << p.x << " " << p.y << " " << p.s;
    return os;
}

int main() {

    std::string filepath;
    std::cout << "Введите путь к файлу: ";
    std::getline(std::cin, filepath);

    
    if (!filepath.empty() && filepath.back() == '\r') {
        filepath.pop_back();
    }

    if (filepath.empty()) {
        std::cerr << "Ошибка: путь к файлу не указан.\n";
        return 1;
    }

    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл \"" << filepath << "\" для чтения.\n";
        return 1;
    }

    std::vector<point> V;
    std::copy(std::istream_iterator<point>(ifs),
        std::istream_iterator<point>(),
        std::back_inserter(V));
    ifs.close(); 


    std::stable_sort(V.begin(), V.end());

    std::ofstream ofs(filepath, std::ios::trunc);
    if (!ofs.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл \"" << filepath << "\" для записи.\n";
        return 1;
    }


    std::copy(V.begin(), V.end(), std::ostream_iterator<point>(ofs, "\n"));
    ofs.close();

    std::cout << "Файл успешно отсортирован и перезаписан.\n";
    return 0;
}
