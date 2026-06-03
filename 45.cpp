#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
/**
 * @brief Структура, представляющая точку с координатами и строкой.
 *
 * Содержит две целочисленные координаты (x, y) и строку s.
 * Поддерживает операции сравнения, ввода и вывода.
 */
struct point {
    int x, y;
    std::string s;
     /**
     * @brief Оператор сравнения точек.
     *
     * Сравнивает точки сначала по координате x, затем по координате y.
     * Используется для сортировки.
     *
     * @param other Другая точка для сравнения.
     * @return true, если текущая точка меньше @p other.
     */
    bool operator<(const point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    /**
     * @brief Оператор ввода из потока.
     *
     * Читает координаты x, y и строку s из входного потока.
     *
     * @param is Входной поток.
     * @param p Точка для заполнения.
     * @return std::istream& Ссылка на входной поток.
     */
    friend std::istream& operator>>(std::istream& is, point& p);
      /**
     * @brief Оператор вывода в поток.
     *
     * Записывает координаты x, y и строку s в выходной поток.
     *
     * @param os Выходной поток.
     * @param p Точка для вывода.
     * @return std::ostream& Ссылка на выходной поток.
     */
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
/**
 * @brief Главная функция программы сортировки точек.
 * Читает точки из файла, сортирует их по координатам (x, y)
 * и перезаписывает файл отсортированными данными.
 * @return int Код завершения программы (0 — успех, 1 — ошибка).
 * @details Алгоритм работы:
 * 1. Запрос пути к файлу у пользователя.
 * 2. Чтение точек из файла.
 * 3. Стабильная сортировка точек.
 * 4. Запись отсортированных точек обратно в файл.
 * @note Файл должен содержать строки формата: "x y s"
 */
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
