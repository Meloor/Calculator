#pragma once
#include "pch.h"
#include <stack>
#include <vector>
#include <iostream>
#include "stdlib.h"
#include <ctime>
#include <string>  
using namespace std;

class Calculator {
private:
	string op[4] = { "+", "-", "*", "/" };
	static int formula_num;
public:
	Calculator();
	string MakeFormula();
	string MakeCorrectFormula();
	string Solve(string formula);
	void WriteToFile(fstream &fout);
	string OpenAndWriteToFile(string file_name = "subject.txt");
};
