#include "Income.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool validateLine(string date, string source, string value) {
    regex date_regex(R"(\d{4}\.\d{2}\.\d{2})"); // ������ ����.��.��.
    if (!regex_match(date, date_regex)) {
        cout << "������: ������������ ����: " << date << "\n";
        return false;
    }
    if (source.empty()) {
        cout << "������: ��� �������� �� �������.\n";
        return false;
    }
    if (value.empty()) {
        cerr << "������: �������� ���� �� �������.\n";
        return false;
    }
    return true;
};


vector<income> load(const string& filename) {
    ifstream ist(filename);
    if (!ist) {
        cout << "������: �� ������� ������� ����: " << filename << "\n";
        return{};
    }

    vector<income> data;
    string line;

    // ���������� ��������� ��� ������ ��������
    regex format1(R"((\d{4}\.\d{2}\.\d{2})\s+(\S+["])\s+(\d+))"); // ���� "��������" �����
    regex format2(R"((\d+)\s+(\d{4}\.\d{2}\.\d{2})\s+(\S+["]))"); // ����� ���� "��������"
    regex format3(R"((\S+["])\s+(\d+)\s+(\d{4}\.\d{2}\.\d{2}))"); // "��������" ����� ����

    while (getline(ist, line)) {
        smatch match;
        income obj;

        // �������� ������ �� ������������ ������� �������
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
            cout << "������: ������ �� ������������� �� ������ �������: " << line << "\n\n";
            continue;
        }

        if (validateLine(obj.date, obj.source, obj.value)) {
            data.push_back(obj);
        }
    }
    return data;
};

void print(vector<income> data) {
    if (data.empty()) {
        cout << "������ ����������� ��� �����������.\n";
    }
    else {
        for (const auto& entry : data) {
            cout << "�����:\n";
            cout << "����: " << entry.date << "\n";
            cout << "��������: " << entry.source << "\n";
            cout << "�����: " << entry.value << "\n\n";
        }
    }
};