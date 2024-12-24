#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
#include "income.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    string filename = "ist.txt";
    vector<income> data = load(filename);
    print(data);

    return 0;
}