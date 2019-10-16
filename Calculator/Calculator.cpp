/*
需求
程序接收一个命令行参数 n，然后随机产生 n 道加减乘除（分别使用符号+ - * /来表示）练习题，每个数字在 0 和 100 之间，运算符在2个 到 3 个 之间。
由于阿超的孩子才上一年级，并不知道分数所以软件所出的练习题在运算过程中不得出现非整数，比如不能出现 3÷5 + 2 = 2.6 这样的算式。
练习题生成好后，将生成的n道练习题及其对应的正确答案输出到一个文件 subject.txt 中。
*/

#include "pch.h"
#include <stack>
#include <vector>
#include <iostream>
#include "stdlib.h"
#include <ctime>
#include <string>
#include "Calculator.h"
#include "Calculate.h"
#define random(a,b) (rand()%(b-a+1)+a)

using namespace std;

//初始化静态变量
int Calculator::formula_num = 0;

Calculator::Calculator() {}

string Calculator::MakeFormula() {
	string formula = "";
	srand((unsigned int)time(NULL)*formula_num); //乘以formula_num参数，防止用for生成formula时同一秒内生成的formula一样
	formula_num++;
	int count = random(2, 3);//(1,3)改为(2，3)
	int start = 0;
	int number1 = random(1, 100);
	formula += to_string(number1);
	/* 首先已经输出了一个数，要求是运算符是两到三个之间，所以while循环
	 * 应该在两到三次之间
	 * count = random(2, 3);
	 */
	while (start < count) {//<= 改为 <
		int operation = random(0, 3);
		int number2 = random(1, 100);
		formula += op[operation] + to_string(number2);
		start++;
	}
	return formula;
};
string Calculator::MakeCorrectFormula() {
	while (1) {//知道生成一个没有错误（出现小数）的式子
		string question = this->MakeFormula();
		string ans = Calculate::Solve(question);
		if (ans != "error")
			return question;
	}
}
string Calculator::Solve(string formula) {
	vector<string>* tempStack = new vector<string>();
	stack<char>* operatorStack = new stack<char>();
	int len = formula.length();
	int k = 0;
	for (int j = -1; j < len - 1; j++) {
		char formulaChar = formula[j + 1];
		if (j == len - 2 || formulaChar == '+' || formulaChar == '-' ||
			formulaChar == '*' || formulaChar == '/') {
			if (j == len - 2) {//倒数第二个字符
				tempStack->push_back(formula.substr(k));//substr(k)从位置k开始到结尾截取子串
			}else {//遇到运算符
				if (k < j) {
					tempStack->push_back(formula.substr(k, j + 1));
				}
				if (operatorStack->empty()) {//栈为空
					operatorStack->push(formulaChar);
				}else {//栈非空
					char stackChar = operatorStack->top();
					if ((stackChar == '+' || stackChar == '-')
						&& (formulaChar == '*' || formulaChar == '/')) {
						operatorStack->push(formulaChar);
					}else {
						tempStack->push_back(to_string(operatorStack->top()));
						operatorStack->pop();
						operatorStack->push(formulaChar);
					}
				}
			}
			k = j + 2;
		}
	}
	while (!operatorStack->empty()) {
		tempStack->push_back(string(1, operatorStack->top()));
		operatorStack->pop();
	}
	stack<string>* calcStack = new stack<string>();
	for (int i = 0; i < tempStack->size(); i++) {
		string peekChar = tempStack->at(i);
		if (peekChar != "+" && peekChar != "-"
			&& peekChar != "/" && peekChar != "*") {
			calcStack->push(peekChar);
		}else {
			int a1 = 0;
			int b1 = 0;
			if (!calcStack->empty()) {
				b1 = stoi(calcStack->top());
				calcStack->pop();
			}
			if (!calcStack->empty()) {
				a1 = stoi(calcStack->top());
				calcStack->pop();
			}
			if (peekChar == "+") {
				calcStack->push(to_string(a1 + b1));
			}
			else if (peekChar == "-") {
				calcStack->push(to_string(a1 - b1));
			}
			else if (peekChar == "*") {
				calcStack->push(to_string(a1 * b1));
			}
			else if (peekChar == "/") {
				calcStack->push(to_string(a1 / b1));
			}
		}
	}
	return formula + "=" + calcStack->top();
}

int main()
{
	//Calculate测试
	int num;
	cout << "num=";
	cin >> num;
	for (int i = 0; i < num; i++) {
		Calculator* calc = new Calculator();
		string question = calc->MakeCorrectFormula();
		string ans = Calculate::Solve(question);
		cout << question << "=" << ans<<endl;
	}
	system("pause");
	//return 0;
}


