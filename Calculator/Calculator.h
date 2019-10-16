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
public:
	static int formula_num;
	Calculator();
	string MakeFormula();
	string MakeCorrectFormula();
	string Solve(string formula);
};
