
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <clocale>
#include <cstdlib> 

using namespace std;
/**
 * @brief Функтор для сравнения слов.
 *
 * Сравнивает слова сначала по длине (в порядке возрастания),
 * а при равной длине — лексикографически.
 */
struct WordComparator {
 /**
     * @brief Оператор сравнения двух строк.
     * @param a Первое слово.
     * @param b Второе слово.
     * @return true, если @p a должно идти перед @p b.
     */
    bool operator()(const string& a, const string& b) const {
        if (a.length() != b.length()) {
            return a.length() < b.length();
        }
        return a < b;
    }
};
/**
 * @brief Запрашивает у пользователя путь к файлу.
 *
 * Читает путь из стандартного ввода, удаляет лишние кавычки
 * (если путь был перетащен в консоль) и проверяет существование файла.
 *
 * @param prompt Текст приглашения для ввода.
 * @return std::string Проверенный путь к существующему файлу.
 *
 * @note В случае ошибки программа завершается с кодом EXIT_FAILURE.
 */
string getFilePath(const string& prompt) {
    string path;
    cout << prompt;
    getline(cin, path);

   
    if (!path.empty() && path.front() == '"') path.erase(0, 1);
    if (!path.empty() && path.back() == '"') path.pop_back();

    ifstream test(path);
    if (test.good()) {
        return path;
    } else {
        cerr << "Ошибка: файл не найден или путь неверен. Завершение работы." << endl;
        exit(EXIT_FAILURE); 
    }
}
/**
 * @brief Считывает все слова из файла.
 *
 * Использует istream_iterator для чтения слов, разделённых
 * любыми пробельными символами (пробел, табуляция, перевод строки).
 *
 * @param path Путь к файлу.
 * @return std::vector<std::string> Вектор, содержащий все слова файла.
 */
vector<string> readAllWords(const string& path) {
    ifstream fin(path);
    return vector<string>(istream_iterator<string>(fin),
        istream_iterator<string>());
}
/**
 * @brief Главная функция программы.
 *
 * Объединяет два отсортированных текстовых файла в одну
 * отсортированную последовательность слов.
 *
 * @return int Код завершения программы (0 — успех).
 */
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Объединение отсортированных файлов ===" << endl << endl;

    string file1_path = getFilePath("Введите путь к первому файлу: ");
    string file2_path = getFilePath("Введите путь ко второму файлу: ");

    vector<string> words1 = readAllWords(file1_path);
    vector<string> words2 = readAllWords(file2_path);

    cout << "\n[Отладка] Файл 1: " << words1.size() << " слов(а)" << endl;
    cout << "[Отладка] Файл 2: " << words2.size() << " слов(а)" << endl;

    if (words1.empty() && words2.empty()) {
        cerr << "Оба файла пустые! Завершение работы." << endl;
        return EXIT_FAILURE;
    }

    WordComparator comp;
    bool sorted1 = is_sorted(words1.begin(), words1.end(), comp);
    bool sorted2 = is_sorted(words2.begin(), words2.end(), comp);

    cout << " Файл 1 отсортирован: " << (sorted1 ? "Да" : "НЕТ") << endl;
    cout << " Файл 2 отсортирован: " << (sorted2 ? "Да" : "НЕТ") << endl;

    cout << "\n=== Результат объединения ===" << endl;

   
    ifstream fin1(file1_path);
    ifstream fin2(file2_path);

    if (!fin1.is_open() || !fin2.is_open()) {
        cerr << "Ошибка открытия файлов! Завершение работы." << endl;
        return EXIT_FAILURE;
    }

    istream_iterator<string> it1_begin(fin1);
    istream_iterator<string> it1_end;
    istream_iterator<string> it2_begin(fin2);
    istream_iterator<string> it2_end;

    ostream_iterator<string> out_it(cout, " ");

    merge(it1_begin, it1_end, it2_begin, it2_end, out_it, comp);

    cout << "\n=== Готово ===" << endl;

    return 0;
}
