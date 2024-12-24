#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class income
{
public:
	string source;
	string value;
	string date;
	vector<income> load(const string& filename);
	void print(vector<income> data);
	bool validateLine(string date, string source, string value);
};