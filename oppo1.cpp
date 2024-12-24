#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
using namespace std;


struct income {
    string date;     // Дата
    string source; // Источник
    string value;     // Сумма
};

// Функция для проверки строки (дополнительная валидация)
bool validateLine(string date, string source, string value) {
    regex date_regex(R"(\d{4}\.\d{2}\.\d{2})"); // Формат гггг.мм.дд.
    if (!regex_match(date, date_regex)) {
        cout << "Ошибка: Некорректная дата: " << date << "\n";
        return false;
    }
    if (source.empty()) {
        cout << "Ошибка: Имя студента не указано.\n";
        return false;
    }
    if (value.empty()) {
        cerr << "Ошибка: Название темы не указано.\n";
        return false;
    }
    return true;
}

vector<income> readDataFromFile(const string& filename) {
    ifstream ist(filename);
    if (!ist) {
        cout << "Ошибка: Не удалось открыть файл: " << filename << "\n";
        return {};
    }

    vector<income> data;
    string line;

    // Регулярные выражения для разных форматов
    regex format1(R"((\d{4}\.\d{2}\.\d{2})\s+(\S+["])\s+(\d+))"); // Дата "Источник" Сумма
    regex format2(R"((\d+)\s+(\d{4}\.\d{2}\.\d{2})\s+(\S+["]))"); // Сумма Дата "Источник"
    regex format3(R"((\S+["])\s+(\d+)\s+(\d{4}\.\d{2}\.\d{2}))"); // "Источник" Сумма Дата

    while (getline(ist, line)) {
        smatch match;
        income obj;

        // Проверка строки на соответствие каждому формату
        if (regex_match(line, match, format1)) {
            obj.date = match[1];
            obj.source = match[2];
            obj.value = match[3];
        }
        else if (regex_match(line, match, format2)) {
            obj.value = match[1];
            obj.date = match[2];
            obj.source = match[3];
        }
        else if (regex_match(line, match, format3)) {
            obj.source = match[2];
            obj.value = match[1];
            obj.date = match[3];
        }
        else {
            cout << "Ошибка: Строка не соответствует ни одному формату: " << line << "\n\n";
            continue;
        }

        if (validateLine(obj.date, obj.source, obj.value)) {
            data.push_back(obj);
        }
    }
    return data;
}


int main() {
    setlocale(LC_ALL, "rus");

    string filename = "ist.txt";
    vector<income> data = readDataFromFile(filename);

    if (data.empty()) {
        cout << "Данные отсутствуют или некорректны.\n";
    }
    else {
        for (const auto& entry : data) {
            cout << "Доход:\n";
            cout << "Дата: " << entry.date << "\n";
            cout << "Источник: " << entry.source << "\n";
            cout << "Сумма: " << entry.value << "\n\n";
        }
    };

    return 0;
}