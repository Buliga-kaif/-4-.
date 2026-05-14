
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <clocale>
#include <cstdlib> 

using namespace std;

struct WordComparator {
    bool operator()(const string& a, const string& b) const {
        if (a.length() != b.length()) {
            return a.length() < b.length();
        }
        return a < b;
    }
};

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

vector<string> readAllWords(const string& path) {
    ifstream fin(path);
    return vector<string>(istream_iterator<string>(fin),
        istream_iterator<string>());
}

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
