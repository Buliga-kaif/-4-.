#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iterator>

/**
 * @brief Считывает список целых чисел с клавиатуры.
 *
 * Запрашивает у пользователя ввод строки, содержащей целые числа,
 * разделённые пробелами. Формирует и возвращает список этих чисел.
 *
 * @return std::list<int> Список введённых целых чисел.
 *
 * @note Если пользователь введёт нечисловые данные, они будут проигнорированы.
 * @note Если ввод пустой, возвращается пустой список.
 */
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
/**
 * @brief Выводит список целых чисел в стандартный поток вывода.
 *
 * Печатает все элементы списка через пробел. 
 *
 * @param L Список целых чисел для вывода.
 * @param label Текстовая метка, выводимая перед списком.
 *      По умолчанию пустая строка.
 */
void printList(const std::list<int>& L, const std::string& label = "") {
    std::cout << label;
    for (int x : L) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}
/**
 * @brief Главная функция программы обработки списка.
 *
 * Считывает список целых чисел с клавиатуры и модифицирует его,
 * вставляя значение -1 перед каждым элементом второй половины списка.
 *
 * @return int Код завершения программы (0 — успех, EXIT_FAILURE — ошибка).
 *
 * @details Алгоритм работы:
 * 1. Считывание списка с клавиатуры.
 * 2. Проверка на пустоту списка.
 * 3. Вывод исходного списка.
 * 4. Вычисление середины списка.
 * 5. Вставка -1 перед каждым элементом второй половины.
 * 6. Вывод изменённого списка.
 *
 * @note Если список пуст, программа завершается с ошибкой.
 */
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
